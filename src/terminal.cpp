#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

void write_end_file(std::string str){
  std::ofstream file;
  file.open("communication.txt", std::ios::app);
  if (!file) {
      std::cout << "Error: Could not open the file" << std::endl;
      return;
  }
  file << str << std::endl;
  file.close();
}

int main(){
  while(true){
    std::string input;
    std::getline(std::cin, input);
  
    std::string command;
    int parameter;
    std::istringstream iss(input);
    iss >> command >> parameter;

    if (command == "create") {
        write_end_file("c " + std::to_string(parameter));
    } else if (command == "kill") {
        write_end_file("k " + std::to_string(parameter));
    } else {
        std::cout << "Invalid command! Please use 'create' or 'kill'." << std::endl;
    }
  }
  
  return 0;
}