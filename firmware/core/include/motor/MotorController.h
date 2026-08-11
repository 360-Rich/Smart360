#pragma once

#include "motor/MotorState.h"
#include "motor/MotionProfile.h"

namespace Smart360
{

class MotorController
{
public:
    void initialize();

    void update(float deltaTime);

    void setTarget(const MotionProfile& profile);

    void stop();

    const MotorState& getState() const;

private:
    MotorState state;
    MotionProfile profile;
};

} // namespace Smart360
