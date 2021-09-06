#pragma once


//--------------------------------------------------------------------------------------
// Name: class Log
// Desc: Utility static class with different printing functions.
//--------------------------------------------------------------------------------------
class Log
{
public:
    static VOID Info(const std::string& message, ...);
    static VOID Error(const std::string& message, ...);
private:
    static VOID Print(const std::string& strFormat, const va_list pArgList);
};
