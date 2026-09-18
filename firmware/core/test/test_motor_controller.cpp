#include <Arduino.h>
#include <unity.h>

#include "motor/MotorController.h"
#include "motor/MotionProfile.h"

using namespace Smart360;

void setUp()
{
}

void tearDown()
{
}

void test_motor_initializes_to_idle()
{
    MotorController motor;

    motor.initialize();

    const MotorState& state = motor.getState();

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorMode::Idle),
        static_cast<int>(state.mode));

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorDirection::Stopped),
        static_cast<int>(state.direction));

    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, state.position);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, state.velocity);
}

void test_valid_profile_enters_ready_state()
{
    MotorController motor;

    motor.initialize();

    MotionProfile profile;

    profile.targetPosition = 100.0f;
    profile.maxVelocity = 50.0f;
    profile.maxAcceleration = 25.0f;
    profile.maxDeceleration = 25.0f;
    profile.direction = MotionDirection::Forward;

    motor.setTarget(profile);

    const MotorState& state = motor.getState();

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorMode::Ready),
        static_cast<int>(state.mode));

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        100.0f,
        state.targetPosition);
}

void test_invalid_profile_enters_fault_state()
{
    MotorController motor;

    motor.initialize();

    MotionProfile profile;

    profile.targetPosition = 100.0f;
    profile.maxVelocity = 0.0f;
    profile.maxAcceleration = 25.0f;
    profile.maxDeceleration = 25.0f;
    profile.direction = MotionDirection::Forward;

    motor.setTarget(profile);

    const MotorState& state = motor.getState();

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorMode::Fault),
        static_cast<int>(state.mode));
}


void setup()
{
    delay(1000);

    UNITY_BEGIN();

    RUN_TEST(test_motor_initializes_to_idle);
    RUN_TEST(test_valid_profile_enters_ready_state);
    RUN_TEST(test_invalid_profile_enters_fault_state);

    UNITY_END();
}

void loop()
{
}
