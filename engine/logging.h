#pragma once

#include <stdarg.h>
#include <string>
#include <cstdio>
#include <vector>

class Log {
private:
	enum LOG_LEVELS {
		LOG_DEBUG = 0,
		LOG_INFO = 1,
		LOG_WARN = 2,
		LOG_ERROR = 3,
		LOG_FATAL = 4,
	};

	// Max buffer size in bytes
	static constexpr int BUFFER_SIZE = 1024;

	// Sizes of log level strings
	static constexpr int log_level_string_size[] = {
		7, // [DEBUG]
		6, // [INFO]
		6, // [WARN]
		7, // [ERROR]
		7  // [FATAL]
	};

	static void output_log(const int log_level, const char *buffer)
	{
		const std::vector<std::string> log_level_string = {
			"[DEBUG]",
			"[INFO]",
			"[WARN]",
			"[ERROR]",
			"[FATAL]"
		};

		char output[BUFFER_SIZE];
		std::snprintf(output, BUFFER_SIZE + log_level_string_size[log_level] + 2,
				"%s: %s\n", log_level_string[log_level].c_str(), buffer);

		std::printf("%s", output);
		// TODO: Save logs to a file
	}

public:
	/*
	 * There are 5 different logging levels:
	 * DEBUG, INFO, WARN, ERROR, FATAL
	 * 
	 * Their uses are... obvious.
	 */

	static void DEBUG(const char *format, ...)
	{
		char buffer[BUFFER_SIZE];
		va_list arg;

		memset(buffer, 0, BUFFER_SIZE);
		va_start(arg, format);
		vsnprintf(buffer, BUFFER_SIZE, format, arg);
		output_log(LOG_DEBUG, buffer);
		va_end(arg);
	}

	static void INFO(char *format, ...)
	{
		char buffer[BUFFER_SIZE];
		va_list arg;

		memset(buffer, 0, BUFFER_SIZE);
		va_start(arg, format);
		vsnprintf(buffer, BUFFER_SIZE, format, arg);
		output_log(LOG_INFO, buffer);
		va_end(arg);
	}

	static void WARN(char *format, ...)
	{
		char buffer[BUFFER_SIZE];
		va_list arg;

		memset(buffer, 0, BUFFER_SIZE);
		va_start(arg, format);
		vsnprintf(buffer, BUFFER_SIZE, format, arg);
		output_log(LOG_WARN, buffer);
		va_end(arg);
	}

	static void ERROR(char *format, ...)
	{
		char buffer[BUFFER_SIZE];
		va_list arg;

		memset(buffer, 0, BUFFER_SIZE);
		va_start(arg, format);
		vsnprintf(buffer, BUFFER_SIZE, format, arg);
		output_log(LOG_ERROR, buffer);
		va_end(arg);
	}

	static void FATAL(char *format, ...)
	{
		char buffer[BUFFER_SIZE];
		va_list arg;

		memset(buffer, 0, BUFFER_SIZE);
		va_start(arg, format);
		vsnprintf(buffer, BUFFER_SIZE, format, arg);
		output_log(LOG_DEBUG, buffer);
		va_end(arg);
	}
};