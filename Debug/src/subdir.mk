################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Document.cpp \
../src/PointerArray.cpp \
../src/Spreadsheet.cpp \
../src/WebPage.cpp \
../src/main.cpp 

OBJS += \
./src/Document.o \
./src/PointerArray.o \
./src/Spreadsheet.o \
./src/WebPage.o \
./src/main.o 

CPP_DEPS += \
./src/Document.d \
./src/PointerArray.d \
./src/Spreadsheet.d \
./src/WebPage.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


