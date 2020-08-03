# Project 2

Calvin Mak

Files:
  inputs:
    BAnomaly              Belady Anomaly example input file
    process_1
    process_2             Sample input files provided
    process_3
    sim_1
  src:                    Source folder
    main.cpp              Main file for running the program
    flag_parser:          Parses Flags
      flag_parser_tests.cpp flag tests
      flag_parser.cpp     flag Program
      flag_parser.h       flag header
    frame:                frame that relates to the page table and holds a reference to a page in memory
      frame_tests.cpp     frame tests
      frame.cpp           frame program
      frame.h             frame header
    page:                 A row of the process image
      page_tests.cpp      page tests
      page.cpp            page program
      page.h              page header
    page_table:           page table is essentially an index table relating page number to frame number in memory for a physical address.
      page_table_tests.cpp page table tests
      page_table.cpp       page table Program
      page_table.h         page_table header
    physical_address:     A physical address formed from the VirtualAddress and the page_table
      physical_address_tests.cpp  physical address tests
      physical_address.cpp        physical address program
      physical_address.h          physical address header
    process:              holds the process image and all the data related to the process
      process_tests.cpp           process tests
      process.cpp                 process Program
      process.h                   process header
    simulation:           Runs the simulation itself and all the replacement strategies.
      simulation.cpp              Simulation program
      simulation.h                Simulation header
    virtual_address:
      virtual_address_tests.cpp   Virtual Address tests
      virtual_address.cpp         Virtual Address Program
      virtual_address.h           Virtual Address Header
  makefile            Compiles the program and for running the program and flags.
  README.md           README File

I don't really have any big, interesting features in my program other than an output file called Output.txt depending on the flag.
I spent about 78 hours on this project.

Belady's Anomaly.
  Belady's anomally occurs when increasing the number of frames in memory increases the number of page faults.

  The command line flag to demonstrate the anomaly is -b or --ba.

  Page frequency is ignored, so regardless of how many times a page has been accessed, if more memory needs to be loaded, the page is replaced, and replaced back in later on.


Other Comments:
  I had lots of issues regarding page faults in the program. I was unable to figure out why I couldn't get the page faults to fit in time. I got the rest of the program to work though. There were just a lot of issues that didn't make sense that I couldn't figure out.
