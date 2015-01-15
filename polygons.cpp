#include "polygons.h"

bool Polygon::HasTwoEqualSides() {
	int points = vertices.size();
	//cycle through the possible combinations of sides
	for (int i = 0; i < points; ++i) {
		for (int j = 1; j < points; ++j) {
			//dont look at the same side twice and check the distances
			if ( i != j && EqualSides( DistanceBetween(vertices[i], vertices[(i+1)%points]),
												DistanceBetween(vertices[j], vertices[(j+1)%points]) ))
				return true;
		}
	}
	return false;
}

bool Polygon::HasTwoPairsEqualSides() {
	int points = vertices.size();
	int count = 0;
	//cycle through the possible combinations of sides
	for (int i = 0; i < points; ++i){
		if (EqualSides( DistanceBetween(vertices[i], vertices[(i+1)%points]),
							 DistanceBetween(vertices[(i+1)%points], 
							 vertices[(i+2)%points]) ))
			++count;
	}
	if (count < 2)
		return false;
	if (count >= 2)
		return true;
}

bool Polygon::IsConcave() {
	if (IsConvex())
		return false;
	return true;
	/* 
	int points = vertices.size();
	for (int i = 0; i < points; ++i) {
		if (ReflexAngle( Angle(vertices[i], vertices[(i+1)%points], vertices[(i+2)%points]) ) )
			return true;
	}
	return false; 
	*/
}

bool Polygon::IsConvex() {
	int points = vertices.size();
	for (int i = 0; i < points; ++i) {
		if (ReflexAngle( Angle(vertices[i], vertices[(i+1)%points], vertices[(i+2)%points]) ) )
			return false;
	}
	return true;
}

bool Polygon::HasAllEqualSides() {
	int points = vertices.size();
	//compare an angle against each other angle
	double side1 = DistanceBetween(vertices[0], vertices[1]);
	for (int i = 0; i < points; ++i){
		if (!EqualSides( DistanceBetween( vertices[i], vertices[(i+1) % points] ), side1))
			return false;
	}
	return true;
}

bool Polygon::HasTwoParallelSides() {
	int points = vertices.size();
	//check all side combinations
	for (int i = 0; i < points; ++i) {
		for (int j = 1; j < points; ++j) {
			Vector v1(vertices[i], vertices[(i+1)%points]);
			Vector v2(vertices[j], vertices[(j+1)%points]);
			if (i != j && Parallel(v1, v2))
				return true;
		}
	}
	return false;
}

bool Polygon::HasAllEqualAngles() {
	int number_of_points = vertices.size();
	//first angle, the one to compare to
	double angle1 = Angle(vertices[0], vertices[1], vertices[2]);
	for (int i = 0; i < number_of_points; ++i) {
		if (!EqualAngles( Angle( vertices[i], vertices[(i+1)%number_of_points], vertices[(i+2)%number_of_points] ), angle1))
			return false;
	}
	return true;
}

bool Polygon::HasARightAngle() {
	//find a right angle in the loop -> return true
	int points = vertices.size();
	for (int i = 0; i < points; ++i){
		if (RightAngle(Angle(vertices[i], vertices[(i+1)%points], vertices[(i+2)%points])))
			return true;
	}
	return false;
}

//HasObtuse and HaveAcute are the same process as HasRight:
//loop through, if you find x angle, return true.
bool Polygon::HasAnObtuseAngle() {
	int points = vertices.size();
	for (int i = 0; i < points; ++i){
		if (ObtuseAngle(Angle(vertices[i], vertices[(i+1)%points], vertices[(i+2)%points])))
			return true;
	}
	return false;
}

bool Polygon::HasAnAcuteAngle() {
	int points = vertices.size();
	for (int i = 0; i < points; ++i){
		if (AcuteAngle(Angle(vertices[i], vertices[(i+1)%points], vertices[(i+2)%points])))
			return true;
	}
	return false;
}

//ease of use return statements that are guarenteed true/false
bool Triangle::HasTwoParallelSides() { return false; }
bool Triangle::IsConvex() 				 { return true;  }
bool Triangle::IsConcave()				 { return false; }

bool EquilateralTriangle::HasTwoEqualSides()  { return true;  }

bool IsoscelesObtuseTriangle::HasAnObtuseAngle() { return true; }
bool IsoscelesObtuseTriangle::HasTwoEqualSides() { return true; }

bool IsoscelesRightTriangle::HasARightAngle()   { return true;  }
bool IsoscelesRightTriangle::HasTwoEqualSides() { return true; }

bool Rectangle::HasTwoEqualSides() { return true; }

bool Parallelogram::HasTwoParallelSides() { return true; }


//Constructors
//Throws an integer when constructor fails
//Most of these are self-explanatory
Triangle::Triangle(const string& name_, const vector<Point>& vertices_) :
	Polygon(name_, vertices_) {
		//if we don't have 4 vertices, it's not a quadralateral, so throw
		if (vertices.size()!=3) 
			throw(1337);
}

