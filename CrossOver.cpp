#include "CrossOver.h"

std::vector<int> CrossOver::crossoverSelection(std::vector< std::vector <int> > population, int crossOverRate)
{
	int rate = 2*crossOverRate;

	for(int i = 0; i < 20; i++)
	{
		remainingPopulation.push_back(i);
	}
	
	std::vector<int> shuffler = CrossOver::geneCount(population, remainingPopulation, rate);

	for(int i = 0; i < shuffler.size(); i++)
	{
		remainingPopulation.erase(std::remove(remainingPopulation.begin(), remainingPopulation.end(), shuffler[i]), remainingPopulation.end());
	}
	
	return shuffler;
}

std::vector<int> CrossOver::geneCount(std::vector< std:: vector<int> > chromosomePopulation, std::vector<int> crossOverselector, int rate)
{
	std::vector<int> highestChromosome;

	int counter = 0;
	int highestFitnessValue = 0;
	int tracker = 0;
	
	while(counter < rate)
	{
		for(int i = 0; i< 20; i++)
		{
			int fitnessValue = 0;
			
			for(int j = 0; j < 10; j++)
			{
				if(chromosomePopulation[crossOverselector[i]][j] == 1)
				{
				  fitnessValue++;
				}
			}
			
			if(highestFitnessValue <= fitnessValue && std::find(highestChromosome.begin(), highestChromosome.end(), i) == highestChromosome.end() && counter != rate)
			{
				highestFitnessValue = fitnessValue;
				tracker = i;
			}
		}
		highestChromosome.push_back(tracker);
		counter++;
		highestFitnessValue = 0;
	}
	
	return highestChromosome;
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










