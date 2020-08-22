//
// Created by rene on 22/08/20.
//
#include "gameoflife.h"
#define SELECTION_PERCENTUAGE 0.50
unsigned cellmap_width = 500;
unsigned cellmap_height = 500;

typedef struct s{
    CellMap *citizen;
    struct s *next;
}list;
//
typedef struct c{
    CellMap *citizen;
    int score;
    list *seen;
}citizen;


void fitness(CellMap *citizen);
citizen **create_population();

citizen **create_population(int size,int step){

    // create the starting population and initialize the boards
    int i,j;
    citizen **population;
    population = new citizen*[size]();
    for(i=0; i < size; i++){
        population[i]->citizen = new CellMap(cellmap_width,cellmap_height);
        population[i]->citizen->Init();
        population[i]->score = 0;
        for (j=0; j < step; j++)
            population[i]->citizen->NextGen();
    }
    return population;
}

void fitness(citizen *citizen){

    pattern(citizen);
    life_trend(citizen);
}

void get_score(citizen **population, int size){

    int i;
    for(i=0; i < size; i++) {
        fitness(population[i]->citizen);
    }
    order(population);
}

void selection(citizen  **population, int size){

    citizen *parent1,*parent2;
    int i = 0;
    int retain_size = size * SELECTION_PERCENTUAGE;

    while(i < retain_size){
        parent1 = population[i];
        parent2 = population[i+1];
        population[retain_size-i-1] = crossover(parent1,parent2);
        ++i;
    }
}


