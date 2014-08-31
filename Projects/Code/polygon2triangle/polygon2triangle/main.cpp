#include <iostream>

#include "./poly2tri/poly2tri.h"
//using namespace p2t;

/// Constrained triangles
std::vector<p2t::Triangle*> triangles;

template <class C> void FreeClear( C & cntr ) {
	for ( typename C::iterator it = cntr.begin(); 
		it != cntr.end(); ++it ) {
			delete * it;
	}
	cntr.clear();
}

int main(int argc, char* argv[])
{
	std::vector<p2t::Point*> polyline;

	// Create a simple bounding box
	polyline.push_back(new p2t::Point( 0, 0));
	polyline.push_back(new p2t::Point( 0,10));
	polyline.push_back(new p2t::Point(10,10));
	polyline.push_back(new p2t::Point(15, 5));
	polyline.push_back(new p2t::Point(10, 0));

	/*
	* Perform triangulation!
	*/

	/*
	* STEP 1: Create CDT and add primary polyline
	* NOTE: polyline must be a simple polygon. The polyline's points
	* constitute constrained edges. No repeat points!!!
	*/
	p2t::CDT* cdt = new p2t::CDT(polyline);

	/*
	* STEP 2: Triangulate!
	*/
	cdt->Triangulate();

	triangles = cdt->GetTriangles();

	std::cout << "Number of points = " << polyline.size() << std::endl;
	std::cout << "Number of triangles = " << triangles.size() << std::endl;

	for (unsigned int i = 0; i < triangles.size(); i++)
	{
		p2t::Triangle& t = *triangles[i];
		p2t::Point& a = *t.GetPoint(0);
		p2t::Point& b = *t.GetPoint(1);
		p2t::Point& c = *t.GetPoint(2);
		std::cout << "a(" << a.x << ", " << a.y << "), b(" << b.x << ", " << b.y << "), c(" << c.x << ", " << c.y << ")" << std::endl;
	}

	// Cleanup
	delete cdt;

	// Free points
	FreeClear(polyline);

	return 0;
}