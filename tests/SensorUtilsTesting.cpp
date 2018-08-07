#include "SensorUtils.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(SensorUtils, EmissionAngle) {
   vector<double> observerBodyFixedPosition1{-2399.5377741187439824,-2374.0338295628557717,1277.6750059817834426};
   vector<double> groundPtIntersection1{-2123.3622582859998147,-2380.37178122360001,1194.6783966636000969};
   vector<double> surfaceNormal1{-0.62338400000000004919,-0.69883799999999995922,0.35073799999999999422};
   EXPECT_NEAR(0.81971651917135968102, EmissionAngle(observerBodyFixedPosition1, groundPtIntersection1,surfaceNormal1),1e-5);

   vector<double> observerBodyFixedPosition2{0.0,0.0,0.0};
   vector<double> groundPtIntersection2{0.0,0.0,0.0};
   vector<double> surfaceNormal2{0.0,0.0,0.0};
   EXPECT_NEAR(M_PI/2.0, EmissionAngle(observerBodyFixedPosition2, groundPtIntersection2,surfaceNormal2),1e-5);


   vector<double> observerBodyFixedPosition3{2.0,0.0,0.0};
   vector<double> groundPtIntersection3{1.0,0.0,0.0};
   vector<double> surfaceNormal3{1.0,0.0,0.0};
   EXPECT_NEAR(0.0,EmissionAngle(observerBodyFixedPosition3, groundPtIntersection3,surfaceNormal3),1e-5);


   vector<double> observerBodyFixedPosition4{1.0,1.0,1.0};
   vector<double> groundPtIntersection4{0.0,0.0,0.0};
   vector<double> surfaceNormal4{-2.0,-2.0,2.0};
   EXPECT_NEAR(M_PI,EmissionAngle(observerBodyFixedPosition4, groundPtIntersection4,surfaceNormal4),1e-5);



}


TEST(SensorUtils, PhaseAngle) {

   vector<double> instrumentPosition1{-1, 0, 0};
   vector<double> sunPosition1{1, 0, 0};
   vector<double> surfaceIntersection1{0, 0, 0};
   EXPECT_EQ(M_PI, PhaseAngle(instrumentPosition1, sunPosition1, surfaceIntersection1));


   vector<double> instrumentPosition2{0, 1, 0};
   vector<double> sunPosition2{0, 1, 0};
   vector<double> surfaceIntersection2{0, 0, 0};
   EXPECT_EQ(0, PhaseAngle(instrumentPosition2, sunPosition2, surfaceIntersection2));

   vector<double> instrumentPosition3{1, 1, 0};
   vector<double> sunPosition3{-1, 1, 0};
   vector<double> surfaceIntersection3{0, 0, 0};
   EXPECT_EQ(M_PI/2.0, PhaseAngle(instrumentPosition3, sunPosition3, surfaceIntersection3));


}

// BEGIN RectangularToLongitude TESTS

TEST(RectangularToLongitude, Meridian) {
   std::vector<double> point{1.0, 0.0, 0.0};
   EXPECT_EQ(0, RectangularToLongitude(point));
}

TEST(RectangularToLongitude, PositiveAngle) {
   std::vector<double> point{1.0, 1.0, 1.0};
   EXPECT_EQ(45, RectangularToLongitude(point));
}

TEST(RectangularToLongitude, NegativeAngle) {
   std::vector<double> point{-1.0, -1.0, -1.0};
   EXPECT_EQ(-135, RectangularToLongitude(point));
}

TEST(RectangularToLongitude, NorthPole) {
   std::vector<double> point{0.0, 0.0, 1.0};
   EXPECT_EQ(0, RectangularToLongitude(point));
}

TEST(RectangularToLongitude, SouthPole) {
   std::vector<double> point{0.0, 0.0, -1.0};
   EXPECT_EQ(0, RectangularToLongitude(point));
}

TEST(RectangularToLongitude, ShortVector) {
   std::vector<double> point{0.0, 0.0};
   try {
      RectangularToLongitude(point);
   }
   catch(std::invalid_argument const &err) {
      EXPECT_EQ(err.what(),
                std::string("Cannot compute longitude of a point with less than 3 elements"));
   }
   catch(...) {
      FAIL() << "Expected std::invalid_argument";
   }
}

// BEGIN SubSolarLongitude TESTS

TEST(SubSolarLongitude, TestPoint) {
   std::vector<double> sunPosition{1.0, 1.0, 1.0};
   EXPECT_EQ(45, SubSolarLongitude(sunPosition));
}


int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
