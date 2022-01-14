#include "BVH.h"

BVHNode::BVHNode() : box_bounds(Vector3(0), 0)
{
	m_surface_type = SurfaceType::SurfaceBVH;
}

BVHNode::BVHNode(Queue<Surface*>& object_queue, int axis) : box_bounds(Vector3(0), 0)
{
	m_surface_type = SurfaceType::SurfaceBVH;
	create(object_queue, axis);
}

BVHNode::~BVHNode()
{
	
}

bool BVHNode::hit(const Ray3D& ray_to_check, HitRecord& the_hit_record)
{
	HitRecord temp;
	if (box_bounds.hit(ray_to_check, temp))
	{
		HitRecord lrec, rrec;

		const bool left_hit = (m_left != nullptr) && (m_left->hit(ray_to_check, lrec));
		const bool right_hit = (m_right != nullptr) && (m_right->hit(ray_to_check, rrec));

		if ((left_hit && lrec.m_time < ray_to_check.get_max_length()) && (right_hit && rrec.m_time < ray_to_check.get_max_length()))
		{
			if (lrec.m_time < rrec.m_time)
			{
				the_hit_record = lrec;
			}
			else
			{
				the_hit_record = rrec;
			}
			return true;
		}
		if (left_hit && lrec.m_time < ray_to_check.get_max_length())
		{
			the_hit_record = lrec;
			return true;
		}
		if (right_hit && rrec.m_time < ray_to_check.get_max_length())
		{
			the_hit_record = rrec;
			return true;
		}
	}
	
	return false;
}

BoundingBox combine(const BoundingBox& first, const BoundingBox& second)
{
	BoundingBox new_bounds = first;

	if (new_bounds.get_min().x > second.get_min().x)
		new_bounds.set_x_min(second.get_min().x);
	if (new_bounds.get_min().y > second.get_min().y)
		new_bounds.set_y_min(second.get_min().y);
	if (new_bounds.get_min().z > second.get_min().z)
		new_bounds.set_z_min(second.get_min().z);

	if (new_bounds.get_max().x < second.get_max().x)
		new_bounds.set_x_max(second.get_max().x);
	if (new_bounds.get_max().y < second.get_max().y)
		new_bounds.set_y_max(second.get_max().y);
	if (new_bounds.get_max().z < second.get_max().z)
		new_bounds.set_z_max(second.get_max().z);
	
	return new_bounds;
}

// https://www.geeksforgeeks.org/cpp-program-for-quicksort/
//void swap(QueueNode<Surface*>* a, QueueNode<Surface*>* b)
//{
//	Surface* temp = a->get_data();
//	a->set_data(b->get_data());
//	b->set_data(temp);
//}

// sort based on vector3 axis
//void quick_sort_axis(
//	Queue<Surface*>& object_queue, 
//	int low, 
//	int high, const int axis)
//{
//	int i_count = low;
//	QueueNode<Surface*>* i = object_queue.get_head_node()->next_amount(i_count);
//	int j_count = high;
//	QueueNode<Surface*>* j = object_queue.get_head_node()->next_amount(j_count);
//	QueueNode<Surface*>* pivot = object_queue.get_head_node()->next_amount((i_count + j_count) * 0.5f);
//	QueueNode<Surface*>* temp;
//
//	while(i->get_data()->get_origin().f[axis] <= j->get_data()->get_origin().f[axis])
//	{
//		while (i->get_data()->get_origin().f[axis] < pivot->get_data()->get_origin().f[axis])
//		{
//			i_count++;
//			i = i->next();
//		}
//		while (j->get_data()->get_origin().f[axis] > pivot->get_data()->get_origin().f[axis])
//		{
//			j_count--;
//			j = j->prev();
//		}
//		
//		if (i->get_data()->get_origin().f[axis] <= j->get_data()->get_origin().f[axis])
//		{
//			swap(i, j);
//			i_count++;
//			i = i->next();
//			j_count--;
//			j = j->prev();
//		}
//	}
//	if (j_count > low)
//		quick_sort_axis(object_queue, low, j_count, axis);
//	if (i_count < high)
//		quick_sort_axis(object_queue, i_count, high, axis);
//}

