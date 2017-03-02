#include "cell.h"

class Mesh {

	// Primitive point geometry
	struct Point {
		double coordinate_x;
		double coordinate_y;
		double coordinate_z;
		int index;
	};

	// Cell geometry
	class Mesh_Cell: public Cell {

		std::vector< Point* > points;
		Point centroid;

		public:
			Mesh_Cell();
			Mesh_Cell(std::vector< Point* > points);	
			
			int getVTKType();	
			std::vector<int> getPoints();

			bool isPointInside(
				std::vector<double> pointA,
				std::vector<double> pointB
			);
	};

	// Vectors with the geometry points and cells
	std::vector< Point     > points;
	std::vector< Mesh_Cell > cells;

	// Useful for printing VTK file, calculated in constructor
	int number_of_VTK_Cell_entries;

public:

	// A Mesh is constructed by providing two points in
	// space (x,y,z) which define oposing corners of a 
	// parallelepiped. "meshsize" indicates the number of
	// Cells in the X Y Z directions.
	Mesh( 
		std::vector<double> pointA, 
		std::vector<double> pointB, 
		std::vector<size_t> meshsize
	);
	
	std::vector< Cell >* exportMesh();

	std::ostream& toVTK(std::ostream &out);	

};