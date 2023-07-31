#include <iostream>
#include <pthread.h>
#include <chrono>
#include <thread>


void* printHi(void* arg) {
    while (true) {
        std::cout << "Hi" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return nullptr;
}

int main() {
    pthread_t thread;

    int result = pthread_create(&thread, nullptr, printHi, nullptr);
    if (result != 0) {
        std::cerr << "Error: Unable to create the new thread." << std::endl;
        return 1;
    }

    // Do other tasks in the main program here
    // For demonstration purposes, let's keep the main program running for 10 seconds.
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<< "Hello" << std::endl;

    // Wait for the thread to finish

    return 0;
}