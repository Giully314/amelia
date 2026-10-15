add_library(amelia_exceptions)

target_sources(amelia_exceptions
    PRIVATE 
        ameliaexceptions_irq.S 
        ameliaexceptions_irq.cpp 
    
    # PRIVATE FILE_SET private_modules TYPE CXX_MODULES 
    # FILES 
    #     ameliaexceptions_gic_regs.cppm
    
    PUBLIC FILE_SET CXX_MODULES 
    FILES 
    ameliaexceptions_irq.cppm 
    ameliaexceptions_gic.cppm
    ameliaexceptions_gic_regs.cppm
)

target_link_libraries(amelia_exceptions PRIVATE amelia_print amelia_src)