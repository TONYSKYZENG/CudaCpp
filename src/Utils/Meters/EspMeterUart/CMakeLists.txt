if (NOT DEFINED ENV{METER_UART_NAME})
    set(ENV{METER_UART_NAME} "/dev/ttyUSB0")
    message(STATUS "auto set UART= " $ENV{METER_UART_NAME})
else ()
    message(STATUS "you have set UART= " $ENV{METER_UART_NAME})
endif ()
set(METER_UART_NAME "$ENV{METER_UART_NAME}")
configure_file (
        "EspMeterUart_config.h.in"
        "${PROJECT_BINARY_DIR}/configs/EspMeterUart/EspMeterUart_config.h"
)
include_directories(${PROJECT_SOURCE_DIR}/include/Utils/Meters/$ENV{METER})
include_directories("${PROJECT_BINARY_DIR}")
aux_source_directory(. ESPMETERUART_LIST)
add_sources(${ESPMETERUART_LIST})
