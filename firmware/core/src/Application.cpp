#include <Arduino.h>
#include "Application.h"
#include "Config.h"
#include "Version.h"
using namespace Smart360;
void Application::begin(){Serial.begin(Config::SERIAL_BAUD);delay(100);Serial.println("=== Smart360 Core ===");Serial.println(Version::FIRMWARE);} void Application::update(){}
