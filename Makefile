# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -std=c++11

RM = rm
#-------------------------------------------------

simulator:  MemoryHandler.o FIFOQueue.o  CreateProcess.o InstructionProcess.o KillProcess.o simulator.o  
	$(CC)  MemoryHandler.o  FIFOQueue.o CreateProcess.o InstructionProcess.o KillProcess.o simulator.o -o simulator

simulator.o: src/simulator.cpp src/process/CreateProcess.h src/memory/MemoryHandler.h src/queue/AbstractQueue.h src/queue/FIFOQueue.h
	$(CC) $(CFLAGS) -c src/simulator.cpp

MemoryHandler.o: src/memory/MemoryHandler.cpp src/memory/MemoryHandler.h 
	$(CC) $(CFLAGS) -c src/memory/MemoryHandler.cpp

FIFOQueue.o: src/queue/FIFOQueue.cpp src/queue/FIFOQueue.h src/queue/AbstractQueue.h  src/process/AbstractProcess.h
	$(CC) $(CFLAGS) -c src/queue/FIFOQueue.cpp

CreateProcess.o: src/process/CreateProcess.cpp src/process/CreateProcess.h src/process/InstructionProcess.h src/process/AbstractProcess.h  src/queue/AbstractQueue.h src/memory/MemoryHandler.h
	$(CC) $(CFLAGS) -c src/process/CreateProcess.cpp

InstructionProcess.o: src/process/InstructionProcess.cpp src/process/InstructionProcess.h src/process/AbstractProcess.h  src/memory/MemoryHandler.h
	$(CC) $(CFLAGS) -c src/process/InstructionProcess.cpp

KillProcess.o: src/process/KillProcess.cpp src/process/KillProcess.h src/process/AbstractProcess.h  src/memory/MemoryHandler.h src/queue/AbstractQueue.h
	$(CC) $(CFLAGS) -c src/process/KillProcess.cpp

clean: 
	$(RM) *.o simulator