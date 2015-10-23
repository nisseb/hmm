CC=g++ 
FLAGS=-std=c++11 -Wall 


main_forward: main_forward.cpp forward.cpp forward.h
	$(CC) $(FLAGS) -o main_forward main_forward.cpp forward.cpp

