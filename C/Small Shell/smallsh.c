/****************************************************************************************
*   Author:                       Alex Samuel
*   Date Created:                 11/17/2015
*   Last Modification Date:       11/23/2015
*   Filename:                     smallsh.c
*
*   Overview:   This program is a simple shell that runs several commands.
*
*   Input:  The input shall consist of commands (such as exit, cd, status) and arguments.
*
*   Output: The output of the program will be printed to the screen or into a file.
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/* global variable to hold status */
int intstatus = 0;

/* sighandler for catching INT signals */
void catchint(int signo)
{
  printf("terminated by signal %d\n", signo);
  fflush(stdout);
  intstatus = signo;
}

/* stores background and foreground process PID values */
int bpids[100];
int fpids[100];

/* sighandler function for handling all other signals */
void back(int signo)
{
  /* 
  Design influenced from discussion on 
  http://www.microhowto.info/howto/reap_zombie_processes_using_a_sigchld_handler.html
   */
  pid_t childid;
  int status2;

/* this waitpid reaps the most recent background process*/
  childid = waitpid(-1, &status2, WNOHANG);
  if(childid == bpids[0]) {
      printf("background pid %d is done: ", bpids[0]);
      fflush(stdout);

      if(WIFEXITED(status2)) {
          printf("exit value %d\n",  WEXITSTATUS(status2));
          fflush(stdout);
          bpids[0] = 0;
      }
      else {
          printf("terminated by signal %d\n", signo);
          fflush(stdout);
      }

  }

/* this waitpid reaps any remaining zombies */
  while (childid = waitpid((pid_t)(-1), &status2, WNOHANG) > 0) {}

}


