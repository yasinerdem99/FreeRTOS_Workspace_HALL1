################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third-Party/FreeRTOS/org/Source/croutine.c \
../Middlewares/Third-Party/FreeRTOS/org/Source/event_groups.c \
../Middlewares/Third-Party/FreeRTOS/org/Source/list.c \
../Middlewares/Third-Party/FreeRTOS/org/Source/queue.c \
../Middlewares/Third-Party/FreeRTOS/org/Source/stream_buffer.c \
../Middlewares/Third-Party/FreeRTOS/org/Source/tasks.c \
../Middlewares/Third-Party/FreeRTOS/org/Source/timers.c 

OBJS += \
./Middlewares/Third-Party/FreeRTOS/org/Source/croutine.o \
./Middlewares/Third-Party/FreeRTOS/org/Source/event_groups.o \
./Middlewares/Third-Party/FreeRTOS/org/Source/list.o \
./Middlewares/Third-Party/FreeRTOS/org/Source/queue.o \
./Middlewares/Third-Party/FreeRTOS/org/Source/stream_buffer.o \
./Middlewares/Third-Party/FreeRTOS/org/Source/tasks.o \
./Middlewares/Third-Party/FreeRTOS/org/Source/timers.o 

C_DEPS += \
./Middlewares/Third-Party/FreeRTOS/org/Source/croutine.d \
./Middlewares/Third-Party/FreeRTOS/org/Source/event_groups.d \
./Middlewares/Third-Party/FreeRTOS/org/Source/list.d \
./Middlewares/Third-Party/FreeRTOS/org/Source/queue.d \
./Middlewares/Third-Party/FreeRTOS/org/Source/stream_buffer.d \
./Middlewares/Third-Party/FreeRTOS/org/Source/tasks.d \
./Middlewares/Third-Party/FreeRTOS/org/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third-Party/FreeRTOS/org/Source/%.o Middlewares/Third-Party/FreeRTOS/org/Source/%.su Middlewares/Third-Party/FreeRTOS/org/Source/%.cyclo: ../Middlewares/Third-Party/FreeRTOS/org/Source/%.c Middlewares/Third-Party/FreeRTOS/org/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"C:/Users/stj.yerdem/Desktop/FreeRTOS_Workspace_HALL1/002_Led_Control/Middlewares/Third-Party/FreeRTOS/org/Source/include" -I"C:/Users/stj.yerdem/Desktop/FreeRTOS_Workspace_HALL1/002_Led_Control/FreeRTOSConfig" -I"C:/Users/stj.yerdem/Desktop/FreeRTOS_Workspace_HALL1/002_Led_Control/Middlewares/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third-2d-Party-2f-FreeRTOS-2f-org-2f-Source

clean-Middlewares-2f-Third-2d-Party-2f-FreeRTOS-2f-org-2f-Source:
	-$(RM) ./Middlewares/Third-Party/FreeRTOS/org/Source/croutine.cyclo ./Middlewares/Third-Party/FreeRTOS/org/Source/croutine.d ./Middlewares/Third-Party/FreeRTOS/org/Source/croutine.o ./Middlewares/Third-Party/FreeRTOS/org/Source/croutine.su ./Middlewares/Third-Party/FreeRTOS/org/Source/event_groups.cyclo ./Middlewares/Third-Party/FreeRTOS/org/Source/event_groups.d ./Middlewares/Third-Party/FreeRTOS/org/Source/event_groups.o ./Middlewares/Third-Party/FreeRTOS/org/Source/event_groups.su ./Middlewares/Third-Party/FreeRTOS/org/Source/list.cyclo ./Middlewares/Third-Party/FreeRTOS/org/Source/list.d ./Middlewares/Third-Party/FreeRTOS/org/Source/list.o ./Middlewares/Third-Party/FreeRTOS/org/Source/list.su ./Middlewares/Third-Party/FreeRTOS/org/Source/queue.cyclo ./Middlewares/Third-Party/FreeRTOS/org/Source/queue.d ./Middlewares/Third-Party/FreeRTOS/org/Source/queue.o ./Middlewares/Third-Party/FreeRTOS/org/Source/queue.su ./Middlewares/Third-Party/FreeRTOS/org/Source/stream_buffer.cyclo ./Middlewares/Third-Party/FreeRTOS/org/Source/stream_buffer.d ./Middlewares/Third-Party/FreeRTOS/org/Source/stream_buffer.o ./Middlewares/Third-Party/FreeRTOS/org/Source/stream_buffer.su ./Middlewares/Third-Party/FreeRTOS/org/Source/tasks.cyclo ./Middlewares/Third-Party/FreeRTOS/org/Source/tasks.d ./Middlewares/Third-Party/FreeRTOS/org/Source/tasks.o ./Middlewares/Third-Party/FreeRTOS/org/Source/tasks.su ./Middlewares/Third-Party/FreeRTOS/org/Source/timers.cyclo ./Middlewares/Third-Party/FreeRTOS/org/Source/timers.d ./Middlewares/Third-Party/FreeRTOS/org/Source/timers.o ./Middlewares/Third-Party/FreeRTOS/org/Source/timers.su

.PHONY: clean-Middlewares-2f-Third-2d-Party-2f-FreeRTOS-2f-org-2f-Source

