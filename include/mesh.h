#include <vector>
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "cell.h"

class Mesh {

	struct Point{
		double coordinate_x;
		double coordinate_y;
		double coordinate_z;
	};

	struct Face{
		std::vector< Point*  > points;
		std::vector< double  > normal;
		double area;
	};

	class Mesh_Cell: public Cell {

		//Geometric properties of the cell
		std::vector< Point*  > points;
		std::vector< double* > centroid;
		std::vector< Face*   > faces;
		
		bool checkPointConsistency();
		bool createFaces();
		bool createCentroid();

		public:

			Mesh_Cell( std::vector< Point* > points );		
	};

	// 3 dimensional vectors of points and cells
	std::vector< std::vector< std::vector< Point*     > > > points;
	std::vector< std::vector< std::vector< Mesh_Cell* > > > cells;

	int number_of_cells;
	

public:

	// 1D equally spaced mesh creation Constructor call
	Mesh( 
		std::vector<double> pointA, 
		std::vector<double> pointB, 
		std::vector<size_t> meshsize
	);

	~Mesh();
	void printVTK();
};