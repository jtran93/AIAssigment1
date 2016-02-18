#include "Genetic.h"
#include "Mutation.h"
#include "CrossOver.h"

int main()
{
	srand(time(0));
	
	int i = 0;
	int sMax = 0, zMax = 0;
	int sum = 0;
	int numGen = 0;
	int crossOverRate[] =  {0, 3, 5, 7, 9};
	int numGenPerRun [20];
	
	bool chromosomeFound = false;
	
	double avgNumGenPerPCO[5];
	
	std::vector < std::vector <int> > p, initialP;
	std::vector < std::vector <int> > secondLastP;
	std::vector<int> rate;
	
	Genetic population;
	Mutation mutation;
	CrossOver cross;
	
	population.createInitialPopulation(p);
	initialP = p;
	
	for(i = 0; i < 5; i++)
	{
		//Loop for # of trials
		for(int w = 0; w < 20; w++)
		{	

			rate = cross.crossoverSelection(crossOverRate[0]);
			numGen = 0;
			p = initialP;
			chromosomeFound = false;

			std::cout<<"\n"<<"\n=========================\n";
			std::cout<<"Trial #"<<w<<"\n";
			std::cout<<"=========================\n";
			
			while(chromosomeFound != true)
			{
				std::cout<<"Generation #"<<numGen<<"\n";
				population.printPopulation(p);
				if(w == 0)
				{
					if(crossOverRate[0] == 7)
					{
						if(sMax < 2)
						{
							//std::cout<<"Print to File\n";
							population.printToFile(p);
						}
						sMax++;
					}
					if(crossOverRate[0] == 0)
					{
						if(zMax < 2)
						{
							//std::cout<<"Print to File\n";
							population.printToFile(p);
						}
						zMax++;
					}
				}
				
				secondLastP = p;
				
				p = cross.crossOver(p, rate);
				//std::cout<<"Generation #"<<numGen<<" after crossover\n";
				
				p = mutation.generateMutation(p);
				//std::cout<<"Generation #"<<numGen<<" after mutation\n";
				
				//population.geneCount(p);
				chromosomeFound = population.findChromosome(p);
				numGen++;
				
				
			}
			
			if(w == 18||w==19 && crossOverRate[i] == 7 || crossOverRate[i] == 0)
			{
				population.printToFile(secondLastP);
				population.printToFile(p);
			}
			
			std::cout<<"\nPerfect chromosome found!\n";
			population.printPopulation(p);
			std::cout<<"Number of generations: "<<numGen++;
			numGenPerRun[w] = numGen;
			
			p.clear();
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
	}
	
	for(int q = 0; q<5; q++)
		std::cout<<"\nAverage number of generations per run at PCO "<<crossOverRate[q]<<" = "<<avgNumGenPerPCO[q];
	population.printAvg(avgNumGenPerPCO, crossOverRate);

	return (0); 
}













