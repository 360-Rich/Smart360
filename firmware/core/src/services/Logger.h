#pragma once

#include <Arduino.h>

namespace Smart360
{
    enum class LogLevel : uint8_t
    {
        Debug,
        Info,
        Warning,
        Error
    };

    class Logger
    {
    public:

        static void begin(unsigned long baud = 115200);

        static void debug(const String& message);

        static void info(const String& message);

        static void warning(const String& message);

        static void error(const String& message);

    private:

        static void write(
            LogLevel level,
            const String& message);

        static const char* levelToString(LogLevel level);
    };
}