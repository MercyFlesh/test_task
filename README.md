# Test task for an intern for position «C++ developer»

***The task consists of two programs that need to be implemented. The interaction of programs must be implemented using sockets.***


### Program №1
should consist of two streams and one common buffer. The shared buffer type must be file or shared memory.

Stream 1 accepts a string that the user enters. There should be a check that the string consists only of numbers and does not exceed 64 characters. After checking, the string should be sorted in descending order and all even elements should be replaced with the Latin letters "KB". After this line is placed in the general buffer and the stream must wait for further user input.

Stream 2. Must process data that is placed in a shared buffer. After receiving the data, the shared buffer is cleared. The stream must display the received data on the screen, calculate the total sum of all elements that have numerical values. Transfer the received amount to Program №2. After that, the thread waits for the next data.

***Note on Program №1:*** *Stream interaction must be synchronized, stream №2 must not constantly poll the shared buffer. The mechanism does not have to be a global variable.*


### Program №2
is awaiting for data from Program №1. When receiving data, an analysis is made of what characters the transmitted value consists. If it is longer than 2 characters and if it is a multiple of 32, a received data message is displayed, otherwise an error message is displayed. Then the program continues to wait for data.
