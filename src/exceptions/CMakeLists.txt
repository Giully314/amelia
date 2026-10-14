add_library(amelia_exceptions)

target_sources(amelia_exceptions
    PRIVATE 
        ameliaexceptions_irq.S 
        ameliaexceptions_irq.cpp 
    
    PUBLIC FILE_SET CXX_MODULES 
    FILES 
        ameliaexceptions_irq.cppm 
        ameliaexceptions_gic_regs.cppm
)

target_link_libraries(amelia_exceptions PRIVATE amelia_print amelia_src)