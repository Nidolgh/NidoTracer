#pragma once

#include <cmath>

class Vector3
{
public:
	#pragma warning(push)
	#pragma warning(disable: 4201)
	union
	{
		float f[3];

		struct
		{
			float x;
			float y;
			float z;
		};
	};
	#pragma warning(pop)
	
public:
	/// Default 0 contructor
	Vector3() : x(0), y(0), z(0) { }

	/// Constructor from components
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	/// Constructor from components
	explicit Vector3(float v) : x(v), y(v), z(v) {}

	/// Returns the value of the given vector added to this.
	Vector3 operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	/// Returns the value of the given vector subtracted from this.
	Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	/// Returns a copy of this vector scaled the given value.
	Vector3 operator*(float value) const
	{
		return Vector3(x * value, y * value, z * value);
	}

	/// Returns a copy of this vector scaled the given value.
	Vector3 operator/(const float value) const
	{
		return Vector3(x / value, y / value, z / value);
	}
	
	/// Calculates and returns the dot product of this vector
	/// with the given vector.
	float operator *(const Vector3& vector) const
	{
		return Dot(vector);
	}

	/// Adds the given vector to this.
	void operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	/// Subtracts the given vector from this
	void operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	/// Multiplies this vector by the given scalar
	void operator*=(const float value)
	{
		x *= value;
		y *= value;
		z *= value;
	}

	/// Checks if the two vectors have identical components
	bool operator==(const Vector3& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	/// Checks if the two vectors have non-identical components
	bool operator!=(const Vector3& other) const
	{
		return !(*this == other);
	}

	/// Calculates and returns the dot product of this vector
	/// with the given vector.
	float Dot(const Vector3& vector) const
	{
		return (x * vector.x) + (y * vector.y) + (z * vector.z);
	}

	/// Cross product in 2D, look on mathworld
	Vector3 Cross(const Vector3& rhs) const
	{
		return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
		//return Vector3(x * rhs.y - y * rhs.x - z * rhs.z);
	}

	/// Gets the magnitude of this vector
	float Magnitude() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	/// Gets the squared magnitude of this vector
	float SquareMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	/// Limits the size of the vector to the given maximum
	void Trim(float size)
	{
		if (SquareMagnitude() > size * size)
		{
			Normalize();
			x *= size;
			y *= size;
			z *= size;
		}
	}

	/// Turns a non-zero vector into a vector of unit length
	void Normalize()
	{
		float l = Magnitude();
		if (l > 0)
		{
			(*this) *= ((float)1) / l;
		}
	}

	Vector3 GetInvert()
	{
		return Vector3(1 / x, 1 / y, 1 / z);
	}
	
	/// Returns the normalised version of a vector
	Vector3 Unit() const
	{
		Vector3 result = *this;	// Copy ctor
		result.Normalize();
		return result;
	}

	/// Returns the perpendicular of the vector
	Vector3 Perpendicular() const
	{
		Vector3 result(y, -x, z);
		return result;
	}

	/// Zero all the components of the vector
	void Clear()
	{
		x = y = z = 0;
	}


	/// Squared distance to another vector
	float SquareDistance(const Vector3& other) const
	{
		return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z * other.z) - (z * other.z);
	}

	static Vector3 Zero;
};

/// Multiplication with Rhs Vector
inline Vector3 operator*(float val, const Vector3& rhs)
{
	return Vector3(rhs.x * val, rhs.y * val, rhs.z * val);
}
