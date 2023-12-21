CXX := g++

CXXFLAGS := -std=c++17 -Wall

TARGET_DIR := $(dir $(firstword $(MAKEFILE_LIST)))

SUBDIR := $(word 2, $(MAKECMDGOALS))

SRC_FILE := $(SUBDIR)\$(SUBDIR).cpp

TARGET := $(SUBDIR)\$(SUBDIR)

all: $(TARGET)

$(TARGET): $(SRC_FILE)
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGET)
	@echo _________________________________________________________________________
	@powershell -Command "Measure-Command { ./$< } | Select-Object TotalMilliseconds"
	@./$<
	@echo _________________________________________________________________________
	del $(TARGET).exe

clean:
	del $(TARGET).exe

%:
	@: