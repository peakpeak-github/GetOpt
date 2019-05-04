#include <string.h>
#include <ctype.h>
#include "getoptandval.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Handles	-option Value, -optionValue, 
//			-option=Value, -option= Value, -option = Value, -option =Value 
//			-Option (empty) First letter in option must be upper case if no argument (value) given
//
int getOptAndVal(IN OUT int &argc, IN OUT char ** &argv, OUT char * &optValPtr)
{
	int optNum, n;

	optValPtr = *(++argv);		// First is program name
										
	if ((*optValPtr == '-') || (*optValPtr == '/')) 		// Option here 
	{
		optValPtr++;	                          			// Skip option delimiter "-" or "/"
		for (optNum = 0; optNum < g_optCount; optNum++)		// Search in option table
		{
			n = strncmp(g_optTable[optNum], optValPtr, strlen(g_optTable[optNum]));
			if (n == 0)	// Found one
				break;
		}
		if (n)						// Not found any matching option
			return NOTFOUND;
		if (isupper(*optValPtr))
			return optNum;			// No argument on this one
		//
		// Make optValPtr point at the option value regardless of spaces, equal sign or not
		//
		optValPtr += strlen(g_optTable[optNum]);	// Skip option word
		if (*optValPtr == '=')
			optValPtr++;
		if (*optValPtr == '\0')		// Space between option specifier & option value OR missing value
		{
			optValPtr = *(++argv);
			argc--;
			if (optValPtr == NULL)		// Last option, missing value
				return MISSINGVALUE;	
			if (*optValPtr == '=')	// ' =' or ' = '
			{
				optValPtr++;
				if (*optValPtr == '\0')	// '= '
				{
					optValPtr = *(++argv);
					argc--;
				}
			}
		}
	} // if ((*argv == '-') || (*argv == '/'))
	else // No option given -> no optNum value
		return NOOPTION;
	return optNum;
}
