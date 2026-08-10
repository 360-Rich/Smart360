#include <Arduino.h>

#include "services/Logger.h"

namespace Smart360
{
    void Logger::info(const String& message)
    {
        Serial.print("[INFO ] ");
        Serial.println(message);
    }

    void Logger::warning(const String& message)
    {
        Serial.print("[WARN ] ");
        Serial.println(message);
    }

    void Logger::error(const String& message)
    {
        Serial.print("[ERROR] ");
        Serial.println(message);
    }

    void Logger::debug(const String& message)
    {
        Serial.print("[DEBUG] ");
        Serial.println(message);
    }
}