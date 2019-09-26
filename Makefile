bin/mukar: src/main.cpp build/IceKey.o build/md5.o
	mkdir -p bin
	clang++ -o bin/mukar src/main.cpp build/IceKey.o build/md5.o -O2 -Wall

build/IceKey.o: src/IceKey.h src/IceKey.cpp
	mkdir -p build
	clang++ -o build/IceKey.o -c src/IceKey.cpp -std=c++98

build/md5.o: src/md5.h src/md5.cpp
	mkdir -p build
	clang++ -o build/md5.o -c src/md5.cpp
