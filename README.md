# FlightSimulator

# Description
This project is in C++, and simulates flying a plain from FLIGHTGEAR FLIGHT SIMULATOR.
In the project we use communication between servers to communicate with the plain
and update/ change flight status and make it take off and fly.
 
 **pin points of projet**
 - lexer :read fly.txt and turn into vector of strings
 - parser: iterate over vector of strings and turn into commands
 - run each command and watch the plain take off and fly!

# to run our code
- download Flight gear simulator
-put in flight simulator advanced settings: 
`--telnet=socket,in,10,10.0.2,5402,tcp `
`--generic=socket,out,10,127.0.1,5400,tcp,generic_small`
- run our code on linux OS
- press fly on flght simulator

# Links
- for github https://github.com/shmuelSuna/flightSim
- to download Flight gear simulator https://www.flightgear.org/download/



