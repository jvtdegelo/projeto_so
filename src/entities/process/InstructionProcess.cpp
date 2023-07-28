#include <stdio.h>
#include <vector>
#include <string>
#include<utility>
using namespace std;

class InstructionProcess: public AbstractProcess{
public:
  InstructionProcess(int pid, int memorySize, int memoryPosition): priority(2), pid(pid), memorySize(memorySize), memoryPosition(memoryPosition) {
    vector
  }

  int getPriority() override {
    return priority;
  }

  vector< pair< string, string> > getTCB() override {
    vector< pair < string, string> > tcb;
    tcb.push_back(make_pair("PID", to_string(pid)));
    tcb.push_back(make_pair("Priority", to_string(pid))); 

    return tcb;
  };

  bool executeOneQuantum() override {

  }
  
  void killProcess() override {

  }

private:
  int pid;
  int priority;
  int memorySize;
  int memoryPosition;
  vector< string > code;

}