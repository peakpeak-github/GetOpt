#include <string.h>
#include <ctype.h>
#include "getoptandval.h"
#include "mystyle.h"			// Custom style defined here

///////////////////////////////////////////////////////////////////////////////////////////
// Parse one option - value pair
// Allows -option value, -optionvalue, see mystyle.h 
//
int getOptAndVal(IN OUT int &argc, IN OUT char ** &argv, OUT char * &optValPtr)
{
	int optNum, n;

	optValPtr = *(++argv);								// Next option
	if ((*optValPtr == '-') || (*optValPtr == '/')) 	// Option here 
	{
		optValPtr++;	                          		// Skip option delimiter "-" or "/"
		for (optNum = 0; optNum < g_optCount; optNum++)	// Search in option table
		{
			n = strncmp(g_optTable[optNum], optValPtr, strlen(g_optTable[optNum]));
			if (n == 0)	// Found one
				break;
		}
		if (n)						// Not found any matching option
			return NOTFOUND;
#ifdef ALLOWNOVALUE
		if (isupper(*optValPtr))
			return optNum;			// No argument on this one
#endif
		//
		// Make optValPtr point at the option value regardless of spaces, equal sign or not
		//
		optValPtr += strlen(g_optTable[optNum]);	// Skip option word
#ifdef ALLOWEQUALSIGN
		if (*optValPtr == '=')
			optValPtr++;
#endif
		if (*optValPtr == '\0')		// Space between option specifier & option value OR missing value
		{
			optValPtr = *(++argv);
			argc--;
			if (optValPtr == NULL)		// Last option, missing value
				return MISSINGVALUE;	
#ifdef ALLOWEQUALSIGN
			if (*optValPtr == '=')	// ' =' or ' = '
			{
				optValPtr++;
				if (*optValPtr == '\0')	// '= '
				{
					optValPtr = *(++argv);
					argc--;
				}
			}
#endif
		}
	} // if ((*argv == '-') || (*argv == '/'))
	else // No option given -> no optNum value
		return NOOPTION;
	return optNum;
}
