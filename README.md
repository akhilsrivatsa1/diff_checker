# Diff Checker

## Description

This project is designed to compare files between two directories and produce a summary of common files and files that exist exclusively in each directory. 

## Requirements

- **Language**: C++

## OS used: 
MacOs(version 12.4)


## External Libraries

1. **OpenSSL**: Used to compute MD5 hash of a file.
2. **Google Test**: Used for writing tests.


Commands to Execute

To complie: 
make

For Running: 
make run ARGS="path1 path2"

For testing: 
make test 

For Cleaning: 
make clean

Most of the main logic is written in file_util.cpp
The tests are written in the test subfolder and test_util.cpp


