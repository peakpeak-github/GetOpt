/////////////////////////////////////////////////////
// Template for option handling
//
#include <stdio.h>
#include <stdlib.h>
#include "getoptandval.h"

void help();	// Last in this file
//
// Case sensitive option strings
//
const char *g_optTable[] =
{
	"file",
	"max",
	"min",
	"w",
	"h",
	"Verbose",	// First letter upper case -> Requires no argument if NOVALUE defined
	"help"
};
const int g_optCount = sizeof(g_optTable) / sizeof(g_optTable[0]);

enum
{
	INFILE,
	MAX,
	MIN,
	W,
	H,
	VERBOSE,
	HELP,
};
//
// -file charles.txt -min -11.61 -max +12.95 -Verbose -w 100 -h 64
//
int main(int argc, char* argv[])
{
	char *optValPtr = NULL;
	char* fileName = NULL;		// output file name template
	double max = 1.1;
	double min = 1.1;
	bool verbose = false;
	int width = 10;
	int height = 100;
	int optNum;

	while (--argc > 0)	// First argument is program name
	{
		optNum = getOptAndVal(argc, argv, optValPtr);
		//
		// optValPtr is pointing to an actual value if the option requires a value
		// OR in case the option needs no argument (first letter upper case), the option itself
		//
		switch (optNum)
		{
		case INFILE:
			fileName = optValPtr;
			break;
		case MAX:
			max = atof(optValPtr);
			break;
		case MIN:
			min = atof(optValPtr);
			break;
		case W:
			width = atoi(optValPtr);
			break;
		case H:
			height = atoi(optValPtr);
			break;
		case VERBOSE:
			verbose = true;
			break;
		case MISSINGVALUE:						// Option value missing
			printf("Missing value for %s\n", optValPtr);
			help();
		case NOOPTION:							// No option given, just the value -> pgm filename
			printf("No options given\n");
			help();
		case NOTFOUND:							// -option not found
			printf("%s illegal option\n", optValPtr);
			help();
		} // switch()
	} // while

	printf("file name: %s\n", fileName);
	printf("Max: %g\n", max);
	printf("Min: %g\n", min);
	printf("Width: %d\n", width);
	printf("Height: %d\n", height);
	printf("Verbose: %d\n", verbose);
	//
	// Determine action
	//
//	if (fileName && verbose)
// ... etc ...
	return 0;
}
void help()
{
	printf("MyProgram 1.00\n"
		"  Usage:\n"
		"  [-file <file_name>]\n"
		"  [-max <max value>]\n"
		"  [-min <min value>]\n"
		"  [-w <width>]\n"
		"  [-h <height>]\n"
		"  [-Verbose]\n"
		"  [-help]\n"
		);
 	exit(0);
}

