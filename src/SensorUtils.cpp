#include "SensorUtils.h"

#include "math.h"

#include <vector>

#include <armadillo>

using namespace std;


 /**
   * Computes and returns phase angle, in radians, given the positions of the
   * observer and illuminator.
   *
   * Phase Angle: The angle between the vector from the surface intersection point to
   * the observer (usually the spacecraft) and the vector from the surface intersection
   * point to the illuminator (usually the sun).
   *
   * @author Kaj Williams
   *
   * @param observerBodyFixedPosition  Three dimensional position of the observer,
   *                                   in the coordinate system of the target body.
   * @param illuminatorBodyFixedPosition Three dimensional position for the illuminator,
   *                                     in the body-fixed coordinate system.
   * @param surfaceIntersection Three dimensional position for the ground (surface intersection) point,
   *                                     in the body-fixed coordinate system.
   * @return @b double Phase angle, in radians.
   */

double PhaseAngle(const std::vector<double> &observerBodyFixedPosition,
                                const std::vector<double> &illuminatorBodyFixedPosition,
				const std::vector<double> &surfaceIntersection) {

    //convert the vector to an arma::vec
    arma::vec observer = arma::zeros<arma::vec>(3);
    observer = arma::conv_to<arma::vec>::from(observerBodyFixedPosition);

    //convert the illuminatorBodyFixedPosition vector to an arma::vec
    arma::vec illuminator = arma::zeros<arma::vec>(3);
    illuminator = arma::conv_to<arma::vec>::from(illuminatorBodyFixedPosition);

    //convert the surfaceIntersection vector to an arma::vec
    arma::vec surface = arma::zeros<arma::vec>(3);
    surface = arma::conv_to<arma::vec>::from(surfaceIntersection);

    // Get vector from surface point to observer and normalise it
    arma::vec surfaceToObserver = arma::zeros<arma::vec>(3);
    arma::vec normSurfaceToObserver = arma::zeros<arma::vec>(3);
    surfaceToObserver = observer - surface;
    normSurfaceToObserver = arma::normalise(surfaceToObserver);

    // Get vector from surface point to sun and normalise it
    arma::vec surfaceToSun = arma::zeros<arma::vec>(3);
    arma::vec normSurfaceToSun = arma::zeros<arma::vec>(3);
    surfaceToSun = illuminator - surface;
    normSurfaceToSun = arma::normalise(surfaceToSun);

    double cos_angle=arma::dot(normSurfaceToObserver,normSurfaceToSun);

    if(cos_angle >= 1.0) return 0.0;
    if(cos_angle <= -1.0) return M_PI;

    return acos(cos_angle);


}


/**
 * Computes the longitude of the subsolar point from the sun position.
 * If the sun is perfectly over a pole, then 0 is returned.
 *
 * @author Jesse Mapel
 *
 * @param sunPosition The body fixed rectangular positon of the sun
 *
 * @return @b double The longitude of the subsolar point in -180:180 positive East degrees
 */
double SubSolarLongitude(const vector<double> &sunPosition) {
   return RectangularToLongitude(sunPosition);
}


/**
 * Computes the local solar time for a ground point.
 *
 * @author Jesse Mapel
 *
 * @param groundPoint The body fixed rectangular positon of the ground point
 * @param sunPosition The body fixed rectangular positon of the sun
 *
 * @return @b double The local solar time in hours
 */
double LocalSolarTime(const vector<double> &groundPoint, const vector<double> &sunPosition) {
   double groundLon = RectangularToLongitude(groundPoint);
   double sunLon = SubSolarLongitude(sunPosition);
   double lonDiff = (groundLon - sunLon);
   // Divide by 15 because each hour is 15 degrees
   return (lonDiff + 180) / 15;
}


/**
 * Computes the longitude of a rectangular point in -180:180 positive East degrees.
 * If the point is on a pole, then 0 is returned. If the point does not have 3 elements,
 * then a std::invalid_argument exception is thrown
 *
 * @author Jesse Mapel
 *
 * @param point The body fixed rectangular coordinate of the point
 *
 * @return @b double The longitude of the point in -180:180 positive East degrees
 */
double RectangularToLongitude(const vector<double> &point) {
   if (point.size() < 3) {
      throw invalid_argument("Cannot compute longitude of a point with less than 3 elements");
   }
   double radLon = atan2(point[1], point[0]);
   return 180/M_PI * radLon;
}
