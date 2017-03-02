#include "mesh.h"

Mesh::Mesh_Cell::Mesh_Cell(){  
    points.resize(8);
}

Mesh::Mesh_Cell::Mesh_Cell( std::vector< Point* > input_points ){
    
    points.swap(input_points);

    // provisory centroid calculation

    centroid.coordinate_x = 0.0;
    centroid.coordinate_y = 0.0;
    centroid.coordinate_z = 0.0;

    for( int i = 0; i < points.size(); i++)
    {
        centroid.coordinate_x += points[i]->coordinate_x;
        centroid.coordinate_y += points[i]->coordinate_y;
        centroid.coordinate_z += points[i]->coordinate_z;
    }

    centroid.coordinate_x /= points.size();
    centroid.coordinate_y /= points.size();
    centroid.coordinate_z /= points.size();
}

int Mesh::Mesh_Cell::getVTKType(){

    // 12 is the VTK cell type for Hexahedrons
    if( points.size() == 8 ){ return 12; }

    return 0;
}

std::vector<int> Mesh::Mesh_Cell::getPoints(){

    std::vector<int> return_points(points.size());

    for( int i = 0; i < points.size(); i++ ){
        return_points[i] = points[i]->index;
    }

    return return_points;
}

bool Mesh::Mesh_Cell::isPointInside(std::vector<double> pointA, std::vector<double> pointB){

    _DEBUG( std::cout << "---- checking point with centroid (" 
                      << centroid.coordinate_x << ","
                      << centroid.coordinate_y << ","
                      << centroid.coordinate_z << ")" 
                      << " against point (" 
                      << pointA[0] << "," << pointA[1] << ","  << pointA[2] << ") and (" 
                      << pointB[0] << "," << pointB[1] << ","  << pointB[2] << ")" 
                      << "..."; 
    );

    if( centroid.coordinate_x > pointA[0] && centroid.coordinate_x > pointB[0] ){
        return false;
    }
    if( centroid.coordinate_x < pointA[0] && centroid.coordinate_x < pointB[0] ){
        return false;
    }
    if( centroid.coordinate_y > pointA[1] && centroid.coordinate_y > pointB[1] ){
        return false;
    }
    if( centroid.coordinate_y < pointA[1] && centroid.coordinate_y < pointB[1] ){
        return false;
    }
    if( centroid.coordinate_z > pointA[2] && centroid.coordinate_z > pointB[2] ){
        return false;
    }
    if( centroid.coordinate_z < pointA[2] && centroid.coordinate_z < pointB[2] ){
        return false;
    }

    return true;
}

