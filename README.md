# Project MFilerTool

MFilerTool
├── bin
├── build
├── common
│   ├── <TODO>: Logger.h - for developer debugging perposes
│   ├── <TODO: utils and includes>
│   └── <*h, *.cpp>
|
├── src
│   ├── TransferQueue.h
│   ├── <*h, *.cpp>
│   └── main.cpp
|
├── test
│   └── <contains test artifacts>
|
├── Makefile
├── README.md
└── sloppy_build.sh -> just compile & run application

## How to setup

    * just execute sloppy_build.sh or manually make.
    usage -> ./sloppy_build.sh

## Test Articats
    1. input.csv -  original csv provided


## Low latency improvements
    * avoid strings and use char pre-allocated buffers
    * use boost lock-free queues - I couldn't able to install boost in my env.
