#pragma once
#define DEBUG
#include "debug.h"

#include <vector>
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <time.h>

#include "mesh.h"
//#include "field.h"
#include "tree.h"

class Solver {

	Mesh*   mesh;
	//Fields* fields;

	std::vector< Tree*  > Trees;

	int step;

	public:

		Solver(Mesh* input_mesh);

		void printVTK();
};