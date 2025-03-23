# Overview
The kernel init block is responsible to initialize basic hardware resources 
like the mini_uart (or uart), printf debugging function and setup everything 
related to interrupts (vector table, enable the controller, initialize each
interrupt device).