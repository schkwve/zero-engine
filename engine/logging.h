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
	static std::mutex mtx_logging;

public:
	template<typename... Args>
	static void TRACE(const char *fmt, Args... args)
	{
#ifdef __DEBUG__
		printf("[trace]: %s\n", fmt, args...);
#endif
	}

	template<typename... Args>
	static void DEBUG(const char *fmt, Args... args)
	{
#ifdef __DEBUG__
		printf("[debug]: %s\n", fmt, args...);
#endif
	}

	template<typename... Args>
	static void INFO(const char *fmt, Args... args)
	{
		printf("[info]: %s\n", fmt, args...);
	}

	template<typename... Args>
	static void WARN(const char *fmt, Args... args)
	{
		printf("[warn]: %s\n", fmt, args...);
	}

	template<typename... Args>
	static void ERROR(const char *fmt, Args... args)
	{
		printf("[error]: %s\n", fmt, args...);
	}

	template<typename... Args>
	static void FATAL(const char *fmt, Args... args)
	{
		printf("[fatal]: %s\n", fmt, args...);
	}
};
