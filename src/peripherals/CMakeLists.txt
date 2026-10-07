add_library(amelia_peripherals)

target_sources(amelia_peripherals 
    PUBLIC FILE_SET CXX_MODULES 
    FILES ameliaperipherals_aux.cppm ameliaperipherals_gpio.cppm ameliaperipherals_regs.cppm ameliaperipherals_uart1.cppm)


target_link_libraries(amelia_peripherals PRIVATE amelia_src amelia_memory)

