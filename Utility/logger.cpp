#include "logger.hpp"
#include <fstream>
#include <time.h>

void Logger::restart_log(const char* logFile)
{
	time_t now = time(0); //Get current time
	char date[26];

	ctime_s(date, 26, &(now));
	
	std::string output = "GL_LOG local time: ";
	output += date;
	output += "\n";

	print_to_log(logFile, output.c_str());
}

void Logger::print_to_log(const char* logFile, std::string text)
{
	//initialise ofstream
	std::ofstream outputStream(logFile, std::ios::app);

	//write to log file
	outputStream << text;

	outputStream.close();
}