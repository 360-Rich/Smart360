#pragma once

#include <Arduino.h>

namespace Smart360
{
    namespace Version
    {
        constexpr char Name[] = "Smart360";

        constexpr uint8_t Major = 0;
        constexpr uint8_t Minor = 1;
        constexpr uint8_t Patch = 0;

        constexpr char Stage[] = "alpha1";

        String getVersionString();
    }
}