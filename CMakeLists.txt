cmake_minimum_required(VERSION 3.15)
project(flightSim)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(flightSim main.cpp Command.h OpenDataServer.cpp OpenDataServer.h ConnectCommand.cpp ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h Parser.cpp Parser.h PrintCommand.cpp PrintCommand.h SleepCommand.cpp SleepCommand.h CreateSymbolTable.cpp CreateSymbolTable.h SimulatorObject.cpp SimulatorObject.h SymbolTable.cpp SymbolTable.h SetVarCommand.cpp SetVarCommand.h Expression.cpp Expression.h ex1.cpp ex1.h CondtionParserCommand.cpp CondtionParserCommand.h WhileCommand.cpp WhileCommand.h)