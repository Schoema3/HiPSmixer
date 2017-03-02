#include "tree.h"

Tree::Tree(double number_of_dimensions, std::vector< Cell* >* field){

	std::cout << "\nCreating Binary tree...!" << std::endl;

	leaves = field;

	srand(time(NULL));
	_DEBUG(srand(3););

}

void Tree::createEddyEvent(){

	int r1 = rand()%(int)( leaves->size() );
	int r2 = rand()%(int)( leaves->size() );

	std::cout << "\nChaning cell " << r1 << " with cell " << r2 << std::endl; 
	Cell* temp_leave;

	temp_leave = leaves->at(r1);
	leaves->at(r1) = leaves->at(r2);
	leaves->at(r2) = temp_leave;
}