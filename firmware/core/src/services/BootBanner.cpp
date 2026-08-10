#include <Arduino.h>

#include "services/BootBanner.h"
#include "Version.h"

using namespace Smart360;

void BootBanner::print()
{
    Serial.println();
    Serial.println("=================================================");
    Serial.println("               Smart360 Controller");
    Serial.println("=================================================");
    Serial.println();

Serial.print("Firmware : ");
Serial.println(Version::getVersionString());

    Serial.printf(
        "Chip     : %s\n",
        ESP.getChipModel());

    Serial.printf(
        "CPU      : %u MHz\n",
        ESP.getCpuFreqMHz());

    Serial.printf(
        "Flash    : %u MB\n",
        ESP.getFlashChipSize() / (1024 * 1024));

    Serial.printf(
        "PSRAM    : %u MB\n",
        ESP.getPsramSize() / (1024 * 1024));

    Serial.printf(
        "Heap     : %u KB\n",
        ESP.getFreeHeap() / 1024);

    Serial.println();
}