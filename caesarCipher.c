#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Takes in string containing name of input file and opens it,
* returning the file pointer, otherwise printing and error and 
* exiting. Output file is always named "output.txt".
*/
FILE *openFile(char *textFile)
{
    FILE *file;
    if (textFile != NULL)
    {
        file = fopen(textFile, "r");
    }
    else
    {
        file = fopen("output.txt", "w+");
    }
    if (file == NULL)
    {
        printf("Error opening file: %s\n", textFile);
        exit(1);
    }

    return file;
}

/*
* Shifts an individual char by shiftNum chars to the right.
* Only shifts A-Z and a-z, wrapping around if shift results
* in going off the end. Returns the shifted char, or the
* original char if not alphabet char.
*/
char shiftChar(char currChar, int shiftNum)
{
    char shiftChar;
    if (0x41 <= currChar && currChar <= 0x5a)
    {
        shiftChar = currChar + shiftNum;
        if (shiftChar < 0x40)
        {
            shiftChar = 0x5a - (0x40 - shiftChar);
        }
        else if (shiftChar > 0x5a)
        {
            shiftChar = 0x40 + (shiftChar - 0x5a);
        }
    }
    else if (0x61 <= currChar && currChar <= 0x7a)
    {
        shiftChar = currChar + shiftNum;
        if (shiftChar < 0x61)
        {
            shiftChar = 0x7a - (0x61 - shiftChar);
        }
        else if (shiftChar > 0x7a)
        {
            shiftChar = 0x61 + (shiftChar - 0x7a);
        }
    }
    else
    {
        return currChar;
    }

    return shiftChar;
}

/*
* Iterates through an input string and calls shiftChar() on each
* char. Assigns shifted char to respective index in shiftedString.
*/
void shiftString(char *inputString, char *shiftedString, int shiftNum)
{
    int len = strlen(inputString);
    for (int i = 0; i < len; i++)
    {
        char currChar = inputString[i];
        shiftedString[i] = shiftChar(currChar, shiftNum);
    }
    shiftedString[len] = '\0';
}

/*
* Gets 63 chars at a time from inputFile and calls shiftString each loop
* iteration, then writes shiftedString to outputFile until EOF is reached.
*/
void shiftFile(FILE *inputFile, FILE *outputFile, int shiftNum)
{
    char inputString[64];
    char shiftedString[64];

    while (fgets(inputString, 63, inputFile) != NULL)
    {
        shiftString(inputString, shiftedString, shiftNum);
        fprintf(outputFile, "%s", shiftedString);
    }
}

/*
* Gets command line arguments shiftNum and name of inputFile.
* Opens both inputFile and outputFile, calls shiftFile(), then
* closes both files and returns.
*/
int main(int argc, char *argv[])
{
    // Assume correct command line argument input
    // ./caesarCipher -s <shiftNum> <textFile>

    int shiftNum = atoi(argv[2]);
    FILE *inputFile = openFile(argv[3]);
    FILE *outputFile = openFile(NULL);

    shiftFile(inputFile, outputFile, shiftNum);

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
