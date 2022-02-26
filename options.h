#pragma once
#include <Arduino.h>

// car define
#define CAR_LENGTH 114.75
#define CAR_WIDTH 177.0
// diameter 40 plus 3mm rubber
#define CAR_WHEEL_DIAMETER 43.0
// when distance ahead less than this value then change direction of the car
#define DISTANCE_TO_TURN_CAR 150
// measure distance every moving after DISTANCE_TO_OPEN_EYE mm
#define DISTANCE_TO_OPEN_EYE 20

// ===== motor configuration =====
#define STEP_PER_REVERLUTION (512)
#define HALF_REVOLUTION (512 / 2)
#define QUATER_REVOLUTION (512 / 4)
// this will be around 1 to 15, any other value almost not working
#define MOTOR_MAX_RPM 8
#define LATCH_PIN 12
#define CLOCK_PIN 13
#define DATA_PIN 11
#define POWER_SENSOR_PIN 9
// #define POWER_EYE_PIN 8

// ===== eye setup =====
// speed of sound at 25°C, meter per second
#define SOUND_SPEED 346.13
// time minimum between each trigger, limited by the hardware
#define HARDWARE_MIN_DELAY 50
// max distance to measure in mm, this will effect to time to wait echo pin, we do not need to measure what ever distance longer than this value
#define MAX_DISTANCE_TO_MEASURE 1000
