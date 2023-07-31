#ifndef ABSTRACTPROCESS_H
#define ABSTRACTPROCESS_H

#include <vector>
#include <string>

class AbstractProcess {
public:
  virtual int getPriority()=0;
  virtual int getPID()=0;
  virtual std::vector< std::string > getTCB()=0;
  virtual std::vector< std::string > getStatus()=0;
  virtual std::string getName()=0;
  virtual bool executeOneQuantum()=0;
  virtual void killProcess()=0;  
};

#endif
