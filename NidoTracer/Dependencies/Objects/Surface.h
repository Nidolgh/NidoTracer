#pragma once

#include "../Math/Vector3.h"
#include "Ray3D.h"

#include "../Misc/BoundingBox.h"
#include "../Misc/HitRecord.h"
#include "../Misc/Material.h"
#include "../Math/MathDefines.h"

enum SurfaceType
{
	SurfaceEmpty,
	SurfaceBVH,
	SurfacePlane,
	SurfaceSphere,
	SurfaceBox,
	SurfaceTorus,
	SurfaceTriangle,
	SurfaceMesh_OBJ
};

class Surface
{
protected:
	Vector3 m_origin = Vector3(0, 0, 0);
	Material m_material;

	SurfaceType m_surface_type = SurfaceType::SurfaceEmpty;
	
public:
	Surface();

	virtual bool hit(const Ray3D& ray_to_check, HitRecord& r_rec) = 0;
	virtual BoundingBox bounding_box() = 0;

	Material& get_material() { return m_material; }
	void set_material(Material& new_mat) { m_material = new_mat; }

	Vector3 get_origin() const { return m_origin; }
	Color get_color() const { return m_material.m_dif_col; }

	void set_surface_type(const SurfaceType new_type) { m_surface_type = new_type; }
	SurfaceType get_surface_type() const { return m_surface_type; }
	bool is_of_type(const SurfaceType check) const { return check == m_surface_type; }
};