/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"
#include "frame/frame.h"
#include "page/page.h"
#include "physical_address/physical_address.h"
#include <map>
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;


void Simulation::run() {
  size_t numProcess;                                                               //Variable holding number of active Processes
  ifstream inputFile;                                                           //InputFile
  string input;
  const int TOTAL_FRAMES = 512;
  vector<int> ProcessList;                                                   //Maps a vector of every virtual address by its ProcessID Key
  vector<VirtualAddress> Addresses;
  inputFile.open(flags.filename);
  if (inputFile >> input) {
    numProcess = stoi(input);                                                   //Total Number of Active Processes
  } else { cout << "Error reading file, file is empty. " << endl; }
  //cout << numProcess << endl;
  if (numProcess) {                                                             //Check if numProcess is null
    for(size_t i = 0; i < numProcess; i++) {
      int processID;
      string fileName;
      string fileContent;
      if (inputFile >> input) {
        processID = stoi(input);
        ProcessList.push_back(processID);                                       //Appends to the full processList
      }
      if (inputFile >> input) {
        fileName = input;
      }
      ifstream newInputFile(fileName);
      Processes[processID] = Process::read_from_input(newInputFile);
      newInputFile.close();
      //cout << "Process " << processID << " is " << Processes[processID]->size() << "." << endl;
    }
  }
  while(!inputFile.eof()) {
    size_t ID;
    if (inputFile >> input) {                                                   //ProcessID
      ID = stoi(input);
      //cout << "Check";
      if (inputFile >> input) {
        Addresses.push_back(VirtualAddress::from_string(ID,input));                      //Appends it the  map
      }                                          //Gets the Process ID it belongs to
    }
  }
  inputFile.close();

  setProcessMap(Processes);
  sort(ProcessList.begin(), ProcessList.end());                                 //Sorts the list of processes in ascending order.
  size_t time = 0;
  string filename2 = "Output.txt";                                              //Creates an output file for storage and print
  removeFile(filename2);                                    //Proceeds through each process
  //minFrame = 0;
  frameCount = 0 - flags.max_frames;
  maxFrame = flags.max_frames;
  for(size_t j = 0; j < Addresses.size(); j++) {            //Increment currentFrameLimit each new process                    //Proceeds through each memory access
    if(Addresses[j].process_id != Addresses[j - 1].process_id) {
      frameCount += flags.max_frames;
      //cout << flags.max_frames << endl;
      if (maxFrame + flags.max_frames < TOTAL_FRAMES) {
        maxFrame += flags.max_frames;
      } else {
        maxFrame += TOTAL_FRAMES % maxFrame;
      }
    }
    perform_memory_access(Addresses.at(j), time);
    time = time + 1;
  }
  if(flags.verbose) {
    string line;
    ifstream inputFile("Output.txt");
    while(getline(inputFile, line)) {
      cout << line << endl;
    }
    inputFile.close();
  }
  size_t memAccess = 0;
  size_t pageFaults = 0;
  size_t framesRemaining = TOTAL_FRAMES;
  cout << "\nDONE!" << endl << endl;
  for(size_t i = 0; i < numProcess; i++) {
    Process* p = Processes.at(ProcessList[i]);
    cout << "Process " << ProcessList[i];
    cout << "  ACCESSES: " << p->memory_accesses;
    cout << "    FAULTS: " << p->page_faults;
    cout << "    FAULT RATE " << p->get_fault_percent();
    cout << "    RSS: " << p->get_rss() << endl;
    memAccess += p->memory_accesses;
    pageFaults += p->page_faults;
    framesRemaining -= p->get_rss();
  }

  cout << endl;
  cout << "Total memory accesses                   " << memAccess << endl;
  cout << "Total page faults:                      " << pageFaults << endl;
  cout << "Free frames remaining                   " << framesRemaining << endl;
  if(flags.output) {
    fstream outputFile;
    outputFile.open("Output.txt", fstream::app);
    outputFile << "\nDONE!" << endl << endl;
    for(size_t i = 0; i < numProcess; i++) {
      Process* p = Processes.at(ProcessList[i]);
      outputFile << "Process " << ProcessList[i];
      outputFile << "  ACCESSES: " << p->memory_accesses;
      outputFile << "    FAULTS: " << p->page_faults;
      outputFile << "    FAULT RATE: " << p->get_fault_percent();
      outputFile << "        RSS: " << p->get_rss() << endl;
      memAccess += p->memory_accesses;
      pageFaults += p->page_faults;
      framesRemaining -= maxFrame;
    }

    outputFile << endl;
    outputFile << "Total memory accesses                   " << memAccess << endl;
    outputFile << "Total page faults:                      " << pageFaults << endl;
    outputFile << "Free frames remaining                   " << framesRemaining << endl;
  } else {
    removeFile("Output.txt");
  }
}

