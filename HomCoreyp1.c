// A.	Create and run, a program (1 file), with multiple functions/methods as follows: 
// 1	The main function will:
// a	Determine the input and output files
// b	Request the “mode” for the program to use. The input will be:
// (1)	A “0” for the character-by-character mode (1st function below)
// (2)	A “1” for the line-by-line mode (2nd function below)
// 2	The 1st function does the following:
// a	Open a simple text file
// b	Read a line of the file (one byte at a time), testing for "end of line" as it goes.
// c	Write that line of the file to a NEW file on the same drive, one character at a time!
// (Read a byte, then immediately write that byte – NO buffering of multiple bytes!)
// d	Repeat the above to the end of the file.
// e	Closes the files
// f	Computes the time it took to read and write the total file in:
// (1)	CPU milli-seconds (amount of time your program used the CPU to do work)
// (2)	Wall-clock milli-seconds (real-world time at start of program to real-world time at end of program). You MUST use my time_functions.h file for this.
// g	Displays the times calculated
// B.	The 2nd function, is similar to the 1st one, but instead of reading and writing character-by-character, it reads and writes a whole line of the file at a time, repeating this until the whole file has been pro-cessed.
#define _CRT_SECURE_NO_WARNINGS 1 
#include <stdio.h>
#include "time_functions.h"
#include <stdlib.h>
#include <iostream>
#include <string>
/**Using a 1, 880, 808 byte size file.
Windows: Byte - by - byte
the time from 'CPU time' for byte copying is      0.234 seconds
the time from 'ftime' for byte copying is      0.235 seconds
Windows : Line - by - line
the time from 'CPU time' for byte copying is      0.031 seconds
the time from 'ftime' for line copying is      0.034 seconds
Linux : Byte - by - byte
the time from 'CPU time' for byte copying is      0.020 seconds
the time from 'ftime' for byte copying is      0.033 seconds
Linux : Line - by - line
the time from 'CPU time' for byte copying is      0.000 seconds
the time from 'ftime' for line copying is      0.007 seconds
*/
int main(int argc, const char* argv[])
{

	//initialize input/output file to be opened
	FILE *iFP, *oFP;
	//we use output/input [256] to take in the max size for an input in scanf
	char input[256];
	char output[256];
	int modeSelect[256];
	printf("Name of an input file? \n");
	scanf("%s", input);

	//need to open the input file so that we can read it later
	iFP = fopen(input, "r");



	printf("Name of an output file? \n");
	scanf("%s", output);

	//need to open the output file, if the name doesn't exist a file will be created. 
	oFP = fopen(output, "w");
	printf("The name of the file is: %s\n", output);

	printf("Select the mode you would like to use. 0 for char-by-char mode or 1 for line-by-line mode.\n");
	scanf("%d", modeSelect);

	//THIS IS PART 1: BYTE-BY-BYTE MODE
	if (*modeSelect == 0)
	{
		printf("Using char-by-char mode.\n");
		//we will use getc which returns an integer, so initialize an int to be used.
		int ch;

		printf("%s", "start_timing begins now.\n");
		//initialize CPU timer so that we can record the result for the total time the cpu clock takes to calculate
		start_timing();

		//loop to read/write byte by byte
		while ((ch = getc(iFP)) != EOF)
		{
			putc(ch, oFP);
		}
		stop_timing();

		printf("%s", "stop_timing is now called.\n");
		//F/G to find the total time elapsed we subtract start from end/print the CPU time used, which is in the function get_CPU_time_diff()
		printf("the time from 'CPU time' for byte copying is %10.3f seconds\n", get_CPU_time_diff());
		printf("the time from 'ftime' for byte copying is %10.3f seconds \n ", get_wall_clock_diff());

		//E. Closes the files.
		fclose(iFP);
		fclose(oFP);

		//we want to keep the terminal window open on WINDOWS
		std::string leaveOpen;
		std::cout << "Enter any key to continue!" << std::endl;
		std::cin >> leaveOpen;
	}

	//THIS IS PART 2: LINE-BY-LINE MODE.
	else if (*modeSelect == 1)
	{
		printf("Using line-by-line mode.\n");

		//initialize some variables for getline, we need a char to read lines
		char buf[256];

		printf("%s", "start_timing begins now.\n");
		//initialize CPU timer so that we can record the result for the total time the cpu clock takes to calculate
		start_timing();

		//loop to read/write line-by-line
		while (fgets(buf, sizeof(buf), iFP)) {
			fputs(buf, oFP);
		}

		stop_timing();
		printf("%s", "stop_timing is now called.\n");
		//F/G to find the total time elapsed we subtract start from end/print the CPU time used, which is in the function get_CPU_time_diff()
		printf("the time from 'CPU time' for line copying is %10.3f seconds\n", get_CPU_time_diff());
		printf("the time from 'ftime' for line copying is %10.3f seconds \n ", get_wall_clock_diff());

		//E. Closes the files.
		fclose(iFP);
		fclose(oFP);

		//we want to keep the terminal window open on WINDOWS
		std::string leaveOpen;
		std::cout << "Enter any key to continue!" << std::endl;
		std::cin >> leaveOpen;
	}
	else
	{
		printf("That is not a valid option! Terminating program.\n");
	}
	return 0;
}
