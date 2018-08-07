#include "SensorUtils.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(EmissionAngle, TestAngle) {
   vector<double> observerBodyFixedPosition{-2399.5377741187439824,-2374.0338295628557717,1277.6750059817834426};
   vector<double> groundPtIntersection{-2123.3622582859998147,-2380.37178122360001,1194.6783966636000969};
   vector<double> surfaceNormal{-0.62338400000000004919,-0.69883799999999995922,0.35073799999999999422};
   EXPECT_DOUBLE_EQ(0.81971651917135968102, EmissionAngle(observerBodyFixedPosition, groundPtIntersection,surfaceNormal));
}

TEST(EmissionAngle, ObserverEquGround) {
   vector<double> observerBodyFixedPosition{0.0,0.0,0.0};
   vector<double> groundPtIntersection{0.0,0.0,0.0};
   vector<double> surfaceNormal{1.0,0.0,0.0};
   EXPECT_DOUBLE_EQ(M_PI/2.0, EmissionAngle(observerBodyFixedPosition, groundPtIntersection,surfaceNormal));
}

TEST(EmissionAngle, ZeroNormal) {
   vector<double> observerBodyFixedPosition{-2399.5377741187439824,-2374.0338295628557717,1277.6750059817834426};
   vector<double> groundPtIntersection{-2123.3622582859998147,-2380.37178122360001,1194.6783966636000969};
   vector<double> surfaceNormal{0.0, 0.0, 0.0};
   EXPECT_DOUBLE_EQ(M_PI/2.0, EmissionAngle(observerBodyFixedPosition, groundPtIntersection,surfaceNormal));
}

TEST(EmissionAngle, MinEmission) {
   vector<double> observerBodyFixedPosition{2.0,0.0,0.0};
   vector<double> groundPtIntersection{1.0,0.0,0.0};
   vector<double> surfaceNormal{1.0,0.0,0.0};
   EXPECT_DOUBLE_EQ(0.0,EmissionAngle(observerBodyFixedPosition, groundPtIntersection,surfaceNormal));
}

TEST(EmissionAngle, MaxEmission) {
   vector<double> observerBodyFixedPosition{1.0,1.0,1.0};
   vector<double> groundPtIntersection{0.0,0.0,0.0};
   vector<double> surfaceNormal{-2.0,-2.0,2.0};
   EXPECT_DOUBLE_EQ(M_PI,EmissionAngle(observerBodyFixedPosition, groundPtIntersection,surfaceNormal));
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


int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
