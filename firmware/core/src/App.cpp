#include <Arduino.h>

#include "App.h"
#include "Config.h"
#include "Version.h"

void App::begin()
{
    Serial.begin(Config::SERIAL_BAUD);

    while (!Serial)
    {
        delay(10);
    }

    Serial.println();
    Serial.println("========================================");
    Serial.println(Config::APPLICATION_NAME);
    Serial.print("Firmware : ");
    Serial.println(Version::FIRMWARE);
    Serial.print("Board    : ");
    Serial.println(Config::BOARD_NAME);
    Serial.print("Built    : ");
    Serial.print(Version::BUILD_DATE);
    Serial.print(" ");
    Serial.println(Version::BUILD_TIME);
    Serial.println("========================================");
    Serial.println();
}

void App::update()
{
    // Reserved for future services.
}