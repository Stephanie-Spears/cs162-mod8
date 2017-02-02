/* A header file for the standard input tools.

   Written by: Li Liang
   Date: 09/20/2009

   Sources: None
*/

#ifndef INPUT_TOOLS_H
#define INPUT_TOOLS_H

//function prototypes
int readInt(const char prompt[]);
double readDouble(const char prompt[]);
char readChar(const char prompt[]);
void readString (const char prompt[], char inputStr[], int maxChar);

#endif