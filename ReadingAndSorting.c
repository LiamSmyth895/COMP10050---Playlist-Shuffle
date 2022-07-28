/* Liam Smyth's C source code file for functions that sort and print the artist and song names
 * and functions that create the randomised playlist */

#include "ReadingAndSorting.h"

int readInput(char inputArray[][MAX_CHAR], char *filename)
{
    /* This function reads input from the file and stores it in a 2D array */
    int numLines = 0;
    FILE *fp;

    fp = fopen(filename, "r+");    /*  Open file for reading.  */

    /*  This will take each row in the file and store it in inputResults  */
    if(fp == NULL)// Check does the file exist
    {
        perror("Error opening artists+songs file");
        exit(1); // use this as a file not found code
    }
    else {
        while (fgets(inputArray[numLines], sizeof(inputArray[numLines]), fp) != NULL)
            numLines++;

        fclose(fp);
    }

    return numLines; // Return the amount of lines that were read into the array
}

void sortSongs(char inputArray[][MAX_CHAR], int numLines)
{
    /* This function sorts all of the songs in the array, but not the artists */
    int i, j, k;
    char swap[MAX_CHAR]; // character array used for swapping song names

    for(i = 2; strcmp(inputArray[i], seperator) != 0; i++)
    {
        /* This loop will sort the first block of songs using insertionSort for each the first artist
         * and keep them stored in the original inputArray */
        j = i;
        while (j > 1 && strcmp(inputArray[j] , inputArray[j - 1]) < 0)
        {
            strcpy(swap, inputArray[j]);
            strcpy(inputArray[j], inputArray[j - 1]);
            strcpy(inputArray[j - 1], swap);
            j--;
        }
    }

    k = i; // The variable that indexes the total array will now be set to the end of the first block of songs
    while(k < numLines)
    {
        // This loop will go through the rest of the array and sort all of the other artists' respective songs
        if(strcmp(inputArray[k - 2], seperator) == 0)
        {
            /* If we have reached the first song in a block of songs for an artist, then
             * start sorting the songs for that artist using Insertion Sort */
            for(i = k + 1; (strcmp(inputArray[i], seperator) != 0) && (i < numLines); i++)
            {
                j = i;
                while (j > k && strcmp(inputArray[j] , inputArray[j - 1]) < 0)
                {
                    strcpy(swap, inputArray[j]);
                    strcpy(inputArray[j], inputArray[j - 1]);
                    strcpy(inputArray[j - 1], swap);
                    j--;
                }
            }
            k = i; // Once this block of songs is sorted, set the index to the end of the block
        }
        k++; // If we have not reached the first song for an artist, increment the index by 1
    }
}

int sortArtists(char inputArray[][MAX_CHAR], char artistArray[][MAX_CHAR], int numLines)
{
    /* This function stores all the artist names in an array and sorts them alphabetically */
    int i = 0, j;
    int numArtists = 0; // variable numArtists will record the length of the artistArray
    char swap[MAX_CHAR]; // character array used for swapping artist names

    // Read the first artists' name into the array "artistArray"
    strcpy(artistArray[numArtists], inputArray[i]);
    numArtists++;

    for(i = 1; i < numLines; i++)
    {
        /* Loop through the inputArray and if we find an artists name, store it in the artistArray.
         * Artist names are always preceded by an empty line in this input file format */
        if(strcmp(inputArray[i - 1], seperator) == 0)
        {
            strcpy(artistArray[numArtists], inputArray[i]);
            numArtists++;
        }
    }

    /* Sort the artistArray using insertion sort */
    for(i = 1; i < numArtists; i++)
    {
        /* This loop will sort all of the artist names which are now stored in the artistArray */
        j = i;
        while (j > 0 && strcmp(artistArray[j] , artistArray[j - 1]) < 0)
        {
            strcpy(swap, artistArray[j]);
            strcpy(artistArray[j], artistArray[j - 1]);
            strcpy(artistArray[j - 1], swap);
            j--;
        }
    }

    return numArtists;
}

void printSortedList(char inputArray[][MAX_CHAR], char artistArray[][MAX_CHAR], int numLines, int numArtists)
{
    /* This function prints out the sorted output in the required manner */
    int i, j;
    bool found;

    for(i = 0; i < numArtists; i++)
    {
        /* This loop will go through the entire artistArray and print out each ordered artist name */
        j = 0;
        found = false; // The boolean "found" will be used to break the inner loop when a block of songs is printed
        while(!found)
        {
            /* This loop will go though the inputArray and find the corresponding block of songs for the
             * current artist */
            if(strcmp(inputArray[j], artistArray[i]) == 0)
            {
                /* Once the current artist is found, print out the artists' name and then print out each
                 * sorted song name in the required format */
                printf("%s", artistArray[i]);
                j++;
                while((strcmp(inputArray[j], seperator) != 0) && (j < numLines))
                {
                    /* The loop will end when it reaches the end of the current block, either by reaching the string
                     * "\n\0" or by reaching the end of the inputArray */
                    printf("  o %s", inputArray[j]);
                    j++;
                }
                printf("\n");
                found = true; // Break the loop by changing "found" to true
            }
            j++; // Keep incrementing j until the current artist is found
        }
    }
}

