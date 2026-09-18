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

void test_motor_accelerates_towards_target()
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

    motor.update(0.1f);

    const MotorState& state = motor.getState();

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        2.5f,
        state.velocity);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.25f,
        state.position);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        25.0f,
        state.acceleration);

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorDirection::Forward),
        static_cast<int>(state.direction));

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorMode::Moving),
        static_cast<int>(state.mode));
}

void test_motor_reaches_target_and_stops()
{
    MotorController motor;

    motor.initialize();

    MotionProfile profile;

    profile.targetPosition = 10.0f;
    profile.maxVelocity = 50.0f;
    profile.maxAcceleration = 25.0f;
    profile.maxDeceleration = 25.0f;
    profile.direction = MotionDirection::Forward;

    motor.setTarget(profile);

    for (int i = 0; i < 100; ++i)
    {
        motor.update(0.1f);
    }

    const MotorState& state = motor.getState();

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        10.0f,
        state.position);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.velocity);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.acceleration);

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorDirection::Stopped),
        static_cast<int>(state.direction));

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorMode::Ready),
        static_cast<int>(state.mode));
}

void test_motor_controlled_stop_decelerates_to_idle()
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

    // Build up some forward velocity.
    motor.update(0.1f);
    motor.update(0.1f);
    motor.update(0.1f);

    TEST_ASSERT_TRUE(motor.getState().velocity > 0.0f);

    motor.stop();

    // Allow the controller to decelerate to zero.
    for (int i = 0; i < 100; ++i)
    {
        motor.update(0.1f);
    }

    const MotorState& state = motor.getState();

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.velocity);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.acceleration);

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorDirection::Stopped),
        static_cast<int>(state.direction));

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorMode::Idle),
        static_cast<int>(state.mode));
}

void test_motor_reverse_motion_reaches_target_and_stops()
{
    MotorController motor;

    motor.initialize();

    MotionProfile profile;

    profile.targetPosition = -10.0f;
    profile.maxVelocity = 50.0f;
    profile.maxAcceleration = 25.0f;
    profile.maxDeceleration = 25.0f;
    profile.direction = MotionDirection::Reverse;

    motor.setTarget(profile);

    for (int i = 0; i < 100; ++i)
    {
        motor.update(0.1f);
    }

    const MotorState& state = motor.getState();

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        -10.0f,
        state.position);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.velocity);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.acceleration);

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorDirection::Stopped),
        static_cast<int>(state.direction));

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorMode::Ready),
        static_cast<int>(state.mode));
}

void test_motor_update_with_zero_delta_time_does_nothing()
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

    motor.update(0.0f);

    const MotorState& state = motor.getState();

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.position);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.velocity);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.acceleration);

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorMode::Ready),
        static_cast<int>(state.mode));
}

void test_motor_update_with_negative_delta_time_does_nothing()
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

    motor.update(-0.1f);

    const MotorState& state = motor.getState();

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.position);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.velocity);

    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        0.0f,
        state.acceleration);

    TEST_ASSERT_EQUAL(
        static_cast<int>(MotorMode::Ready),
        static_cast<int>(state.mode));
}

void setup()
{
    delay(1000);

    UNITY_BEGIN();

    RUN_TEST(test_motor_initializes_to_idle);
    RUN_TEST(test_valid_profile_enters_ready_state);
    RUN_TEST(test_invalid_profile_enters_fault_state);
    RUN_TEST(test_motor_accelerates_towards_target);
    RUN_TEST(test_motor_reaches_target_and_stops);
    RUN_TEST(test_motor_controlled_stop_decelerates_to_idle);
    RUN_TEST(test_motor_reverse_motion_reaches_target_and_stops);
    RUN_TEST(test_motor_update_with_zero_delta_time_does_nothing);
    RUN_TEST(test_motor_update_with_negative_delta_time_does_nothing);

    UNITY_END();
}

void loop()
{
}