/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 10/26/2015
*   Last Modification Date:       11/2/2015
*   Filename:                     samuelal.adventure.c
*
*   Overview:   This program is a game in which the player must travel from the start
*               room to the end room.
*
*   Input:  The input shall consist of strings to select different rooms to enter.
*
*   Output: The output of the program will be created room files in a subdirectory
*           and messages to the user.
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*********************************************************************
** Function: randCheck
** Description: Function used to check if array of randomly generated rooms is unique.
** Parameters: integers describing size of array, range of random numbers, array
**              containing unique random numbers.
** Pre-Conditions: NONE
** Post-Conditions: returns array of unique random numbers
*********************************************************************/
int randCheck(int x, int y, int range, int array[]);

int main(int argc, char *argv[]) {

/**< Seeds random number generator */
    srand(time(NULL));
    int i;
    int j;
    int k;

/**< Gets pid value and stores it in an integer */
    int pid = getpid();
    char pidString[16];
    sprintf(pidString, "%d", pid);
    char dirString[] = "samuelal.rooms.";

/**< Appends pid value to end of directory string */
    strcat(dirString, pidString);

/**< Creates directory to store files */
    mkdir(dirString, 0777);

    char room1[] = "Bridge";
    char room2[] = "Communications Room";
    char room3[] = "AirLock";
    char room4[] = "Medical Bay";
    char room5[] = "Crew Quarters";
    char room6[] = "Greenhouse";
    char room7[] = "Engineering Lab 1";
    char room8[] = "Engineering Lab 2";
    char room9[] = "Engine Room";
    char room10[] = "Escape Pod";

/**< Creates array of room names */
    char *roomArr[] = {room1, room2, room3, room4, room5, room6, room7, room8, room9, room10};

    char path1[strlen(dirString)+strlen(room1)+2];
    char path2[strlen(dirString)+strlen(room2)+2];
    char path3[strlen(dirString)+strlen(room3)+2];
    char path4[strlen(dirString)+strlen(room4)+2];
    char path5[strlen(dirString)+strlen(room5)+2];
    char path6[strlen(dirString)+strlen(room6)+2];
    char path7[strlen(dirString)+strlen(room7)+2];
    char path8[strlen(dirString)+strlen(room8)+2];
    char path9[strlen(dirString)+strlen(room9)+2];
    char path10[strlen(dirString)+strlen(room10)+2];

/**< Appends room names to directory path */
    snprintf( path1, sizeof(path1), "%s%c%s", dirString, '/', room1 );
    snprintf( path2, sizeof(path2), "%s%c%s", dirString, '/', room2 );
    snprintf( path3, sizeof(path3), "%s%c%s", dirString, '/', room3 );
    snprintf( path4, sizeof(path4), "%s%c%s", dirString, '/', room4 );
    snprintf( path5, sizeof(path5), "%s%c%s", dirString, '/', room5 );
    snprintf( path6, sizeof(path6), "%s%c%s", dirString, '/', room6 );
    snprintf( path7, sizeof(path7), "%s%c%s", dirString, '/', room7 );
    snprintf( path8, sizeof(path8), "%s%c%s", dirString, '/', room8 );
    snprintf( path9, sizeof(path9), "%s%c%s", dirString, '/', room9 );
    snprintf( path10, sizeof(path10), "%s%c%s", dirString, '/', room10 );

/**< Creates array of paths to different rooms */
    char *pathArr[] = {path1, path2, path3, path4, path5, path6, path7, path8, path9, path10};

    int roomSelect[7];
    int typeSelect[7];
    int startFlag = 0;
    int endFlag = 0;

/**< This for loop creates an array of unique random numbers which
     correspond to room names (roomSelect[]) */
    for (i=0; i<7; i++) {
        roomSelect[i] = rand() % 10;
        if (i>0) {
            for (j=0; j < i; j++) {
                if (roomSelect[i] == roomSelect[j]) {
/**< randCheck ensures that the array of random numbers is unique (no duplicate values) */
                    randCheck(i, j, 10, roomSelect);
                }
            }
        }
/**< These if/else statements randomly create an array of numbers
     corresponding to the room type of each room (1 START, 5 MID, 1 END rooms) */
        if (startFlag == 0 && endFlag == 0) {
            typeSelect[i] = rand() % 3;
            if (typeSelect[i] == 0) {
                startFlag = 1;
            }
            else if (typeSelect[i] == 2) {
                endFlag = 1;
            }
        }
        else if (startFlag == 1 && endFlag == 0) {
            typeSelect[i] = (rand() % 2) + 1;
            if (typeSelect[i] == 2) {
                endFlag = 1;
            }
        }
        else if (startFlag == 0 && endFlag == 1) {
            typeSelect[i] = rand() % 2;
            if (typeSelect[i] == 0) {
                startFlag = 1;
            }
        }
        else if (startFlag == 1 && endFlag == 1) {
            typeSelect[i] = 1;

        }
        if (i == 6 && startFlag == 0) {
            typeSelect[i] = 0;
            startFlag = 1;
        }

        if (i == 6 && endFlag == 0) {
            typeSelect[i] = 2;
            endFlag = 1;
        }
    }

/**< Creates adjacency matrix array describing connections between rooms */
    int rmConn[7][7] = {};
    int conCount = 0;
    int temp = 0;
    int conTotal = 0;

/**< Creates random number of connections between rooms */
    for (i=0; i<7; i++) {
        conCount = 0;
        for (j=0; j<7; j++) {
            if (rmConn[i][j] == 1) {
                conCount++;
            }
        }

/**<  conTotal holds the value of the number of connections each room should have (3-6)*/
        conTotal = (rand() % 4) + 3;

/**< This while loop creates the random connections between rooms */
        while (conCount < (conTotal + 1)) {
            temp = rand() % 7;
/**< This if statement ensures that the connections are bidirectional */
            if (i != temp) {
                rmConn[i][temp] = 1;
                rmConn[temp][i] = 1;
                conCount++;
            }
            continue;
        }
    }

/**< Creates an array of file pointers */
    FILE **rmFiles = malloc(7 * sizeof(FILE *));

/**< This for loop creates each room file in the subdirectory and then
     writes the room connection information to each file. */
    for (i=0; i<7; i++) {
        rmFiles[i] = fopen(pathArr[roomSelect[i]], "w+");
        fprintf(rmFiles[i], "ROOM NAME: ");
        fprintf(rmFiles[i], roomArr[roomSelect[i]]);
        fprintf(rmFiles[i], "\n");
        k = 1;
/**< This for loop reads the adjacency matrix and writes the connection information
     to each file.*/
        for (j=0; j<7; j++) {
            if (rmConn[i][j] == 1) {
                fprintf(rmFiles[i], "CONNECTION ");
                fprintf(rmFiles[i], "%d: ", k);
                fprintf(rmFiles[i], "%s\n", roomArr[roomSelect[j]]);
                k++;
            }
        }
/**< Writes the room type information to each file. */
        fprintf(rmFiles[i], "ROOM TYPE: ");
        if (typeSelect[i] == 0) {
            fprintf(rmFiles[i], "START_ROOM");
        }
        else if (typeSelect[i] == 1) {
            fprintf(rmFiles[i], "MID_ROOM");
        }
        else if (typeSelect[i] == 2) {
            fprintf(rmFiles[i], "END_ROOM");
        }
/**< Closes all opened files */
        fclose(rmFiles[i]);
    }

    char* startFile;
    char* endFile;
    int startRoom;
    int endRoom;
/**< This file opens each file in the subdirectory and tracks
     which file is the start room and end room. */
    for (i=0; i<7; i++) {
        char fileLine[50];
        rmFiles[i] = fopen(pathArr[roomSelect[i]], "r");
        while (fgets(fileLine, 50, rmFiles[i])) {
            startFile = strstr( fileLine, "START_ROOM" );
            endFile = strstr( fileLine, "END_ROOM" );
            if (startFile != NULL) {
                startRoom = i;
            }
            if (endFile != NULL) {
                endRoom = i;
            }
        }
/**< Closes all opened files */
    fclose(rmFiles[i]);
    }

/**< Frees allocated memory for file pointers
    for (i=0; i<7; i++) {
        free(rmFiles[i]);
    }
    free(rmFiles);
*/

    int exitFlag = 0;
/**< Opens file of start room */
    FILE* curFile = fopen(pathArr[roomSelect[startRoom]], "r");
    int colLoc;
    int endLine = 0;
    char col[] = ":";
    char curLine[50];
/**< Creates array to hold room information within each room file and also
     creates an array to store the path the user traveled.*/
    char** roomInfo = (char**)malloc(8*sizeof(char*));
    char** pathInfo = (char**)malloc(1000*sizeof(char*));
    pathInfo[0] = malloc(50*sizeof(char));

    for(i = 0; i < 8; i++) {
    roomInfo[i] = malloc(50*sizeof(char));
    }
    int lineNum = 0;
/**< Searches for colon (:) symbol and stores connection info that comes after
     into an array. */
    while (fgets(curLine, 50, curFile)) {

        colLoc = strcspn(curLine, col);
        strncat(roomInfo[lineNum], curLine+(colLoc+2), (strlen(curLine) - (colLoc)));
        strncpy(roomInfo[lineNum], roomInfo[lineNum], 35);

        int len = strlen(roomInfo[lineNum]);


        char* startString = "START";
        char* midString = "MID";
        char* endString = "END";
        char* result1 = strstr( roomInfo[lineNum], startString );
        char* result2 = strstr( roomInfo[lineNum], midString );
        char* result3 = strstr( roomInfo[lineNum], endString );


        if( result1 == NULL && result2 == NULL && result3 == NULL) {
            roomInfo[lineNum][len-1] = 0;
        }

/**< Stores the line number of the last line of the room file */
        if( result1 != NULL || result2 != NULL || result3 != NULL) {
            endLine = lineNum;
        }

        lineNum++;
    }
/**< Closes file of starting room */
        fclose(curFile);
        int steps = 0;
/**< Instructor gave permission for brief intro to user. */
        printf("YOU MUST EXIT THE SPACE STATION IMMEDIATELY IN ORDER TO SURVIVE.\n");
        FILE* curFile2 = NULL;
/**< Keeps executing until user enters End Room and changes exitFlag variable */
        while (exitFlag == 0) {
/**< Prints "Current Location" and "Possible Connections" info to screen */
            for(i = 0; i < 8; i++) {
                if(i == 0) {
                    printf("\nCURRENT LOCATION: %s\n", roomInfo[i]);
                    pathInfo[steps] = malloc(50*sizeof(char));
                    strncpy(pathInfo[steps], roomInfo[i], 35);
                    printf("POSSIBLE CONNECTIONS: ");
                }
                else if(i > 0 && i < (endLine-1)) {
                    printf("%s, ", roomInfo[i]);
                }
                else if(i == ((endLine)-1)) {
                    printf("%s.\n", roomInfo[i]);
                }
            }

        printf("WHERE TO? >");
        char input[35];
        fgets(input, 35, stdin);
        int endString;
        endString = strlen(input)-1;

        if( input[ endString ] == '\n') {
            input[ endString ] = '\0';
        }

/**< Compares user input to possible room connections, then opens matching room file. */
        for(i = 0; i < 7; i++) {
            if (strcmp(input, roomArr[roomSelect[i]]) == 0) {
                steps++;
/**< Per instructor's instructions, if user exceeds max number of steps, exit gracefully. */
                if (steps == 1000) {
                    printf("\nYOU TOOK TOO LONG TO ESCAPE! YOU DIED!\n");
                    exit(0);
                }
                curFile2 = fopen(pathArr[roomSelect[i]], "r");
                break;

            }
            else if (i == 6) {
                printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
                break;
            }
        }

        lineNum = 0;
/**< Reads in lines from room file. */
        while (curFile2 != NULL && fgets(curLine, 50, curFile2)) {
            colLoc = strcspn(curLine, col);
            memset(roomInfo[lineNum], '\0', sizeof( roomInfo[lineNum] ));
            strncat(roomInfo[lineNum], curLine+(colLoc+2), (strlen(curLine) - (colLoc)));
            int len = strlen(roomInfo[lineNum]);

            char* startString = "START";
            char* midString = "MID";
            char* endString = "END";
            char* result1 = strstr( roomInfo[lineNum], startString );
            char* result2 = strstr( roomInfo[lineNum], midString );
            char* result3 = strstr( roomInfo[lineNum], endString );

            if( result1 == NULL && result2 == NULL && result3 == NULL) {
                roomInfo[lineNum][len-1] = 0;
            }

            if( result1 != NULL || result2 != NULL || result3 != NULL) {
                endLine = lineNum;
            }

            lineNum++;
        }

/**< Checks if user entered End Room and changes exitFlag. */
        if (strcmp(roomInfo[0], roomArr[roomSelect[endRoom]]) == 0) {
            pathInfo[steps] = malloc(50*sizeof(char));
            strncpy(pathInfo[steps], roomInfo[0], 35);
            printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
            printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", steps);
            for(i = 0; i < steps; i++) {
                printf("%s\n", pathInfo[i]);
            }
            printf("%s\n", roomInfo[0]);
            exitFlag = 1;
        }

        }

/**< Closes all open files. */
    int fcloseall(void);

/**< Frees allocated memory before program exits. */
    for (i=0; i<steps; i++) {
        if (i < 8) {
            free(roomInfo[i]);
        }
        free(pathInfo[i]);
    }
    free(roomInfo);
    free(pathInfo);

    return 0;
}

/**< This function checks if randomly created numbers in array are unique. */
int randCheck(int x, int y, int range, int array[]) {
    array[x] = rand() % range;
    for (y=0; y < x; y++) {
        if (array[x] == array[y]) {
            randCheck(x, y, range, array);
        }
    }
    return 0;
}