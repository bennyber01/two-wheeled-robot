#pragma once

struct Vector2D
{
	Vector2D();
	Vector2D( const Vector2D& ) ;								// copy constructor
	Vector2D( double x, double y ) ;

	double Length() ;
	void   Normalize() ;

	void Set( double x, double y );

	// Scalar-Vector product
	void     operator  - ( void ) ;								// negate a vector
	void     operator *= ( double ) ;
	void     operator /= ( double ) ;
	Vector2D operator * ( double ) const ;						// for the case when the operand order is Vector * Scalar

	// vector addition
	Vector2D operator +  ( const Vector2D& ) const ;
	Vector2D operator -  ( const Vector2D& ) const ;
	void     operator +=  (const Vector2D& ) ;
	void     operator -= ( const Vector2D& ) ;

	// the Dot-Product
	double   operator *  ( const Vector2D& ) const ;

	bool     operator == ( const Vector2D& ) const ;
	bool     operator != ( const Vector2D& ) const ;

	double x, y;
};
