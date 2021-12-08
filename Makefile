# Makefile for building github.com/BikeLinc/BuildTool

# TARGET
TARGET=BuildTool

# COMPILER
CC=g++
CPPSTD=-std=c++11

# SOURCES
SRC=./src/
CPPSOURCES=$(wildcard $(SRC)*.cpp)

# BUILD
OUT=./build/

all: build-tool

build-tool:
	@echo Building BuildTool...
	@rm -rf build
	@mkdir build 
	$(CC) $(CPPSOURCES) -o $(OUT)$(TARGET) $(CPPSTD)

run: build-tool
	@echo Running BuildTool...
	@$(OUT)$(TARGET)
	
clean:
	rm -rf build