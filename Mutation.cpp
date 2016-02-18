#include "Mutation.h"

/*
	Randomly choose an element in the vector and swap it's value.
	If 1 -> 0
	If 0 -> 1
*/
	
std::vector < std::vector <int> > Mutation::generateMutation(std::vector < std::vector <int> > population)
{
	int n = 10;
	int m = 20;
	int originalValue = 0;
	int newValue = 0;
	
	srand(time(0));
	mutationX = rand()%m;
	mutationY = rand()%n;
	
	//Displays where the mutation occured.
	//std::cout<<"Mutation (Row, Column): ("<<mutationX<<", "<<mutationY<<")"<<"\n";
	originalValue = population[mutationX][mutationY];
	
	//Tests the value and swaps accordingly.
	if (originalValue == 0)
	{
		newValue = 1;
	}
	else if (originalValue == 1)
	{
		newValue = 0;
	}
	population[mutationX][mutationY] = newValue;
	
	//Displays what value was swapped and what it was swapped to.
	//std::cout<<"Original value: "<<originalValue<<"\n";
	//std::cout<<"New value: "<<newValue<<"\n";
	
	return population;
}

int Mutation::getMutationX()
{
	return mutationX;
}

int Mutation::getMutationY()
{
	return mutationY;
}










