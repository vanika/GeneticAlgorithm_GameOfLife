# GeneticAlgorithm_GameOfLife
**Genetic Algorithm to search selected pattern in the Conway's Game of Life**

The aim of this project is to apply a [genetic algorithm](https://en.wikipedia.org/wiki/Genetic_algorithm) to the a popular Cellular Automata, [Conway's Game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) and find starting configuration that produce selected behaviors.
Using the suggested genetic algorithm is also possible to go back in time: starting from a final configuration of the game, the GA try to predict a possible starting configuration.


# Goals

The genetic algorithm is used to select configurations that produce this behaviors:

* *Oscillation: board configuration repeate themselves in a periodic cycle*

* *Live cells stay alive after applying the rules of the game*

* *Dead cells come back to life after applying the rules of the game*

* *Patterns in the board remains equal during the game*


# Fitness function and evolutionary strategy

The fitness function is a crucial part of a genetic algoritm.Here it will rewards configurations based on the meeting on the aforementioned goals.

I've found that in research, there are a lot of techniques to optimize GA. The one I decided to use are summarize in the table below:



| Parameter | Value |
| - | ------ |
| Random Immigrants | Introduce a new configuration in the population|
| Elitism | Make only the fittests survive  |
| Mutation | Flip the state of random cells |
| Crossing-Over | 50% cross beetween two population's members|
| Gene | single cell |
| Triggered Hypermutation |  *---to be completed---* |







