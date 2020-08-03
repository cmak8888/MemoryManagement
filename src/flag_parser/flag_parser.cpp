/**
 * This file contains implementations for methods in the flag_parser.h file.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "flag_parser/flag_parser.h"
#include <iostream>
#include <cstring>

using namespace std;


void print_usage() {
  cout <<
      "Usage: mem-sim [options] filename\n"
      "\n"
      "Options:\n"
      "  -v, --verbose\n"
      "      Output information about every memory access.\n"
      "\n"
      "  -s, --strategy (FIFO | LRU)\n"
      "      The replacement strategy to use. One of FIFO or LRU.\n"
      "      If an invalid strategy has been called the program\n"
      "      will produce an error and report it and exit\n"
      "\n"
      "  -f, --max-frames <positive integer>\n"
      "      The maximum number of frames a process may be allocated.\n"
      "\n"
      "  -h --help\n"
      "      Display a help message about these flags and exit\n"
      "\n"
      "  -o --output\n"
      "      Prints all information into an output file called Output.txt\n"
      "\n"
      "  -b --ba\n"
      "      Performs the Belady's Anomaly Algorithm.\n"
      "\n"
      "The code has been modified to handle multiple single character flags\n"
      "and will display information accordingly.\n"
      "\n"
      "If strategy and frames have been called, the arguments must be\n"
      "displayed in sequence with the strategy in front and frame\n"
      "integer following else, the program will produce an error.\n"
      "\n"
      "Invalid flags will display an error, but will be skipped over\n"
      "and will not ruin the functionality of the program.\n"
      "\n";
}


/*
  Notes"
  argc = ARGument Count: An integer with the number of command-line arguments
  argv = ARGument Vector: An array of character pointers listing all the arguments
*/

bool parse_flags(int argc, char** argv, FlagOptions& flags) {
  // TODO: implement me
  bool strat = false;
  for(int i = 1; i < argc; i++) {
    flags.filename = argv[argc - 1];
    //cout << "Check" << endl;
    if(argc > 2) {        //If there are more than 2 arguments, then there are flags
      //cout << (string)argv[i] << endl;
      if ((string)argv[i] == "--verbose") {
        flags.verbose = true;
      }
      //cout << "Check" << endl;
      if ((string)argv[i] == "--strategy") {
        //cout << "Check" << endl;
        if (argv[i + 1]) {
          if ((string)argv[i + 1] == "LRU") {
            flags.strategy = ReplacementStrategy::LRU;
          } else if((string)argv[i + 1] == "FIFO"){
            flags.strategy = ReplacementStrategy::FIFO;
          } else {
            return false;
          }
        } else {
          return false;
        }
        i++;
      }
      if ((string)argv[i] == "--max-frames") {
        char *p;
        strtol(((string)argv[i + 1]).c_str(), &p, 10);            //Takes a c string and sets the pointer to the first non-integer value. The 10 defines the base.
        if (*p != 0) {
          cout << "Value is not an integer" << endl;
          return false;
        }
        //cout << "Max_frames" << endl;
        flags.max_frames = stoi((string)argv[i + 1]);
        //cout << flags.max_frames << endl;
        if (flags.max_frames <= 0) {
          cout << "Maximum amount of frames cannot be 0 nor a negative integer." << endl;
          cout << "Now exitting the program." << endl;
          return false;
        }
        i++;
      }
      if ((string)argv[i] == "--help") {
          print_usage();
          exit(0);
      }
      if ((string)argv[i] == "--output") {
        flags.output = true;
      }
      if ((string)argv[i] == "--ba") {
        flags.ba = true;
      }
      char flagList[((string)argv[i]).length() + 1];        //Creates a c-string called flagList and allocates memory for it.
      strcpy(flagList, ((string)argv[i]).c_str());        //Converts the argument of flags into a c-string
      if(flagList[0] == '-') {
        for(size_t i = 1; i < strlen(flagList); i++) {
          switch(flagList[i]) {
            case('v'):
              flags.verbose = true;
              break;
            case('s'):
              if(argv[i + 1]) {
                if ((string)argv[i + 1] == "LRU") {
                  flags.strategy = ReplacementStrategy::LRU;
                } else if((string)argv[i + 1] == "FIFO"){
                  flags.strategy = ReplacementStrategy::FIFO;
                } else {return false;}
              } else {
                return false;
              }
                strat = true;
              break;
            case('f'):
              if(strat) {
                flags.max_frames = stoi(argv[i + 3]);
              } else {
                flags.max_frames = stoi(argv[i + 2]);
              }
              if (flags.max_frames <= 0) {
                cout << "Maximum amount of frames cannot be 0 nor a negative integer." << endl;
                cout << "Now exitting the program." << endl;
                return false;
              }
              break;
            case('h'):
              print_usage();
              exit(0);
              break;
            case('o'):
              flags.output = true;
              break;
            case('b'):
              flags.ba = true;
              break;
            }
          }
        }
      }
    }
    return true;
}
