cmake_minimum_required(VERSION 3.12)
project(controller)

set(CMAKE_CXX_STANDARD 17)

add_executable(controller main.cpp controller.cpp controller.h light_element.cpp light_element.h nw_toolkit.cpp input.cpp input.h input_analog.cpp input_analog.h input_digital.cpp input_digital.h effects/fire.cpp effects/fire.h)