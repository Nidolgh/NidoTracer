#pragma once

#include "../Math/Vector3.h"
#include "Ray3D.h"

class Shape
{
public:
	Shape();
	
	virtual float Intersection(Ray3D& rayToCheck, float time) = 0;
};