ObtuseTriangle::ObtuseTriangle(const string& name_, const vector<Point>& vertices_) :
	Triangle(name_, vertices_) {
		//if we don't have 3 vertices, it's not a triangle, so throw
		if (vertices.size()!=3 || !HasAnObtuseAngle()) 
			throw(1337);
}

IsoscelesObtuseTriangle::IsoscelesObtuseTriangle(const string& name_, const vector<Point>& vertices_) :
	Triangle(name_, vertices_),
	ObtuseTriangle(name_, vertices_),
	IsoscelesTriangle(name_, vertices_) {
		if (vertices.size()!=3) 
			throw(1337);
}


IsoscelesTriangle::IsoscelesTriangle(const string& name_, const vector<Point>& vertices_) :
	Triangle(name_, vertices_) {
		if (!HasTwoEqualSides()) 
			throw(1337);
}

RightTriangle::RightTriangle(const string& name_, const vector<Point>& vertices_) :
	Triangle(name_, vertices_) { 
		if (!HasARightAngle()) 
			throw(1337);
}

EquilateralTriangle::EquilateralTriangle(const string& name_, const vector<Point>& vertices_) :
	Triangle(name_,vertices_),
	IsoscelesTriangle(name_, vertices_) {
		if (!HasAllEqualSides()) 
			throw(1337);
}

IsoscelesRightTriangle::IsoscelesRightTriangle(const string& name_, const vector<Point>& vertices_) :
	Triangle(name_, vertices_),
	IsoscelesTriangle(name_,vertices_),
	RightTriangle(name_,vertices_) { } //other classes take care of the checks

//////////////quads//////////
	

Quadrilateral::Quadrilateral(const string& name_, const vector<Point>& vertices_) :
	Polygon(name_, vertices_) {
		if (vertices.size()!=4) 
			throw(1337);
}

Arrow::Arrow(const string& name_, const vector<Point>& vertices_) :
	Quadrilateral(name_, vertices_) {
		if (!HasTwoPairsEqualSides())
			throw(1337);
		if (vertices.size()!=4)
			throw(1337);
		//ALL concave shapes have a reflexive angle
		if (!IsConcave())
			throw(1337);
		
}

Trapezoid::Trapezoid(const string& name_, const vector<Point>& vertices_) :
	Quadrilateral(name_, vertices_) {
		if (!HasTwoParallelSides()) 
			throw(1337);
}

IsoscelesTrapezoid::IsoscelesTrapezoid(const string& name_, const vector<Point>& vertices_) :
	Quadrilateral(name_, vertices_),
	Trapezoid(name_, vertices_) {

		//has opposite parallel sides and other opposite equal sides
		//throw if we dont have two equal sides at all
		if (!HasTwoEqualSides()) throw(5);
		Vector v1(vertices[0],vertices[1]);
		Vector v2(vertices[1],vertices[2]);
		Vector v3(vertices[2],vertices[3]);
		Vector v4(vertices[3],vertices[0]);

		//find the two sides that are parallel and check if the other sides are not equal
		//in length. Also make sure there aren't two sets of parallel sides. A right angle
		//negates the entire process, as that would make it a square, which is a further
		//derivation.
		if (Parallel(v1,v3)){
			if (!HasARightAngle() && Parallel(v2,v4) || !EqualSides(v2.Length(), v4.Length()))
				throw(1337);
		}
		else if (Parallel(v2,v4)){
			if (!HasARightAngle() && Parallel(v1,v3) || !EqualSides(v1.Length(), v3.Length()))
				throw(1337);
		}

}

Kite::Kite(const string& name_, const vector<Point>& vertices_) :
	Quadrilateral(name_, vertices_) {
		if (!HasTwoPairsEqualSides())
			throw(1337);
}

Rhombus::Rhombus(const string& name_, const vector<Point>& vertices_) :
	Quadrilateral(name_, vertices_),
	Trapezoid(name_, vertices_),
	Parallelogram(name_, vertices_),
	Kite(name_, vertices_) {
		if (!HasAllEqualSides())
			throw (1337);
}


Parallelogram::Parallelogram(const string& name_, const vector<Point>& vertices_) :
	Quadrilateral(name_, vertices_),
	Trapezoid(name_, vertices_) {
		if (!HasTwoEqualSides())
			throw(1337);
}

Rectangle::Rectangle(const string& name_, const vector<Point>& vertices_) :
	Quadrilateral(name_, vertices_),
	Trapezoid(name_, vertices_), 
	IsoscelesTrapezoid(name_, vertices_),
	Parallelogram(name_, vertices_) {
			
	int points = vertices.size();
	//Rectangles have four (all) right angles. Therefore, if any
	//arbitrary angle is NOT right, in this case acute, throw.
	if (AcuteAngle(Angle(vertices[0],vertices[1%points], vertices[2%points])))
		throw(1337);
}


Square::Square(const string& name_, const vector<Point>& vertices_) : 
	Quadrilateral(name_, vertices_),
	Trapezoid(name_, vertices_),
	Parallelogram(name_, vertices_),
	Rectangle(name_, vertices_),
	Rhombus(name_, vertices_) {
		if (!HasAllEqualSides()) 
			throw (1337);
}
