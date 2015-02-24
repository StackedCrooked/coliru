/*
 ============================================================================
 Name        : GenericAlgorithm.c
 Author      : Luyi LIu
 Version     :
 Copyright   : @Louis Liu
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#define LENGTH 10 //length of gene
#define PSIZE 50 //population size
#define MUTAION_RATE 0.001 //mutation rate

//convert decimal int to binary format int which is represented in a decimal format.
//only for display, cannot be used for computing.
unsigned long long int_to_binary(unsigned long long k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_binary(k / 2)));
}

void generate_mask(char *mask1, char *mask2, double crossover) {
	int i;
	for (i = 0; i < LENGTH; i++) {
		if (i < LENGTH * crossover) {
			mask1[i] = '0';
			mask2[i] = '1';
		} else {
			mask1[i] = '1';
			mask2[i] = '0';
		}
	}
}

int fitness(char *chrom) {
	int fitness = 0;
	int i;
	for (i = 0; i < LENGTH; i++) {
		if (chrom[i] == '1')
			fitness++;
	}
	return fitness;
}

int totalFitness(char **population) {
	int total_fitness = 0;
	int i;
	for (i = 0; i < PSIZE; i++) {
		total_fitness += fitness(population[i]);
	}
	return total_fitness;
}

void mutate(char *chrom, double mutationRate) {
	int i;
	for (i = 0; i < LENGTH; i++) {
		double random = (double) rand() / (double) RAND_MAX;
		if (random < mutationRate)
			(chrom[i] == '1') ? (chrom[i] = '0') : (chrom[i] = '1');
	}
}

void initp(char **population) {
	int i, j;
	for (i = 0; i < PSIZE; i++) {
		for (j = 0; j < LENGTH; j++) {
			int random = rand() % 100;
			if (random < 50) {
				population[i][j] = '0';
			} else {
				population[i][j] = '1';
			}
		}
		//printf("population[%d]: %s\n", i, population[i]);
	}
}

void selection(char **population, int *x, int *y) {
	int total_fitness = totalFitness(population);
	//printf("total fitness: %d\n",total_fitness);
//printf("xy: %d %d",*x,*y);
//	while (*x == *y) {  //make sure the two parents are different
		int random1 = rand() % (total_fitness + 1);
		int random2 = rand() % (total_fitness + 1);
		if (random1 > random2) {
			int temp = 0;
			temp = random1;
			random1 = random2;
			random2 = temp;
		} //let random 1 < random2
		  //printf("random 1: %d 2: %d\n", random1, random2);
		int t = 0;
		int i;
		for (i = 0; i < PSIZE; i++) {
			t += fitness(population[i]);
			if (t > random1 && *x == 0)
				*x = i;
			if (t > random2 && *y == 0) {
				*y = i;
				break;
			}
		}
//	}
}

char * crossover(char **population, double p_crossover) {
	//selection
	int x = 0, y = 0; //x,y store the index of two selected parents
	selection(population, &x, &y);
	//printf("selected parents index: %d %d\n",x, y);

	char *child = (char *) malloc(LENGTH * sizeof(char));
	int crossover_point = p_crossover * LENGTH;
	int gene;
	for (gene = 0; gene < LENGTH; gene++) {
		if (gene < crossover_point)
			child[gene] = population[x][gene];
		else
			child[gene] = population[y][gene];
	}
	// printf("parents : %s %s\n", population[x], population[y]);
	return child;
}

void print_population(char **population) {
	int i;
	for (i = 0; i < PSIZE; i++) {
		printf("population[%02d]: %s (%d)\n", i, population[i],
				fitness(population[i]));
	}
}

int main(int argc, char **argv) {
    time_t t;
    /* Intializes random number generator */
   srand((unsigned) time(&t));
	char **population; //include every parent that is about to have childen
	int length = LENGTH;
	int max_population = PSIZE;
	double mutation_rate = MUTAION_RATE;
	int i;
	population = (char **) malloc(max_population * sizeof(char *));
	for (i = 0; i < max_population; i++) {
		population[i] = (char *) malloc(length * sizeof(char));
	}
//	puts("init..");
	initp(population);
//	print_population(population);
	int total_fitness = totalFitness(population);
	printf("total fitness: %d\n", total_fitness);

	double p_crossover = (double) 0.5; //this determines the crossover point in chrom
	int generation = 0;
	int limit = LENGTH * max_population;
	while (total_fitness < limit) {
		generation++;
		for (i = 0; i < max_population; i++) {
			char *child = crossover(population, p_crossover);
			mutate(child, mutation_rate);
			//printf("child: %s\n", child);
			population[i] = child;
		}
		printf("after %d generation\n", generation);
	//	print_population(population);
		total_fitness = totalFitness(population);
		printf("total fitness: %d\n", total_fitness);
	}

	//long long type can represent upto 20 bits of 1 and 0,
	//chroms longer than 20bits will be splited to array of long long numbers

	/*char chrom1[] = "10101010001101011";
	 char chrom2[] = "11010000110010010";
	 int length = sizeof(chrom1)-1;

	 double crossover = (double)0.5; //this determines the crossover point in chrom

	 //generate mask for crossover
	 char *mask1 = (char *) malloc(length*sizeof(char));
	 char *mask2 = (char *) malloc(length*sizeof(char));
	 generate_mask(mask1, mask2, length, crossover);
	 printf("input  1: %15s (%d) 2: %15s (%d) Length: %d\n", chrom1, fitness(chrom1,length), chrom2, fitness(chrom2, length), length);
	 printf("masks  1: %15s 2: %15s\n", mask1, mask2);
	 char *ptr1,*ptr2;

	 //convert the above 4 string values to decimal int following binary rule.
	 long long ret1 = strtoul(chrom1, &ptr1, 2);
	 long long ret2 = strtoul(chrom2, &ptr2, 2);
	 long long m1 = strtoul(mask1, &ptr1, 2);
	 long long m2 = strtoul(mask2, &ptr2, 2);

	 //crossover operation
	 long long ichild1 = (ret1 & m2) ^ (ret2 & m1);
	 long long ichild2 = (ret1 & m1) ^ (ret2 & m2);
	 //convert binary format childern to string, in order to add them to parent pool.
	 char *child1 = (char *)malloc(length * sizeof(char));
	 char *child2 = (char *)malloc(length * sizeof(char));
	 sprintf(child1,"%lld",int_to_binary(ichild1));
	 sprintf(child2,"%lld",int_to_binary(ichild2));

	 printf("child 1: %18s 2: %s",child1,child2);
	 */

	return 0;
}