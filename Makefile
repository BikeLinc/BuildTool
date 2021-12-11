# Makefile for building github.com/BikeLinc/BuildTool

# TARGET
TARGET=BuildTool

# COMPILER
CC=g++
CPPSTD=-std=c++11

# SOURCES
SRC=./src/
TOOL2SRC=./tool2src/
CPPSOURCES=$(wildcard $(SRC)*.cpp)
TOOL2SOURCES=$(wildcard $(TOOL2SRC)*.cpp)

# BUILD
OUT=./build/

all: build-tool build-tool2

build-tool:
	@echo Building BuildTool...
	@rm -rf build
	@mkdir build 
	$(CC) $(CPPSOURCES) -o $(OUT)$(TARGET) $(CPPSTD)
	
build-tool2:
	@echo Building Tool2...
	@rm -rf build2
	@mkdir build2
	$(CC) $(TOOL2SOURCES) -o ./build2/$(TARGET)2 $(CPPSTD)
	

run:
	@echo Running BuildTool...
	@$(OUT)$(TARGET) 
	
tool2: build-tool2 
	@echo Running Tool2...
	@./build2/BuildTool2
	
clean:
	rm -rf build
	rm -rf build 2