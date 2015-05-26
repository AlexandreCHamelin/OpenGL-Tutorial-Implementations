#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

class Logger
{
public:
	static void restart_log(const char* logFile);
	static void print_to_log(const char* logFile, std::string text);
};

#endif