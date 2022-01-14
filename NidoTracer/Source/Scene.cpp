#include "Scene.h"

Scene::Scene()
{
	
}

Scene::~Scene()
{
	scene_objects.delete_all_payload();
	light_objects.delete_all_payload();
}

bool Scene::determine_closest_hit_surface(const Ray3D& the_view_ray, HitRecord& the_hit_record, const bool ignore_bvh) 
{
	float min_time = INFINITY;
	bool is_hit = false;

	HitRecord cur_hit_rec;
	HitRecord main_hit_rec;

	if (ignore_bvh || (m_the_bvh.m_left == nullptr && m_the_bvh.m_right == nullptr))
	{
		// no bvh setup, we use all scene objects
		QueueNode<Surface*>* sel_node = scene_objects.get_head_node();

		while (sel_node != nullptr)
		{
			Surface& sel_surface = *sel_node->get_data();

			if (sel_surface.hit(the_view_ray, cur_hit_rec) && cur_hit_rec.m_time < the_view_ray.get_max_length() && cur_hit_rec.m_time < min_time)
			{
				min_time = cur_hit_rec.m_time;
				//hit_surface = &sel_surface;
				main_hit_rec = cur_hit_rec;
				is_hit = true;
			}

			sel_node = sel_node->next();
		}
	}
	else
	{
		// go through the bvh 
		is_hit = m_the_bvh.hit(the_view_ray, main_hit_rec);

		if (!is_hit)
		{
			QueueNode<Surface*>* sel_node = scene_objects.get_head_node();

			while (sel_node != nullptr)
			{
				Surface& sel_surface = *sel_node->get_data();
				if (sel_surface.is_of_type(SurfaceType::SurfacePlane))
					if (sel_surface.hit(the_view_ray, cur_hit_rec) && cur_hit_rec.m_time < the_view_ray.get_max_length() && cur_hit_rec.m_time < min_time)
					{
						min_time = cur_hit_rec.m_time;
						main_hit_rec = cur_hit_rec;
						is_hit = true;
					}

				sel_node = sel_node->next();
			}
		}
	}
	
	the_hit_record = main_hit_rec;
	return is_hit;
}