/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <cstdlib>
#include <iostream>
#include "simulation/simulation.h"
#include "flag_parser/flag_parser.h"

using namespace std;


/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {
  // TODO: implement me
  Simulation sim;
  FlagOptions flags;                                        //Holds flags
  if (!parse_flags(argc, argv, flags)) {                    //Parses the flags
    cout << "Error in processing flags.\n Program will now exit.\n";
    exit(1);
  }
  if (flags.ba) {
    flags.filename = "BAnomaly.txt";
    flags.max_frames = 3;
    flags.strategy = ReplacementStrategy:FIFO;
  }
  sim.setflags(flags);
  sim.run();
  if (flags.ba) {
    flags.filename = "BAnomaly.txt";
    flags.max_frames = 4;
    flags.strategy = ReplacementStrategy:FIFO;
    sim.setflags(flags);
    sim.run();
  }
  return EXIT_SUCCESS;
}
