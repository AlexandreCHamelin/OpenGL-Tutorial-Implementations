#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

class Logger
{
public:
	static void restartLog(const char* logFile);
	static bool printToLog(const char* logFile, const char* text, ...);
};

#endif