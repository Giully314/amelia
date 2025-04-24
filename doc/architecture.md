# Overview
This file is a specification for the software architecture, describing the role of 
each package and its level in terms of [levelization design](https://youtu.be/QjFpKJ8Xx78?si=yR0F_oxvZKFGrI0v).  
Levels indicate that something at level n depends on level n-1. So for a bottom up
approach to the repo, you can start to explore the code at level 0.  
For a logical flow exploration, check the diagram flow.  
A note on assembly glue code: there are some functions which are declared
as extern C. This is done for linking and naming convention to facilitate 
assembly interops. These functions should be used only in the low level context
and the C++ interface should be preferred to access the OS functionalities.

# Level 0
hardware: low level functions for accessing hardware.
memory: low level functions for memory management and allocators.
arm: architecture dependent values.

# Level 1
peripherals: hardware devices.

# Level 2
kernel: high level operating system services.