#include "GetterPID.h"

int GetterPID::get(){
  return NEW_PID++;
}

int GetterPID::NEW_PID = 0;