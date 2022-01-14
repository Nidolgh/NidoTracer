#pragma once

#include "../Objects/Box.h"
#include "Queue.h"

class BVHNode : public Surface
{
public:
	BVHNode();
	BVHNode(Queue<Surface*>& object_queue, int axis);
	virtual ~BVHNode();
	
	virtual bool hit(const Ray3D& ray_to_check, HitRecord& r_rec) override;
	virtual BoundingBox bounding_box() override { return box_bounds.bounding_box(); }

	void create(Queue<Surface*>& object_array, int axis);
	Color visualize(const Ray3D& ray, float dyn_col = 1.0f);
	
	Surface* m_left = nullptr;
	Surface* m_right = nullptr;
	
	Box box_bounds;
};