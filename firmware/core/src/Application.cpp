#include <Arduino.h>

#include "Application.h"
#include "Config.h"
#include "services/BootBanner.h"
#include "services/Logger.h"

namespace Smart360
{
    void Application::begin()
    {
        Serial.begin(Config::SERIAL_BAUD);

        delay(1500);

        BootBanner::print();

        Logger::info("Initialising services...");

        Logger::info("Logger initialised");
        Logger::info("Configuration loaded");
        Logger::info("Diagnostics initialised");

        Logger::info("System Ready.");
    }

    void Application::update()
    {
    }
}