#pragma once
#include "Surface.h"

class Box :
	public Surface
{
private:
	BoundingBox m_bounding_box;

public:
	Box(const BoundingBox new_box, Material new_mat = Material());
	Box(const Vector3 min_pos, const float size, Material new_mat = Material());
	Box(const Vector3 new_min, const Vector3 new_max, Material new_mat = Material());

	virtual ~Box() {}

	virtual bool hit(const Ray3D& ray, HitRecord& r_rec);
	virtual BoundingBox bounding_box() override { return m_bounding_box; }
};