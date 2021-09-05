#include "pch.h"
#include "Core\Log.h"

//--------------------------------------------------------------------------------------
// Name: DebugPrint()
// Desc: Print a formatted message to the console.
//--------------------------------------------------------------------------------------
VOID DebugPrint(LPCSTR strFormat, ...)
{
    CONST INT MAX_SIZE = 2048;

    // Get the variadic arguments
    va_list pArgList;
    va_start(pArgList, strFormat);

    // Build the string with the format
    CHAR szBuffer[MAX_SIZE] = { 0 };
    vsnprintf_s(szBuffer, _TRUNCATE, strFormat, pArgList);

    // Append \n to the string
    strcat_s(szBuffer, MAX_SIZE, "\n");

    // Print
    OutputDebugString(szBuffer);

    // Free variadic arguments
    va_end(pArgList);
}