int main(int argc, char *argv[]) {

/* shell will continue to execute while exitFlag < 1  */
  int exitFlag = 0;
  int status;

/* args is an array of pointers to pointers to each arguments entered by user */
  char** args = NULL;

/* input is a string containing the line of input entered by the user*/
  char input[2048];
  int i;
  int j = 0;

/* argCount tracks the total number of arguments entered by the user*/
  int argCount = 0;
  pid_t  pid;
  pid_t  exitpid;

/* maxargCount tracks the largest number of arguments ever entered by the user*/
  int maxargCount = 0; 

/* creates sigaction structures to handle SIGTERM and all signals generated from child*/
  struct sigaction act, backG;
  act.sa_handler = catchint;
  act.sa_flags = 0;
  sigfillset(&(act.sa_mask));
  sigaction(SIGINT, &act, NULL);

  backG.sa_handler = back;
  backG.sa_flags = 0;
  sigfillset(&(backG.sa_mask));
  sigaction(SIGCHLD, &backG, NULL);

/* shell continues to run while exitFlag < 1*/
  while (exitFlag < 1) {

/* clears string containing user input */
    memset(input, 0, sizeof(input));
/* clears array containing user commands and arguments */
    for(i = 0; i < argCount; i++) {
      args[i] = 0;
    }

    argCount = 0;

/* flag for tracking whether process should run in background */
    int backFlag = 0;
    int backPrint = 0;

/* infilepos and outfilepos track the position of the redirection argument (< or >) */
    int infilepos = 0;
    int outfilepos = 0;

/* prints prompt and waits for user input */
    printf(": ");
    fflush(stdout);
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

/* input is tokenized by spaces */
    char* tokens = strtok(input, " ");

/* if no commands/arguments enteres by user, loop restarts and reprompts user */
    if(!strcmp(input, "")) {
        continue;
      }

/* input is split up by blank spaces and commands/arguments stored in args array*/
    if (tokens != NULL) {
          while( tokens != NULL ) {
            argCount++;
            args = realloc(args, sizeof(char*) * argCount);
            args[argCount-1] = tokens;
            tokens = strtok(NULL, " ");
           }

          if(argCount > maxargCount) {
            maxargCount = argCount;
          }

/* if first argument is exit, program will exit.*/
        if (!strcmp(args[0], "exit")) {
                free(args);
                exitFlag = 10;
                exit(0);
        }

        if(argCount > 1) {

  /* checks for redirection operators, removes operators from arg array
  and keeps track of position that operator was located within input */
            for(i = 0; i < argCount; i++) {
                if(!strcmp(args[i], "<")) {
                    infilepos = i + 1;
                    args[i] = args[infilepos];
                    args[infilepos] = NULL;
                    argCount--;
                }
                if(!strcmp(args[i], ">")) {
                    outfilepos = i + 1;
                    args[i] = args[outfilepos];
                    args[outfilepos] = NULL;
                    argCount--;
                }
            }

/* checks for kill command and sends it to process identified by stored PID*/
          if (!strcmp(args[0], "kill")) {
              if( (!strcmp(args[1], "-KILL") || !strcmp(args[1], "-15")) ) {
                  kill( bpids[0], SIGKILL );
                  continue;
              }
              if( (!strcmp(args[1], "-TERM") || !strcmp(args[1], "-9")) ) {
                  kill( bpids[0], SIGTERM );
                  continue;
              }
          }
        }  

/* checks for background process and removes ampersand from args array*/
        if(!strcmp(args[argCount-1], "&")) {
            backFlag = 1;
            args[argCount-1] = NULL;
            argCount--;
          }

/* checks for mkdir command and whether dir should contain PID,
then concatenates PID onto the name of the directory entered by the user*/
        if(!strcmp(args[0], "mkdir")) {
            if(strstr(args[1], "$$") != NULL) {
                    int pid4dir = getpid();
                    char pidString[16];
                    sprintf(pidString, "%d", pid4dir);
                    fflush(stdout);
                    strncpy (strstr(args[1], "$$"), pidString, strlen(pidString));

            }
        }
    }

/* checks for exit command and then exits program*/
    if (!strcmp(args[0], "exit")) {
          free(args);
          exitFlag = 10;
          exit(0);
        }

/* checks to see if user entered comment and reprompts for input*/
    if ( (!strcmp(args[0], "#"))) {
        continue;
    }

/* checks to see if user entered cd command by itself and changes to HOME direcotry
or another directory if specified by user*/
    if (!strcmp(args[0], "cd")) {
        int try;
        if(args[1] == NULL) {
            try = chdir(getenv("HOME"));
            if(try != 0) {
               printf("Cannot change to HOME directory.\n");
               fflush(stdout);
               intstatus = 1;
            }
            else {
                intstatus = 0;
                continue;
            }
        }

        else {
            if(strstr(args[1], "$$") != NULL) {
                int pid4dir = getpid();
                char pidString[16];
                sprintf(pidString, "%d", pid4dir);
                fflush(stdout);
                strncpy (strstr(args[1], "$$"), pidString, strlen(pidString));
            }

            try = chdir(args[1]);
            if(try != 0) {
               printf("Cannot change directory to %s.\n", args[1]);
               fflush(stdout);
               intstatus = 1;
            }
            else {
                intstatus = 0;
                continue;
            }
        }
      }

/*Checks to see if user entered status command and prints currently stored status to user,
then resets status*/
    if (!strcmp(args[0], "status")) {
      if(intstatus > 1) {
          status = intstatus;
          printf("terminated by signal %d\n", status);
          fflush(stdout);

      }
      else if( WIFEXITED(status) == 0) {
        status = WEXITSTATUS(status);
        printf("exit value %d\n", status);
        fflush(stdout);
      }
      else {
        printf("exit value %d\n", intstatus);
        fflush(stdout);
      }

      status = 0;
      intstatus = 0;
      continue;
    }

/*creates process fork and prints background pid*/
    pid = fork();
    if(backFlag == 1 && pid > 0) {
        bpids[0] = pid;-
        printf("\nbackground pid is %d\n", pid);
        fflush(stdout);
    }

/*checks value of pid to determine if we are in child*/
        if (pid == 0) {
          int fd;
          int fd2;

/*opens file for reading*/
          if(infilepos > 0) {
              fd = open(args[infilepos-1], O_RDONLY);
               if(fd == -1) {
                printf("smallsh: cannot open %s for input\n", args[infilepos-1]);
                fflush(stdout);
                intstatus = 1;
                continue;
               }

               fd2 = dup2(fd, 0);
               if(fd2 == -1) {
                printf("smallsh: cannot open %s for input\n", args[infilepos-1]);
                fflush(stdout);
                intstatus = 1;
                continue;
               }

/*closes file on execute*/
               fcntl(fd, F_SETFD, 1);
               args[infilepos-1] = NULL;
          }
          
/*opens file for  writing*/
            if(outfilepos > 0) {
                 fd = open(args[outfilepos-1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                 if(fd == -1) {
                  printf("smallsh: cannot open %s for output\n", args[outfilepos-1]);
                  fflush(stdout);
                  intstatus = 1;
                  continue;
                 }

                 fd2 = dup2(fd, 1);
                 if(fd2 == -1) {
                  printf("smallsh: cannot open %s for output\n", args[outfilepos-1]);
                  fflush(stdout);
                  intstatus = 1;
                  continue;
                 }

/*closes file on execute*/
                fcntl(fd, F_SETFD, 1);
                args[outfilepos-1] = NULL;
          }

          if(backFlag == 1) {
              signal(SIGINT, SIG_IGN);
          }

/*executes arguments entered by the user*/
          if(execvp(args[0], args) < 0) {
            printf("command or file name not found\n");
            fflush(stdout);
            intstatus = 1;
            exit(1);
          }
        }

/*checks if fork failed*/
        else if(pid < 0) {
          printf("fork failed!");
          fflush(stdout);
          intstatus = 1;
        }
        /* sets waitOption for waitpid for background process */
        else {
          int waitOption;
          if(backFlag == 1) {
              waitOption = WNOHANG;
          }
          /* sets waitOption for waitpid for foreground process */
          else {
            waitOption = 0;
          }

          exitpid = waitpid(pid, &status, waitOption);
          fpids[0] = exitpid; 
        }     
  }

  return 0;
}
