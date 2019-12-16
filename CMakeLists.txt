cmake_minimum_required(VERSION 3.15)
project(flightSim)

set(CMAKE_CXX_STANDARD 14)

add_executable(flightSim main.cpp Command.h OpenDataServer.cpp OpenDataServer.h ConnectCommand.cpp ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h Parser.cpp Parser.h PrintCommand.cpp PrintCommand.h SleepCommand.cpp SleepCommand.h)