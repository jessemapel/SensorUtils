#ifndef SensorUtils_h
#define SensorUtils_h
#include <vector>

using namespace std;

double PhaseAngle(const vector<double> & instPosition, const vector<double> & sunPosition, const vector<double> & surfaceIntersection);
double SubSolarLongitude(const vector<double> &sunPosition);
double LocalSolarTime(const vector<double> &groundPoint, const vector<double> &sunPosition);

double RectangularToLongitude(const vector<double> &point);

double EmissionAngle(const vector<double>  &observerBodyFixedPosition,
                     const vector<double> &groundPtIntersection,
                     const vector<double> &surfaceNormal);

#endif
