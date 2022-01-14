#pragma once
#include "Surface.h"

class Triangle :
	public Surface
{
private:
	Vector3 m_a = Vector3(0.0f);
	Vector3 m_b = Vector3(0.0f);
	Vector3 m_c = Vector3(0.0f);
	
public:
	Triangle(const Vector3 a, const Vector3 b, const Vector3 c);
	virtual ~Triangle();

	virtual bool hit(const Ray3D& ray, HitRecord& r_rec);
	virtual BoundingBox bounding_box() override { return BoundingBox(Vector3(0), Vector3(0)); }
};