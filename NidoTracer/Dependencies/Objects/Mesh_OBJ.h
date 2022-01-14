#pragma once
#include "Triangle.h"
#include "../DataTypes/LinkedList.h"

class Mesh_OBJ :
	public Surface
{
private:
//	const char* m_file_name;
	LinkedList<Triangle*> m_triangles;
	
public:
	Mesh_OBJ(const Vector3 origin, const char* file_name);
	virtual ~Mesh_OBJ();
	
	virtual bool hit(const Ray3D& ray, HitRecord& r_rec);
	virtual BoundingBox bounding_box() override { return BoundingBox(Vector3(0), Vector3(0)); }
};