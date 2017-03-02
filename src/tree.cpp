#include "tree.h"

#include <cstdlib>	// rand()
#include <cmath>	// pow(), log2()
#include <time.h>	// time 
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

void Tree::createFlatEddyEvent(){
	// little note, maybe a TODO for the future
	// get ride of the log2() and pow() because they are slow
	// store these within the nodes.

	const size_t max_valid_Grandparent_ID = pow(2,number_of_levels-2)-1;

	// select random grandparent
	const size_t grandparent_ID = rand()% max_valid_Grandparent_ID;

	// select random children
	const size_t L = rand()%2;
	const size_t R = rand()%2;
	
	
	_DEBUG(
		std::cout << "number_of_levels         : " 		<< number_of_levels 		<< std::endl;
		std::cout << "max_valid_Grandparent_ID : [0 - " << max_valid_Grandparent_ID <<"]"<< std::endl;
		std::cout << "grandparent_ID           : " 		<< grandparent_ID 			<< std::endl;
		);

	// from grandparent to child ID:
	const size_t left_child_ID  = L==0 ?  grandparent_ID*4+3 : grandparent_ID*4+4;
	const size_t right_child_ID = R==0 ?  grandparent_ID*4+5 : grandparent_ID*4+6;

	_DEBUG(
		std::cout << std::endl;
		std::cout << "L|R                                 : " << L <<" | "<< R << std::endl;
		std::cout << "left_child_ID|right_child_ID        : " << left_child_ID << " | " << right_child_ID << std::endl;
		std::cout << "child_level                         : " << child_level << std::endl;
		);

	const size_t grandparent_level = log2(grandparent_ID+1);
	const size_t child_level = grandparent_level + 2;
	const size_t level_2_leaves = number_of_levels - child_level;

	// for the future, i guess instead of 2 use the number of children
	// leave = startID *  2 ^lvlToGo +( 2^lvlToGo -1)
		// to save time store the result of power
	const size_t t = pow( 2, level_2_leaves-1);
	const size_t source = left_child_ID  *t + t-1;
	const size_t dest   = right_child_ID *t + t-1;

	const size_t number_swaps = pow(2, number_of_levels-2  - grandparent_level -1 );

	_DEBUG(
		std::cout << std::endl;
		std::cout << "lv to go: " << level_2_leaves << std::endl;
		std::cout << "source  : " << source << std::endl;
		std::cout << "dest    : " << dest << std::endl;
		std::cout << "number_swaps  : " << number_swaps << std::endl;		
		);

	swapLeaves(source, dest, number_swaps);
}

void Tree::swapLeaves(size_t source, size_t dest, size_t count){
	Cell* temp_leave;
	for (int i = 0; i < count; ++i){
		temp_leave             = leaves->at(source +i);
		leaves->at(source +i)  = leaves->at(dest   +i);
		leaves->at(dest   +i)  = temp_leave;
	}
}