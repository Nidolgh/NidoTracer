#pragma once
#include "../Math/Vector3.h"
#include "../Objects/Ray3D.h"

class BoundingBox
{
private:
	#pragma warning(push)
	#pragma warning(disable: 4201)
	union
	{
		Vector3 m_bounds[2];

		struct
		{
			Vector3 m_min;
			Vector3 m_max;
		};
	};
	#pragma warning(pop)

public:
	BoundingBox(Vector3 new_min, Vector3 new_max) : m_min(new_min), m_max(new_max) {}

	bool hit(const Ray3D& ray);
	
	const Vector3* get_bounds() const { return m_bounds; }
	void set_min(const Vector3 new_min) { m_min = new_min; }
	void set_max(const Vector3 new_max) { m_max = new_max; }
	Vector3 get_min() const { return m_min; }
	Vector3 get_max() const { return m_max; }

	void set_x_min(const float new_x) { m_min.x = new_x; }
	void set_y_min(const float new_y) { m_min.y = new_y; }
	void set_z_min(const float new_z) { m_min.z = new_z; }
	void set_x_max(const float new_x) { m_max.x = new_x; }
	void set_y_max(const float new_y) { m_max.y = new_y; }
	void set_z_max(const float new_z) { m_max.z = new_z; }
};