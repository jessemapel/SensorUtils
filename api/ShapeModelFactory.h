#ifndef ShapeModelFactory_h
#define ShapeModelFactory_h

#include <memory>
#include <string>

#include "ShapeModel.h"

class ShapeModelFactory {

  public:
    static ShapeModel* create(const std::string &imagePath);

  private:
    ShapeModelFactory();
    ~ShapeModelFactory();
};

#endif
