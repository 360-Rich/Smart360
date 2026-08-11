#include <Arduino.h>

#include "Application.h"
#include "Config.h"
#include "services/BootBanner.h"
#include "services/Logger.h"
#include "services/Diagnostics.h"
#include "motor/MotorController.h"
#include "motor/MotionProfile.h"

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

    motorController.initialize();
    Logger::info("Motor controller initialised");

    MotionProfile testProfile;

    testProfile.targetPosition = 100.0f;
    testProfile.maxVelocity = 50.0f;
    testProfile.maxAcceleration = 25.0f;
    testProfile.maxDeceleration = 25.0f;
    testProfile.direction = MotionDirection::Forward;

    motorController.setTarget(testProfile);

    Logger::info("System Ready.");
}

void Application::update()
{
    static unsigned long lastMotorTest = 0;

    const unsigned long now = millis();

    if (now - lastMotorTest >= 1000)
    {
        lastMotorTest = now;

        motorController.update(1.0f);

        const MotorState& state = motorController.getState();

        Serial.printf(
            "[MOTOR] Position=%.2f | Target=%.2f | Velocity=%.2f | Direction=%d\n",
            state.position,
            state.targetPosition,
            state.velocity,
            static_cast<int>(state.direction));
    }

    if (now - lastDiagnostics >= DIAGNOSTICS_INTERVAL)
    {
        lastDiagnostics = now;

        Diagnostics::printRuntimeStatus();
    }
}

} // namespace Smart360