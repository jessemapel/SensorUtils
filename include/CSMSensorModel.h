#ifndef CSMSensorModel_h
#define CSMSensorModel_h

#include <vector>
#include <typeinfo>
#include <iostream>

#include "sensorcore.h"
#include "SensorModel.h"

#include <Model.h>
#include <RasterGM.h>

class CSMSensorModel : public SensorModel {
  public:
    CSMSensorModel(csm::Model* model); 
    CartesianPoint imageToGround(ImagePoint &);
    ImagePoint groundToImage(CartesianPoint &);
    CartesianVector groundToLook(CartesianPoint & );
    double imageTime(ImagePoint & );

    CartesianPoint getSensorPosition(ImagePoint &);
    CartesianVector getIlluminationDirection (CartesianPoint &);

  private:
    csm::RasterGM *m_model;
};

#endif