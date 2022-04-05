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
            std::cout<<"Hello user! Welcome to the SolarSystemSimulator application.\n"
                     <<"This program simulates the motion of a star and eight planets in the solar system started on the epoch of 2021-01-0T00:00:00Z  based on the parameters you enter.\n"
                     <<"You can control the total number of time steps and time steps for simulating galaxy motion by entering parameters on the command line. E.g:\n"
                     <<"./bin/solarSystemSimulator 3650 0.000274\n"
                     <<"This means that the solar system will take 0.000274 years (about 0.1 days) as a step and iterate 3650 times to simulate the motion of each celestial body in the solar system for one year.\n";
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
            
            //Use the SolarSystemGenerator class to initialize the solar system to generate a particle cluster solarSystem
            numberOfParticles = 9;
            std::string nameOfParticles[9] = {{"Sun"},{"Mercury"},{"Venus"},{"Earth"},{"Mars"},{"Jupiter"},{"Saturn" },{"Uranus"},{"Neptune"}};
            nbsim::MassiveParticle emptySolarSystem[numberOfParticles];
            nbsim::SolarSystemGenerator solarSystemGenerator(numberOfParticles);
            nbsim::MassiveParticle* solarSystem = solarSystemGenerator.generateParticleCluster(emptySolarSystem);

            //Before the simulation calculation, calculate the static energy and dynamic energy of all celestial bodies in the solar system
            eKinetic = nbsim::CalculateKineticEnergy(solarSystem,numberOfParticles);
            ePotential = nbsim::CalculatePotentialEnergy(solarSystem,numberOfParticles);
            
            // Before the simulation calculation, output the total energy of all celestial bodies in the solar system.
            std::cout << "Before the simulation starts, " << std::endl;
            std::cout << "The kinetic energy of the system objects is " << eKinetic << std::endl;
            std::cout << "The potential energy of the system objects is " << ePotential << std::endl;
            std::cout << "The total energy of the solar system objects is " << (eKinetic + ePotential) << std::endl;
            
            //Before the simulation calculation, output the position information of all celestial bodies in the solar system.
            std::cout << "Below are the initial positions of the solar system bodies before the simulation started.\n" << std::endl;
            for (int i=0;i<numberOfParticles;i++){
                Eigen::Vector3d posres0 = solarSystem[i].getPosition();
                std::cout << "The initial position of "<< nameOfParticles[i] <<" is at:\n" << posres0 << std::endl;
                std::cout << " " << std::endl;
            }
            std::cout << "<------------------------------------------------------ > " << std::endl;

            //Based on timeStepSize and timeSteps information, simulate the motion of each celestial body in the solar system.
            std::clock_t c_start = std::clock();
            auto t_start = std::chrono::high_resolution_clock::now();
            for (int i=0;i<timeSteps;i++){
                for (int i=0;i<numberOfParticles;i++){
                    solarSystem[i].calculateAcceleration(1);
                }
                for (int i=0;i<numberOfParticles;i++){
                    solarSystem[i].integrateTimestep(timeStepSize);
                }
            }
            std::clock_t c_end = std::clock();
            auto t_end = std::chrono::high_resolution_clock::now();

            //After the simulation calculation, calculate the total energy of all celestial bodies in the solar system.
            eKinetic = nbsim::CalculateKineticEnergy(solarSystem,numberOfParticles);
            ePotential = nbsim::CalculatePotentialEnergy(solarSystem,numberOfParticles);
            
            //After the simulation calculation, output the total energy of all celestial bodies in the solar system.
            std::cout << "After the simulation ends," << std::endl;
            std::cout << "The kinetic energy of the system objects is " << eKinetic << std::endl;
            std::cout << "The potential energy of the system objects is " << ePotential << std::endl;
            std::cout << "The total energy of the solar system objects is " << (eKinetic + ePotential) << std::endl;

            //After the simulation calculation, output a summary of the position information of all celestial bodies in the solar system.
            std::cout << "After a simulation with a time step of " << timeStepSize <<" years and a simulation time of "<< timeStepSize*timeSteps <<" years, the following are the final positions of the celestial bodies in the solar system after the simulated motion.";    
            for (int i=0;i<numberOfParticles;i++){
                Eigen::Vector3d posres0 = solarSystem[i].getPosition();              
                std::cout << "The final position of "<< nameOfParticles[i] <<" is at:\n" << posres0 << std::endl;
                std::cout << " " << std::endl;
            }
        
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