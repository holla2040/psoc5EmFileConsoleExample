/*  PSoC emFile example
    Opens a file, reads a buffer, scans buffer for lines, prints lines
    Reading buffer length into ram then line scanning is faster than 
    single character reads. 
    
    Approach here allows for line by line processing and line content 
    filtering as well, see switch statement.
    
    Change BUFFERLEN, LINELEN, switch cases to match application requirements.
    
    see UM02001.pdf, UM02001 User Guide & Reference Manual for emFile Segger
    https://www.segger.com/downloads/emfile/UM02001
*/

#include <project.h>
#include <FS.h>
#include <string.h>
#include <Global.h>
#include <stdio.h>

char sdFile[20] = "test.nc";

#define BUFFERLEN 512
#define LINELEN   50


int main() {
    char buffer[BUFFERLEN];
    char line[LINELEN];
    uint8_t lineIndex = 0;
    char c;
    uint16_t bufferLen;
    FS_FILE * pFile;
    
    UART_Start();
    UART_PutString("\r\n\r\nemFileConsole\r\n");
    
    FS_Init();
    
    FS_FIND_DATA fd;
    char acFilename[20];
    if (FS_FindFirstFile(&fd, "", acFilename, sizeof(acFilename)) == 0) {
        do {
            if (!(fd.Attributes & FS_ATTR_DIRECTORY)) {
                UART_PutString(acFilename);
                UART_PutString("\n");
//              sprintf(buffer,"attr 0x%X\n",fd.Attributes);
//              UART_PutString(buffer); 
            }
        } while (FS_FindNextFile (&fd));
    }
    FS_FindClose(&fd);
    
    UART_PutString("\n\nhit any key to cat 'test.nc' ... ");
    while (UART_GetChar() == 0) {};

    pFile = FS_FOpen(sdFile, "r");
    if(pFile){
        UART_PutString("file opened: ");
        UART_PutString(sdFile);
        UART_PutString("\r\n\r\n");
        
        while ((bufferLen = FS_Read(pFile,&buffer,BUFFERLEN))) {
            for (uint16_t i = 0; i < bufferLen; i++){
                c = buffer[i];
                switch(c) {
                    case '\n':
                        line[lineIndex] = 0; // null terminate
                        UART_PutString(line);
                        UART_PutString("\n");
                        lineIndex = 0;
                        break;
                    case '\r':
                        break;
                    default:
                        line[lineIndex++] = c;
                        if (lineIndex > LINELEN) {
                            line[lineIndex] = 0; // null terminate
                            UART_PutString(line);
                            UART_PutString(" overrun\r\n");
                            lineIndex = 0;
                        }
                }
            }
        }
        if(FS_FClose(pFile)) {
            UART_PutString("\r\n\r\nFile close error\r\n");
        } else {
            UART_PutString("\r\n\r\nFile closed\r\n");
        }
    } else {
        UART_PutString("Failed to open: ");
        UART_PutString(sdFile);
        UART_PutString("\r\n");
    }
    
    for (;;){}
}