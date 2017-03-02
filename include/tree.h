	#include "cell.h"

class Tree {

	std::vector< Cell* >* leaves;

	size_t number_of_levels;
	size_t number_of_dimensions;
	size_t children_per_node;

public:

	Tree(double number_of_dimensions, std::vector< Cell* >* field);

	void createEddyEvent();

};


