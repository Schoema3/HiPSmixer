// Compile  clear && make && ./bin/HipsMixer.x 

#include <iostream>
#include <stdlib.h>     
#include <time.h>       

#include "debug.h"
#include "mesh.h"
#include "tree.h"

int main(){

	_DEBUG( std::cout << "DEBUG mode is on!" << std::endl; );

	std::vector<double> pointA = {  0.0,  0.0, 0.0 };
	std::vector<double> pointB = { 1.0, 1.0, 1.0 };
	std::vector<size_t> meshsize  = { 4,3,2 };

	Mesh *mesh = new Mesh(pointA,pointB,meshsize);

	//mesh->printVTK();

	std::cout << "Program Finished" << std::endl;
	
	return 0;
}