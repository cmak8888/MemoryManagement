/**
 * This file contains the definition of the Simulation class.
 *
 * You're free to modify this class however you see fit. Add new methods to help
 * keep your code modular.
 */

#pragma once
#include "process/process.h"
#include "flag_parser/flag_parser.h"
#include "virtual_address/virtual_address.h"
#include "frame/frame.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <map>

/**
 * Class responsible for running the memory simulation.
 */
class Simulation {
// PUBLIC CONSTANTS
public:

  /**
   * The maximum number of frames in the simulated system (512).
   */
  static const size_t NUM_FRAMES = 1 << 9;

// PUBLIC API METHODS
public:

  /**
   * Runs the simulation.
   */
  void run();

  /**
   *  Deletes the File
   */
  void removeFile(std::string filename);

  /**
    * Setter for Processes map
    */
  void setProcessMap(std::map<int,Process*> &Processes) {
    this->Processes = Processes;
  }


  /**
    * Get process map
    */
  std::map <int, Process*> gettheProcess() {
    return this->Processes;
  }

  /**
    * Getter for Processes map
    */
  Process* getProcess(int key) {
    return this->Processes.at(key);
  }

  /**
    * Setter for flags
    */
  void setflags(FlagOptions& flags) {
    this->flags = flags;
  }
  
  int getSumFrames() {
    int sum = 0;
    for(std::map<int,Process*>::iterator it = this->Processes.begin(); it != this->Processes.end(); ++it) {
      sum += it->second->get_rss();
    }
    return sum;
  }

//PUBLIC VARIABLES
public:
  std::map<int,Process*> Processes;
  FlagOptions flags;
  std::vector<Frame> frames;
  size_t frameCount;                    //Frame parameters change each new process
  size_t maxFrame;
// PRIVATE METHODS
private:

  /**
   * Performs a memory access for the given virtual address, translating it to
   * a physical address and loading the page into memory if needed. Returns the
   * byte at the given address.
   */
  char perform_memory_access(const VirtualAddress& address, size_t time);

  /**
   * Handles a page fault, attempting to load the given page for the given
   * process into memory.
   */
  void handle_page_fault(Process* process, size_t page, size_t time);

// INSTANCE VARIABLES
private:

};
