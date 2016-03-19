# populationGrowth

Simulates population growth and evolution through generations to best fit their enviroment using images.

## How does it work?

The program begins by generating an image of random pixels for each member of the population.  The 'fitness' of each population member to the input image is calculated and the bottom half of the popluation based on fitness is discarded.  Of the top half, members are "bred" with each other to create an image that is between both parents.  Finally, the new images are randomly mutated and the fitness is recalculated.  This process is repeated over the input number of generations

Example of output: https://www.youtube.com/watch?v=nAOQSPdggbQ
---

## How to Compile
```
  All versions:
    $ make
  Omp version:
    $ make omp
  openACC version
    $ make acc
  sequential version
    $ make single
```

---

## How to Run
```
  ./genimg inputppmfile.ppm outputppmfile.ppm num_generations population_size
  ./genimg_omp num_threads inputppmfile.ppm outputppmfile.ppm num_generations population_size
  ./genimg_acc inputppmfile.ppm outputppmfile.ppm num_generations population_size
```

To create intermediate images, add -DVIDEO flag to makefile
