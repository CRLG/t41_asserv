# Teensyduino Core Library
# http://www.pjrc.com/teensy/
# Copyright (c) 2019 PJRC.COM, LLC.
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# 1. The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# 2. If the Software is incorporated into a build system that allows
# selection among a list of target devices, then similar target
# devices manufactured by PJRC.COM must be included in the list of
# target devices and selectable in the same manner.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Use these lines for Teensy 4.0
#MCU = IMXRT1062
#MCU_LD = imxrt1062.ld
#MCU_DEF = ARDUINO_TEENSY40

# Use these lines for Teensy 4.1
MCU = IMXRT1062
MCU_LD = imxrt1062_t41.ld
MCU_DEF = ARDUINO_TEENSY41

TEENSYLIB_PATH = ./ext/teensylib
TEENSY_DRV_PATH = $(TEENSYLIB_PATH)/cores/teensy4
TEENSY_LIBRARIES_PATH = $(TEENSYLIB_PATH)/libraries

# The name of your project (used to name the compiled .hex file)
TARGET = main

# INCLUDE PATH
INCLUDE_PATHS += -I./.
INCLUDE_PATHS += -I./includes
INCLUDE_PATHS += -I./sources
INCLUDE_PATHS += -I./ext
INCLUDE_PATHS += -I./ext/CppRobLib
INCLUDE_PATHS += -I./ext/CppRobLib/common-rob
INCLUDE_PATHS += -I./ext/CppRobLib/ConsoleInteractiveMenu/
INCLUDE_PATHS += -I./ext/CppRobLib/Communication/DataEncoderDecoder
INCLUDE_PATHS += -I./ext/CppRobLib/Communication/Messenger
INCLUDE_PATHS += -I./ext/CppRobLib/Communication/Messenger/DatabaseAsservissementDeporte


INCLUDE_PATHS += -I$(TEENSYLIB_PATH)/cores
INCLUDE_PATHS += -I$(TEENSYLIB_PATH)/cores/teensy4
INCLUDE_PATHS += -I$(TEENSYLIB_PATH)/cores/avr
INCLUDE_PATHS += -I$(TEENSYLIB_PATH)/cores/usb_rawhid
INCLUDE_PATHS += -I$(TEENSYLIB_PATH)/cores/teensy

INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/QuadEncoder
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/TeensyID
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/FlexiTimer2
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/Servo
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/PWMServo
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/SPI
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/OneWire
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/EEPROM
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/InternalTemperature
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/FreqCount
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/FreqMeasure
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/ADC
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/FlexCAN_T4  # Pour le FlexCAN_T4, le code source est intégré (pas de .cpp)
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/i2c_t4/src
INCLUDE_PATHS += -I$(TEENSY_LIBRARIES_PATH)/i2c_t4/src/imx_rt1060

# APPLICTION OBJECTS FILES
CPP_FILES += ./main.cpp
CPP_FILES += ./application.cpp
CPP_FILES += ./CAsservissement.cpp
CPP_FILES += ./CCodeurs.cpp
CPP_FILES += ./debug_serial.cpp
CPP_FILES += ./CRoues.cpp
CPP_FILES += ./data_logger.cpp
CPP_FILES += ./MessengerAsservissementDeporte.cpp

CPP_FILES += ./ext/CppRobLib/common-rob/CAsservissementBase.cpp
CPP_FILES += ./ext/CppRobLib/common-rob/CRouesBase.cpp
CPP_FILES += ./ext/CppRobLib/ConsoleInteractiveMenu/console_interaction.cpp

CPP_FILES += ./ext/CppRobLib/Communication/DataEncoderDecoder/data_encoder_decoder.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/databasebase.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/messagebase.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/nodebase.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/messengerinterfacebase.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/transporterbase.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/transportergeneric.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/DatabaseAsservissementDeporte/databaseasservissementdeporte.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/DatabaseAsservissementDeporte/message_commande_mouvement_distance_angle.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/DatabaseAsservissementDeporte/message_commande_mouvement_xy_a.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/DatabaseAsservissementDeporte/message_commande_mouvement_xy_b.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/DatabaseAsservissementDeporte/message_commande_mouvement_xy.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/DatabaseAsservissementDeporte/message_commande_mouvement_xy_teta.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/DatabaseAsservissementDeporte/message_commande_vitesse_mouvement.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/DatabaseAsservissementDeporte/message_reinit_position_xy_teta.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/DatabaseAsservissementDeporte/message_commande_indice_sportivite.cpp
CPP_FILES += ./ext/CppRobLib/Communication/Messenger/DatabaseAsservissementDeporte/message_etat_asservissement.cpp

