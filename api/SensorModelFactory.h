#ifndef SensorModelFactory_h
#define SensorModelFactory_h

#include <memory>
#include <string>

#include "SensorModel.h"

class SensorModelFactory {

  public:
    static SensorModel* create(const std::string &metadata);

  private:
    SensorModelFactory();
    ~SensorModelFactory();
};

#endif
