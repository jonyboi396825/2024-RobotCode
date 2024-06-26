#include "Util/Utils.h"

#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884197169399
#endif

#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <units/length.h>

/**
 * Gets the value with the minimum absolute value between two numbers
 *
 * @param a One number
 * @param b Another number
 *
 * @returns a or b, depending on which one has a lesser absolute value
 */
double Utils::AbsMin(const double a, const double b)
{
  return std::abs(a) < std::abs(b) ? a : b;
}

/**
 * Averages a std::vector of vec::Vector2D
 *
 * @param vectors the non-zero sized array of vectors
 *
 * @note If the size of vectors is 0, then returns a zero vector.
 *
 * @returns The averaged vector
 */
vec::Vector2D Utils::GetVecAverage(const std::vector<vec::Vector2D> vectors)
{
  vec::Vector2D res;
  if (vectors.size() == 0)
  {
    return res;
  }

  for (auto vec : vectors)
  {
    res += vec;
  }

  res /= vectors.size();

  return res;
}

/**
 * Determines if a number is near zero
 *
 * @param num Number
 * @param tolerance Tolerance for being near zero
 */
bool Utils::NearZero(const double num, const double tolerance)
{
  return std::abs(num) <= tolerance;
}

/**
 * Determines if a vector is near zero
 *
 * @param vec Vector
 * @param tolerance Tolerance for being near zero
 */
bool Utils::NearZero(const vec::Vector2D vec, const double tolerance)
{
  for (auto component : vec)
  {
    if (!NearZero(component, tolerance))
    {
      return false;
    }
  }
  return true;
}


/**
 * Normalizes angle to (-pi, pi]
 * 
 * @returns normalized angle, in radians
*/
double Utils::NormalizeAng(const double ang) {
  double ang2 = std::fmod(ang, M_PI * 2);
  ang2 = std::fmod(ang2 + M_PI * 2, M_PI * 2);
  if (ang2 > M_PI) {
    ang2 -= M_PI * 2;
  }

  return ang2;
}

/**
 * Normalizes angle to (-180, 180]
 * 
 * @returns Normalized angle, in degrees
 */
double Utils::NormalizeAngDeg(const double ang) {
  double angRad = ang * (M_PI / 180.0);
  angRad = NormalizeAng(angRad);
  return angRad * (180.0 / M_PI); 
}

/**
 * Gets the current time from robot start in ms
 * 
 * @returns Current robot time in ms
*/
std::size_t Utils::GetCurTimeMs() {
  auto curTime = frc::Timer::GetFPGATimestamp();
  auto timeMs = curTime.convert<units::millisecond>();
  return static_cast<std::size_t>(timeMs.value());
}

/**
 * Gets current time from robot start in s
 * 
 * @returns Current robot time in s
*/
double Utils::GetCurTimeS() {
  auto curTime = frc::Timer::GetFPGATimestamp();
  auto timeS = curTime.convert<units::second>(); 
  return timeS.value();
}

/**
 * Converst degrees to radians
 * 
 * @param deg Angle in degrees
 * 
 * @returns Angle in radians
*/
double Utils::DegToRad(const double deg) {
  return deg * (M_PI / 180.0);
}

/**
 * Converts radians to degrees
 * 
 * @param rad Angle in radians
 * 
 * @returns Angle in degrees
*/
double Utils::RadToDeg(const double rad) {
  return rad * (180.0 / M_PI);
}


/**
 * Converts inches to meters
 * 
 * @param in Length in inches
 * 
 * @returns meters
*/
double Utils::InToM(const double in) {
  return units::inch_t{in}.convert<units::meters>().value();
}

/**
 * Converts inches to meters
 * 
 * @param in Vector lengths in inches
 * 
 * @returns meters
*/
vec::Vector2D Utils::InToM(const vec::Vector2D in) {
  vec::Vector2D ret;
  for (int i = 0; i < 2; i++) {
    ret[i] = units::inch_t{in[i]}.convert<units::meters>().value();
  }
  return ret;
}

/**
 * Gets unit vector from a direction angle
 * 
 * @param ang Direction angle
 * 
 * @returns Unit vector with a direction in the indicated angle
*/
vec::Vector2D Utils::GetUnitVecDir(const double ang) {
  return vec::Vector2D{std::cos(ang), std::sin(ang)};
}

/**
 * Gets component of v in the direction of w
 * 
 * @param v Vector to project
 * @param w Reference vector, must be nonzero
 * 
 * @returns Component of v in the direction of w
*/
vec::Vector2D Utils::GetProjection(const vec::Vector2D v, const vec::Vector2D w) {
  return w * (dot(v, w) / (magn(w) * magn(w)));
}

/**
 * Gets angle between two vectors
 * 
 * @param v1 First vector (must be nonzero)
 * @param v2 Second vector (must be nonzero)
 * 
 * @returns Angle between two vectors
*/
double Utils::GetAngBetweenVec(const vec::Vector2D v1, const vec::Vector2D v2) {
 return std::acos(std::clamp(
      dot(v1, v2) / (magn(v1) * magn(v2)), -1.0, 1.0));
}

/**
 * Multiplies components of vectors together and forms into new vector
 * 
 * @param v1 first vector
 * @param v2 second vector
 * 
 * @returns <v1.x*v2.x, v1.y*v2.y>
*/
vec::Vector2D Utils::MultiplyComps(const vec::Vector2D v1, const vec::Vector2D v2) {
  return {v1.x() * v2.x(), v1.y() * v2.y()};
}

/**
 * Rounds vec to 2 digits
 * 
 * @param vec vector
 * 
 * @returns vector in 2 digits
*/
vec::Vector2D Utils::Round2(const vec::Vector2D vec) {
  vec::Vector2D ret;
  for (int i = 0; i < 2; i++) {
    ret[i] = std::round(vec[i] * 100.0) / 100.0;
  }

  return ret;
}

/**
 * Rounds number to 2 digits
 * 
 * @param num number
 * 
 * @returns rounded number
*/
double Utils::Round2(const double num) {
  return std::round(num * 100.0) / 100.0;
}

/**
 * Returns the sign of the double
 * 
 * @returns -1.0, 0.0, or 1.0
*/
double Utils::Sign(double x){
  if(x > 0.0){
    return 1.0;
  }
  else if(x < 0.0){
    return -1.0;
  }
  else{
    return 0.0;
  }
}