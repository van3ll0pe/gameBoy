cmake_minimum_required(VERSION 3.0)

project(GAMEBOY CXX)


include_directories(${CMAKE_SOURCE_DIR}/include)

add_definitions(-DDEBUG_INFO_CPU)

set(FLAGS "-g -Wall")
set(SRC_cpu src/cpu/addressing_mode.cpp
                src/cpu/cpu.cpp
                src/cpu/flags.cpp
                src/cpu/interrupts.cpp
                src/cpu/opcode_arithmetic_8b.cpp
                src/cpu/opcode_arithmetic_16b.cpp
                src/cpu/opcode_bit.cpp
                src/cpu/opcode_ctrl.cpp
                src/cpu/opcode_jump.cpp
                src/cpu/opcode_load_8b.cpp
                src/cpu/opcode_load_16b.cpp
                src/cpu/opcode_rotate.cpp
                src/cpu/stack.cpp
                src/cpu/debug.cpp)

set(SRC_bus src/bus/bus.cpp)
set(SRC_component src/component/component.cpp)
set(SRC_gameboy src/gameboy/gameboy.cpp)

add_executable(GameBoy src/main.cpp ${SRC_cpu} ${SRC_bus} ${SRC_component} ${SRC_gameboy})