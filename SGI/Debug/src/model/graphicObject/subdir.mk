################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/model/graphicObject/GraphicObject.cpp \
../src/model/graphicObject/Point.cpp 

OBJS += \
./src/model/graphicObject/GraphicObject.o \
./src/model/graphicObject/Point.o 

CPP_DEPS += \
./src/model/graphicObject/GraphicObject.d \
./src/model/graphicObject/Point.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/graphicObject/%.o: ../src/model/graphicObject/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/atk-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/pango-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/harfbuzz -I/usr/include/at-spi2-atk/2.0 -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


