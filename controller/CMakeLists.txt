cmake_minimum_required(VERSION 3.12)
project(controller)

set(CMAKE_CXX_STANDARD 17)

add_executable(controller controller.cpp controller.hpp light_element.cpp light_element.hpp nw_toolkit.cpp input.cpp input.hpp input_analog.cpp input_analog.hpp input_digital.cpp input_digital.hpp effect.cpp effect.hpp arduino_std_definitions.h e_fire.hpp nw_toolkit.h e_fire.cpp effect_inclusions.h e_bouncing_balls.cpp e_bouncing_balls.hpp e_rainbow_shift.cpp e_rainbow_shift.hpp nw_toolkit.cpp lib/Arduino.h e_static_color.cpp e_static_color.hpp e_meteor.cpp e_meteor.hpp)