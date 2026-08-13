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
    constexpr unsigned long MOTOR_REPORT_INTERVAL = 250;
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
    static unsigned long lastMotorUpdate = 0;
    static unsigned long lastMotorReport = 0;

    const unsigned long now = millis();
    

    if (lastMotorUpdate == 0)
    {
        lastMotorUpdate = now;
    }
    else
    {
        const float deltaTime =
            static_cast<float>(now - lastMotorUpdate) / 1000.0f;

        lastMotorUpdate = now;

        motorController.update(deltaTime);

        if (now - lastMotorReport >= MOTOR_REPORT_INTERVAL)
        {
            lastMotorReport = now;

            const MotorState& state = motorController.getState();

            Serial.printf(
                "[MOTOR] dt=%.3f | Position=%.2f | Target=%.2f | Velocity=%.2f | Acceleration=%.2f | Direction=%d\n",
                deltaTime,
                state.position,
                state.targetPosition,
                state.velocity,
                state.acceleration,
                static_cast<int>(state.direction));
        }
    }

    if (now - lastDiagnostics >= DIAGNOSTICS_INTERVAL)
    {
        lastDiagnostics = now;

        Diagnostics::printRuntimeStatus();
    }
}

} // namespace Smart360
