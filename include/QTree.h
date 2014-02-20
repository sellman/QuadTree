#ifndef QT_H
#define QT_H

#include <vector>

//Representation of a point
struct Point
{
	double x, y; //Coordinates
	
	Point();
	Point(const double, const double); //Constructor
};

//Axis-aligned bounding box
struct BoundingBox
{
	Point center, halfDim;
	
	BoundingBox();
	BoundingBox(const Point,const Point); //(center, half dimension)
	bool contains(const Point&); //Function to check if a point is found within this object.
	bool intersects(const BoundingBox&); //Examines if this BB intersects with the argument
};

class QTree
{
	public:
		static int nMain;
		static int nChildren;
		QTree(const double, const double, const double); //User constructor
		bool insert(const Point&);
		void querySquare(const double, const double, const double, std::vector<Point*>&);
		void queryCircle(const double, const double, const double, std::vector<Point*>&);
		
	
	private:
		//How many elements can be stored in one node
		const int QT_NODE_CAPACITY = 4;
		const int QT_MAX_DEPTH = 6;
		
		//Value keeping track of the depth of this node
		int depth;
		//Axis-aligned bounding box representing the center and boundaries of this quad.
		BoundingBox boundary;
		//Vector to store data (will only be used at deepest level)
		std::vector<Point> points;
		//Children
		QTree* nE;
		QTree* nW;
		QTree* sE;
		QTree* sW;
		
		//Constructor with parents depth called when splitting a node
		QTree(const BoundingBox, const int); 
		
		void subdivide();
		void queryRange(const BoundingBox, std::vector<Point*>&, const int);
		void getPointsSquare(std::vector<Point>&, std::vector<Point*>&);
		void getPointsCircle(const BoundingBox, std::vector<Point>&, std::vector<Point*>&);
		double euclideanDistance(const Point&, const Point&);
};

#endif //QT_H