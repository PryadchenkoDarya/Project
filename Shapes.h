#ifndef __Shapes_H_
#define __Shapes_H_

#define _USE_MATH_DEFINES
#include < math.h >

#include "Base.h"
#include "Container.h"

class Shape: virtual public Printable {
public:
	Shape() {
		GetCount( 1 );
	}
	static size_t GetCount( int iParam ) {
		static size_t count = 0;
		return count += iParam;
	}
	virtual ~Shape() {
		GetCount( -1 );
	}
};
class Point: public Shape, public Named {
public:
	Point(): Named( "Point" ), m_x( 0 ), m_y( 0 ) {}
	Point( int iX, int iY ): Named( "Point" ), m_x( iX ), m_y( iY ) {}
	Point( Point const & iPoint ): Named( "Point" ) {
		m_x = iPoint.GetX();
		m_y = iPoint.GetY();
	}
	int GetX() const {
		return m_x;
	}
	int GetY() const {
		return m_y;
	}
	void Print() const {
		Named::Print();
		std::cout << *this << '\n';
	}
	friend std::ostream & operator <<( std::ostream & iStream, Point const & iPoint );

private:
	int m_x;
	int m_y;
};
std::ostream & operator <<( std::ostream & iStream, Point const & iPoint ) {
	return iStream << iPoint.m_x << ',' << iPoint.m_y;
}

class Circle: public Shape, public Named {
public:
	Circle( Point const & iPoint, int iRadius)
		: Named( "Circle" )
		, m_center( iPoint )
		, m_radius( iRadius )
	{
		m_area = M_PI * pow( m_radius, 2);
	}
	void Print() const {
		Named::Print();
		std::cout << * this << '\n';
	}
	friend std::ostream & operator <<( std::ostream & iStream, Circle const & iCircle );

private:
	Point const m_center;
	int m_radius;
	double m_area;
};
std::ostream & operator <<( std::ostream & iStream, Circle const & iCircle ) {
	return iStream << " Center: " << iCircle.m_center << '\t' << " Raduis: " << iCircle.m_radius << '\t' << " Area: " <<  iCircle.m_area;
}

class Rect: public Shape, public Named {
public:
	Rect( Point const & iPoint1, Point const & iPoint2 )
		: Named( "Rect" )
		, m_point1( iPoint1 )
		, m_point2( iPoint2 )
	{
		int width = abs ( iPoint1.GetX() - iPoint2.GetX() );
		int height = abs ( iPoint1.GetY() - iPoint2.GetY() );
		m_area = width * height;
		m_perimeter = 2 * ( width + height );
	}
	void Print() const {
		Named::Print();
		std::cout << * this << '\n';
	}
	friend std::ostream & operator <<( std::ostream & iStream, Rect const & iRect );

private:
	Point const m_point1;
	Point const m_point2;
	int m_area;
	int m_perimeter;
};
std::ostream & operator <<( std::ostream & iStream, Rect const & iRect ) {
	return iStream << " Area: " << iRect.m_area << '\t' << " Perimeter: " <<  iRect.m_perimeter;
}

class Square: public Shape, public Named {
public:
	Square( Point const & iPoint, int iSide ): Named( "Square" ), m_point( iPoint ), m_side( iSide ) {
		m_area = int(pow( m_side, 2 ));
		m_perimeter = 4 * m_side;
	}
	void Print() const{
		Named::Print();
		std::cout << * this << '\n';
	}
	friend std::ostream & operator <<( std::ostream & iStream, Square const & iSquare );

private:
	Point const m_point;
	int m_side;
	int m_area;
	int m_perimeter;
};
 std::ostream & operator <<( std::ostream & iStream, Square const & iSquare ) {
	return iStream << " Area: " << iSquare.m_area << '\t' << " Perimeter: " <<  iSquare.m_perimeter;
}

class Polyline: public Shape, public Named {
public:
	Polyline(): Named( "Polyline" ) {
		m_lenght = 0;
		m_points = new Container< Point >;
	}
	~Polyline(){
		delete m_points;
	}
	void AddPoint( Point const & iPoint ) {
		if ( m_points->GetCount() > 0 ) {
			Point const * lastPoint = m_points->GetLastElem();
			m_lenght += sqrt( pow( iPoint.GetX() - lastPoint->GetX(), 2) + pow( iPoint.GetY() - lastPoint->GetY(), 2 ) );
		}
		m_points->PushLastElem( iPoint );
	}
	void Print() const{
		if( m_points->GetCount() < 2 ) {
			throw std::invalid_argument( "Polyline must contain more than one point." );
		}
		Named::Print();
		std::cout << * this << '\n';
	}
	friend std::ostream & operator <<( std::ostream & iStream, Polyline const & iPolyline );

private:
	Container< Point > * m_points;
	double m_lenght;
};
std::ostream & operator <<( std::ostream & iStream, Polyline const & iPolyline ) {
	return iStream << " Lenght: " <<  iPolyline.m_lenght;
}

class Polygon: public Shape, public Named {
public:
	Polygon(): Named( "Polygon" ) {
		m_perimeter = 0;
		m_vertexes = new Container< Point >;
	}
	~Polygon(){
		delete m_vertexes;
	}
	void AddVertexes( Point const & iPoint ){
		if( m_vertexes->GetCount() > 0 ) {
			Point const * lastPoint = m_vertexes->GetLastElem();
			m_perimeter += sqrt( pow( iPoint.GetX() - lastPoint->GetX(), 2 ) + pow( iPoint.GetY() - lastPoint->GetY(), 2) );
		}
		m_vertexes->PushLastElem( iPoint );
	}
	void Print() const {
		if( m_vertexes->GetCount() < 3 ) {
			throw std::invalid_argument( "Polygon must contain more than two vertexes." );
		}
		Named::Print();
		std::cout << * this << '\n';
	}
	friend std::ostream & operator <<( std::ostream & iStream, Polygon const & iPolygon );

private:
	Container< Point > * m_vertexes;
	double m_perimeter;
};
 std::ostream & operator <<( std::ostream & iStream, Polygon const & iPolygon ) {
	Point const * firstVertex = iPolygon.m_vertexes->GetFistElem();
	Point const * lastVertex = iPolygon.m_vertexes->GetLastElem();
	return iStream << " Perimeter: " <<  (iPolygon.m_perimeter + sqrt( pow( firstVertex->GetX() - lastVertex->GetX(), 2) + pow( firstVertex->GetY() - lastVertex->GetY(), 2 ) ) );
}

#endif // __Shapes_H_
