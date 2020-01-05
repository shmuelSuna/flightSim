# FlightSimulator

# Description
This project is in C++, and simulates flying a plane from FLIGHTGEAR FLIGHT SIMULATOR.
In the project we use communication between servers to communicate with the plane
and update/ change flight status and make it take off and fly.
The program creates a server and the program of the simulator connects to this server as a client,thus the 
simulator sends us values from the flight. We also connect to the simulator as a client and
thus we send to plane commands.
There is a format of a text that we analyze and by that create commands to the simulator.
You can change the values of the "fly.txt" file, which it has the necessary format that our 
program knows to analye.

# Usage
You can create your own fly.txt (link to the file in the links) file and create an automat pilot to the flight simulator,
all you need to do is to set your own values of the and code lines in the text file. 
First you need to set the details of the communication commands, the ip and port.
Then you can see the variables that we handle with.
After declaring the variables we are ready to write the commands. Pay attention that 
the variables that we are allowd to change are those with this arrow: <-, and variables 
that we can take thier values are those with this -> arrow.
In order to end the set of commands you need to print "done".


 
 **pin points of projet**
 - lexer :read fly.txt and turn into vector of strings
 - parser: iterate over vector of strings and turn into commands
 - run each command and watch the plane take off and fly!

# to run our code
- download Flight gear simulator
-put in flight simulator advanced settings: 
`--telnet=socket,in,10,127.0.0.1,5402,tcp `
`--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small`
- run our code on linux OS
- press fly on flght simulator

# Links
- for github https://github.com/shmuelSuna/flightSim
- for fly.txt https://github.com/shmuelSuna/flightSim/blob/master/fly.txt
- to download Flight gear simulator https://www.flightgear.org/download/