void BVHNode::create(Queue<Surface*>& object_array, int axis)
{
	const int count = object_array.get_count();
	if (count == 0)
	{
		//assert(count);
		return;
	}
	
	QueueNode<Surface*>* head_node = object_array.get_head_node();
	
	if (count == 1)
	{
		m_left = (head_node->get_data()->is_of_type(SurfaceType::SurfacePlane) ? nullptr : head_node->get_data());
		m_right = nullptr;
		if (m_left != nullptr)
			box_bounds = Box(m_left->bounding_box());
	}
	else if (count == 2)
	{
		m_left = (head_node->get_data()->is_of_type(SurfaceType::SurfacePlane) ? nullptr : head_node->get_data());
		m_right = (head_node->next()->get_data()->is_of_type(SurfaceType::SurfacePlane) ? nullptr : head_node->next()->get_data());
		if (m_left != nullptr && m_right != nullptr)
			box_bounds = combine(m_left->bounding_box(), m_right->bounding_box());
		else if (m_left != nullptr)
			box_bounds = Box(m_left->bounding_box());
		else if (m_right != nullptr)
			box_bounds = Box(m_right->bounding_box());
	}
	else
	{
		QueueNode<Surface*>* sel_node = object_array.get_head_node();
		Queue<Surface*> p_list_0;
		Queue<Surface*> p_list_1;
		BoundingBox new_bounds(Vector3(0), Vector3(0));

		bool initial_set = false;
		while (sel_node != nullptr)
		{
			Surface* sel_sur = sel_node->get_data();
			if (!sel_sur->is_of_type(SurfaceType::SurfacePlane))
			{
				if (!initial_set)
					new_bounds = sel_sur->bounding_box(), initial_set = true;
				
				if (new_bounds.get_min().x > sel_sur->bounding_box().get_min().x)
					new_bounds.set_x_min(sel_sur->bounding_box().get_min().x);
				if (new_bounds.get_min().y > sel_sur->bounding_box().get_min().y)
					new_bounds.set_y_min(sel_sur->bounding_box().get_min().y);
				if (new_bounds.get_min().z > sel_sur->bounding_box().get_min().z)
					new_bounds.set_z_min(sel_sur->bounding_box().get_min().z);

				if (new_bounds.get_max().x < sel_sur->bounding_box().get_max().x)
					new_bounds.set_x_max(sel_sur->bounding_box().get_max().x);
				if (new_bounds.get_max().y < sel_sur->bounding_box().get_max().y)
					new_bounds.set_y_max(sel_sur->bounding_box().get_max().y);
				if (new_bounds.get_max().z < sel_sur->bounding_box().get_max().z)
					new_bounds.set_z_max(sel_sur->bounding_box().get_max().z);
			}
			sel_node = sel_node->next();
		}

		const Vector3 middle_point = (new_bounds.get_min() + new_bounds.get_max()) * 0.5f;
		sel_node = object_array.get_head_node();
		while (sel_node != nullptr)
		{
			Surface* sel_sur = sel_node->get_data();
			if (!sel_sur->is_of_type(SurfaceType::SurfacePlane))
			{
				const float m_f = middle_point.f[axis];
				const float m_o = sel_sur->get_origin().f[axis];
				if (m_f > m_o)
				{
					p_list_0.push(sel_sur);
				}
				else
				{
					p_list_1.push(sel_sur);
				}
			}
			sel_node = sel_node->next();
		}

		if (++axis >= 3)
			axis = 0;

		if (p_list_0.get_count() > 0)
			m_left = new BVHNode(p_list_0, axis);
		if (p_list_1.get_count() > 0)
			m_right = new BVHNode(p_list_1, axis);
		box_bounds = new_bounds;

		//quick_sort_axis(partitioned_list, 0, partitioned_list.get_count(), axis);
	}
}

Color BVHNode::visualize(const Ray3D& ray, float dyn_col)
{
	Color col_pix = Color(0);

	if (box_bounds.bounding_box().hit(ray))
	{
		dyn_col++;
		col_pix += Color(0.0f, dyn_col * 0.05f, 0.0f);
		/*if (dyn_col > 4)
			col_pix.r += dyn_col * 0.1f, col_pix.g = 0;*/
		
		if (m_left != nullptr && m_left->is_of_type(SurfaceType::SurfaceBVH))
			col_pix += dynamic_cast<BVHNode*>(m_left)->visualize(ray, dyn_col);

		if (m_right != nullptr && m_right->is_of_type(SurfaceType::SurfaceBVH))
			col_pix += dynamic_cast<BVHNode*>(m_right)->visualize(ray, dyn_col);
	}
	
	return col_pix;
}
