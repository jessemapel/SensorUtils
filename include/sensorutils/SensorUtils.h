#ifndef SensorUtils_h
#define SensorUtils_h
#include <vector>

using namespace std;

double PhaseAngle(const vector<double> & instPosition, const vector<double> & sunPosition, const vector<double> & surfaceIntersection);
double SubSolarLongitude(const vector<double> &sunPosition);

double RectangularToLongitude(const vector<double> &point);

#endif
