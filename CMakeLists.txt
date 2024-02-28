cmake_minimum_required(VERSION 3.23)
project(sequentialDM)

set(CMAKE_CXX_STANDARD 14)

add_executable(sequentialDM main.cpp Model/seqJob.cpp Model/seqJob.h Model/node.cpp Model/node.h FileService/readFromFile.h FileService/readFromFile.cpp ToolKit/global.h ToolKit/global.cpp Mining/doMining.cpp Mining/doMining.h Model/connect.cpp Model/connect.h Model/DataHead.cpp Model/DataHead.h Model/CompleteNode.cpp Model/CompleteNode.h main.h MyQueue/MyQueue.cpp MyQueue/MyQueue.h Model/CompleteHead.cpp Model/CompleteHead.h Model/Complete.cpp Model/Complete.h FileService/saveToFile.cpp FileService/saveToFile.h)
