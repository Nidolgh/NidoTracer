#include "Mesh_OBJ.h"
#include <cstdio>
#include <cstring>

// https://www.tutorialspoint.com/cprogramming/c_file_io.htm
// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fopen-s-wfopen-s?view=vs-2019
// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fscanf-s-fscanf-s-l-fwscanf-s-fwscanf-s-l?view=vs-2019
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
Mesh_OBJ::Mesh_OBJ(const Vector3 origin, const char* file_name)
{
	m_origin = origin;
	
	m_surface_type = SurfaceType::SurfaceMesh_OBJ;
	
	m_material.m_dif_col = Color(0.1f, 0, 1);
	m_material.m_flat_coloring = true;
	m_material.m_diffuse = 1.0f;
	//m_material.m_specular = 1.0f;
	m_material.m_specular_reflection = true;

	FILE* file_stream = nullptr;
	const errno_t err = fopen_s(&file_stream, file_name, "r");
	if (!err && file_stream != nullptr)
	{
		char buff[255];

		LinkedList<Vector3> ver;
		LinkedList<Vector3> ver_nor;
		
		while (true) {

			const int res = fscanf_s(file_stream, "%s", buff, static_cast<unsigned int>(sizeof(buff)));
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

			if (buff[0] == 'v' && buff[1] == '\0') {
				Vector3 vertex;
				fscanf_s(file_stream, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				ver.push(vertex);
			}
			/*if (buff[0] == 'v' && buff[1] == 'n') {
				Vector3 vertex;
				fscanf_s(file_stream, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				ver_nor.push(vertex);
			}*/
		}
		
		fclose(file_stream);

		// TODO correctly set triangles
		int counter = 0;
		Vector3 verts[3];
		LinkedNode<Vector3>* sel_node = ver.get_top();
		while(sel_node != nullptr)
		{
			verts[counter++] = sel_node->GetData() + origin;
			if (counter >= 3)
			{
				Triangle* new_triangle = new Triangle(verts[0], verts[1], verts[2]);
				m_triangles.push(new_triangle);
				verts[0] = verts[1] = verts[2] = Vector3(0.0f);
				counter = 0;
			}

			sel_node = sel_node->Next();
		}
	}
}

Mesh_OBJ::~Mesh_OBJ()
{
	m_triangles.delete_all_payload();
}


bool Mesh_OBJ::hit(const Ray3D& ray, HitRecord& r_rec)
{
	float min_time = INFINITY;
	bool is_hit = false;

	HitRecord cur_hit_rec;
	HitRecord main_hit_rec;

	LinkedNode<Triangle*>* sel_node = m_triangles.get_top();
	while (sel_node != nullptr)
	{
		Surface* sel_surface = sel_node->GetData();

		if (sel_surface->hit(ray, cur_hit_rec)/* && cur_hit_rec.m_time < ray.get_max_length()*/ && cur_hit_rec.m_time < min_time)
		{
			min_time = cur_hit_rec.m_time;
			main_hit_rec = cur_hit_rec;
			is_hit = true;
		}

		sel_node = sel_node->Next();
	}
	
	//r_rec = main_hit_rec;
	r_rec.m_material = &get_material();
	return is_hit;
}
