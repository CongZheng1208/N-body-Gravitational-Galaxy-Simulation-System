PHAS0100Assignment2
------------------

[![Build Status](https://travis-ci.com/[USERNAME]/PHAS0100Assignment2.svg?branch=master)](https://travis-ci.com/[USERNAME]/PHAS0100Assignment2)
[![Build Status](https://ci.appveyor.com/api/projects/status/[APPVEYOR_ID]/branch/master)](https://ci.appveyor.com/project/[USERNAME]/PHAS0100Assignment2)


Purpose
-------

This project serves as a starting point for the PHAS0100 Assignment 2 Gravitational N-body Simulation coursework. It has a reasonable folder structure for [CMake](https://cmake.org/) based projects,
that use [CTest](https://cmake.org/) to run unit tests via [Catch](https://github.com/catchorg/Catch2). 

Further information on the specific project is left as an exercise for the student.


Credits
-------

This project is maintained by [Dr. Jim Dobson](https://www.ucl.ac.uk/physics-astronomy/people/dr-jim-dobson). It is based on [CMakeCatch2](https://github.com/UCL/CMakeCatch2.git) that was originally developed as a teaching aid for UCL's ["Research Computing with C++"](http://rits.github-pages.ucl.ac.uk/research-computing-with-cpp/)
course developed by [Dr. James Hetherington](http://www.ucl.ac.uk/research-it-services/people/james)
and [Dr. Matt Clarkson](https://iris.ucl.ac.uk/iris/browse/profile?upi=MJCLA42).


Build Instructions
------------------

**Contents**<br>

[Introduction](#introduction)<br>
[How to build](#how_to_build)<br>
[How to use solarSystemSimulator](#how_to_use_solarSystemSimulator)<br>
[How to use openMpSystemSimulator](#how_to_use_openMpSystemSimulator)<br>
[How to run tests](#how_to_run_tests)<br>
[Energy comparison based on solarSystemSimulator](#Energy_comparison_based_on_solarSystemSimulator)<br>
[Benchmark results based on solarSystemSimulator](#Benchmark_results_based_on_solarSystemSimulator)<br>
[Benchmark results based on openMpSystemSimulator](#Benchmark_results_based_on_openMpSystemSimulator)<br>


## Introduction

Welcome to N-body gravity simulation built in C++.

* This project realizes the simulation of particle motion in the presence of N-body gravitation, and extends it to the motion of various celestial bodies. In this project, we designed the command line program `solarSystemSimulator`. Furthermore, we designed the command line program `openMpSystemSimulator`. Based on the above design, we also conduct benchmarking and accuracy verification.

* Specifically, first of all, we designed the Particle class and MassiveParticle class to simulate the motion principle of particles. After that, in order to generate particle clusters of different modes, we also designed `Generator` class, `SolarSystemGenerator` class and `RandomParticleClusterGenerator` class to generate different kinds of particle clusters. After that, we developed the command-line program `solarSystemSimulator` to simulate the motion of various celestial bodies in the solar system. After that, we developed the command-line program `openMpSystemSimulator` to implement N-body motion simulation of random particle clusters optimized by `OpenMp` parallelization.

* In addition, we provide a unit testing application `nbsimSystemSimulatorTest` based on [CTest](https://cmake.org/) and [Catch](https://github.com/catchorg/Catch2) for unit testing the Particle class and the MassiveParticle class.


The last three chapters will be used to present the benchmark results and accuracy test results of the program.

## How to build

First, go to the root directory of the file with the help of the IDE's terminal.

````Bash
mkdir build
cd build
````
The project is compiled based on Cmake. Therefore, if you are using it for the first time, simply enter the following command line in the newly created build directory.
````Bash
cmake..
make
````
Normally the program takes close to a minute to compile. When the compilation is complete, you will see the following output.

````
Scanning dependencies of target phas0100assignment2
[ 7%] Building CXX object Code/Lib/CMakeFiles/phas0100assignment2.dir/nbsimParticle.cpp.o
[ 14%] Building CXX object Code/Lib/CMakeFiles/phas0100assignment2.dir/nbsimMassiveParticle.cpp.o
[ 21%] Building CXX object Code/Lib/CMakeFiles/phas0100assignment2.dir/nbsimParticleGenerator.cpp.o
[ 28%] Linking CXX static library ../../bin/libphas0100assignment2.a
[ 50%] Built target phas0100assignment2
[ 57%] Linking CXX executable ../../bin/openMpSystemSimulator
[ 64%] Built target openMpSystemSimulator
[ 71%] Linking CXX executable ../../bin/solarSystemSimulator
[ 78%] Built target solarSystemSimulator
[ 85%] Linking CXX executable ../bin/nbsimSystemSimulatorTest
[100%] Built target nbsimSystemSimulatorTest
````

## How to use solarSystemSimulator


After compiling, follow the rules below to use the command line application `solarSystemSimulator`.

The command line application `solarSystemSimulator` provides us with a way to simulate the motion of various celestial bodies in the solar system before and after the specified motion time. The data of each celestial body at the beginning comes from the solar system started on the epoch of 2021-01-0T00:00:00Z. You can enter parameters to control the timing and step size of its motion, and observe the energy, position results, and elapsed time of the solar system before and after the simulated motion.

The input command has two parameters, which are the number of iterations and the iteration step size. Example.

````Bash
./bin/solarSystemSimulator 3650 0.000274
````
Among them, the input of `3650` and `0.000274` means that you want the solar system to perform `3650` iterations of simulation calculations with an iterative step size of `0.000274` years (about `0.1` days), that is, to simulate the solar system after about ` 1.0001` year movement.

Normally, you would see output like this!

```
Before the simulation starts, 
The kinetic energy of the system objects is 0.187358
The potential energy of the system objects is -0.356872
The total energy of the solar system objects is -0.169514
Below are the initial positions of the solar system bodies before the simulation started.

The initial position of Sun is at:
-0.00670894
  0.0060565
 0.00010651
 
The initial position of Mercury is at:
  0.230275
 -0.351957
-0.0508834
 
The initial position of Venus is at:
-0.453178
-0.563815
0.0180571
 
The initial position of Earth is at:
  -0.185741
   0.972886
4.83111e-05
 
The initial position of Mars is at:
 0.614263
  1.38167
0.0136846
 
The initial position of Jupiter is at:
   3.0346
 -4.08225
-0.050909
 
The initial position of Saturn is at:
    5.4834
  -8.33624
-0.0732546
 
The initial position of Uranus is at:
  15.3436
  12.4673
-0.152634
 
The initial position of Neptune is at:
  29.4537
 -5.22631
-0.571104
 
<------------------------------------------------------ > 
After the simulation ends,
The kinetic energy of the system objects is 0.222977
The potential energy of the system objects is -0.392047
The total energy of the solar system objects is -0.169071
After a simulation with a time step of 0.000274 years and a simulation time of 1.0001 years, the following are the final positions of the celestial bodies in the solar system after the simulated motion.The final position of Sun is at:
-0.00850808
 0.00286806
0.000173415
 
The final position of Mercury is at:
 -0.133503
  -1.03322
-0.0742189
 
The final position of Venus is at:
  0.171486
  0.753935
7.4371e-05
 
The final position of Earth is at:
-0.0882755
   1.00545
4.6332e-05
 
The final position of Mars is at:
 -2.52465
  1.26141
0.0881059
 
The final position of Jupiter is at:
   4.32898
  -1.39267
-0.0910706
 
The final position of Saturn is at:
  6.83314
 -6.88108
-0.152436
 
The final position of Uranus is at:
  14.2433
  13.3617
-0.135071
 
The final position of Neptune is at:
  29.5955
 -4.08302
-0.597839
 
CPU time used: 3.898518 s
Wall clock time passed: 3.898581 s
```
Among them, before starting the simulation, the kinetic energy of the system is `0.187358`, the potential energy is `-0.356872`, the total energy of the solar system objects is `-0.169514`. After the simulated motion, their values ​​are `0.222977`, `-0.392047`, `-0.169071`, which basically follow the conservation of energy. In addition, the initial position of each celestial body is also printed, for example, before the motion simulation starts, the initial position of the earth is `(-0.185741 0.972886 4.83111e-05)`, and after about 1 year of simulated motion, its position It is `(-0.0882755 1.00545 4.6332e-05)`, which remains basically unchanged, which means that the planet has completed one revolution in a year and roughly returned to its previous position.


In addition, you can also enter the `-h` or `--help` identifier to see more help information.

````Bash
./bin/solarSystemSimulator -h
````
````Bash
./bin/solarSystemSimulator --help
````


## How to use openMpSystemSimulator

Similarly, we provide the command line application openMpSystemSimulator for simulating `2000` random particles


After compiling, follow the rules below to use the command line application `solarSystemSimulator`.

The command line application `solarSystemSimulator` provides us with a way to simulate the motion of various celestial bodies in the solar system before and after the specified motion time. You can enter parameters to control the time and step size of its motion, and observe the energy and position results of the solar system before and after the simulated motion.

The input command has two parameters, which are the number of iterations and the iteration step size. Example.

````Bash
./bin/openMpSystemSimulator 3650 0.000274
````
Among them, the input of `3650` and `0.000274` means that you want the cluster to perform `3650` iterative simulation calculations with an iterative step size of `0.000274` years (about `0.1` days), that is, to simulate the cluster after Movement for about `1.0001` years.

Normally, you would see output like this!

````
Before the simulation starts,
The kinetic energy of the system objects is 0.0186525
The potential energy of the system objects is -1.51196
The total energy of the solar system objects is -1.49331
<------------------------------------------>
After the simulation ends,
The kinetic energy of the system objects is 0.0186525
The potential energy of the system objects is -1.51196
The total energy of the solar system objects is -1.49331
CPU time used: 55.242669 s
Wall clock time passed: 55.246126 s
````

## How to run tests

In addition, we also provide the unit testing application `nbsimSystemSimulatorTest` for unit testing the Particle class and MassiveParticle class.

You can use it with the following command!

````Bash
./bin/nbsimSystemSimulatorTest
````

## Energy comparison based on solarSystemSimulator

Before the simulation, we knew the initial energy of the solar system as shown in the table below.

| Kinetic Energy | Potential Energy | Total Energy |
| ---- | ---- | ---- |
|0.187358 | -0.356872 | -0.169514 |

In order to reflect the influence of the step size selection on the energy before and after the simulation of the motion of the solar system, we selected 10 different step sizes to simulate 100 years of time, and counted the kinetic energy, potential energy, and total energy of the solar system after the simulation, as shown in the following table Show.

| Iteration step size (year) | Number of iterations | Kinetic Energy | Potential Energy | Total Energy |
| ---- | ---- | ---- | ---- | ---- |
| 0.137 | 730 | 48.6749 | -0.0338147 | 48.6411 |
| 0.0548 | 1825 | 60.9605 | -0.0290884 | 60.9314 |
| 0.0274 | 3650 | 54.5068 | -0.030256 | 54.4766 |
| 0.0137 | 7300 | 47.8265 | -0.0347741 | 47.7917 |
| 0.00548 | 18250 | 38.5399 | -0.0408106 | 38.4991 |
| 0.00274 | 36500 | 30.0076 | -0.0542412 | 29.9534 |
| 0.00137 | 73000 | 21.0232 | -0.0646007 | 20.9586 |
| 0.000548 | 182500 | 11.2488 | -0.0900878 | 11.1587 |
| 0.000274 | 365000 | 6.36001 | -0.14031 | 6.2197 |
| 0.000137 | 730000 | 3.40302 | -0.207835 | 3.19518 |

As shown in the above table, with the gradual reduction of the iteration step size, the energy of the system gradually converges to the initial energy before the simulation. This means that the selection of the iterative step size controls the accuracy of the iterative simulation calculation. The smaller the step size, the higher the accuracy of the simulation.


## Benchmark results based on solarSystemSimulator

Similarly, we picked 10 different sets of step sizes for benchmarking the simulation run times. The statistical results are shown in the table below.

| Iteration step size (year) | Number of iterations | CPU Time(s) | Wall Clock Time(s) |
| ---- | ---- | ---- | ---- |
| 0.137 | 730 | 0.846748 | 0.857644 |
| 0.0548 | 1825 | 1.787472 | 1.787477 |
| 0.0274 | 3650 | 3.652815 | 3.652824 |
| 0.0137 | 7300 | 7.348401 | 7.348569 |
| 0.00548 | 18250 | 18.063838 | 18.064103 |
| 0.00274 | 36500 | 36.219869 | 36.243214 |
| 0.00137 | 73000 | 72.283587 | 72.286029 |
| 0.000548 | 182500 | 181.095563 | 181.102941 |
0.000274 | 365000 | 359.914779 | 359.925051 |
| 0.000137 | 730000 | 723.421311 | 723.448250 |

As shown in the table above, as the iteration step size is gradually reduced, the CPU time and Wall Clock Time spent are higher. This means that the smaller the step size, the longer the computation time required for the simulation.

Based on the above considerations, we choose a time step value of `0.000274` that provides a good balance between simulation runtime and accuracy.


## Benchmark results based on openMpSystemSimulator

Next, we used OpenMp for parallelized simulation optimization, and counted the benchmark results before and after optimization. Among them, we selected several groups of different iteration times and iteration steps, and recorded the CPU time and Wall Clock Time under different threads of the simulation calculation of `2000` random particle clusters based on this.

Below are the results of the CPU time.

| iteration step size (year) | number of iterations | not parallelized | number of threads = 1 | number of threads = 2 | number of threads = 4 |
| ---- | ---- | ---- | ---- | ---- | ---- |
0.0548 | 1825 | 27.413210 | 27.411340 | 31.352563 | 42.216389 |
0.0274 | 3650 | 55.034101 | 55.074900 | 62.164351 | 77.438851 |
| 0.0137 | 7300 | 108.30875 | 108.697718 | 124.125319 | 167.267532|
| 0.00548 | 18250 | 282.783029 | 282.784735 | 312.131313 |400.629887 |
| 0.00274 | 36500 | 551.715021 | 551.713688 | 623.113399 | 782.342311|

Below are the results for Wall Clock Time.

| iteration step size (year) | number of iterations | not parallelized | number of threads = 1 | number of threads = 2 | number of threads = 4 |
| ---- | ---- | ---- | ---- | ---- | ---- |
0.0548 | 1825 | 27.43822 | 27.411522 | 15.680104 | 10.560377 |
0.0274 | 3650 | 55.0319401 | 55.077507 | 31.085852 | 19.364649 |
| 0.0137 | 7300 | 108.70310 | 108.701400 | 62.065410 | 41.832294|
| 0.00548 | 18250 | 282.1484 | 282.799602 | 156.071492 |100.176392 |
| 0.00274 | 36500 | 551.387408 | 551.730181 | 311.568369 | 204.24124|

It is not difficult to see that the two usages show opposite results. When not parallelized and when the number of threads is 1, the two times are basically the same. When parallelization and multi-threading are enabled, the CPU time increases as the number of threads increases, while the Wall Clock Time decreases as the number of threads increases.
