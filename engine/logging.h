#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

/*
 * There are 6 different logging levels:
 * TRACE, DEBUG, INFO, WARN, ERROR, FATAL
 * 
 * Their uses are... obvious.
 */

#ifdef __DEBUG__
#define TRACE(fmt, ...) log("TRACE", fmt, #__VA_ARGS__)
#define DEBUG(fmt, ...) log("DEBUG", fmt, #__VA_ARGS__)
#else
#define TRACE(fmt, ...)
#define DEBUG(fmt, ...)
#endif
#define INFO(fmt, ...) log("INFO", fmt, #__VA_ARGS__)
#define WARN(fmt, ...) log("WARN", fmt, #__VA_ARGS__)
#define ERROR(fmt, ...) log("ERROR", fmt, #__VA_ARGS__)
#define FATAL(fmt, ...) log("FATAL", fmt, #__VA_ARGS__)

static void log(const char *log_level_str, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	time_t cur_time = time(NULL);
	struct tm *timestamp = localtime(&cur_time);
	char buffer[80];
	strftime(buffer, 80, "%c", timestamp);
	fprintf(stderr, "%s | [%s]: %s\n", buffer, log_level_str, fmt, args);

	va_end(args);
}
