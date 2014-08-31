#include "Vector2D.h"
#include "math.h"

const double EPSILON = 0;

Vector2D::Vector2D() : x(0), y(0)
{
}

Vector2D::Vector2D(const Vector2D& other)
{
	*this = other;
}

Vector2D::Vector2D(double x, double y)
{
	this -> x = x;
	this -> y = y;
}

double Vector2D::Length()
{
	return sqrt(x * x + y * y); 
}

void Vector2D::Normalize()
{
	double length = Length() ;
	if ( length > EPSILON ) // do not divide is length is really small
	{
		x /= length;
		y /= length;
	}

}

void Vector2D::Set( double x, double y )
{
	this -> x = x;
	this -> y = y;
}

void Vector2D::operator - ( void )
{
	x = -x;
	y = -y;
}

void Vector2D::operator *= ( double scalar )
{
	x *= scalar;
	y *= scalar;
}



void Vector2D::operator /= ( double scalar )
{
	x /= scalar;
	y /= scalar;
}

Vector2D Vector2D::operator * ( double scalar ) const
{
	Vector2D result;

	result.x = x * scalar;
	result.y = y * scalar;

	return result ;
}

Vector2D Vector2D::operator + ( const Vector2D& other ) const
{
	Vector2D result;

	result.x = x + other.x;
	result.y = y + other.y;

	return result ;
}

Vector2D Vector2D::operator - ( const Vector2D& other ) const
{
	Vector2D result;

	result.x = x - other.x;
	result.y = y - other.y;

	return result ;
}

void Vector2D::operator += ( const Vector2D& other )
{
	x += other.x;
	y += other.y;
}

void Vector2D::operator -= ( const Vector2D& other )
{
	x -= other.x;
	y -= other.y;
}

double Vector2D::operator * ( const Vector2D& other ) const
{
	double dot_product = 0.0 ;

	dot_product =  x * other.x + y * other.y;

	return dot_product ;
}

bool Vector2D:: operator == ( const Vector2D& other ) const
{
	bool result = x == other.x && y == other.y ;

	return result ;
}

bool Vector2D:: operator != ( const Vector2D& other ) const
{
	return ! (*this == other) ;
}