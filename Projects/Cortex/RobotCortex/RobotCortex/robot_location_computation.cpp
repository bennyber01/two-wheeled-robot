#include "robot_location_computation.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "Matrix2x2.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

double deg_2_rad(double deg) { return deg * M_PI / 180.0; }
double rad_2_deg(double rad) { return rad * 180.0 / M_PI; }

WheelsLocation compute_new_location_no_rotation(const WheelsLocation & oldLocation, double wheel_l_dist, double wheel_r_dist, WheelsLocationsHolder * wheelsLocationsHolder)
{
	Vector2D dir_x = oldLocation.rightWheelLoc - oldLocation.leftWheelLoc;
	dir_x.Normalize();
	Vector2D dir_y(-dir_x.y, dir_x.x);

	// compute final result
	WheelsLocation result;
	result.leftWheelLoc  = oldLocation.leftWheelLoc  + dir_y * wheel_l_dist;
	result.rightWheelLoc = oldLocation.rightWheelLoc + dir_y * wheel_r_dist;

	if (wheelsLocationsHolder)
	{
		WheelsLocation currLoc;

		currLoc.leftWheelLoc  = oldLocation.leftWheelLoc;
		currLoc.rightWheelLoc = oldLocation.rightWheelLoc;
		wheelsLocationsHolder -> push_back(currLoc);

		int num_of_segments = ceil(MAX(fabs(wheel_l_dist), fabs(wheel_r_dist)));

		if (num_of_segments)
		{
			// compute update pos
			double update_pos_l = wheel_l_dist / num_of_segments;
			double update_pos_r = wheel_r_dist / num_of_segments;

			for (int i = 0; i < num_of_segments; ++i)
			{
				currLoc.leftWheelLoc  = currLoc.leftWheelLoc  + dir_y * update_pos_l;
				currLoc.rightWheelLoc = currLoc.rightWheelLoc + dir_y * update_pos_r;
				wheelsLocationsHolder -> push_back(currLoc);

#ifdef DEBUG_MY_PROGRAM
				double curr_dist_between_wheels0 = (oldLocation.leftWheelLoc - oldLocation.rightWheelLoc).Length();
				double curr_dist_between_wheels1 = (currLoc.leftWheelLoc - currLoc.rightWheelLoc).Length();
				double error = fabs(curr_dist_between_wheels0 - curr_dist_between_wheels1);
				ASSERT(error < 0.000001);
#endif
			}
		}

#ifdef DEBUG_MY_PROGRAM
		double curr_dist_between_left_wheels  = (result.leftWheelLoc - currLoc.leftWheelLoc).Length();
		double curr_dist_between_right_wheels = (result.rightWheelLoc - currLoc.rightWheelLoc).Length();
		ASSERT(curr_dist_between_left_wheels < 0.000001 && curr_dist_between_right_wheels < 0.000001);
#endif
	}

	return result;
}



WheelsLocation compute_new_location_with_roration(const WheelsLocation & oldLocation, double wheel_l_dist, double wheel_r_dist, WheelsLocationsHolder * wheelsLocationsHolder)
{
	double dist_between_wheels  = (oldLocation.rightWheelLoc - oldLocation.leftWheelLoc).Length();

	double alpha_rad = (wheel_l_dist - wheel_r_dist) / dist_between_wheels;
#ifdef DEBUG_MY_PROGRAM
	double alpha_deg = rad_2_deg(alpha_rad);
#endif
	double r = wheel_r_dist / alpha_rad;

	// compute final result
	Matrix2x2 rotation_matrix(cos(alpha_rad), sin(alpha_rad), -sin(alpha_rad), cos(alpha_rad));
	Vector2D dir_x = oldLocation.rightWheelLoc - oldLocation.leftWheelLoc;
	dir_x.Normalize();
	Vector2D center = oldLocation.rightWheelLoc + dir_x * r;

	WheelsLocation result;
	result.leftWheelLoc  = center + rotation_matrix * (oldLocation.leftWheelLoc - center);
	result.rightWheelLoc = center + rotation_matrix * (oldLocation.rightWheelLoc - center);

	if (wheelsLocationsHolder)
	{
		WheelsLocation currLoc;

		currLoc.leftWheelLoc  = oldLocation.leftWheelLoc;
		currLoc.rightWheelLoc = oldLocation.rightWheelLoc;
		wheelsLocationsHolder -> push_back(currLoc);
		
		int num_of_segments = ceil(MAX(fabs(wheel_l_dist), fabs(wheel_r_dist)));

		double alpha = alpha_rad / num_of_segments;

		Matrix2x2 rotation_matrix(cos(alpha), sin(alpha), -sin(alpha), cos(alpha));

		for (int i = 0; i < num_of_segments; ++i)
		{
			dir_x = currLoc.rightWheelLoc - currLoc.leftWheelLoc;
			dir_x.Normalize();

			Vector2D center = currLoc.rightWheelLoc + dir_x * r;

			currLoc.leftWheelLoc = center + rotation_matrix  * (currLoc.leftWheelLoc - center);
			currLoc.rightWheelLoc = center + rotation_matrix * (currLoc.rightWheelLoc - center);
			wheelsLocationsHolder -> push_back(currLoc);

#ifdef DEBUG_MY_PROGRAM
			double curr_dist_between_wheels0 = (oldLocation.leftWheelLoc - oldLocation.rightWheelLoc).Length();
			double curr_dist_between_wheels1 = (currLoc.leftWheelLoc - currLoc.rightWheelLoc).Length();
			double error = fabs(curr_dist_between_wheels0 - curr_dist_between_wheels1);
			ASSERT(error < 0.000001);
#endif
		}

#ifdef DEBUG_MY_PROGRAM
		double curr_dist_between_left_wheels  = (result.leftWheelLoc - currLoc.leftWheelLoc).Length();
		double curr_dist_between_right_wheels = (result.rightWheelLoc - currLoc.rightWheelLoc).Length();
		ASSERT(curr_dist_between_left_wheels < 0.000001 && curr_dist_between_right_wheels < 0.000001);
#endif
	}

	return result;
}

WheelsLocation computeNewLocation(const WheelsLocation & oldLocation, const MotorsTicks & motorsTicks, WheelsLocationsHolder * wheelsLocationsHolder)
{
	double wheel_l_dist = deg_2_rad(motorsTicks.leftMotorTicks) * WHEEL_RADIUS;
	double wheel_r_dist = deg_2_rad(motorsTicks.rightMotorTicks) * WHEEL_RADIUS;

	WheelsLocation result;

	if (motorsTicks.leftMotorTicks == motorsTicks.rightMotorTicks)
		result = compute_new_location_no_rotation(oldLocation, wheel_l_dist, wheel_r_dist, wheelsLocationsHolder);
	else
		result = compute_new_location_with_roration(oldLocation, wheel_l_dist, wheel_r_dist, wheelsLocationsHolder);

#ifdef DEBUG_MY_PROGRAM
	double dist_between_wheels0 = (oldLocation.leftWheelLoc - oldLocation.rightWheelLoc).Length();
	double dist_between_wheels1 = (result.leftWheelLoc - result.rightWheelLoc).Length();
	double error = fabs(dist_between_wheels0 - dist_between_wheels1);
	if (error > 0.0000001)
	{
		ASSERT(false);
	}
#endif

	return result;
}