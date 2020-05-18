#pragma once

#include "Component.hpp"

struct Player : Component
{
private:

public:
	// Units per frame
	float speed = 0.08f;
	// Radians per frame
	float turnSpeed = 0.04;
};