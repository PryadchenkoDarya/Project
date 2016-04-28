# include "FactoryShapes.h"
# include "Shapes.h"

void Application(){
	Container< Shape * > cont;
	FactoryShapes factory;
	size_t count = 0;
	size_t countShapes = 20 + rand() % 10;
	for( size_t i = 0; i < countShapes; ++i ) {
		size_t k = 1 + rand() % 6;
		switch ( k ) {
		case 1:
			cont.PushFirstElem( factory.CreatePoint() );
			break;
		case 2:
			cont.PushFirstElem( factory.CreateCircle( count ) );
			break;
		case 3:
			cont.PushFirstElem( factory.CreateRect( count ) );
			break;
		case 4:
			cont.PushFirstElem( factory.CreateSquare( count ) );
			break;
		case 5:
			cont.PushFirstElem( factory.CreatePolyline( count ) );
			break;
		case 6:
			cont.PushFirstElem( factory.CreatePolygon( count ) );
			break;
		default:
			break;
		}
	}
	for( size_t i = 0; i < countShapes; ++i ) {
		try {
			Shape const * shape =  * cont.GetElem( i );
			shape->Print();
		}
		catch( std::invalid_argument & except ) {
			std::cerr << except.what() << std::endl;
		}
	}
	std::cout << Shape::GetCount( 0 )-count<< '\n';
	while( ! cont.Empty()) {
		Shape const * shape = * cont.GetFistElem();
		delete shape;
		cont.PopFistElem();
	}
	std::cout << Shape::GetCount( 0 ) << '\n';
}

void main() {
	Application();
}
