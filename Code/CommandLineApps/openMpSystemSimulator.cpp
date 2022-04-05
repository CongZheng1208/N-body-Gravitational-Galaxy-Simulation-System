/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "nbsimParticle.h"
#include "nbsimMassiveParticle.h"
#include "nbsimParticleGenerator.h"

#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <ctime>
#include <iomanip> 
#include <chrono> 
#include <stdlib.h>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

/**
 * \brief Demo file to check that includes and library linkage is correct.
 */


int main(int argc, char** argv){

    //For the case where the number of input command line parameters is 0, no error will be reported, and a prompt message will be output
    if (argc < 2){
        //If the number of input parameters is 0
        std::cout<<"More information is provided by the instruction --help or -h\n";
        std::cout<<"\n"<<std::endl;
        return 1;
    }
    
    try{
        double timeSteps,timeStepSize;
        int numberOfParticles;

        if ((strcmp(argv[1], "--help")==0) || (strcmp(argv[1], "-h") == 0)) {
            //If the input parameter is -h or --help
            std::cout<<"Hello user! Welcome to the SystemSimulator application.\n"
                     <<"This program simulates the motion of 1 star and 1999 planets in the random particle system based on the parameters you enter.\n"
                     <<"You can control the total number of time steps and time steps for simulating galaxy motion by entering parameters on the command line. E.g:\n"
                     <<"./bin/solarSystemSimulator 3650 0.000274\n"
                     <<"This means that the system will take 0.000274 years (about 0.1 days) as a step and iterate 3650 times to simulate the motion of each celestial body in the system for one year.\n";
        }else if (argc == 3){
            double eKinetic, ePotential;

            //If the number of input parameters is 2
            timeSteps = std::atof(argv[1]);
            timeStepSize = std::atof(argv[2]);
            
            //Check the plausibility of the input parameter data
            if(timeSteps<=0 || timeStepSize<=0 ){
                std::cout<<"Should input integer > 0\n";
                throw std::runtime_error("value error of command line arguments");
            }
            
            //使用RandomParticleClusterGenerator类，进行初始化，以生成粒子集群fullSystem
            numberOfParticles = 2000;
            nbsim::MassiveParticle emptySystem[numberOfParticles];
            nbsim::RandomParticleClusterGenerator randomParticleClusterGenerator(numberOfParticles);
            nbsim::MassiveParticle* fullSystem = randomParticleClusterGenerator.generateParticleCluster(emptySystem);

            
            eKinetic = nbsim::CalculateKineticEnergyOpenMp(fullSystem,numberOfParticles);
            ePotential = nbsim::CalculatePotentialEnergyOpenMp(fullSystem,numberOfParticles);
            std::cout << "Before the simulation starts," << std::endl;
            std::cout << "The kinetic energy of the system objects is " << eKinetic << std::endl;
            std::cout << "The potential energy of the system objects is " << ePotential << std::endl;
            std::cout << "The total energy of the solar system objects is " << (eKinetic + ePotential) << std::endl;
            std::cout << "<------------------------------------------> " << std::endl;
            
            //在模拟计算之前，输出太阳系中所有天体的position信息。
        #if 0
            std::cout << "Below are the initial positions of the system bodies before the simulation started.\n" << std::endl;
            for (int i=0;i<numberOfParticles;i++){
                Eigen::Vector3d posres0 = fullSystem[i].getPosition();              
                std::cout << "The initial position of the "<< i <<"th particle is at:\n" << posres0 << std::endl;
                std::cout << " " << std::endl;
            }
        #endif

            //基于timeStepSize和timeSteps信息，对太阳系各个天体进行运动的模拟。
            std::clock_t c_start = std::clock();
            auto t_start = std::chrono::high_resolution_clock::now();
            for (int j=0;j<timeSteps;j++){
                               
                #pragma omp parallel 
                {    
                    int tid = omp_get_thread_num();
                    int nthreads = omp_get_num_threads();
                    int h = numberOfParticles / nthreads;                     
                    for (int i=tid*h;i<(tid+1)*h;i++){
                        fullSystem[i].calculateAcceleration(1);
                    }
                }

                #pragma omp parallel 
                {   
                    int tid = omp_get_thread_num();
                    int nthreads = omp_get_num_threads();
                    int h = numberOfParticles / nthreads; 
                    for (int i=tid*h;i<(tid+1)*h;i++){
                        fullSystem[i].integrateTimestep(timeStepSize);
                    }
                }

                /*
                for (int i=0;i<timeSteps;i++){
                    fullSystem[i].calculateAcceleration(nthreads);
                }

                //#pragma omp parallel for num_threads(nthreads)
                for (int i=0;i<timeSteps;i++){
                    fullSystem[i].integrateTimestep(timeStepSize);
                }*/
            }
            std::clock_t c_end = std::clock();
            auto t_end = std::chrono::high_resolution_clock::now();

            //在模拟计算之后，计算并输出所有天体的energy信息总结。   
                   
            eKinetic = nbsim::CalculateKineticEnergyOpenMp(fullSystem,numberOfParticles);
            ePotential = nbsim::CalculatePotentialEnergyOpenMp(fullSystem,numberOfParticles);

            std::cout << "After the simulation ends," << std::endl;
            std::cout << "The kinetic energy of the system objects is " << eKinetic << std::endl;
            std::cout << "The potential energy of the system objects is " << ePotential << std::endl;
            std::cout << "The total energy of the solar system objects is " << (eKinetic + ePotential) << std::endl;

            //在模拟计算之后，输出所有天体的position信息总结。
        #if 0    
            std::cout << "After a simulation with a time step of " << timeStepSize <<" years and a simulation time of "<< timeStepSize*timeSteps <<" years, the following are the final positions of the celestial bodies in the solar system after the simulated motion.";    
            for (int i=0;i<numberOfParticles;i++){
               Eigen::Vector3d posres0 = fullSystem[i].getPosition();              
                std::cout << "The final position of the "<< i <<"th particle is at:\n" << posres0 << std::endl;
                std::cout << " " << std::endl;
            }
        #endif

            std::cout << std::fixed << "CPU time used: "
                    << (double)(c_end - c_start) / CLOCKS_PER_SEC << " s\n"
                    << "Wall clock time passed: "
                    << std::chrono::duration<double, std::milli>((t_end-t_start)/1000).count()
                    << " s\n";
         
        }else{
            std::cout<<"More information is provided by the instruction --help or -h\n";
            std::cout<<"\n"<<std::endl;
            throw std::runtime_error("Command line arguments error");
        }
    }catch(std::exception& error){
        std::cerr << "Caught Exception: " << error.what() << std::endl;
        throw;
    }    
    return 0;
}