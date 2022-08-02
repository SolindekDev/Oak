#
#	Use build.js it's better
#

CC = clang++
CC_FLAGS = -O3 -std=c++17 -I./Include

ifeq ($(OS),Windows_NT)
	OUTPUT = ./Build/oak.exe
else
	OUTPUT = ./Build/oak
endif

all: compile

compile: $(wildcard ./Source/*.cpp)
	$(CC) $(CC_FLAGS) $? -o $(OUTPUT)
