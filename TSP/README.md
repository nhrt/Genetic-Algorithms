Requirements  
System:
* Windows 10
* g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
* cmake version 3.19.1
Libraries: 
* Boost with python component Version 1.7.4 (Python Wrapper)
* Catch2 (Unit Tests)

We recommend to use msys2 to manage your environment and build tools.  
https://www.msys2.org/  
This collection contains the package manager pacman.
Use this package manager to install Boost and g++.

To build this project use following commands:
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - MinGW Makefiles" ..
make
```
To run the unit tests use following command:
```
.\bin\unit_tests.exe -r xml -d yes 
```

Project structure:  
>include  
>>TSP (Directory for the public header files. Every functionality to USE the engine from outside.)

>libs (Directory for the external libraries)

>src (Directory for source code)

>tests (Directory for the unit-tests)