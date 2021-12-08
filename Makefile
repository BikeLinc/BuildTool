all: fake.o test
	rm build/compiler.o
	rm build/parser.o

test: fake.o																					
	g++ -o ./build/fake_test -I./googleTest/include -I./fake/src ./fake/src/fake_test.cpp ./build/parser.o ./build/compiler.o ./googleTest/lib/libgtest.a

fake.o: setup parser.o compiler.o
	g++ ./fake/src/main.cpp ./fake/src/Parser.cpp ./fake/src/Compiler.cpp -o ./build/fake -std=c++11
	
parser.o:
	g++ -c -o ./build/parser.o ./fake/src/Parser.cpp

compiler.o:
	g++ -c -o ./build/compiler.o ./fake/src/Compiler.cpp

setup: clean
	mkdir -p build

clean:
	rm -rf build