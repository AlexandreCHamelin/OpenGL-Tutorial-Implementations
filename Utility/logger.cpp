#include "logger.hpp"
#include <time.h>
#include <stdarg.h>

void Logger::restart_log(const char* logFile)
{
	time_t now = time(0); //Get current time
	char date[26];

	ctime_s(date, 26, &(now));

	print_to_log(logFile, "--------------------------\nGL_LOG local time: %s", date);
}

bool Logger::print_to_log(const char* logFile, const char* text, ...)
{
	va_list argptr;
	errno_t err;

	FILE* file;
	err = fopen_s(&file, logFile, "a");
	if (!file)
	{
		fprintf(stderr, "ERROR: could not open GL_LOG_FILE %s file for appending\ n", logFile);
		return false;
	}

	va_start(argptr, text);
	vfprintf(file, text, argptr);
	va_end(argptr);
	fclose(file);
	return true;
}
