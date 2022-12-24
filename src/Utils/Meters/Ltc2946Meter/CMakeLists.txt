if (NOT DEFINED ENV{METER_I2C_NAME})
    set(ENV{METER_I2C_NAME} "/dev/i2c-0")
    message(STATUS "auto set I2C= " $ENV{METER_I2C_NAME})
else ()
    message(STATUS "you have set I2C= " $ENV{METER_I2C_NAME})
endif ()
set(METER_I2C_NAME "$ENV{METER_I2C_NAME}")
configure_file (
        "Ltc2946Meter_config.h.in"
        "${PROJECT_BINARY_DIR}/configs/Ltc2946Meter/Ltc2946Meter_config.h"
)
include_directories("${PROJECT_BINARY_DIR}")
aux_source_directory(. LTC2946_LIST)
add_sources(${LTC2946_LIST})

