/* This Project should be able to read in a text file of songs and artists, sort the text alphabetically and
 * produce a randomised playlist of roughly 1 hour */
#include "ReadingAndSorting.h"

int main(int argc, char *argv[])
{
    int numLines = 0; // Records the number of rows the inputArray will have read into it
    FILE *fp;
    int numArtists; // Records the number of artists in the list
    char inputArray[MAX_LINES][MAX_CHAR]; // Array to store the Artists and Song names
    char artistArray[MAX_LINES / 2][MAX_CHAR]; // Array to hold and sort The Artist names

    if(argc < 2)
    {
        // If there is no file specified as an argument, check the current directory for the input file
        fp = fopen("artists+songs.txt", "r");
        if(fp == NULL)
        {
            // If there is no such file in the current directory, ask the user to manually input the artists and songs
            printf("File not found\n");
            printf("Please manually input the artists and songs in the required format\nType -1 when you have reached the end:\n");
            while((strcmp(fgets(inputArray[numLines], MAX_CHAR, stdin), "-1\n") != 0) && numLines < MAX_LINES)
            {
                // While the user has not indicated that they are finished and we have not reached the end of the array
                numLines++;
            }
        }
        else
        {
            /* If the file is in the current directory, then copy the contents of the file into the inputArray
             * and record the number of lines read in */
            while ((fgets(inputArray[numLines], sizeof(inputArray[numLines]), fp) != NULL) && numLines < MAX_LINES)
            {
                numLines++;
            }
            fclose(fp);
        }
    }
    else
    {
        // Read the songs + Artists into the array using the file name specified by the user
        numLines = readInput(inputArray, argv[1]);
    }

    // Use user-defined functions to sort the input and print out the result for the user
    sortSongs(inputArray, numLines);
    numArtists = sortArtists(inputArray, artistArray, numLines);
    printSortedList(inputArray, artistArray, numLines, numArtists);

    // Create and print out the playlist using the function "createPlaylist"
    createPlaylist(inputArray, artistArray, numLines, numArtists);

    return 0;
}
