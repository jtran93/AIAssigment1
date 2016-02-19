#include "Genetic.h"
#include "Mutation.h"
#include "CrossOver.h"

int main()
{
	
	int i = 0;
	int sMax = 0, zMax = 0;
	int sum = 0;
	int numGen = 0;
	int crossOverRate[] =  {3, 5, 7, 9, 0};
	int numGenPerRun [20];
	
	bool chromosomeFound = false;
	
	double avgNumGenPerPCO[5];
	
	std::vector < std::vector <int> > p, initialP;
	std::vector < std::vector <int> > secondLastP;
	std::vector<int> rate;
	
	Genetic population;
	Mutation mutation;
	CrossOver cross;
	
	population.createInitialPopulation(initialP);
	p = initialP;
	
	//Loop for each PCO value
	for(i = 0; i < 5; i++)
	{
		//Loop for # of trials
		for(int w = 0; w < 20; w++)
		{	
			rate = cross.crossoverSelection(p, crossOverRate[i]);
			numGen = 0;
			p = initialP;
			chromosomeFound = false;

			std::cout<<"\n"<<"\n=========================\n";
			std::cout<<"Trial #"<<w<<"\n";
			std::cout<<"=========================\n";
			
			//Loop until perfect chromosome is found
			while(chromosomeFound != true)
			{
				std::cout<<"PCO = "<<crossOverRate[i]<<" Generation #"<<numGen<<"\n";
				population.printPopulation(p);
				
				secondLastP = p;
				
				p = cross.crossOver(p, rate);

				p = mutation.generateMutation(p);
				
				if(w == 0)
				{
					if(crossOverRate[i] == 7)
					{
						if(sMax < 2)
						{
							population.printToFile(p);
						}
						sMax++;
					}
					if(crossOverRate[i] == 0)
					{
						if(zMax < 2)
						{
							population.printToFile(p);
						}
						zMax++;
					}
				}
				

				chromosomeFound = population.findChromosome(p);
				numGen++;
			}
			
			if(chromosomeFound == true)
					std::cout<<"\nTrial #"<<w<<"\n";
			
			if(w == 18||w==19 && crossOverRate[i] == 7 || crossOverRate[i] == 0)
			{
				population.printToFile(secondLastP);
				population.printToFile(p);
			}
			
			std::cout<<"\nPerfect chromosome found!\n";
			population.printPopulation(p);
			std::cout<<"Number of generations: "<<numGen++;
			numGenPerRun[w] = numGen;
			
			cross.clearPopulation();
		}
		
		for(int k = 0; k < 20; k++)
		{
			std::cout<<"\nRun "<<k<<": "<<numGenPerRun[k];
			sum = numGenPerRun[k]+sum;
		}
		
		avgNumGenPerPCO[i] = sum / 20;
		sum = 0;
		population.printNumGen(numGenPerRun, crossOverRate[i]);
		population.printAvg(numGenPerRun, crossOverRate[i]);
	}
	
	for(int q = 0; q<5; q++)
		std::cout<<"\nAverage number of generations per run at PCO "<<crossOverRate[q]<<": "<<avgNumGenPerPCO[q];

	return (0); 
}













