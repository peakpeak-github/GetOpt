#pragma once
extern const char *g_optTable[];
extern const int g_optCount;

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif

enum
{
	MISSINGVALUE = -1,	// Option value missing
	NOOPTION = -2,		// No option given, just the value -> pgm filename
	NOTFOUND = -3		// -option not found
};
int getOptAndVal(IN OUT int &argc, IN OUT char **&argv, OUT char *& optValPtr);
