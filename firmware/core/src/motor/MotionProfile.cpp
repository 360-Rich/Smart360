#include "motor/MotionProfile.h"

namespace Smart360
{

bool MotionProfile::validate() const
{
    if (maxVelocity <= 0.0f)
    {
        return false;
    }

    if (maxAcceleration <= 0.0f)
    {
        return false;
    }

    if (maxDeceleration <= 0.0f)
    {
        return false;
    }

    return true;
}

} // namespace Smart360
