#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Math/MathDefines.h"

#include "DataTypes/LinkedList.h"
#include "DataTypes/BVH.h"
#include "DataTypes/HashTable.h"
#include "DataTypes/Queue.h"

#include <UnitTest/doctest.h>
#include <Math/TestVector2.h>
#include <Math/Vector3.h>

#include "Objects/Ray3D.h"
#include "Objects/Plane.h"
#include "Objects/Sphere.h"
#include "Objects/Mesh_OBJ.h"

#include "Math/Max.h"

float rand_0_1() { return (static_cast<float>(rand()) / RAND_MAX); }

bool check_if_in_range_of_epsilon(const float var,const float var_to_check)
{
	if (var_to_check + S_EPSILON > var && var_to_check - S_EPSILON < var)
		return true;

	return false;
}

TEST_CASE("Mesh")
{
	SUBCASE("Loading")
	{
		Mesh_OBJ suzanne_obj(Vector3(-2.0f, 0.0f, -0.5f), "../Project_Raytracer/3D_OBJ/Suz_tri.oobj");
		// check if vertices match up - 190
	}
}

TEST_CASE("Spatial Datastructures")
{
	SUBCASE("BVH")
	{
		Queue<Surface*> surface_list;
		for (size_t i = 0; i < 5; i++)
		{
			const float placement_rad = 20;

			const float r_rad = (static_cast<float>(rand()) / RAND_MAX) + 0.1f;

			const Vector3 new_vec = Vector3(rand_0_1() - 0.5f, 0, rand_0_1()) * placement_rad;

			surface_list.push(new Sphere(Vector3(new_vec), r_rad));
		}
		
		HitRecord temp_record;
		Ray3D ray_forward(Vector3(0, 0, 0), Vector3(0, 0, 1));
		BVHNode the_bvh;
		the_bvh.create(surface_list, 0);

		CHECK(the_bvh.hit(ray_forward, temp_record));
		
		surface_list.delete_all_payload();
	}
}

TEST_CASE("Data Structures")
{
	SUBCASE("LinkedList")
	{
		int temp = 0;
		LinkedList<int> l_int_list;
		l_int_list.push(20);
		l_int_list.push(90);
		l_int_list.push(65);
		l_int_list.push(82);
		temp = l_int_list.get_count();
		CHECK(temp == 4);
		CHECK(82 == l_int_list.get_top()->GetData());
		l_int_list.pop();
		CHECK(l_int_list.get_count() == 3);
		CHECK(l_int_list.get_top()->GetData() == 65);
		l_int_list.pop();
		l_int_list.pop();
		l_int_list.pop();
		CHECK(l_int_list.get_count() == 0);
	}
	
	SUBCASE("Queue")
	{
		Queue<int> l_int_queue;
		l_int_queue.push(20);
		l_int_queue.push(90);
		l_int_queue.push(65);
		l_int_queue.push(82);

		CHECK(4 == l_int_queue.get_count());
		CHECK(82 == l_int_queue.get_head_node()->get_data());
		CHECK(20 == l_int_queue.get_tail_node()->get_data());
		l_int_queue.pop();
		CHECK(3 == l_int_queue.get_count());
		CHECK(82 == l_int_queue.get_head_node()->get_data());
		l_int_queue.pop();
		l_int_queue.pop();
		l_int_queue.pop();
		CHECK(0 == l_int_queue.get_count());
	}
	
	SUBCASE("Hash Map")
	{
		HashTable hash_table;
		
		const char* key_0 = "Example one";
		int val_0 = 5;
		const char* key_1 = "Example two";
		const int val_1 = 88;
		const char* key_2 = "Visual Studio";
		const int val_2 = 21;
		const char* key_3 = "Powerpoint";
		const int val_3 = 58;
		const char* key_4 = "Toggle";
		const int val_4 = 54;
		const char* key_5 = "Chrome";
		const int val_5 = 123;

		// set
		hash_table.Set(key_0, val_0);
		hash_table.Set(key_1, val_1);
		hash_table.Set(key_2, val_2);
		hash_table.Set(key_3, val_3);
		hash_table.Set(key_4, val_4);
		hash_table.Set(key_5, val_5);
		
		HashNode* node_0 = hash_table.Get(key_5);
		CHECK(node_0 != nullptr);
		CHECK(node_0->m_key == key_5);
		CHECK(node_0->m_value == val_5);
		HashNode* node_1 = hash_table.Get(key_3);
		CHECK(node_1 != nullptr);
		CHECK(node_1->m_key == key_3);
		CHECK(node_1->m_value == val_3);
		
		// update pre set
		hash_table.Set(key_0, 40);
		hash_table.Set(key_4, 12);
		hash_table.Set(key_5, 99);

		// get
		HashNode* set_node_0 = hash_table.Get(key_0);
		CHECK(set_node_0 != nullptr);
		CHECK(set_node_0->m_key == key_0);
		CHECK(40 == set_node_0->m_value);
		HashNode* set_node_1 = hash_table.Get(key_4);
		CHECK(set_node_1 != nullptr);
		CHECK(set_node_1->m_key == key_4);
		CHECK(12 == set_node_1->m_value);
		HashNode* set_node_2 = hash_table.Get(key_5);
		CHECK(set_node_2 != nullptr);
		CHECK(set_node_2->m_key == key_5);
		CHECK(99 == set_node_2->m_value);
	}
}

