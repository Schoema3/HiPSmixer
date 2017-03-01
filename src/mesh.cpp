#include "mesh.h"

///////////////////////////////////////////////////////////////////////////////////
////// Operators for subclass Mesh_Cell ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

Mesh::Mesh_Cell::Mesh_Cell( std::vector< Point* > input_points){
    points.swap(input_points);
}

std::vector<int> Mesh::Mesh_Cell::cellToVtk(){

    std::vector<int> cell_in_vtk(points.size() + 1);

    // 12 is the VTK cell type for Hexahedrons
    if( points.size() == 8 ){ cell_in_vtk[0] = 12; }

    for( int i = 0; i < points.size(); i++ ){
        cell_in_vtk[i+1] = points[i]->index;
    }

    return cell_in_vtk;
}

///////////////////////////////////////////////////////////////////////////////////
////// Operators for Mesh class ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

Mesh::Mesh(std::vector<double> pointA, std::vector<double> pointB, std::vector<size_t> meshsize){

    std::cout << "\nCreating Mesh..." << std::endl;
    _DEBUG( std::cout << "-- DEBUG mode is on!" << std::endl; );

    if( meshsize.size() != 3 ){
        std::cout<< "-- Attempted to create a non 3D mesh! \n"
                 << "Mesh creation failed!" << std::endl;
        return;
    }

    if( meshsize[0]*meshsize[1]*meshsize[2] <= 0 ){
        std::cout<< "-- Attempted to create a mesh with impossible refinement! \n"
                 << "-- Mesh size: " << meshsize[0]*meshsize[1]*meshsize[2] << " "
                 << "Mesh creation failed!" << std::endl;
        return;
    }
    
    number_of_cells  = meshsize[0]*meshsize[1]*meshsize[2];
    number_of_points = (1 + meshsize[0])*(1 + meshsize[1])*(1 + meshsize[2]);

    std::cout << "-- Creating mesh with " << number_of_points
              << " points and " << number_of_cells << " cells" 
              << std::endl;

    _DEBUG( std::cout << "-- Creating points" << std::endl; );

    int n;

    points.resize(meshsize[0]+1);
    for( int i = 0; i < points.size(); i++ ){
        points[i].resize(meshsize[1]+1);
        for( int j = 0; j < points[i].size(); j++ ){
           points[i][j].resize(meshsize[2]+1);
           for( int k = 0; k < points[i][j].size(); k++ ){
                points[i][j][k] = new Point();
                points[i][j][k]->coordinate_x = pointA[0] + (pointB[0] - pointA[0])*i/(meshsize[0]);
                points[i][j][k]->coordinate_y = pointA[1] + (pointB[1] - pointA[1])*j/(meshsize[1]);
                points[i][j][k]->coordinate_z = pointA[2] + (pointB[2] - pointA[2])*k/(meshsize[2]);

                points[i][j][k]->index = n;

                n++;

                _DEBUG( std::cout << "---- Created point " 
                                  << points[i][j][k]->index << ", "
                                  << i << " "  << j << " " << k << " coord: "
                                  << "(" << points[i][j][k]->coordinate_x 
                                  << "," << points[i][j][k]->coordinate_y 
                                  << "," << points[i][j][k]->coordinate_z 
                                  << ")" << std::endl; );
           }
        }
    }

    _DEBUG( std::cout << "-- Creating Cells" << std::endl; );

    cells.resize(meshsize[0]);
    for( int i = 0; i < cells.size(); i++ ){
        cells[i].resize(meshsize[1]);
        for( int j = 0; j < cells[i].size(); j++ ){
            cells[i][j].resize(meshsize[2]);
            for( int k = 0; k < cells[i][j].size(); k++ ){
                
                std::vector<Point*> pointVector = { 
                    points[i  ][j  ][k  ],
                    points[i+1][j  ][k  ],
                    points[i+1][j+1][k  ],
                    points[i  ][j+1][k  ],
                    points[i  ][j  ][k+1],
                    points[i+1][j  ][k+1],
                    points[i+1][j+1][k+1],
                    points[i  ][j+1][k+1]
                };

                _DEBUG( std::cout << "---- Created cell " 
                                  << i << " "  << j << " " << k 
                                  << std::endl; );

                cells[i][j][k] = new Mesh_Cell(pointVector);
                n++;
           }
        }
    }

    std::cout << "-- Finished!" << std::endl;
}

