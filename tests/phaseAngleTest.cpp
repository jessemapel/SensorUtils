#include "SensorUtils.h"
#include "math.h"
#include <gtest/gtest.h>

TEST(SensorUtils, PhaseAngle) {

   vector<double> instrumentPosition1{-1, 0, 0};
   vector<double> point1{1, 0, 0};
   vector<double> surfaceIntersection1{0, 0, 0};
   EXPECT_EQ(M_PI, PhaseAngle(instrumentPosition1, point1, surfaceIntersection1));


   vector<double> instrumentPosition2{0, 1, 0};
   vector<double> point2{0, 1, 0};
   vector<double> surfaceIntersection2{0, 0, 0};
   EXPECT_EQ(0, PhaseAngle(instrumentPosition2, point2, surfaceIntersection2));

   vector<double> instrumentPosition3{1, 1, 0};
   vector<double> point3{-1, 1, 0};
   vector<double> surfaceIntersection3{0, 0, 0};
   EXPECT_EQ(M_PI/2.0, PhaseAngle(instrumentPosition3, point3, surfaceIntersection3));


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

// BEGIN LocalSolarTime TESTS

TEST(LocalSolarTime, Midnight) {
   std::vector<double> groundPoint{1.0, 0.0, 0.0};
   std::vector<double> sunPosition{-1.0, 0.0, 0.0};
   EXPECT_EQ(0, LocalSolarTime(groundPoint, sunPosition));
}

TEST(LocalSolarTime, Morning) {
   std::vector<double> groundPoint{1.0, 0.0, 0.0};
   std::vector<double> sunPosition{0.0, 1.0, 0.0};
   EXPECT_EQ(6, LocalSolarTime(groundPoint, sunPosition));
}

TEST(LocalSolarTime, Noon) {
   std::vector<double> groundPoint{1.0, 0.0, 0.0};
   std::vector<double> sunPosition{1.0, 0.0, 0.0};
   EXPECT_EQ(12, LocalSolarTime(groundPoint, sunPosition));
}

TEST(LocalSolarTime, Evening) {
   std::vector<double> groundPoint{1.0, 0.0, 0.0};
   std::vector<double> sunPosition{0.0, -1.0, 0.0};
   EXPECT_EQ(18, LocalSolarTime(groundPoint, sunPosition));
}


int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
