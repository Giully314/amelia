# Overview
In a OS context, we need to provide a way to run multiple processes (not necessarily 
at the time time). To do so, a scheduler must orchestrate which process run at
a certain time and provide a context switch between processes. The context switch
must be done respecting some rules defined by the [ARM call procedure convention](https://developer.arm.com/documentation/102374/0102/Procedure-Call-Standard). 
During a context switch, the task calls a function `cpu_switch_to` so from the 
perspective of the process we are doing a function call. 
For SIMD and FP registers (they are shared) check [this](https://stackoverflow.com/questions/261419/what-registers-to-save-in-the-arm-c-calling-convention). 
