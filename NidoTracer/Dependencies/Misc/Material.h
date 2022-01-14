#pragma once
#include "../Misc/Color.h"

class Material
{
public:
	Material() : m_diffuse(1), m_specular(0), m_dif_col(Color(1)), m_spec_col(Color(1)) {}
	Material(float diffuse, float specular, bool reflecting, Color dif_col, Color spec_col, bool checker_state = false, float check_x_mul = 1.0f, float check_y_mul = 1.0f, Color check_even = Color(1), Color check_odd = Color(0)) : m_diffuse(diffuse), m_specular(specular), m_specular_reflection(reflecting), m_dif_col(dif_col), m_spec_col(spec_col), m_checkerboard(checker_state), m_checker_col_even(check_even), m_checker_col_odd(check_odd), m_checker_x_multiplier(check_x_mul), m_checker_y_multiplier(check_y_mul) {}
	
	float m_diffuse = 1.0f;
	float m_specular = 0.0f;
	
	bool m_specular_reflection = false;
	bool m_flat_coloring = false;
	
	float m_reflection_modifier = 2.0f;
	
	Color m_dif_col = Color(1.0f, 0.5f, 0.0f);
	Color m_spec_col = Color(1.0f, 0.5f, 1.0f);
	
	bool m_checkerboard = false;
	float m_checker_x_multiplier = 1.0f;
	float m_checker_y_multiplier = 1.0f;
	Color m_checker_col_even = Color(0.0f, 0.0f, 0.0f);
	Color m_checker_col_odd = Color(1.0f, 1.0f, 1.0f);
};