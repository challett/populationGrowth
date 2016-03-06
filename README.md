# populationGrowth

Simulates population growth and evolution through generations to best fit their enviroment using images.

Compile with:
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

Run with:
```
  ./genimg inputppmfile.ppm outputppmfile.ppm num_generations population_size
  ./genimg_omp num_threads inputppmfile.ppm outputppmfile.ppm num_generations population_size
  ./genimg_acc inputppmfile.ppm outputppmfile.ppm num_generations population_size
```

Example of output: https://www.youtube.com/watch?v=nAOQSPdggbQ
