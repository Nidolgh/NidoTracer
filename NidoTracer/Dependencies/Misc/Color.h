#pragma once
typedef char pixelcomp;

class Color
{
public:
	#pragma warning(push)
	#pragma warning(disable: 4201)
	union
	{
		float f[3];

		struct
		{
			float r;
			float g;
			float b;
		};
	};
	#pragma warning(pop)
	
	/// Default 0 contructor
	Color() : r(0), g(0), b(0) { }

	/// Constructor from components
	Color(float r, float g, float b) : r(r), g(g), b(b) {}

	/// Constructor from components
	explicit Color(float v) : r(v), g(v), b(v) {}

	/// Returns the value of the given vector added to this.
	Color operator+(const float v) const
	{
		return Color(r + v, g + v, b + v);
	}
	
	/// Returns the value of the given vector added to this.
	Color operator+(const Color v) const
	{
		return Color(r + v.r, g + v.g, b + v.b);
	}
	
	Color operator*(Color c) const
	{
		return Color(r * c.r, g * c.g, b * c.b);
	}
	
	void operator+=(const Color v)
	{
		r += v.r;
		g += v.g;
		b += v.b;
		//  return Color(r + v.r, g + v.g, b + v.b);
	}
	
	/// Returns the value of the given float color subtracted from this.
	Color operator-(const float v) const
	{
		return Color(r - v, g - v, b - v);
	}

	/// Returns a copy of this color scaled the given value.
	Color operator*(float value) const
	{
		return Color(r * value, g * value, b * value);
	}
	
	Color operator/(const float value)const
	{
		return Color(r / value, g / value, b / value);
	}

	pixelcomp get_red_0_255() const { return static_cast<pixelcomp>(get_red_to_max(1.0f) * 255); };
	pixelcomp get_green_0_255() const { return static_cast<pixelcomp>(get_green_to_max(1.0f) * 255); };
	pixelcomp get_blue_0_255() const { return static_cast<pixelcomp>(get_blue_to_max(1.0f) * 255); };
	
	float get_red_to_max(const float max) const { if (r > max) { return max; } return r; }
	float get_green_to_max(const float max) const { if (g > max) { return max; } return g; }
	float get_blue_to_max(const float max) const { if (b > max) { return max; } return b; }
};