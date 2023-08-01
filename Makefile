# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -std=c++11

RM = rm
#-------------------------------------------------

simulator: DispatcherConfiguration.o GetterPID.o MemoryHandler.o FIFODispatcher.o RoundRobinDispatcher.o  CreateProcess.o InstructionProcess.o KillProcess.o simulator.o  
	$(CC) -pthread DispatcherConfiguration.o GetterPID.o MemoryHandler.o  FIFODispatcher.o RoundRobinDispatcher.o CreateProcess.o InstructionProcess.o KillProcess.o simulator.o -o simulator

terminal: terminal.o
	$(CC) terminal.o -o terminal

terminal.o: src/terminal.cpp
	$(CC) $(CFLAGS) -c src/terminal.cpp	

simulator.o: src/configuration/DispatcherConfiguration.h src/utils/GetterPID.h src/simulator.cpp src/process/CreateProcess.h src/memory/MemoryHandler.h src/dispatcher/AbstractDispatcher.h src/dispatcher/FIFODispatcher.h src/dispatcher/RoundRobinDispatcher.h
	$(CC) $(CFLAGS) -c src/simulator.cpp

MemoryHandler.o: src/memory/MemoryHandler.cpp src/memory/MemoryHandler.h 
	$(CC) $(CFLAGS) -c src/memory/MemoryHandler.cpp

FIFODispatcher.o: src/dispatcher/FIFODispatcher.cpp src/dispatcher/FIFODispatcher.h src/dispatcher/AbstractDispatcher.h  src/process/AbstractProcess.h
	$(CC) $(CFLAGS) -c src/dispatcher/FIFODispatcher.cpp

RoundRobinDispatcher.o: src/dispatcher/RoundRobinDispatcher.cpp src/dispatcher/RoundRobinDispatcher.h src/dispatcher/AbstractDispatcher.h  src/process/AbstractProcess.h
	$(CC) $(CFLAGS) -c src/dispatcher/RoundRobinDispatcher.cpp

CreateProcess.o: src/utils/GetterPID.h src/process/CreateProcess.cpp src/process/CreateProcess.h src/process/InstructionProcess.h src/process/AbstractProcess.h  src/dispatcher/AbstractDispatcher.h src/memory/MemoryHandler.h
	$(CC) $(CFLAGS) -c src/process/CreateProcess.cpp

InstructionProcess.o: src/process/InstructionProcess.cpp src/process/InstructionProcess.h src/process/AbstractProcess.h  src/memory/MemoryHandler.h
	$(CC) $(CFLAGS) -c src/process/InstructionProcess.cpp

KillProcess.o: src/process/KillProcess.cpp src/process/KillProcess.h src/process/AbstractProcess.h  src/memory/MemoryHandler.h src/dispatcher/AbstractDispatcher.h
	$(CC) $(CFLAGS) -c src/process/KillProcess.cpp

GetterPID.o: src/utils/GetterPID.cpp src/utils/GetterPID.h
	$(CC) $(CFLAGS) -c src/utils/GetterPID.cpp

DispatcherConfiguration.o: src/configuration/DispatcherConfiguration.cpp src/configuration/DispatcherConfiguration.h
	$(CC) $(CFLAGS) -c src/configuration/DispatcherConfiguration.cpp

clean: 
	$(RM) *.o simulator