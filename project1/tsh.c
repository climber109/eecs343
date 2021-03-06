/***************************************************************************
 *  Title: MySimpleShell
 * -------------------------------------------------------------------------
 *    Purpose: A simple shell implementation
 *    Author: Stefan Birrer
 *    Version: $Revision: 1.1 $
 *    Last Modification: $Date: 2005/10/13 05:24:59 $
 *    File: $RCSfile: tsh.c,v $
 *    Copyright: (C) 2002 by Stefan Birrer
 ***************************************************************************/
/***************************************************************************
 *  ChangeLog:
 * -------------------------------------------------------------------------
 *    $Log: tsh.c,v $
 *    Revision 1.1  2005/10/13 05:24:59  sbirrer
 *    - added the skeleton files
 *
 *    Revision 1.4  2002/10/24 21:32:47  sempi
 *    final release
 *
 *    Revision 1.3  2002/10/23 21:54:27  sempi
 *    beta release
 *
 *    Revision 1.2  2002/10/15 20:37:26  sempi
 *    Comments updated
 *
 *    Revision 1.1  2002/10/15 20:20:56  sempi
 *    Milestone 1
 *
 ***************************************************************************/
	#define __MYSS_IMPL__

  /************System include***********************************************/
	#include <stdlib.h>
	#include <signal.h>
    #include <string.h>
    #include <stdio.h>
    #include <unistd.h>

  /************Private include**********************************************/
	#include "tsh.h"
	#include "io.h"
	#include "interpreter.h"
	#include "runtime.h"
	#include "jobs.h"

  /************Defines and Typedefs*****************************************/
    /*  #defines and typedefs should have their names in all caps.
     *  Global variables begin with g. Global constants with k. Local
     *  variables should be in all lower case. When initializing
     *  structures and arrays, line everything up in neat columns.
     */

	#define BUFSIZE 80

  /************Global Variables*********************************************/
    char* cmdLine;
  /************Function Prototypes******************************************/

  /************External Declaration*****************************************/

/**************Implementation***********************************************/

int main (int argc, char *argv[])
{
    setvbuf(stdout, NULL, _IOLBF, 1024);

	/* Initialize command buffer */
	cmdLine = malloc(sizeof(char*)*BUFSIZE);

	/* shell initialization */
	if(signal(SIGINT, &SignalHandler) == SIG_ERR) PrintPError("SIGINT");
	if(signal(SIGTSTP, &SignalHandler) == SIG_ERR) PrintPError("SIGTSTP");
	if(signal(SIGCHLD, &SignalHandler) == SIG_ERR) PrintPError("SIGCHLD");

	foregroundReadLoop();

	/* shell termination */
	free(cmdLine);
	return 0;
} /* end main */

void foregroundReadLoop() {
    while (!forceExit) /* repeat forever */
	{
	    #ifdef PRINT_DEBUG
        printf("eecs343-tsh> ");
        #endif

		getCommandLine(&cmdLine, BUFSIZE);

        if(strcmp(cmdLine, "exit") == 0)
        {
          forceExit=TRUE;
          continue;
        }

        PrintAndRemoveDoneJobs();

		/* interpret command and line
		 * includes executing of commands */
		Interpret(cmdLine);
	}
}