# configurable options
OPTIONS = -DF_CPU=600000000 -DUSB_DUAL_SERIAL -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE
#
# USB Type configuration:
#   -DUSB_SERIAL
#   -DUSB_DUAL_SERIAL
#   -DUSB_TRIPLE_SERIAL
#   -DUSB_KEYBOARDONLY
#   -DUSB_TOUCHSCREEN
#   -DUSB_HID_TOUCHSCREEN
#   -DUSB_HID
#   -DUSB_SERIAL_HID
#   -DUSB_MIDI
#   -DUSB_MIDI4
#   -DUSB_MIDI16
#   -DUSB_MIDI_SERIAL
#   -DUSB_MIDI4_SERIAL
#   -DUSB_MIDI16_SERIAL
#   -DUSB_AUDIO
#   -DUSB_MIDI_AUDIO_SERIAL
#   -DUSB_MIDI16_AUDIO_SERIAL
#   -DUSB_MTPDISK
#   -DUSB_RAWHID
#   -DUSB_FLIGHTSIM
#   -DUSB_FLIGHTSIM_JOYSTICK

# options needed by many Arduino libraries to configure for Teensy model
OPTIONS += -D__$(MCU)__ -DARDUINO=10813 -DTEENSYDUINO=154 -D$(MCU_DEF)

# for Cortex M7 with single & double precision FPU
CPUOPTIONS = -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -mthumb

# use this for a smaller, no-float printf
#SPECS = --specs=nano.specs

# Other Makefiles and project templates for Teensy
#
# https://forum.pjrc.com/threads/57251?p=213332&viewfull=1#post213332
# https://github.com/apmorton/teensy-template
# https://github.com/xxxajk/Arduino_Makefile_master
# https://github.com/JonHylands/uCee


#************************************************************************
# Location of Teensyduino utilities, Toolchain, and Arduino Libraries.
# To use this makefile without Arduino, copy the resources from these
# locations and edit the pathnames.  The rest of Arduino is not needed.
#************************************************************************
COMPILERPATH = /opt/arduino-1.8.15/hardware/tools/arm/bin
TOOLSPATH = /opt/arduino-1.8.15/hardware/tools


#************************************************************************
# TEENSY DRIVER FILES (DO NOT EDIT !)
#************************************************************************
C_FILES += $(TEENSY_DRV_PATH)/analog.c
C_FILES += $(TEENSY_DRV_PATH)/bootdata.c
C_FILES += $(TEENSY_DRV_PATH)/clockspeed.c
C_FILES += $(TEENSY_DRV_PATH)/debugprintf.c
C_FILES += $(TEENSY_DRV_PATH)/delay.c
C_FILES += $(TEENSY_DRV_PATH)/digital.c
C_FILES += $(TEENSY_DRV_PATH)/eeprom.c
C_FILES += $(TEENSY_DRV_PATH)/extmem.c
C_FILES += $(TEENSY_DRV_PATH)/fuse.c
C_FILES += $(TEENSY_DRV_PATH)/interrupt.c
C_FILES += $(TEENSY_DRV_PATH)/keylayouts.c
C_FILES += $(TEENSY_DRV_PATH)/libc.c
C_FILES += $(TEENSY_DRV_PATH)/nonstd.c
C_FILES += $(TEENSY_DRV_PATH)/pwm.c
C_FILES += $(TEENSY_DRV_PATH)/rtc.c
C_FILES += $(TEENSY_DRV_PATH)/sm_alloc_valid.c
C_FILES += $(TEENSY_DRV_PATH)/sm_calloc.c
C_FILES += $(TEENSY_DRV_PATH)/sm_free.c
C_FILES += $(TEENSY_DRV_PATH)/sm_hash.c
C_FILES += $(TEENSY_DRV_PATH)/sm_malloc.c
C_FILES += $(TEENSY_DRV_PATH)/sm_malloc_stats.c
C_FILES += $(TEENSY_DRV_PATH)/sm_pool.c
C_FILES += $(TEENSY_DRV_PATH)/sm_realloc.c
C_FILES += $(TEENSY_DRV_PATH)/sm_realloc_i.c
C_FILES += $(TEENSY_DRV_PATH)/sm_realloc_move.c
C_FILES += $(TEENSY_DRV_PATH)/sm_szalloc.c
C_FILES += $(TEENSY_DRV_PATH)/sm_util.c
C_FILES += $(TEENSY_DRV_PATH)/sm_zalloc.c
C_FILES += $(TEENSY_DRV_PATH)/startup.c
C_FILES += $(TEENSY_DRV_PATH)/tempmon.c
C_FILES += $(TEENSY_DRV_PATH)/usb.c
C_FILES += $(TEENSY_DRV_PATH)/usb_desc.c
C_FILES += $(TEENSY_DRV_PATH)/usb_joystick.c
C_FILES += $(TEENSY_DRV_PATH)/usb_keyboard.c
C_FILES += $(TEENSY_DRV_PATH)/usb_midi.c
C_FILES += $(TEENSY_DRV_PATH)/usb_mouse.c
C_FILES += $(TEENSY_DRV_PATH)/usb_mtp.c
C_FILES += $(TEENSY_DRV_PATH)/usb_rawhid.c
C_FILES += $(TEENSY_DRV_PATH)/usb_seremu.c
C_FILES += $(TEENSY_DRV_PATH)/usb_serial2.c
C_FILES += $(TEENSY_DRV_PATH)/usb_serial3.c
C_FILES += $(TEENSY_DRV_PATH)/usb_serial.c
C_FILES += $(TEENSY_DRV_PATH)/usb_touch.c