void Simulation::removeFile(string filename) {
  ofstream outputFile(filename);
  if(outputFile) {                                                              //Deletes the file for a clean slate.
    if (remove(filename.c_str()) != 0) {
      return;
    }
  }
}

char Simulation::perform_memory_access(const VirtualAddress& address, size_t time) {
  // TODO: implement me
  //bool page_fault = false;

  fstream outputFile;                                                           //Sets up an output file
  outputFile.open("Output.txt", fstream::app);
  outputFile << address << endl;
  Process* p = getProcess(address.process_id);
  p->memory_accesses++;

  //Verify if Page number and offset are within the bounds
  if (!p->is_valid_page(address.page)) {                                         //If the page does not exist in the within the process image, Segmentation fault
    outputFile << "SEGMENTATION FAULT" << endl;
    outputFile << "PAGE DOES NOT EXIST" << endl;
    exit(1);
  }
  if (!p->pages.at(address.page)->is_valid_offset(address.offset)) {              //If the offset is not within the page, segmentation fault
    if (!p->is_valid_page(address.page)) {
      outputFile << "SEGMENTATION FAULT" << endl;
      outputFile << "OFFSET OUTSIDE OF PROCESS IMAGE" << endl;
      cout << "SEGMENTATION FAULT" << endl;
      cout << "OFFSET OUTSIDE OF PROCESS IMAGE" << endl;
      exit(1);
    }
  }

  if(frames.size() == frameCount || frames[p->page_table.rows.at(address.page).frame].page_number != address.page) {                      //Currently not present in memory, handle page fault
    //if(address.page == 19) {cout << address.page << " is " << p->page_table.rows.at(address.page).frame << endl;}
    outputFile << "    -> PAGE FAULT" << endl;
    p->page_faults++;
    handle_page_fault(p, address.page, time);
  } else {
    outputFile << "    -> IN MEMORY" << endl;
    p->page_table.rows.at(address.page).last_accessed_at = time;
  }
  outputFile << "    -> physical address " << PhysicalAddress(p->page_table.rows.at(address.page).frame, address.offset) << endl;
  outputFile << "    -> RSS: " << getProcess(address.process_id)->get_rss() << endl << endl;
  //if(page_fault) { return 0; }
  outputFile.close();
  return p->pages.at(address.page)->get_byte_at_offset(address.offset);

  //return 0;
}

void Simulation::handle_page_fault(Process* process, size_t page, size_t time) {
  // TODO: implement me
  Frame f;
  if ((int)process->get_rss() < flags.max_frames && frames.size() < maxFrame) {
    f.set_page(process,page);
    frames.push_back(f);
    process->page_table.rows.at(page).present = true;
    process->page_table.rows.at(page).frame = frames.size() - 1;
    cout << page << " " << frames.size()-1 << endl;
    //cout << frames.size() << endl;
    process->page_table.rows.at(page).loaded_at = time;
    //cout << time << endl;
    //frameCount++;
  } else {                               //Page is no longer present in memory

    if(flags.strategy == ReplacementStrategy::FIFO) {
      f.set_page(process,page);                     //Replacement First in first out
      size_t index = process->page_table.get_oldest_page();
      size_t frameNum = process->page_table.rows.at(index).frame + frameCount;
      process->page_table.rows.at(index).loaded_at = time;
      cout << page << " " << frameNum << " " << frames.size() << endl;
      frames[frameNum] = f;
    } else {                                                                    //Replacement Strategy LRU
      size_t index = process->page_table.get_least_recently_used_page();
      size_t frameNum = process->page_table.rows.at(index).frame + frameCount;
      process->page_table.rows.at(index).loaded_at = time;
      frames[frameNum] = f;
    }
  }
}
