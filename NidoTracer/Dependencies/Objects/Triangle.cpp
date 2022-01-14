#include "Triangle.h"

Triangle::Triangle(const Vector3 a, const Vector3 b, const Vector3 c) : m_a(a), m_b(b), m_c(c)
{
	m_surface_type = SurfaceType::SurfaceTriangle;

	m_material.m_dif_col = Color(1, 0, 0);
	m_material.m_diffuse = 1.0f;
	//m_material.m_specular = 1.0f;
	m_material.m_specular_reflection = true;
}

Triangle::~Triangle()
{
}

bool Triangle::hit(const Ray3D& ray, HitRecord& r_rec)
{
	// Cramer’s rule
	const float a = m_a.x - m_b.x, d = m_a.x - m_c.x, g = ray.get_direction().x;
	const float b = m_a.y - m_b.y, e = m_a.y - m_c.y, h = ray.get_direction().y;
	const float c = m_a.z - m_b.z, f = m_a.z - m_c.z, i = ray.get_direction().z;

	const float j = m_a.x - ray.get_origin().x;
	const float k = m_a.y - ray.get_origin().y;
	const float l = m_a.z - ray.get_origin().z;

	const float M =			 a * (e * i - h * f) + b * (g * f - d * i) + c * (d * h - e * g);
	const float B =			(j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / M;
	const float Y =		    (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / M;
	const float t = abs((f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / M);

	if (t < 0 || t > ray.get_max_length())
		return false;
	if (Y < 0 || Y > 1)
		return false;
	if (B < 0 || B > 1 - Y)
		return false;

	r_rec.m_time = t;
	r_rec.m_intersection_point = ray.get_point_on_time(t);
	const Vector3 calculated_normal = (m_b - m_a).Cross(m_c - m_a).Unit();
	r_rec.m_hit_normal = calculated_normal;
	r_rec.m_material = &get_material();
	return true;
}
