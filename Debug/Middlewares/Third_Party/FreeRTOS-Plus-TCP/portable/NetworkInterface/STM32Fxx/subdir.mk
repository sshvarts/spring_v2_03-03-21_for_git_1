################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS-Plus-TCP/portable/NetworkInterface/STM32Fxx/NetworkInterface.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS-Plus-TCP/portable/NetworkInterface/STM32Fxx/NetworkInterface.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS-Plus-TCP/portable/NetworkInterface/STM32Fxx/NetworkInterface.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS-Plus-TCP/portable/NetworkInterface/STM32Fxx/NetworkInterface.o: ../Middlewares/Third_Party/FreeRTOS-Plus-TCP/portable/NetworkInterface/STM32Fxx/NetworkInterface.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F4xx -DFREERTOS_IP_CONFIG_H -DDEBUG -DSTM32F407xx -DconfigSUPPORT_DYNAMIC_ALLOCATION -DconfigUSE_COUNTING_SEMAPHORES -DipconfigUSE_NETWORK_EVENT_HOOK -DipconfigUSE_NETWORK_EVENT_HOOK -DipconfigUSE_RMII -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/stshv/CUBE_learn_02-15-21_WS/spring_v2_03-03-21_for_git_1/Middlewares/Third_Party/FreeRTOS-Plus-TCP/portable/Compiler/GCC" -I"C:/Users/stshv/CUBE_learn_02-15-21_WS/spring_v2_03-03-21_for_git_1/Middlewares/Third_Party/FreeRTOS-Plus-TCP/include" -I"C:/Users/stshv/CUBE_learn_02-15-21_WS/spring_v2_03-03-21_for_git_1/Middlewares/Third_Party/FreeRTOS-Plus-TCP/portable/NetworkInterface/include" -I"C:/Users/stshv/CUBE_learn_02-15-21_WS/spring_v2_03-03-21_for_git_1/Middlewares/Third_Party/FreeRTOS-Plus-TCP/portable/NetworkInterface/STM32Fxx" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/Third_Party/FreeRTOS-Plus-TCP/portable/NetworkInterface/STM32Fxx/NetworkInterface.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

