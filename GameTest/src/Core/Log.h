#pragma once


//--------------------------------------------------------------------------------------
// Name: class Log
// Desc: Utility static class with different printing functions.
//--------------------------------------------------------------------------------------
class Log
{
public:
    static VOID Info(const std::string& strMessage, ...);
    static VOID Error(const std::string& strMessage, ...);
private:
    static VOID Print(const std::string& strFormat, const va_list pArgList);
};
