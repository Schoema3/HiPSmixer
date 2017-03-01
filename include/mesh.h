#include "cell.h"

class Mesh {

	struct Point{
		double coordinate_x;
		double coordinate_y;
		double coordinate_z;
		int index;
	};

	struct Face{
		std::vector< Point*  > points;
		std::vector< double  > normal;
		double area;
	};

	class Mesh_Cell: public Cell {

		//Geometric properties of the cell
		std::vector< Point*  > points;
		std::vector< double* > centroid; // NA
		std::vector< Face*   > faces;    // NA
		
		bool checkPointConsistency();
		bool createFaces();
		bool createCentroid(); 

		public:

			Mesh_Cell( std::vector< Point* > points);	

			std::vector<int> cellToVtk();

			double test_scalar = 0.0;
	};


	// 3 dimensional vectors of points and cells
	std::vector< std::vector< std::vector< Point*     > > > points;
	std::vector< std::vector< std::vector< Mesh_Cell* > > > cells;
	
	//std::vector< double > test_vector;

	int number_of_cells;
	int number_of_points;

public:

	// 1D equally spaced mesh creation Constructor call
	Mesh( 
		std::vector<double> pointA, 
		std::vector<double> pointB, 
		std::vector<size_t> meshsize
	);

	void setExampleScalar();
	void printVTK();
};