#include <Arduino.h>
#include "services/Logger.h"

using namespace Smart360;

void setup()
{
    Logger::begin();

    Logger::info("System booting...");
    Logger::info("Logger online");
}

void loop()
{
}