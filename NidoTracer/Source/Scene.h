#pragma once
#include "DataTypes/LinkedList.h"
#include "DataTypes/Queue.h"

#include "DataTypes/BVH.h"

#include "Objects/Camera.h"
#include "Objects/Lights/PointLight.h"

class Scene
{
protected:
	int m_reflection_depth = 1;
	
	bool m_animate = false;
	bool m_shadow = false;
	bool m_visualize_bvh = false;
	
	float m_ambient_intensity = 0.1f;
	Color m_ambient_color = Color(0.05f);
	
public:
	Scene();
	virtual ~Scene();
	bool determine_closest_hit_surface(const Ray3D& the_view_ray, HitRecord& the_hit_record, const bool ignore_bvh = false);

	bool is_animated() const { return m_animate; }
	void set_animation_state(const bool state) { m_animate = state; }
	bool get_shadow() const { return m_shadow; }
	void set_shadow_state(const bool state) { m_shadow = state; }
	bool get_visualize_bvh_state() const { return m_visualize_bvh; }
	void set_visualize_bvh_state(const bool state) { m_visualize_bvh = state; }
	float get_ambient_intensity() const { return m_ambient_intensity; }
	void set_ambient_intensity(const float ambient_intensity) { m_ambient_intensity = ambient_intensity; }
	Color get_ambient_color() const { return m_ambient_color; }
	void set_ambient_color(const Color ambient_col) { m_ambient_color = ambient_col; }
	int get_reflection_depth() const { return m_reflection_depth; }
	void set_reflection_depth(const int new_depth) { m_reflection_depth = new_depth; }
	
	const Camera& get_active_camera() const { return the_camera; }

	Camera the_camera;
	
	Queue<Surface*> scene_objects;
	Queue<PointLight*> light_objects;

	BVHNode m_the_bvh;
	
	PointLight test_light;
	
	Color m_background_color = Color(0, 0.5f, 0.75f);
};