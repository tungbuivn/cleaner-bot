cmake_minimum_required(VERSION 3.21)
project(cleaner_bot)

set(CMAKE_CXX_STANDARD 14)

# add extra include directories
include_directories(/usr/local/include)
include_directories(C:\\Users\\tungbt\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\avr\\1.8.4\\cores\\arduino)
include_directories(C:\\Users\\tungbt\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\avr\\1.8.4\\variants\\eightanaloginputs)
include_directories(c:\\users\\tungbt\\appdata\\local\\arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7\\lib\\gcc\\avr\\7.3.0\\include)
include_directories(c:\\users\\tungbt\\appdata\\local\\arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7\\lib\\gcc\\avr\\7.3.0\\include-fixed)
include_directories(c:\\users\\tungbt\\appdata\\local\\arduino15\\packages\\arduino\\tools\\avr-gcc\\7.3.0-atmel3.6.1-arduino7\\avr\\include)

# add extra lib directories
#link_directories(/usr/local/lib)
include_directories(.)

add_executable(cleaner_bot
        car.cpp
        car.h
        cleaner-bot.ino
        eye.cpp
        eye.h
        options.h
        sensor.cpp
        sensor.h
        step.cpp
        step.h
        wheel.cpp
        wheel.h)
