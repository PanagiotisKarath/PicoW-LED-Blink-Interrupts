cmake_minimum_required(VERSION 3.13)

# Define project's and executable's name
set(PROJECT_NAME led-blinker-irq)
set(EXECUTABLE_NAME blink_irq)

include(pico_sdk_import.cmake)                # Include pico-sdk files - MUST be included first!
project(${PROJECT_NAME} C CXX ASM)            # Required languages (DO NOT remove any of the "C CXX ASM" for the pico-sdk to work)
set(CMAKE_C_STANDARD 11)                      # Define C Standard
set(CMAKE_CXX_STANDARD 17)                    # Define C++ Standard
pico_sdk_init()                               # Actually "initialize" the pico-sdk

# Define project's files
add_executable(${EXECUTABLE_NAME} blink_irq.c)

# Link required libraries (included in the project's files)
target_link_libraries(${EXECUTABLE_NAME} pico_stdlib pico_cyw43_arch_none)

pico_enable_stdio_usb(${EXECUTABLE_NAME} 1)   # Enable USB output
pico_enable_stdio_uart(${EXECUTABLE_NAME} 1)  # Enable UART output
pico_add_extra_outputs(${EXECUTABLE_NAME})    # Also create .map / .bin / .hex / .uf2 / etc files (without this only .elf is created)