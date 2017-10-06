/// @file
#ifndef INFRARED_HPP
#define INFRARED_HPP

#include "wheels.hpp"
/// Infared
//
/// Create the variables and functions
class infrared{
private:
    int state;
public:
	infrared(int state);
	void init();
	int check();
	void drive(int ir_value);
};

#endif //INFRARED_HPP