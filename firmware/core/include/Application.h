#pragma once

#include "motor/MotorController.h"

namespace Smart360
{
class Application
{
public:
    void begin();
    void update();

private:
    MotorController motorController;
};

}
