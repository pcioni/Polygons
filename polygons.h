#include <iostream>
#include <string>
#include <vector>
#include "utilities.h"
using namespace std;

class Polygon {
public:
	Polygon(const string& name_, const vector<Point>& vertices_) : name(name_), vertices(vertices_) {}
	virtual const string& getName() const {return name;}

	//All defined in Polygon since we can do some of these
	//checks with out making a shape.
	//I.E. we dont have to get all the way to a square to check
	//if the shape only has three sides...
	bool HasAllEqualSides();
	virtual bool HasTwoEqualSides();
	bool HasTwoPairsEqualSides();
	virtual bool HasTwoParallelSides();
	bool HasAllEqualAngles();
	virtual bool HasARightAngle();
	virtual bool HasAnObtuseAngle();
	bool HasAnAcuteAngle();		
	virtual bool IsConvex();				
	virtual bool IsConcave();		
	
protected:
	string name;
	vector<Point> vertices;

		
};


/*================Triangles=======================*/

class Triangle : public Polygon {
public:
	Triangle(const string& name_, const vector<Point>& vertices_);
	bool HasTwoParallelSides();
	bool IsConvex();				
	bool IsConcave();	
};

class IsoscelesTriangle : virtual public Triangle {
public:
	IsoscelesTriangle(const string& name_, const vector<Point>& vertices_);
};

class RightTriangle : virtual public Triangle {
public:
	RightTriangle(const string& name_, const vector<Point>& vertices_);
};

class ObtuseTriangle : virtual public Triangle {
public:
	ObtuseTriangle(const string& name_, const vector<Point>& vertices_);
};

class IsoscelesObtuseTriangle : public ObtuseTriangle, public IsoscelesTriangle {
public:
	IsoscelesObtuseTriangle(const string& name_, const vector<Point>& vertices_);
	bool HasAnObtuseAngle();
	bool HasTwoEqualSides();
};

class IsoscelesRightTriangle : public IsoscelesTriangle, public RightTriangle {
public:
	IsoscelesRightTriangle(const string& name_, const vector<Point>& vertices_);
	bool HasTwoEqualSides();
	bool HasARightAngle();
};

class EquilateralTriangle : public IsoscelesTriangle {
public:
	EquilateralTriangle(const string& name_, const vector<Point>& vertices_);
	bool HasTwoEqualSides();
};

/*================Quadrilaterals=======================*/

class Quadrilateral : public Polygon {
public:
	Quadrilateral(const string& name_, const vector<Point>& vertices_);
};

class Arrow : public Quadrilateral {
public:
	Arrow(const string& name_, const vector<Point>& vertices_);
};

class Kite : virtual public Quadrilateral {
public:
	Kite(const string& name_, const vector<Point>& vertices_);
};

class Trapezoid : virtual public Quadrilateral {
public:
	Trapezoid(const string& name_, const vector<Point>& vertices_);
};

class Parallelogram : virtual public Trapezoid {
public:
	Parallelogram(const string& name_, const vector<Point>& vertices_);
	bool HasTwoParallelSides();
};

class IsoscelesTrapezoid : virtual public Trapezoid {
public:
	IsoscelesTrapezoid(const string& name_, const vector<Point>& vertices_);
};

class Rectangle : public IsoscelesTrapezoid, virtual public Parallelogram {
public:
	Rectangle(const string& name_, const vector<Point>& vertices_);
	bool HasTwoEqualSides();
};

class Rhombus : virtual public Parallelogram, public Kite {
public:
	Rhombus(const string& name_, const vector<Point>& vertices_);
};

class Square : public Rectangle, public Rhombus {
public:
	Square(const string& name_, const vector<Point>& vertices_);
};