void Mesh::setExampleScalar(){
 
    for( int i = 0; i < cells.size()/2; i++ ){
        for( int j = 0; j < cells[i].size(); j++ ){
            for( int k = 0; k < cells[i][j].size(); k++ ){
                
                cells[i][j][k]->test_scalar = 1.0 ;
            }
        }
    }


}

void Mesh::printVTK(){

    std::cout << "\nWriting Mesh to file..." << std::endl;

    std::ofstream my_file("mesh.vtk");

    if( my_file.is_open() )
    {
        my_file << "# vtk DataFile Version 3.1 \n"
                << "something something place-holder \n"
                << "ASCII \n"
                << "DATASET UNSTRUCTURED_GRID\n";

        my_file << "\n\nPOINTS " << number_of_points <<" FLOAT\n";

        _DEBUG( std::cout << "-- Printing Points" << std::endl; );

        for( int i = 0; i < points.size(); i++ ){
            for( int j = 0; j < points[i].size(); j++ ){
                for( int k = 0; k < points[i][j].size(); k++ ){
                    
                    my_file << points[i][j][k]->coordinate_x << " " 
                            << points[i][j][k]->coordinate_y << " "
                            << points[i][j][k]->coordinate_z << "\n";

                    _DEBUG( std::cout << "---- printed point " 
                                      << points[i][j][k]->coordinate_x << " " 
                                      << points[i][j][k]->coordinate_y << " "
                                      << points[i][j][k]->coordinate_z 
                                      << std::endl; );
               }
            }
        }

        std::vector< std::vector<int> > cells_to_print(number_of_cells);

        int n = 0;
        int total_number_of_entries = 0;

        for( int i = 0; i < cells.size(); i++ ){
            for( int j = 0; j < cells[i].size(); j++ ){
                for( int k = 0; k < cells[i][j].size(); k++ ){
                    cells_to_print[n] = cells[i][j][k]->cellToVtk();
                    total_number_of_entries += cells_to_print[n].size();
                    n++;
               }
            }
        }

        my_file << "\n\nCELLS " << number_of_cells <<" " << total_number_of_entries << "\n"; 

        _DEBUG( std::cout << "-- Printing Cells" << std::endl; );

        for( int i = 0; i < number_of_cells; i++ ){

            my_file << cells_to_print[i].size()-1;

            for( int j = 1; j < cells_to_print[i].size(); j++){
                my_file <<  " " << cells_to_print[i][j];
            }

            my_file << "\n";

            _DEBUG( std::cout << "---- printed cell " << i << std::endl; );
        }

        my_file << "\n\nCELL_TYPES " << number_of_cells << "\n";   
        
        for( int i = 0; i < number_of_cells; i++ ){
            my_file << cells_to_print[i][0] << " ";
        }


        my_file << "\n\nCELL_DATA " << number_of_cells << "\n"
                << "SCALARS ExampleScalar float \n"
                << "LOOKUP_TABLE default \n";

        for( int i = 0; i < cells.size(); i++ ){
            for( int j = 0; j < cells[i].size(); j++ ){
                for( int k = 0; k < cells[i][j].size(); k++ ){
                my_file << cells[i][j][k]->test_scalar << "\n";
               }
            }
        }

        my_file.close();
        std::cout << "-- File closed!" << std::endl;

        


    }
    else std::cout << "-- Unable to open file" << std::endl;

    std::cout << "-- Finished!" << std::endl;
}