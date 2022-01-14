#include "Ray3D.h"

Ray3D::Ray3D(const Vector3 new_origin, const Vector3 new_dir, const float max_length) :
	m_origin(new_origin), m_max_length(max_length)
{
	set_direction(new_dir);
}

void Ray3D::set_direction(const Vector3 new_dir)
{
	m_direction = new_dir.Unit();
	
	m_inv_dir = m_direction.GetInvert();
	m_inv_sign[0] = (m_inv_dir.x < 0);
	m_inv_sign[1] = (m_inv_dir.y < 0);
	m_inv_sign[2] = (m_inv_dir.z < 0);
}