// Liam Smyth's header file for functions that sort and print the artist and song names
#ifndef ASSIGNMENT1_SORTING_ARTISTS_SONGS_H
#define ASSIGNMENT1_SORTING_ARTISTS_SONGS_H
#endif //ASSIGNMENT1_SORTING_ARTISTS_SONGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Define global variables to store the size of each row and column in our 2D arrays
#define MAX_LINES 150
#define MAX_CHAR 70
#define MAX_SONGS 30
#define MAX_SONG_LENGTH 8

 // Define special strings used for splitting strings and 2D arrays
 static char seperator[] = "\n";
 static char delim[] = "***";

int readInput(char inputArray[][MAX_CHAR], char *filename); // Read the songs + Artists into the array
void sortSongs(char inputArray[][MAX_CHAR], int numLines); // Sort all of the songs in the inputArray
int sortArtists(char inputArray[][MAX_CHAR], char artistArray[][MAX_CHAR], int numLines);// Store the artists names in a separate array and sort them
void printSortedList(char inputArray[][MAX_CHAR], char artistArray[][MAX_CHAR], int numLines, int numArtists); // Print the output in the required format
void createPlaylist(char inputArray[][MAX_CHAR], char artistArray[][MAX_CHAR], int numLines, int numArtists); // Create and print out the playlist
int timeInSeconds(char songLength[MAX_SONG_LENGTH]); // Function to convert a time-string in minutes and seconds to just seconds