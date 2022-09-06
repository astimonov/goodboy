cmake_minimum_required(VERSION 3.16)

project(Goodboy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EMULATOR_SRC
    src/emulator/cpu.cpp
    src/emulator/cpu.hpp
    src/emulator/memory_controller.cpp
    src/emulator/memory_controller.hpp
    src/emulator/memory_interface.hpp
    src/emulator/random_access_memory.hpp
    src/emulator/register.hpp
    src/emulator/stub_memory.hpp
    src/emulator/types.hpp
)

add_library(emulator STATIC ${EMULATOR_SRC})

set(MAIN_EXECUTABLE_SRC
    src/executable/main.cpp
)

add_executable(goodboy ${MAIN_EXECUTABLE_SRC})
target_link_libraries(goodboy emulator)
