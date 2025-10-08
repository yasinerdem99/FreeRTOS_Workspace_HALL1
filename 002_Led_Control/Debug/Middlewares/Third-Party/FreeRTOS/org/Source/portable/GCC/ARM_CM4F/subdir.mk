################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/%.o Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/%.su Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/%.cyclo: ../Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/%.c Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/stj.yerdem/Desktop/FreeRTOS_Workspace_HALL1/002_Led_Control/Middlewares/Third-Party/FreeRTOS/org/Source/include" -I"C:/Users/stj.yerdem/Desktop/FreeRTOS_Workspace_HALL1/002_Led_Control/FreeRTOSConfig" -I"C:/Users/stj.yerdem/Desktop/FreeRTOS_Workspace_HALL1/002_Led_Control/Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third-2d-Party-2f-FreeRTOS-2f-org-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

clean-Middlewares-2f-Third-2d-Party-2f-FreeRTOS-2f-org-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/port.cyclo ./Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/port.d ./Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/port.o ./Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F/port.su

.PHONY: clean-Middlewares-2f-Third-2d-Party-2f-FreeRTOS-2f-org-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

