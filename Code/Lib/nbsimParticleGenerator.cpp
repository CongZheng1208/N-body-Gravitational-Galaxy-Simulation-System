/*==================================================== ===============================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

===================================================== ==============================*/


#include "nbsimParticleGenerator.h"
#include "nbsimSolarSystemData.ipp"

#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

namespace nbsim
{
    Generator::Generator( ){

    };
    Generator::Generator(int numberOfParticle){
        _numberOfParticle = numberOfParticle;
    };
    Generator::~Generator(){

    };
    MassiveParticle* Generator::generateParticleCluster(MassiveParticle particleCluster[]){
        return particleCluster;
    };

    SolarSystemGenerator::SolarSystemGenerator( ){

    };
    SolarSystemGenerator::SolarSystemGenerator(int numberOfParticle){
        _numberOfParticle = numberOfParticle;
    };
    SolarSystemGenerator::~SolarSystemGenerator(){

    };
    MassiveParticle* SolarSystemGenerator::generateParticleCluster(MassiveParticle particleCluster[]){
        //Based on the data in nbsimSolarSystemData.ipp, initialize each celestial body in the solar system
        for (int i=0;i<_numberOfParticle;i++){
            particleCluster[i] = MassiveParticle(solarSystemData.at(i).position,solarSystemData.at(i).velocity,solarSystemData.at(i).mu);
        }
        //For each celestial body, add all other celestial bodies to its Attractor list
        for (int i=0;i<_numberOfParticle;i++){
            for (int j=0;j<_numberOfParticle;j++){
                if (j != i){
                    particleCluster[i].addAttractor(particleCluster[j]);
                }else{
                    continue;
                }
            }
        }
        return particleCluster;
    };

    RandomParticleClusterGenerator::RandomParticleClusterGenerator( ){

    };
    RandomParticleClusterGenerator::RandomParticleClusterGenerator(int numberOfParticle){
        _numberOfParticle = numberOfParticle;
    };
    RandomParticleClusterGenerator::~RandomParticleClusterGenerator(){

    };
    MassiveParticle* RandomParticleClusterGenerator::generateParticleCluster(MassiveParticle particleCluster[]){
        /**
        * Based on the given initial random particle cluster and its size, this function is used to generate numberOfParticles random particles and fill the random particle cluster
        */
        
        //set randomization seed
        std::srand((unsigned)time(NULL));
        // Set the maximum and minimum values ​​of random radius and random Theta
        double minimumRadius = 0.0;
        double maximumRadius = 40.0;
        double minimumTheta = 0.0;
        double maximumTheta = 6.28;
        //Generate the central particle of the random particle cluster, the particle has no initial velocity, is located at the origin, and has a large mass
        particleCluster[0] = MassiveParticle(Eigen::Vector3d(0.0,0.0,0.0),Eigen::Vector3d(0.0,0.0,0.0),40.0);
        //Generate numberOfParticles random particles and use them to populate the random particle cluster
        for (int i=1;i<_numberOfParticle;i++){
            double radius = minimumRadius + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(maximumRadius-minimumRadius)));
            double theta = minimumTheta + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(maximumTheta-minimumTheta)));
            particleCluster[i] = MassiveParticle(Eigen::Vector3d(radius*sin(theta),radius*cos(theta),0.0),Eigen::Vector3d(-cos(theta)/sqrt(radius),sin(theta)/ sqrt(radius),0.0),1e-4);
        }
        return particleCluster;
    };
}