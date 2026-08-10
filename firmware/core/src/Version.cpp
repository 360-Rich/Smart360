#include <Arduino.h>

#include "Version.h"

namespace Smart360
{
    namespace Version
    {
        String getVersionString()
        {
            String version;

            version.reserve(32);

            version += Major;
            version += ".";
            version += Minor;
            version += ".";
            version += Patch;
            version += "-";
            version += Stage;

            return version;
        }
    }
}