TEST_CASE("Misc math library")
{
	SUBCASE("MAX")
	{
		const float max_test_0 = 10.0f;
		const float max_test_1 = 20.5f;
		const float max_test_2 = 15.2f;
		float container_0 = Max(max_test_0, max_test_1);
		
		CHECK(container_0 == max_test_1);
		container_0 = Max(max_test_2, max_test_0);
		CHECK(container_0 == max_test_2);
	}
}

TEST_CASE("Testing Surface Ray intersection")
{
	HitRecord temp_record;

	SUBCASE("Plane")
	{
		Ray3D ray_down(Vector3(0, 0, 0), Vector3(0, -1, 0));
		Plane plane_0(Vector3(0, -10, 0), Vector3(0, 1, 0));

		CHECK(plane_0.hit(ray_down, temp_record));
	}

	SUBCASE("Sphere")
	{
		Ray3D ray_forward(Vector3(0, 0, 0), Vector3(0, 0, 1));
		Sphere sphere_0(Vector3(0, 0, 10), 1.0f);

		CHECK(sphere_0.hit(ray_forward, temp_record));
	}

	SUBCASE("Box")
	{
		Ray3D ray_forward(Vector3(0, 0, 0), Vector3(0, 0, 1));
		Box box_0(Vector3(0, 0, 10), 1.0f);

		CHECK(box_0.hit(ray_forward, temp_record));
	}

	SUBCASE("Triangle")
	{
		Ray3D ray_forward(Vector3(0, 0, 0), Vector3(0, 0, 1));
		Ray3D non_hit_ray(Vector3(0, -1, 0), Vector3(0, 0, 1));
		Triangle triangle_0(Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

		CHECK(triangle_0.hit(ray_forward, temp_record));
		CHECK(!triangle_0.hit(non_hit_ray, temp_record));
	}
}

TEST_CASE("Testing Vector2 functionality")
{
	SUBCASE("Construction")
	{
		/// Default constructor
		const Vector2 v0;
		CHECK(v0.x == 0.0f);
		CHECK(v0.y == 0.0f);

		/// Constructor from components
		const Vector2 v1(9.1f, -3.0f);
		CHECK(v1.x == 9.1f);
		CHECK(v1.y == -3.0f);

		/// Constructor from components
		const Vector2 v2(4.3f);
		CHECK(v2.x == 4.3f);
		CHECK(v2.y == 4.3f);

		/// Copy construction
		Vector2 v3(v2);
		CHECK(v2.x == v3.x);
		CHECK(v2.y == v3.y);

		/// Zero all the components of the vector
		v3.Clear();
		CHECK(v0.x == v3.x);
		CHECK(v0.y == v3.y);
	}

	SUBCASE("Mathematical operators")
	{
		const Vector2 v0(2.3f, 3.7f);
		const Vector2 v1(-6.6f, 1.2f);
		const float factor = 3.5f;
		Vector2 v2;

		/// Returns the value of the given vector added to this.
		v2 = v0 + v1;
		CHECK(v2.x == v0.x + v1.x);
		CHECK(v2.y == v0.y + v1.y);

		/// Returns the value of the given vector subtracted from this.
		v2 = v0 - v1;
		CHECK(v2.x == v0.x - v1.x);
		CHECK(v2.y == v0.y - v1.y);

		SUBCASE("Vector and scalar multiplication.")
		{
			/// Returns a copy of this vector scaled the given value.
			v2 = v1 * factor;
			CHECK(v2.x == v1.x * factor);
			CHECK(v2.y == v1.y * factor);

			/// Returns a new vector being the result of a float value multiplied on right hand side with a vector
			v2 = factor * v0;
			CHECK(v2.x == v0.x * factor);
			CHECK(v2.y == v0.y * factor);
		}

		/// Returns a copy of this vector scaled the given value.
		v2 = v0 / factor;
		CHECK(v2.x == v0.x / factor);
		CHECK(v2.y == v0.y / factor);

		SUBCASE("Dot product calculation.")
		{
			/// Calculates and returns the dot product of this vector with the given vector.
			const float dot = v0 * v1;
			CHECK(-10.74f == dot);

			const float calculated_dot = v0.Dot(v1);
			CHECK(dot == calculated_dot);
		}

		/// Adds the given vector to this.
		SUBCASE("Adds the given vector to this.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 += v0;
			CHECK(v3.x == v0.x + 3.0f);
			CHECK(v3.y == v0.y + -4.0f);
		}

		/// Subtracts the given vector from this
		SUBCASE("Subtracts the given vector from this.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 -= v1;
			CHECK(v3.x == 3.0f - v1.x);
			CHECK(v3.y == -4.0f - v1.y);
		}

		/// Multiplies this vector by the given scalar
		SUBCASE("Multiplies this vector by the given scalar.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 *= factor;
			CHECK(v3.x == 3.0f * factor);
			CHECK(v3.y == -4.0f * factor);
		}
	}

	SUBCASE("Logical operators")
	{
		/// Checks if the two vectors have identical components
		const float x = 2.93f;
		const float y = 4.39f;
		Vector2 v0(x, y);
		Vector2 v1(x, y);
		Vector2 v2(y, x);

		CHECK(v0 == v1);
		CHECK(v2 != v0);
	}

	SUBCASE("Length operations")
	{
		Vector2 v0(3.0f, 4.0f);

		/// Gets the magnitude of this vector
		const float vector_length = v0.Magnitude();
		CHECK(vector_length == 5.0f);

		/// Gets the squared magnitude of this vector
		const float vector_length_sqr = v0.SquareMagnitude();
		CHECK(vector_length_sqr == 25.0f);

		/// Limits the size of the vector to the given maximum
		v0.Trim(2.5f);
		CHECK(2.5f == v0.Magnitude());

		/// Returns the normalised version of a vector
		Vector2 v1 = v0;
		Vector2 v2 = v1.Unit();
		CHECK(v1 == v0);
		CHECK(1.0f == v2.Magnitude());

		/// Turns a non-zero vector into a vector of unit length
		v0.Normalize();
		CHECK(1.0f == v0.Magnitude());
	}
}

TEST_CASE("Testing Vector3 functionality")
{
	SUBCASE("Construction")
	{
		/// Default constructor
		const Vector3 v0;
		CHECK(v0.x == 0.0f);
		CHECK(v0.y == 0.0f);
		CHECK(v0.z == 0.0f);

		/// Constructor from components
		const Vector3 v1(9.1f, -3.0f, 2.2f);
		CHECK(v1.x == 9.1f);
		CHECK(v1.y == -3.0f);
		CHECK(v1.z == 2.2f);

		/// Constructor from components
		const Vector3 v2(3.2f);
		CHECK(v2.x == 3.2f);
		CHECK(v2.y == 3.2f);
		CHECK(v2.z == 3.2f);

		/// Copy construction
		Vector3 v3(v2);
		CHECK(v2.x == v3.x);
		CHECK(v2.y == v3.y);
		CHECK(v2.z == v3.z);

		/// Zero all the components of the vector
		v3.Clear();
		CHECK(v0.x == v3.x);
		CHECK(v0.y == v3.y);
		CHECK(v0.z == v3.z);
	}

	SUBCASE("Mathematical operators")
	{
		const Vector3 v0(2.3f, 3.7f, 4.5f);
		const Vector3 v1(-6.6f, 1.2f, 3.4f);
		const float factor = 3.5f;
		Vector3 v2;

		/// Returns the value of the given vector added to this.
		v2 = v0 + v1;
		CHECK(v2.x == v0.x + v1.x);
		CHECK(v2.y == v0.y + v1.y);
		CHECK(v2.z == v0.z + v1.z);

		/// Returns the value of the given vector subtracted from this.
		v2 = v0 - v1;
		CHECK(v2.x == v0.x - v1.x);
		CHECK(v2.y == v0.y - v1.y);
		CHECK(v2.z == v0.z - v1.z);

		SUBCASE("Vector and scalar multiplication.")
		{
			/// Returns a copy of this vector scaled the given value.
			v2 = v1 * factor;
			CHECK(v2.x == v1.x * factor);
			CHECK(v2.y == v1.y * factor);
			CHECK(v2.z == v1.z * factor);

			/// Returns a new vector being the result of a float value multiplied on right hand side with a vector
			v2 = factor * v0;
			CHECK(v2.x == v0.x * factor);
			CHECK(v2.y == v0.y * factor);
			CHECK(v2.z == v0.z * factor);
		}

		/// Returns a copy of this vector scaled the given value.
		v2 = v0 / factor;
		CHECK(v2.x == v0.x / factor);
		CHECK(v2.y == v0.y / factor);
		CHECK(v2.z == v0.z / factor);

		SUBCASE("Dot product calculation.")
		{
			/// Calculates and returns the dot product of this vector with the given vector.
			const float dot = v0 * v1;
			bool test = false;
			if (dot + S_EPSILON > 4.56f && dot - S_EPSILON < 4.56f)
			{
				test = true;
			}
			
			CHECK(test);

			const float calculated_dot = v0.Dot(v1);
			CHECK(dot == calculated_dot);
		}

		/// Adds the given vector to this.
		SUBCASE("Adds the given vector to this.")
		{
			Vector3 v3(3.0f, -4.0f, 5.0f);
			v3 += v0;
			CHECK(v3.x == v0.x + 3.0f);
			CHECK(v3.y == v0.y + -4.0f);
			CHECK(v3.z == v0.z + 5.0f);
		}

		/// Subtracts the given vector from this
		SUBCASE("Subtracts the given vector from this.")
		{
			Vector3 v3(3.0f, -4.0f, 5.0f);
			v3 -= v1;
			CHECK(v3.x == 3.0f - v1.x);
			CHECK(v3.y == -4.0f - v1.y);
			CHECK(v3.z == 5.0f - v1.z);
		}

		/// Multiplies this vector by the given scalar
		SUBCASE("Multiplies this vector by the given scalar.")
		{
			Vector3 v3(3.0f, -4.0f, 5.0f);
			v3 *= factor;
			CHECK(v3.x == 3.0f * factor);
			CHECK(v3.y == -4.0f * factor);
			CHECK(v3.z == 5.0f * factor);
		}
	}

	SUBCASE("Logical operators")
	{
		/// Checks if the two vectors have identical components
		const float x = 2.93f;
		const float y = 4.39f;
		const float z = 8.68f;
		Vector3 v0(x, y, z);
		Vector3 v1(x, y, z);
		Vector3 v2(y, x, z);

		CHECK(v0 == v1);
		CHECK(v2 != v0);
	}

	SUBCASE("Length operations")
	{
		Vector3 v0(3.0f, 4.0f, 5.0f);

		/// Gets the magnitude of this vector
		const float vector_length = v0.Magnitude();
		//CHECK(7.071067f == vector_length);
		// CHECK(check_if_in_range_of_epsilon(vector_length, 7.071067f));

		/// Gets the squared magnitude of this vector
		const float vector_length_sqr = v0.SquareMagnitude();
		CHECK(vector_length_sqr == 50.0f);

		/// Limits the size of the vector to the given maximum
		v0.Trim(2.5f);
		CHECK(2.5f == v0.Magnitude());

		/// Returns the normalised version of a vector
		Vector3 v1 = v0;
		Vector3 v2 = v1.Unit();
		CHECK(v1 == v0);
		CHECK(1.0f == v2.Magnitude());

		/// Turns a non-zero vector into a vector of unit length
		v0.Normalize();
		CHECK(1.0f == v0.Magnitude());
	}
}