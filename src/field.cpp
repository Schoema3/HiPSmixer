/*#include "field.h"


Field::Field(std::vector< Cell* >* input_mesh, std::string input_string, double initial_value){

	name = input_string;

	std::cout << "\nCreating field: " << name << " ..." << std::endl;

	field.resize(input_mesh->size());

	for( int i = 0; i < field.size(); i++ ){

		field[i] = new Field_Cell(initial_value);
	}

	std::cout << "-- Created field with " << field.size() << " entries!" << std::endl;
}

void Field::updateField( int index, double value){

	dynamic_cast<Field_Cell*>(field[index])->setValue(value);
}

std::vector<double> Field::toVTK(){

	std::vector<double> response(field.size());

	for( int i = 0; i < field.size(); i++ ){
		response[i] = dynamic_cast<Field_Cell*>(field[i])->getValue();
	}

	return response;
}


void Mesh::addField( std::string field_name, double initial_value ){

    fields.push_back( new Field( &cells, field_name, initial_value) );
}

void Mesh::updateField( std::string field_name, std::vector<double> pointA, std::vector<double> pointB, double value ){

    std::cout << "\nManually modifying field " << field_name  << "..." << std::endl;

    Field* field_to_update;

    for( int i = 0; i < fields.size(); i++ ){
        if( fields[i]->getName() == field_name){
            field_to_update = fields[i];
            break;
        }
    }

    if(field_to_update){

        _DEBUG( std::cout << "-- checking All points..." << std::endl; );

        for( int i = 0; i < cells.size(); i++ ){

            if(dynamic_cast<Mesh_Cell*>(cells[i])->isPointInside(pointA,pointB)){
                _DEBUG( std::cout << " Cell updated!"; );
                field_to_update->updateField(i,value); 
            }
            _DEBUG( std::cout << std::endl; );
        }
        
    }
    else{
        std::cout << "-- Error updating field! Field " << field_name  << " does not exist!" << std::endl;
    }

    std::cout << "-- Finished!" << std::endl;
}


std::vector< Cell* >* Mesh::exportField( std::string field_name ){

    Field* field_to_export;

    for( int i = 0; i < fields.size(); i++ ){
        if( fields[i]->getName() == field_name){
            field_to_export = fields[i];
            break;
        }
    }    

    if(field_to_export){ return field_to_export->exportField(); }
    else{
        std::cout << "-- Error updating field! Field " << field_name  << " does not exist!" << std::endl;
        return NULL;
    }
}
*/