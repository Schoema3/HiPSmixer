#include "mesh.h"

///////////////////////////////////////////////////////////////////////////////////
////// Operators for subclass Mesh_Cell ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


Mesh::Mesh_Cell::Mesh_Cell( std::vector< Point* > input_points ){

    points.swap(input_points);
}


///////////////////////////////////////////////////////////////////////////////////
////// Operators for Mesh class ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

Mesh::Mesh(std::vector<double> pointA, std::vector<double> pointB, std::vector<size_t> meshsize){

    std::cout << "Creating Mesh..." << std::endl;

    if ( meshsize.size() != 3 ){
    	std::cout<< "-- Attempted to create a non 3D mesh! \n"
    	         << "Mesh creation failed!" << std::endl;
    	return;
    }

    if ( meshsize[0]*meshsize[1]*meshsize[2] <= 0 ){
    	std::cout<< "-- Attempted to create a mesh with impossible refinement! \n"
    	         << "-- Mesh size: " << meshsize[0]*meshsize[1]*meshsize[2] << " "
    	         << "Mesh creation failed!" << std::endl;
    	return;
    }
    
    std::cout << "-- Creating mesh with " 
              << (1 + meshsize[0])*(1 + meshsize[1])*(1 + meshsize[2])
              << " points and " << meshsize[0]*meshsize[1]*meshsize[2] 
              << " cells" 
              << std::endl;

    points.resize(meshsize[0]+1);
	for (int i = 0; i < points.size(); i++){
	    points[i].resize(meshsize[1]+1);
	    for (int j = 0; j < points[i].size(); j++){
	       points[i][j].resize(meshsize[2]+1);
	       for( int k = 0; k < points[i][j].size(); k++){
	       		points[i][j][k] = new Point();
	       	    points[i][j][k]->coordinate_x = pointA[0] + (pointB[0] - pointA[0])*i/(meshsize[0]);
		        points[i][j][k]->coordinate_y = pointA[1] + (pointB[1] - pointA[1])*j/(meshsize[1]);
		        points[i][j][k]->coordinate_z = pointA[2] + (pointB[2] - pointA[2])*k/(meshsize[2]);
	       }
	    }
	}

	cells.resize(meshsize[0]);
	for (int i = 0; i < cells.size(); i++){
	    cells[i].resize(meshsize[1]);
	    for (int j = 0; j < cells[i].size(); j++){
	    	cells[i][j].resize(meshsize[2]);
	    	for (int k = 0; k < cells[i][j].size(); j++){

	    		std::vector<Point*> pointVector = { 
	    			points[i  ,j  ,k  ],
	    			points[i+1,j  ,k  ],
	    			points[i+1,j+1,k  ],
	    			points[i  ,j+1,k  ],
	    		    points[i  ,j  ,k+1],
	    			points[i+1,j  ,k+1],
	    			points[i+1,j+1,k+1],
	    			points[i  ,j+1,k+1]
	    		};

	    		//cells[i][j][k] = new Mesh_Cell(pointVector);
	       }
	    }
	}


}


void Mesh::printVTK(){

	std::cout << "Writing Mesh to file..." << std::endl;

    std::ofstream myfile("mesh.vtk");

    if( myfile.is_open() )
    {
        myfile << "# vtk DataFile Version 3.1 \n"
               << "ASCII \n"
               << "DATASET UNSTRUCTURED_GRID\n";

        myfile << "\n\nPOINTS " << points.size() <<" FLOAT\n";

        //for( int i = 0; i < points.size(); i++ ){
        //    myfile << points[i]->coordinate_x << " " 
        //           << points[i]->coordinate_y << " "
        //           << points[i]->coordinate_z << "\n";
        //}
		
        myfile.close();
        std::cout << "-- Finished!" << std::endl;
    }
    else std::cout << "--Unable to open file" << std::endl;


}