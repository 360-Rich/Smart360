#include <Arduino.h>

#include "Application.h"
#include "Config.h"
#include "services/BootBanner.h"
#include "services/Logger.h"
#include "services/Diagnostics.h"

namespace
{
    unsigned long lastDiagnostics = 0;
    constexpr unsigned long DIAGNOSTICS_INTERVAL = 30000;
}

namespace Smart360
{
    void Application::begin()
    {
        Serial.begin(Config::SERIAL_BAUD);

        delay(1500);

        BootBanner::print();

        Diagnostics::printSystemInfo();

        Logger::info("Initialising services...");

        Logger::info("Logger initialised");
        Logger::info("Configuration loaded");
        Logger::info("Diagnostics initialised");

        Logger::info("System Ready.");
    }

    void Application::update()
    {
        const unsigned long now = millis();

        if (now - lastDiagnostics >= DIAGNOSTICS_INTERVAL)
        {
            lastDiagnostics = now;

            Diagnostics::printRuntimeStatus();
        }
    }
}