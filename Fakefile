
TARGET="BuildTool"


CC="g++"
CPPSTD="-std=c++11"


SRC="./src/"
CPPSOURCES="$(wildcard $(SRC)*.cpp)"


OUT="./build/"


all: build-tool


build-tool:
	$(CC) $(CPPSOURCES) -o $(OUT)$(TARGET) $(CPPSTD)

run: build-tool
	$(OUT)$(TARGET)
	
clean:
	rm -rf build