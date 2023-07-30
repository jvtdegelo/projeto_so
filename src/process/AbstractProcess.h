#ifndef ABSTRACTPROCESS_H
#define ABSTRACTPROCESS_H

#include <vector>
#include <string>
#include<utility>

class AbstractProcess {
public:
  virtual int getPriority()=0;
  virtual int getPID()=0;
  virtual std::vector< std::pair< std::string, std::string> > getTCB()=0;
  virtual bool executeOneQuantum()=0;
  virtual void killProcess()=0;  
};

#endif
