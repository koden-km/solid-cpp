#ifndef __NEDOKTEC_SOLID_VECTOR3_HPP__
#define __NEDOKTEC_SOLID_VECTOR3_HPP__

#include <ostream>

namespace nedoktec {
namespace solid {

class Vector3
{
public:
	Vector3()
		: x(0)
		, y(0)
		, z(0)
	{ }

	Vector3(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{ }

	Vector3(const Vector3& that)
		: x(that.x)
		, y(that.y)
		, z(that.z)
	{ }

	Vector3(Vector3&& that)
		: x(that.x)
		, y(that.y)
		, z(that.z)
	{ }

	~Vector3()
	{ }

	Vector3& operator= (const Vector3& that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
		return *this;
	}

	Vector3& operator= (Vector3&& that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
		return *this;
	}

	bool operator== (const Vector3& that) const
	{
		return x == that.x
			&& y == that.y
			&& z == that.z;
	}

	bool operator!= (const Vector3& that) const
	{
		return !operator== (that);
	}

	bool operator< (const Vector3& that) const
	{
		return x < that.x
			&& y < that.y
			&& z < that.z;
	}

	// bool operator> (const Vector3& that) const
	// {
	//     return that < (*this);
	// }

	// bool operator<= (const Vector3& that) const
	// {
	//     return !operator> (that);
	// }

	// bool operator>= (const Vector3& that) const
	// {
	//     return !(that < (*this));
	// }

private:
	friend std::ostream& operator<< (std::ostream& stream, const Vector3& that);

public:
	float x;
	float y;
	float z;
};

std::ostream& operator<< (std::ostream& stream, const Vector3& that)
{
	stream << "{Vector3:" << that.x << "," << that.y << "," << that.z << "}";
	return stream;
}

} // namespace solid
} // namespace nedoktec

#endif // __NEDOKTEC_SOLID_VECTOR3_HPP__
