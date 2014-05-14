#ifndef __NEDOKTEC_SOLID_VECTOR2_HPP__
#define __NEDOKTEC_SOLID_VECTOR2_HPP__

#include <ostream>

namespace nedoktec {
namespace solid {

class Vector2
{
public:
	Vector2()
		: x(0)
		, y(0)
	{ }

	Vector2(float x, float y)
		: x(x)
		, y(y)
	{ }

	Vector2(const Vector2& that)
		: x(that.x)
		, y(that.y)
	{ }

	Vector2(Vector2&& that)
		: x(that.x)
		, y(that.y)
	{ }

	~Vector2()
	{ }

	Vector2& operator= (const Vector2& that)
	{
		x = that.x;
		y = that.y;
		return *this;
	}

	Vector2& operator= (Vector2&& that)
	{
		x = that.x;
		y = that.y;
		return *this;
	}

	bool operator== (const Vector2& that) const
	{
		return x == that.x
			&& y == that.y;
	}

	bool operator!= (const Vector2& that) const
	{
		return !operator== (that);
	}

	bool operator< (const Vector2& that) const
	{
		return x < that.x
			&& y < that.y;
	}

	// bool operator> (const Vector2& that) const
	// {
	//     return that < (*this);
	// }

	// bool operator<= (const Vector2& that) const
	// {
	//     return !operator> (that);
	// }

	// bool operator>= (const Vector2& that) const
	// {
	//     return !(that < (*this));
	// }

private:
	friend std::ostream& operator<< (std::ostream& stream, const Vector2& that);

public:
	float x;
	float y;
};

std::ostream& operator<< (std::ostream& stream, const Vector2& that)
{
	stream << "{Vector2:" << that.x << "," << that.y << "}";
	return stream;
}

} // namespace solid
} // namespace nedoktec

#endif // __NEDOKTEC_SOLID_VECTOR2_HPP__
