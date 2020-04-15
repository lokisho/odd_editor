CC = g++
odd_editor.o: main.cpp
	$(CC) main.cpp -o odd_editor --std=c++17
