# Convert the markers emitted by ameliaentry_asm_offsets.cpp into a header of #define.
# Usage: cmake -DINPUT=<file.s> -DOUTPUT=<file.h> -P gen_asm_offsets.cmake

file(STRINGS "${INPUT}" lines REGEX "->[A-Za-z_0-9]+ ")

set(content "// Generated file, do not edit.\n#pragma once\n\n")
foreach(line IN LISTS lines)
    # The value can be printed with a '#' (aarch64) or '$' (x86) prefix.
    if(line MATCHES "->([A-Za-z_0-9]+) [#$]?(-?[0-9]+)")
        string(APPEND content "#define ${CMAKE_MATCH_1} ${CMAKE_MATCH_2}\n")
    endif()
endforeach()

file(WRITE "${OUTPUT}" "${content}")
