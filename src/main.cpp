// Compile  clear && make && ./bin/HipsMixer.x 
#include <iostream>
#include <stdlib.h>       

#include "debug.h"
#include "solver.h"

int main(){

	std::cout << "\nProgram Started!" << std::endl;
	_DEBUG( std::cout << "DEBUG mode is on!" << std::endl; );

	std::vector<double> pointA    = {   0.0,   0.0,  0.0 };
	std::vector<double> pointB    = { 100.0, 100.0,  1.0 };
	std::vector<size_t> meshsize  = {     2,     2,    1 };

	Mesh mesh     = Mesh(pointA,pointB,meshsize);
	Solver solver = Solver(&mesh);

	solver.printVTK();
	std::cout << "\nProgram Finished" << std::endl;
	
	return 0;
}