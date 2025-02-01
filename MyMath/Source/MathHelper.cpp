#include "MathHelper.h"

// Constants
const double PI = 3.14159265358979323846;

float deg_to_rad(float deg_angle)
{
	float rad_angle = (deg_angle * (float)PI) / 180.0f;
	return rad_angle;
}

float min(float a, float b) {

	return a < b ? a : b;
}

float max(float a, float b) {

	return a > b ? a : b;
}

float clamp(float value, float min_value, float max_value) {

	return max(min(value, max_value), min_value);
}
