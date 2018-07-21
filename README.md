# psoc5EmFileExample
PSoC5 SD Read example project using emFile component

Opens a file, reads a buffer, scans buffer for lines, prints lines
Reading buffer length into ram then line scanning is faster than 
single character reads. 

Approach here allows for line by line processing and line content 
filtering as well, see switch statement.

Reads "test.txt" from fat32 SD card.

Change BUFFERLEN, LINELEN, switch cases to match application requirements.


![Hardware](emFileConsole.cydsn/images/emFileConsoleHardware.jpg)

![TopDesign](emFileConsole.cydsn/images/emFileConsoleTopDesign.cysch.png)

![Build Results](emFileConsole.cydsn/images/emFileConsole.cydwr.png)

![Console Capture](emFileConsole.cydsn/images/emFileConsole.console.png)
