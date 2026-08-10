#include <Arduino.h>
#include <esp_system.h>

#include "services/Diagnostics.h"
#include "Version.h"

namespace Smart360
{
    void Diagnostics::printSystemInfo()
    {
        Serial.println();
        Serial.println("System Diagnostics");
        Serial.println("------------------");

        Serial.print("Firmware     : ");
        Serial.println(Version::getVersionString());

        Serial.print("Chip         : ");
        Serial.println(ESP.getChipModel());

        Serial.print("CPU          : ");
        Serial.print(ESP.getCpuFreqMHz());
        Serial.println(" MHz");

        Serial.print("Flash        : ");
        Serial.print(ESP.getFlashChipSize() / (1024 * 1024));
        Serial.println(" MB");

        Serial.print("PSRAM        : ");
        Serial.print(ESP.getPsramSize() / (1024 * 1024));
        Serial.println(" MB");

        Serial.print("Free Heap    : ");
        Serial.print(ESP.getFreeHeap() / 1024);
        Serial.println(" KB");

        Serial.print("Min Free Heap: ");
        Serial.print(ESP.getMinFreeHeap() / 1024);
        Serial.println(" KB");

        Serial.print("SDK          : ");
        Serial.println(ESP.getSdkVersion());

        Serial.print("Reset Reason : ");
        Serial.println(esp_reset_reason());

        Serial.println();
    }

    void Diagnostics::printRuntimeStatus()
    {
        const unsigned long uptimeSeconds = millis() / 1000;

        const unsigned long hours = uptimeSeconds / 3600;
        const unsigned long minutes = (uptimeSeconds % 3600) / 60;
        const unsigned long seconds = uptimeSeconds % 60;

        Serial.print("[DIAG ] Uptime=");
        Serial.printf(
            "%02lu:%02lu:%02lu",
            hours,
            minutes,
            seconds);

        Serial.print(" | Heap=");
        Serial.print(ESP.getFreeHeap() / 1024);
        Serial.print(" KB");

        Serial.print(" | MinHeap=");
        Serial.print(ESP.getMinFreeHeap() / 1024);
        Serial.println(" KB");
    }
}