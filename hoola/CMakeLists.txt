cmake_minimum_required(VERSION 3.2)
project(camp)
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoteensy/cores/teensy3")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoteensy/cores/teensy3/avr")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoteensy/cores/teensy3/util")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/include")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-gccarmnoneeabi/lib/gcc/arm-none-eabi/4.8.3/include")

macro(import_arduino_library LIB_NAME)
    # Check if we can find the library.

    # Add it to the include path.
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib/${LIB_NAME}")

add_library(${LIB_NAME} SHARED ${CMAKE_CURRENT_SOURCE_DIR}/lib/${LIB_NAME}/${LIB_NAME}.h ${CMAKE_CURRENT_SOURCE_DIR}/lib/${LIB_NAME}/${LIB_NAME}.cpp)
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE C++)

#    # Mark source files to be built along with the sketch code.
#    file(GLOB SOURCES_CPP ABSOLUTE "${LIB_DIR}" "${LIB_DIR}/*.cpp")
#    foreach(SOURCE_CPP ${SOURCES_CPP})
#        set(TEENSY_LIB_SOURCES ${TEENSY_LIB_SOURCES} ${SOURCE_CPP})
#    endforeach(SOURCE_CPP ${SOURCES_CPP})
#    file(GLOB SOURCES_C ABSOLUTE "${LIB_DIR}" "${LIB_DIR}/*.c")
#    foreach(SOURCE_C ${SOURCES_C})
#        set(TEENSY_LIB_SOURCES ${TEENSY_LIB_SOURCES} ${SOURCE_C})
#    endforeach(SOURCE_C ${SOURCES_C})
endmacro(import_arduino_library)

# FastLED
import_arduino_library(FastLED)
import_arduino_library(burnutils)
import_arduino_library(IRremote)
import_arduino_library(Adafruit_NECremote)
import_arduino_library(FastIR)


add_definitions(-DF_CPU=72000000L)
add_definitions(-DUSB_SERIAL)
add_definitions(-DLAYOUT_US_ENGLISH)
add_definitions(-D__MK20DX256__)
add_definitions(-DARDUINO=10600)
add_definitions(-DTEENSYDUINO=124)
add_definitions(-DPLATFORMIO=020202)

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND platformio -f run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND platformio -f run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND platformio -f run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set(${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)