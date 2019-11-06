#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
#
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := Buzzer.cpp BuzzerTask.cpp Display.cpp DisplayTask.cpp GameTask.cpp IrDetector.cpp IrDiode.cpp RecIRMsgControl.cpp RunGameControl.cpp SendTask.cpp TransferHitsControl.cpp

# header files in this project
HEADERS := Buzzer.hpp BuzzerTask.hpp Display.hpp DisplayTask.hpp GameTask.hpp IrDetector.hpp IrDiode.hpp Player.hpp ReceiveTask.hpp RecIRMsgControl.hpp RunGameControl.hpp SendTask.hpp TransferHitsControl.hpp Keyboard.hpp KeyboardListener.hpp HardwareInputTask.hpp

# other places to look for files for this project
SEARCH  :=

# set REATIVE to the next higher directory
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../../v2cpse1-examples/
include $(RELATIVE)Makefile.due