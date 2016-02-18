#include "CrossOver.h"

std::vector<int> CrossOver::crossoverSelection(int crossOverRate)
{
	
	
	int rate = (20 - (20 - 2*crossOverRate ));
	
	for(int i = 0; i < 20; i++)
	{ 
		shuffler.push_back(i); 
	}
	
	std::random_shuffle(shuffler.begin(), shuffler.end());
	
	for(int i = 0; i < (20 - rate); i++)
	{
		remainingPopulation.push_back(shuffler.front());
		shuffler.erase(shuffler.begin()); 
	}

	return shuffler;
}

std::vector< std::vector<int> > CrossOver::crossOver (std::vector< std::vector<int> > population, std::vector<int> crossOverselector)
{
	int m = 20, n = 10;
	newPopulation.resize(m);
	for(int i =0; i < m; i++)
	{
		newPopulation[i].resize(n);
	}

	std::vector<int> parentSelection;
	std::vector<int> crossoverdeletable = crossOverselector;
	std::vector<std::vector<int> > sibling;
	int counter = 0;

	while (crossoverdeletable.size() != 0) {
		parentSelection.push_back(crossoverdeletable.front());
		crossoverdeletable.erase(crossoverdeletable.begin());
		parentSelection.push_back(crossoverdeletable.front());
		crossoverdeletable.erase(crossoverdeletable.begin());
		sibling = CrossOver::crossoverMask(population,parentSelection);
		counter = CrossOver::addToPopulationFromShuffler(counter, sibling);
		parentSelection.erase(parentSelection.begin());
		parentSelection.erase(parentSelection.begin());

	}
	
	CrossOver::addToPopulationFromRemaining(population, counter);
	
	/*for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
		  std::cout << newPopulation[i][j];
		}
		
		std::cout << std::endl;
	}*/
	
	parentSelection.clear();
	crossoverdeletable.clear();
	sibling.clear();
	crossOverselector.clear();
	
	return newPopulation;
}

std::vector< std::vector<int> > CrossOver::crossoverMask(std::vector< std::vector<int> > population, std::vector<int> parentSelection)
{
	
	std::vector< std::vector<int> > sibling;
	sibling.resize(2);
	
	for(int i =0; i <sibling.size();i++)
	{
		sibling[i].resize(10);
	}
	
	for (int i = 0; i < 5; i++)
	{
	  sibling[0][i] = population[parentSelection[0]][i];
	  sibling[1][i] = population[parentSelection[1]][i];
	}
	
	for(int i = 5; i < 10; i++)
	{
		sibling[0][i] = population[parentSelection[1]][i];
		sibling[1][i] = population[parentSelection[0]][i];
	}

	return sibling;
}

int CrossOver::addToPopulationFromShuffler(int counter, std::vector< std::vector<int> > sibling)
{
	for(int i = 0; i < 10; i++) {
		newPopulation[counter][i] = sibling[0][i]; 
	}
	counter++;
	for(int i = 0; i < 10; i++) {
		newPopulation[counter][i] = sibling[1][i]; 
	}
	
	counter++;
	return counter;
}

void CrossOver::addToPopulationFromRemaining(std::vector< std::vector<int> > population, int counter)
{
	/*for (int i = 0; i < remainingPopulation.size(); i++) 
	{
		std::cout<<i<<": ";
		for ( int j = 0; j < 10; j++)
		{
			std::cout << population[remainingPopulation[i]][j];
		}
		std::cout << std::endl;
	}*/
	
	for (int i = 0; i < remainingPopulation.size(); i++)
	{
		for(int j = 0; j < 10; j++)
		{
		  newPopulation[counter][j] = population[remainingPopulation[i]][j];
		}
		counter++;
	}
	
	//Displays index that is not being crossed over
	//for (int i: remainingPopulation)
	//{ std::cout << i << std::endl; }
}

void CrossOver::clearPopulation() {
  newPopulation.clear();
  remainingPopulation.clear();
  shuffler.clear();
}