Mesh::Mesh(std::vector<double> pointA, std::vector<double> pointB, std::vector<size_t> meshsize){

    std::cout << "\nCreating Mesh..." << std::endl;
    _DEBUG( std::cout << "-- DEBUG mode is on!" << std::endl; );

    // sizes for the cell matrix m*n*l
    size_t dim_m = meshsize[0];
    size_t dim_n = meshsize[1];
    size_t dim_l = meshsize[2]; 

    if( meshsize.size() != 3 ){
        std::cout<< "-- Attempted to create a non 3D mesh! \n"
                 << "Mesh creation failed!" << std::endl;
        return;
    }

    if( meshsize[0]*meshsize[1]*meshsize[2] <= 0 ){
        std::cout<< "-- Attempted to create a mesh with impossible refinement! \n"
                 << "-- Mesh size: "   << dim_m  << "x" 
                 << dim_n << "x" << dim_l << " "
                 << "Mesh creation failed!" << std::endl;
        return;
    }
    
    points.resize( (dim_m + 1) * (dim_n + 1) * (dim_l + 1) );
    
    cells.resize( dim_m * dim_n * dim_l );

    std::cout << "-- Creating mesh with " << points.size()
              << " points (" << (dim_m+1) << "x" << (dim_n+1) << "x" << (dim_l+1)
              << ") and " << cells.size() << " cells (" 
              << dim_m << "x" << dim_n << "x" << dim_l << ")"
              << std::endl;

    _DEBUG( std::cout << "-- Creating points" << std::endl; );

    for( int i = 0; i < (dim_m + 1); i++ ){
        for( int j = 0; j < (dim_n + 1); j++ ){
           for( int k = 0; k < (dim_l + 1); k++ ){

                const int index = i*(dim_n+1)*(dim_l+1) + j*(dim_l+1) + k;

                _DEBUG( std::cout << "---- Creating point " 
                                  << index 
                                  << ", "<< i << " " << j << " " << k << "..."; );

                points[index] = Point();

                points[index].coordinate_x = pointA[0] + (pointB[0] - pointA[0])*i/(meshsize[0]);
                points[index].coordinate_y = pointA[1] + (pointB[1] - pointA[1])*j/(meshsize[1]);
                points[index].coordinate_z = pointA[2] + (pointB[2] - pointA[2])*k/(meshsize[2]);
                
                points[index].index = index;

                _DEBUG( std::cout << "OK! coord: "
                                  << "(" << points[index].coordinate_x 
                                  << "," << points[index].coordinate_y 
                                  << "," << points[index].coordinate_z 
                                  << ")" << std::endl; );
           }
        }
    }

    _DEBUG( std::cout << "-- Creating Cells" << std::endl; );

    number_of_VTK_Cell_entries = 0;

    for( int i = 0; i < dim_m; i++ ){
        for( int j = 0; j < dim_n; j++ ){
            for( int k = 0; k < dim_l; k++ ){
                
                const int index = i*dim_n*dim_l + j*dim_l + k;

                _DEBUG( std::cout << "---- Creating cell "  << index 
                                  << " (" << i << " "  << j << " " << k
                                  << ") ..." ; ); 

                std::vector<Point*> pointVector = { 
                    &points[(i  )*(dim_n+1)*(dim_l+1) + (j  )*(dim_l+1) + (k  )],
                    &points[(i+1)*(dim_n+1)*(dim_l+1) + (j  )*(dim_l+1) + (k  )],
                    &points[(i+1)*(dim_n+1)*(dim_l+1) + (j+1)*(dim_l+1) + (k  )],
                    &points[(i  )*(dim_n+1)*(dim_l+1) + (j+1)*(dim_l+1) + (k  )],
                    &points[(i  )*(dim_n+1)*(dim_l+1) + (j  )*(dim_l+1) + (k+1)],
                    &points[(i+1)*(dim_n+1)*(dim_l+1) + (j  )*(dim_l+1) + (k+1)],
                    &points[(i+1)*(dim_n+1)*(dim_l+1) + (j+1)*(dim_l+1) + (k+1)],
                    &points[(i  )*(dim_n+1)*(dim_l+1) + (j+1)*(dim_l+1) + (k+1)]
                };

                cells[index] = Mesh_Cell(pointVector);
                number_of_VTK_Cell_entries += 9; // 8 points + cell type

                _DEBUG( std::cout << " OK! points:";

                    std::vector<int> cell_to_print =cells[index].getPoints();

                    for( int i = 1; i < cell_to_print.size(); i++ ){
                        std::cout <<  " " << cell_to_print[i];
                    }

                    std::cout << std::endl; 
                );
           }
        }
    }

    std::cout << "-- Finished!" << std::endl;
}

std::ostream& Mesh::toVTK(std::ostream &out){

    out << "\n\nPOINTS " << points.size() <<" FLOAT\n";

    _DEBUG( std::cout << "---- Printing Points" << std::endl; );

    for( int i = 0; i < points.size(); i++ ){
                
        out << points[i].coordinate_x << " " 
            << points[i].coordinate_y << " "
            << points[i].coordinate_z << "\n";

        _DEBUG( std::cout << "------ printed point "
                          << points[i].index << " coord: "
                          << points[i].coordinate_x << " " 
                          << points[i].coordinate_y << " "
                          << points[i].coordinate_z 
                          << std::endl; );
    }

    out << "\n\nCELLS " << cells.size() <<" " << number_of_VTK_Cell_entries << "\n"; 

    _DEBUG( std::cout << "---- Printing Cells" << std::endl; );

    for( int i = 0; i < cells.size(); i++ ){

        std::vector< int > points_to_print = cells[i].getPoints();
        
        out <<  points_to_print.size();

        for( int j = 0; j < points_to_print.size(); j++){
            out << " " << points_to_print[j];
        }

        out << "\n";

        _DEBUG( std::cout << "---- printed cell " << i << std::endl; );
    }

    out << "\n\nCELL_TYPES " << cells.size() << "\n";   
    
    for( int i = 0; i < cells.size(); i++ ){
        out << cells[i].getVTKType() << " ";
    }

    out << "\n";

    return out;
}