CPP_FILES += $(TEENSY_DRV_PATH)/AudioStream.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/CrashReport.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/DMAChannel.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/EventResponder.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/HardwareSerial1.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/HardwareSerial2.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/HardwareSerial3.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/HardwareSerial4.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/HardwareSerial5.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/HardwareSerial6.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/HardwareSerial7.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/HardwareSerial8.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/HardwareSerial.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/IntervalTimer.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/IPAddress.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/new.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/Print.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/serialEvent1.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/serialEvent2.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/serialEvent3.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/serialEvent4.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/serialEvent5.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/serialEvent6.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/serialEvent7.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/serialEvent8.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/serialEvent.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/serialEventUSB1.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/serialEventUSB2.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/Stream.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/Time.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/Tone.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/usb_audio.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/usb_flightsim.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/usb_inst.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/WMath.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/WString.cpp
CPP_FILES += $(TEENSY_DRV_PATH)/yield.cpp

#************************************************************************
# TEENSY ADDITIONAL LIBS (DO NOT EDIT !)
#************************************************************************
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/QuadEncoder/QuadEncoder.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/TeensyID/TeensyID.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/FlexiTimer2/FlexiTimer2.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/Servo/Servo.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/PWMServo/PWMServo.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/SPI/SPI.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/OneWire/OneWire.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/EEPROM/EEPROM.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/InternalTemperature/InternalTemperature.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/FreqCount/FreqCount.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/FreqMeasure/FreqMeasure.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/ADC/ADC.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/ADC/ADC_Module.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/ADC/AnalogBufferDMA.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/i2c_t4/src/i2c_driver_wire.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/i2c_t4/src/i2c_register_slave.cpp
CPP_FILES += $(TEENSY_LIBRARIES_PATH)/i2c_t4/src/imx_rt1060/imx_rt1060_i2c_driver.cpp


#************************************************************************
# Settings below this point usually do not need to be edited
#************************************************************************

# CPPFLAGS = compiler options for C and C++
CPPFLAGS = -Wall -g -O2 $(CPUOPTIONS) -MMD $(OPTIONS) -I. $(INCLUDE_PATHS) -ffunction-sections -fdata-sections

# compiler options for C++ only
CXXFLAGS = -std=gnu++14 -felide-constructors -fno-exceptions -fpermissive -fno-rtti -Wno-error=narrowing

# compiler options for C only
CFLAGS =

# linker options
LDFLAGS = -Os -Wl,--gc-sections,--relax $(SPECS) $(CPUOPTIONS) -T$(TEENSY_DRV_PATH)/$(MCU_LD)

# additional libraries to link
LIBS = -larm_cortexM7lfsp_math -lm -lstdc++


# names for the compiler programs
CC = $(COMPILERPATH)/arm-none-eabi-gcc
CXX = $(COMPILERPATH)/arm-none-eabi-g++
OBJCOPY = $(COMPILERPATH)/arm-none-eabi-objcopy
SIZE = $(COMPILERPATH)/arm-none-eabi-size

OBJS := $(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o) 

# the actual makefile rules (all .o files built by GNU make's default implicit rules)


all: $(TARGET).hex

install: $(TARGET).hex
ifneq (,$(wildcard $(TOOLSPATH)))
	$(TOOLSPATH)/teensy_post_compile -file=$(TARGET) -path=$(shell pwd) -tools=$(TOOLSPATH)
	-$(TOOLSPATH)/teensy_reboot
endif

$(TARGET).elf: $(OBJS) $(TEENSY_DRV_PATH)/$(MCU_LD)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS) 

%.hex: %.elf
	$(SIZE) $<
	$(OBJCOPY) -O ihex -R .eeprom $< $@


# compiler generated dependency info
-include $(OBJS:.o=.d)

clean:
	@rm -f $(TARGET).elf $(TARGET).hex
	@find . -name "*.o" -type f -delete
	@find . -name "*.d" -type f -delete
