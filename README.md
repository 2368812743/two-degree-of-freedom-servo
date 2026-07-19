# Two Degree of Freedom Servo

STM32F1 two-degree-of-freedom servo control project.

## Repository contents

- `Inc/` and `Src/`: project headers and source files.
- `MDK-ARM/Two_degree_of_freedom_servo.uvprojx`: Keil MDK project file.
- `MDK-ARM/startup_stm32f103xb.s`: startup assembly file.
- `Two_degree_of_freedom_servo.ioc`: STM32CubeMX configuration.

## Ignored files

The STM32 HAL/CMSIS library folders under `Drivers/` are intentionally not committed. Reopen `Two_degree_of_freedom_servo.ioc` in STM32CubeMX and regenerate code to restore them locally.

Keil build outputs such as object files, AXF/HEX files, maps, logs, and debug output directories are also ignored.
# two-degree-of-freedom-servo
二自由度舵机
