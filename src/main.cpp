#include "qTree.h"

#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <cmath>

double euclSlow(Point p1, Point p2)
{
	return(sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

double euclFast(Point p1, Point p2)
{
	double A = p1.x - p2.x;
	double B = p1.y - p2.y;
	return(sqrt(A*A + B*B));
}

int main()
{	
	std::clock_t c_start = std::clock();
	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_real_distribution<double> distr(0.0, 100.0);
	
	QTree qt(50,50,50);
	std::vector<Point*> resultsQT;
	std::vector<Point> pointsEucl;
	
	for(int i = 0; i<10000000; i++)
	{
		Point p(distr(generator), distr(generator));
		qt.insert(p);
		pointsEucl.push_back(p);
	}
	
	std::clock_t c_loading = std::clock();
	std::cout << "CPU time for initialising QTree: "
			  << 1000.0 * (c_loading - c_start) / CLOCKS_PER_SEC
			  << "ms." << std::endl;
	

	std::clock_t c_query_start = std::clock();	
	qt.queryCircle(50,50,1, resultsQT);
	std::clock_t c_query_end = std::clock();
	
	std::cout << std::endl
			  << "CPU time for querying QTree: "
			  << 1000.0 * (c_query_end - c_query_start) / CLOCKS_PER_SEC
			  << "ms." << std::endl;
	
	
	std::cout << "Found " << resultsQT.size() << " points within the QTree range." << std::endl << std::endl;
	
	std::vector<Point*> resultsEucl;
	Point p(50,50);
	
	std::clock_t c_eucl_start = std::clock();
	for(auto it = pointsEucl.begin(); it != pointsEucl.end(); it++)
	{
		if(euclFast(p,(*it)) < 1)
			resultsEucl.push_back(&(*it));
	}
	std::clock_t c_eucl_end = std::clock();
	
	std::cout << std::endl
			  << "CPU time for querying with euclidean: "
			  << 1000.0 * (c_eucl_end - c_eucl_start) / CLOCKS_PER_SEC
			  << "ms." << std::endl;
	
	std::cout << "Found " << resultsEucl.size() << " points within the euclidean range." << std::endl << std::endl;
	
	std::cout << "Press enter to exit." << std::endl;
	std::cin.ignore();
	
	return 0;
}