void createPlaylist(char inputArray[][MAX_CHAR], char artistArray[][MAX_CHAR], int numLines, int numArtists)
{
    /* This function will create a randomised playlist, adhering to the given restrictions, and then
     * print out the playlist for the user in the given format */
    int i, j, a, s;
    int m = 0, k;
    int minutes, seconds, totalLength = 0;
    bool found;
    char copy[MAX_CHAR], *token;
    int artistAppearances[numArtists]; // array to record how many times each artist has appeared in the playlist
    int songIndexes[MAX_SONGS], artistIndexes[MAX_SONGS];
    char songLengths[MAX_SONGS][MAX_SONG_LENGTH], songs[MAX_SONGS][MAX_CHAR];

    for(i = 0; i < numArtists; i++)
    {
        /* initialise every value in this array to 3 */
        artistAppearances[i] = 3;
    }

    srand(time(NULL)); // seed the random number generator

    while(totalLength < 3470) // This length was chosen as it averaged out as the closest to 1 hour
    {
        /* Keep picking random songs until the total length of the playlist is 130 seconds
         * under an hour, making the playlist roughly 1 hour */

        a = rand() % numArtists; // Use k pick a random artist name
        if(m > 1)
        {
            /* If we have 3 or more songs in the playlist, check that no artist is triple played */
            while(a == artistIndexes[m - 1] && a == artistIndexes[m - 2])
            {
                // an artist cannot have more than 2 songs in a row
                a = rand() % numArtists;
            }
        }

        if(artistAppearances[a] != 0)
        {
            /* If this artist has not already appeared more than 3 times, randomly pick one of
             * their songs */
            i = 0;
            found = false; // The boolean "found" will change to true when we have found the artists' block in the inputArray
            while(!found)
            {
                /* This loop will go though the inputArray and find the corresponding block of songs for the
                * current artist */
                if(strcmp(inputArray[i], artistArray[a]) == 0)
                {
                    /* If we have found the current artist, record their index in the inputArray and
                     * store it in the variable i */
                    found = true;
                    j = i; // i will index the start of this block of songs
                    while((strcmp(inputArray[j], seperator) != 0) && (j < numLines))
                    {
                        j++; // j will record how many songs this artist has in the array
                    }
                    j--;
                }
                i++;
            }

            s = (rand() % (j - i + 1)) + i; // variable s will record the randomly selected songs' index in the inputArray

            found = false; // This boolean will change to true if the current song is already in the playlist
            for(k = 0; k < m; k++)
            {
                /* Loop through the array of song indexes that have already been selected and check to
                 * see if the current song is already in the playlist */
                if(songIndexes[k] == s)
                {
                    /* If the song is already in the playlist then change found to true */
                    found = true;
                }
            }

            if(!found)
            {
                /* If the current song is not in the playlist, then add the song and the artists'
                 * name to the playlist */
                songIndexes[m] = s;
                artistIndexes[m] = a;

                /* Use the strtok function to split and store the individual song names and lengths
                 * in seperate arrays */
                strcpy(copy, inputArray[s]);
                token = strtok(copy, delim);
                strcpy(songs[m], token);
                token = strtok(NULL, delim);
                token[strlen(token) - 1] = '\0'; // remove the '\n' character from the end of the string
                strcpy(songLengths[m], token);

                totalLength += timeInSeconds(songLengths[m]); // add the song length to the total playlist time

                m++; // variable m will record how many songs we've picked so far
                artistAppearances[a]--; // decrement the amount of times left that this artist can appear in the playlist
            }
        }
    }

    // Find the total length of the playlist in minutes and seconds
    minutes = totalLength / 60;
    seconds = totalLength % 60;

    // Loop through the input array and remove any '\n' characters from the strings
    for(i = 0; i < numLines; i++)
    {
        for(j = 0; j < MAX_CHAR; j++)
        {
            if(inputArray[i][j] == '\n')
            {
                inputArray[i][j] = '\0';
            }
        }
    }
    // Loop through the artistsArray and remove any '\n' characters from the strings
    for(i = 0; i < numArtists; i++)
    {
        for(j = 0; j < MAX_CHAR; j++)
        {
            if(artistArray[i][j] == '\n')
            {
                artistArray[i][j] = '\0';
            }
        }
    }

    /* Now print out the playlist for the user, in the required format */
    printf("Randomised playlist\n");
    for(i = 0;i < m; i++)
    {
        printf("%s: \"%s\" (%s)\n", artistArray[artistIndexes[i]], songs[i], songLengths[i]);
    }

    if((seconds / 10) == 0)
    {
        // If "seconds" is a single digit integer, add a 0 to the end of the song duration
        printf("\nTotal duration: %d:0%d\n", minutes, seconds);
    }
    else
    {
        printf("\nTotal duration: %d:%d\n", minutes, seconds);
    }
}

int timeInSeconds(char songLength[MAX_SONG_LENGTH])
{
    /* This function will take in a string that contains a song length in minutes and seconds
     * and returns an integer containing the total amount of seconds in the string */
    int totalSeconds, seconds, minutes;
    char minutesString[4], secondsString[4];
    char copy[MAX_SONG_LENGTH];
    char * token;

    // Copy the string to allow the function to operate on it with strtok without damaging the string
    strcpy(copy, songLength);

    // Break up the string into minutes and seconds
    token = strtok(copy, ":");
    strcpy(minutesString, token);
    token = strtok(NULL, ":");
    strcpy(secondsString, token);

    // Get the total time (in seconds) from the minutesString
    if(strlen(minutesString) == 3)
    {
        // If "minutes" is a double digit number
        minutes = ((minutesString[0] - '0') * 10) + (minutesString[1] - '0');
    }

    else
    {
        // If "minutes" is a single digit number
        minutes = minutesString[0] - '0';
    }

    // Get the total time (in seconds) from the secondsString. This should always be a double-digit number
    seconds = ((secondsString[0] - '0') * 10) + (secondsString[1] - '0');

    // Get the total time (in seconds) of the whole string by adding the minutes and seconds
    totalSeconds = (minutes * 60) + seconds;

    return totalSeconds;
}
