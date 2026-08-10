#pragma once

#include <Arduino.h>

namespace Smart360
{
    class Logger
    {
    public:
        static void info(const String& message);
        static void warning(const String& message);
        static void error(const String& message);
        static void debug(const String& message);
    };
}