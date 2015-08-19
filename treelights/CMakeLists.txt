cmake_minimum_required(VERSION 3.2)

project(treelights)

include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoteensy/cores/teensy3")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoteensy/cores/teensy3/avr")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoteensy/cores/teensy3/util")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/include")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-gccarmnoneeabi/lib/gcc/arm-none-eabi/4.8.3/include")

macro(import_arduino_library LIB_NAME)
    # Check if we can find the library.

    # Add it to the include path.
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/${LIB_NAME}")


    file(GLOB_RECURSE "${LIB_NAME}_SRC"
		 "${CMAKE_CURRENT_SOURCE_DIR}/.pioenvs/teensy31/${LIB_NAME}/*.h"
		 "${CMAKE_CURRENT_SOURCE_DIR}/.pioenvs/teensy31/${LIB_NAME}/*.c"
		 "${CMAKE_CURRENT_SOURCE_DIR}/.pioenvs/teensy31/${LIB_NAME}/*.cpp"
    )

    add_library(${LIB_NAME}
            SHARED
            "${${LIB_NAME}_SRC}"
    )

    set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
	
endmacro(import_arduino_library)

# FastLED
import_arduino_library(FastLED)
import_arduino_library(OctoWS2811)
import_arduino_library(FrameworkArduino)
import_arduino_library(DmxReceiver)

file(GLOB_RECURSE
		treelights_SRC
		src/*.c
		src/*.cpp
		src/*.h
)

add_library(treelights SHARED ${treelights_SRC})


add_definitions(-DF_CPU=72000000L)
add_definitions(-DUSB_SERIAL)
add_definitions(-DLAYOUT_US_ENGLISH)
add_definitions(-D__MK20DX256__)
add_definitions(-DARDUINO=10600)
add_definitions(-DTEENSYDUINO=124)
add_definitions(-DPLATFORMIO=020202)

set(CMAKE_CXX_FLAGS "-std=c++14")

