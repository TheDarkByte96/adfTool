# adfTool

adfTool is a tool which is capable of converting encrypted sound files (.ADF) seen in GTA Vice City (radio stations) to standard .MP3 files. It is also capable of encrypting .MP3 files into .ADF formatted files.

Compiling and installing on Linux: gcc -o adfTool adfTool.c && sudo cp adfTool /bin
Sudo requires administrative priviledges!

For Windows you could use mingw the same way to compile the C code. Later on, copy the adfTool.exe to C:\Windows
Example: gcc -o adfTool.exe adfTool.c && copy /b adfTool.exe %windir%/system32

I haven't tested this code in Mac OS X but there are no reasons why it shouldn't work.

Usage: 

       adfTool -e inputFile.mp3 outputFile.adf
       adfTool -d inputFile.adf outputFile.mp3
       

-e stands for encryption - mp3 to adf; -d stands for decryption - adf to mp3

Have fun :)
