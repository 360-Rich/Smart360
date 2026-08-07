#include "Logger.h"

using namespace Smart360;

void Logger::begin(unsigned long baud)
{
    Serial.begin(baud);

    delay(250);

    Serial.println();
    Serial.println("======================================");
    Serial.println("        Smart360 Controller");
    Serial.println("======================================");
}

void Logger::debug(const String& message)
{
    write(LogLevel::Debug, message);
}

void Logger::info(const String& message)
{
    write(LogLevel::Info, message);
}

void Logger::warning(const String& message)
{
    write(LogLevel::Warning, message);
}

void Logger::error(const String& message)
{
    write(LogLevel::Error, message);
}

void Logger::write(
    LogLevel level,
    const String& message)
{
    Serial.printf(
        "[%08lu] [%s] %s\n",
        millis(),
        levelToString(level),
        message.c_str());
}

const char* Logger::levelToString(LogLevel level)
{
    switch(level)
    {
        case LogLevel::Debug:
            return "DEBUG";

        case LogLevel::Info:
            return "INFO";

        case LogLevel::Warning:
            return "WARN";

        case LogLevel::Error:
            return "ERROR";

        default:
            return "UNKNOWN";
    }
}