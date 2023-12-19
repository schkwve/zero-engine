#pragma once

#include <stdio.h>
#include <mutex>

/*
 * There are 6 different logging levels:
 * TRACE, DEBUG, INFO, WARN, ERROR, FATAL
 * 
 * Their uses are... obvious.
 */

class Log {
private:
	static std::mutex lock_logging;

	// Not yet used
	static FILE *f_logfile;

public:
	template<typename... Args>
	static void TRACE(const char *fmt, Args... args)
	{
#ifdef __DEBUG__
		log("TRACE", fmt, args...);
#endif
	}

	template<typename... Args>
	static void DEBUG(const char *fmt, Args... args)
	{
#ifdef __DEBUG__
		log("DEBUG", fmt, args...);
#endif
	}

	template<typename... Args>
	static void INFO(const char *fmt, Args... args)
	{
		log("INFO", fmt, args...);
	}

	template<typename... Args>
	static void WARN(const char *fmt, Args... args)
	{
		log("WARN", fmt, args...);
	}

	template<typename... Args>
	static void ERROR(const char *fmt, Args... args)
	{
		log("ERROR", fmt, args...);
	}

	template<typename... Args>
	static void FATAL(const char *fmt, Args... args)
	{
		log("FATAL", fmt, args...);
	}

private:
	template<typename... Args>
	static void log(const char *log_level_str, const char *fmt, Args... args)
	{
		std::time_t cur_time = std::time(0);
		std::tm *timestamp = std::localtime(&cur_time);
		char buffer[80];
		strftime(buffer, 80, "%c", timestamp);


		std::scoped_lock lock(lock_logging);
		printf("%s | [%s]: %s\n", buffer, log_level_str, fmt, args...);
	}
};

std::mutex Log::lock_logging;
FILE *f_logfile = NULL;