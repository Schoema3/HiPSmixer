#include "solver.h"

Solver::Solver(Mesh* input_mesh){

    mesh = input_mesh;
    step = 0;

}

void Solver::printVTK(){

    std::cout << "\nWriting current result state to file..." << std::endl;

    std::ofstream my_file("mesh.vtk");

    if( my_file.is_open() ){

        my_file << "# vtk DataFile Version 3.1 \n"
                << "something something place-holder \n"
                << "ASCII \n"
                << "DATASET UNSTRUCTURED_GRID\n";

        _DEBUG( std::cout << "-- Printing mesh data" << std::endl; );
        
        mesh->toVTK(my_file);
     
//        my_file << "\n\nCELL_DATA " << cells.size();
//
//        for( int i = 0; i < fields.size(); i++ ){
//
//            
//            my_file << "\nSCALARS " << fields[i]->getName() << " float \n"
//                    << "LOOKUP_TABLE default \n";
//
//            std::vector<double> field_to_print = fields[i]->toVTK();
//
//            for( int j = 0; j < field_to_print.size(); j++ )
//            {
//                my_file << field_to_print[j] << "\n";
//            }
//        } 

        my_file.close();
        std::cout << "-- File closed!" << std::endl;

    }
    else std::cout << "-- Unable to open file" << std::endl;
}