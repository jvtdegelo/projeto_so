#ifndef DISPATCHERCONFIGURATION_H
#define DISPATCHERCONFIGURATION_H

class DispatcherConfiguration {
public:
  DispatcherConfiguration();
  int timeToExecute;
  int schedulingAlgorithm; // 0 FIFO 1 Round-Robin
};

#endif