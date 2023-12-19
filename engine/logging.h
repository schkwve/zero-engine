#pragma once

#include <stdio.h>
#include <mutex>
#include <ctime>

/*
 * There are 6 different logging levels:
 * TRACE, DEBUG, INFO, WARN, ERROR, FATAL
 * 
 * Their uses are... obvious.
 */

class Log {
private:
	std::mutex lock_logging;

	// Not yet used
	FILE *f_logfile;

public:
	template<typename... Args>
	static void TRACE(const char *fmt, Args... args)
	{
#ifdef __DEBUG__
		GetInstance().log("TRACE", fmt, args...);
#endif
	}

	template<typename... Args>
	static void DEBUG(const char *fmt, Args... args)
	{
#ifdef __DEBUG__
		GetInstance().log("DEBUG", fmt, args...);
#endif
	}

	template<typename... Args>
	static void INFO(const char *fmt, Args... args)
	{
		GetInstance().log("INFO", fmt, args...);
	}

	template<typename... Args>
	static void WARN(const char *fmt, Args... args)
	{
		GetInstance().log("WARN", fmt, args...);
	}

	template<typename... Args>
	static void ERROR(const char *fmt, Args... args)
	{
		GetInstance().log("ERROR", fmt, args...);
	}

	template<typename... Args>
	static void FATAL(const char *fmt, Args... args)
	{
		GetInstance().log("FATAL", fmt, args...);
	}

private:

	Log()
	{
	}

	Log(const Log&) = delete;
	Log& operator= (const Log&) = delete;

	~Log()
	{
	}

	static Log& GetInstance()
	{
		static Log logger;
		return logger;
	}

	template<typename... Args>
	void log(const char *log_level_str, const char *fmt, Args... args)
	{
		std::scoped_lock lock(lock_logging);

		std::time_t cur_time = std::time(0);
		std::tm *timestamp = std::localtime(&cur_time);
		char buffer[80];
		strftime(buffer, 80, "%c", timestamp);
		printf("%s | [%s]: %s\n", buffer, log_level_str, fmt, args...);
	}
};