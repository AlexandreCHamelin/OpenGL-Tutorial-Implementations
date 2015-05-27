#ifndef LOGGER_HPP
#define LOGGER_HPP

#define GL_LOG_FILE "log.txt"

#include <string>

class Logger
{
public:
	static bool restartLog(const char* logFile);
	static bool printToLog(const char* logFile, const char* text, ...);
private:
	inline Logger(){};
};

#endif