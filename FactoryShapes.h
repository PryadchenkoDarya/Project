#ifndef __FactoryShapes_H_
#define __FactoryShapes_H_

#include "Shapes.h"

class FactoryShapes{
public:
	Shape * CreatePoint() {
		Shape * point = new Point( rand() % 250, rand() % 250 );
		return point;
	}
	Shape * CreateCircle( size_t & iCount ) {
		Point center( rand() % 250, rand() % 250 );
		Shape * circle = new Circle( center, rand() % 250 );
		++iCount;
		return circle;
	}
	Shape * CreateRect( size_t & iCount ) {
		Point point1( rand() % 250, rand() % 250 );
		Point point2( rand() % 250, rand() % 250 );
		Shape * rect = new Rect( point1, point2 );
		iCount += 2;
		return rect;
	}
	Shape * CreateSquare( size_t & iCount ) {
		Point point( rand() % 250, rand() % 250 );
		Shape * square = new Square( point, rand() % 250 );
		++iCount;
		return square;
	}
	Shape * CreatePolyline( size_t & iCount ) {
		Polyline * polyline = new Polyline();
		size_t countPoints = 2 + ( rand() % 7 );
		iCount += countPoints;
		for( size_t i = 0; i < countPoints; ++i ) {
			Point point( rand() % 250, rand() % 250 );
			polyline->AddPoint( point );
		}
		return polyline;
	}
	Shape * CreatePolygon( size_t & iCount ) {
		Polygon * polygon = new Polygon();
		size_t countVertexes = 3 +( rand() % 7);
		iCount += countVertexes;
		for( size_t i = 0; i < countVertexes; ++i ) {
			Point vertex( rand() % 250, rand() % 250 );
			polygon->AddVertexes( vertex );
		}
		return polygon;
	}

};

#endif // __FactoryShapes_H_
