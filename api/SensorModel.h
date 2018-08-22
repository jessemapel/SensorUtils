#ifndef SensorModel_h
#define SensorModel_h

#include "sensorcore.h"

class SensorModel {

public:
  virtual ~SensorModel() { };
  virtual CartesianPoint imageToGround(ImagePoint &) =0;
  virtual ImagePoint groundToImage(CartesianPoint &) = 0;
  virtual CartesianVector groundToLook(CartesianPoint & ) = 0;
  virtual double imageTime(ImagePoint & )= 0;
  virtual CartesianPoint getSensorPosition(ImagePoint &) = 0; 
  virtual CartesianVector getIlluminationDirection (CartesianPoint &) = 0; 
};

#endif
