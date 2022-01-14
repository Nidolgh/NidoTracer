#pragma once
#include "Surface.h"

// https://gamedev.stackexchange.com/questions/162819/how-do-axis-aligned-bounding-boxes-update-with-rotations
class Box_Rotatable :
	public Surface
{
private:
	BoundingBox m_bounding_box;

	Vector3 m_corners[8];
	
public:
	Box_Rotatable(const BoundingBox new_box, Material new_mat = Material());
	Box_Rotatable(const Vector3 min_pos, const float size, Material new_mat = Material());
	Box_Rotatable(const Vector3 new_min, const Vector3 new_max, Material new_mat = Material());

	// virtual ~Box_Rotatable() {}

	virtual bool hit(const Ray3D& ray, HitRecord& r_rec);
	virtual BoundingBox bounding_box() override { return m_bounding_box; }

	void populate_corners();
};