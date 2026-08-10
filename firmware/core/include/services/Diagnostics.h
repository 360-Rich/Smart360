#pragma once

#include <Arduino.h>

namespace Smart360
{
    class Diagnostics
    {
    public:
        static void printSystemInfo();
        static void printRuntimeStatus();
    };
}