#include "pch.h"
#include "Core\Log.h"


static CONST INT MAX_SIZE = 2048;

//--------------------------------------------------------------------------------------
// Name: Info()
// Desc: Print an info message to the console.
//--------------------------------------------------------------------------------------
VOID Log::Info(const std::string& message, ...)
{
    // Get the variadic arguments
    va_list pArgList;
    va_start(pArgList, message);

    // Print
    Print("Info: " + message, pArgList);

    // Free the variadic arguments
    va_end(pArgList);
}


//--------------------------------------------------------------------------------------
// Name: Error()
// Desc: Print an error message to the console.
//--------------------------------------------------------------------------------------
VOID Log::Error(const std::string& message, ...)
{
    // Get the variadic arguments
    va_list pArgList;
    va_start(pArgList, message);

    // Print
    Print("Error: " + message, pArgList);

    // Free the variadic arguments
    va_end(pArgList);
}


//--------------------------------------------------------------------------------------
// Name: Print()
// Desc: Print a formatted message to the console.
//--------------------------------------------------------------------------------------
VOID Log::Print(const std::string& strFormat, const va_list pArgList)
{
    // Build the string with the format
    CHAR szBuffer[MAX_SIZE] = { 0 };
    vsnprintf_s(szBuffer, _TRUNCATE, strFormat.c_str(), pArgList);

    // Append \n to the string
    strcat_s(szBuffer, MAX_SIZE, "\n");

    // Print
    OutputDebugString(szBuffer);
}
