#ifndef TREE_H
#define TREE_H

#include "cell.h"

class Tree {

	std::vector< Cell* >* leaves;

	size_t number_of_levels;
	size_t number_of_dimensions;
	size_t children_per_node;

public:

	Tree(double number_of_dimensions, std::vector< Cell* >* field);

	void createEddyEvent();

	/**
	* Randomly select a node and it's grandchildren to swap there subtrees.
	* To identify the subtrees use the binary tree rule:
	* The children of a node with index N are given by (2*N)+1 and 2*(N+1)
	*/
	void createFlatEddyEvent();

private:
	/**
	* Exchange the source and  destination leave
	* @ param source, index of the source leave
	* @ param dest  , index of the source leave
	* @ param count,  number of exchange
	*/
	void swapLeaves(size_t source, size_t dest, size_t count);

};
#endif