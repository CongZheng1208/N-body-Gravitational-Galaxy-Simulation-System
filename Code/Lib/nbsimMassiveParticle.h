/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef nbsimMassiveParticle_h
#define nbsimMassiveParticle_h

#include "nbsimParticle.h"

#include <iostream>
#include <string.h>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>


namespace nbsim{

    class MassiveParticle:public Particle{

    public:
        MassiveParticle( );
        MassiveParticle( Eigen::Vector3d position, Eigen::Vector3d velocity, double mu);
        ~MassiveParticle();
        Eigen::Vector3d getPosition();
        Eigen::Vector3d getVelocity();
        Eigen::Vector3d getAcceleration();
        double getMu();
        std::vector<Eigen::Vector3d> getAttractorPositions();
        std::vector<double> getAttractorMus();
        void addAttractor(MassiveParticle massiveParticle);
        void removeAttractor(MassiveParticle massiveParticle);
        void calculateAcceleration(int nthreads);
        void integrateTimestep(double timestep);

    private:
        Eigen::Vector3d _position;
        Eigen::Vector3d _velocity;
        Eigen::Vector3d _acceleration;
        double _mu;
        std::vector<Eigen::Vector3d> _attractor_position;
        std::vector<double> _attractor_mu;
    };

    double CalculateKineticEnergy(MassiveParticle solarSystem[], int numberOfParticles);
    double CalculatePotentialEnergy(MassiveParticle solarSystem[], int numberOfParticles);
    double CalculateKineticEnergyOpenMp(MassiveParticle solarSystem[], int numberOfParticles);
    double CalculatePotentialEnergyOpenMp(MassiveParticle solarSystem[], int numberOfParticles);

}

#endif