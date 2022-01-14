#pragma once
#include "Surface.h"

class Plane :
	public Surface
{
public:
	Plane(const Vector3 new_origin, const Vector3 new_normal, Material new_mat = Material());

	virtual bool hit(const Ray3D& ray_to_check, HitRecord& r_rec);
	virtual BoundingBox bounding_box();

private:
	Vector3 m_normal = Vector3(0, 0, 0);
};