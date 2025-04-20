# How to build
Go inside the build directory and type:  
cmake -GNinja -S .. -B Release -D CMAKE_BUILD_TYPE=Release
cmake --build Release 

Clean build:  
cmake --fresh -GNinja -S . -B Release -D CMAKE_BUILD_TYPE=Release  
or for the build: cmake --build Release --clean-first 