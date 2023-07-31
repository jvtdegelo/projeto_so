#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int counter = 0;

void write_file(std::string str){
  std::ofstream file("communication.txt");
  if (!file) {
      std::cout << "Error: Could not open the file" << std::endl;
      return;
  }
    file << counter << std::endl;
    file << str << std::endl;
    counter++;

    file.close();
}


int main(){
  write_file("");
  while(true){
    std::string input;
    std::getline(std::cin, input);
  
    std::string command;
    int parameter;
    std::istringstream iss(input);
    iss >> command >> parameter;

    if (command == "create") {
        write_file("c " + std::to_string(parameter));
    } else if (command == "kill") {
        write_file("k " + std::to_string(parameter));
    } else {
        std::cout << "Invalid command! Please use 'create' or 'kill'." << std::endl;
    }
  }
  

  return 0;
}