/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef nbsimParticle_h
#define nbsimParticle_h

#include <iostream>
#include <string.h>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

/**
* \file nbsimParticle.h
* \brief Various Utilities.
* \ingroup utilities
*/

namespace nbsim{

    class Particle{

    public:
        Particle( );
        Particle( Eigen::Vector3d position, Eigen::Vector3d velocity);
        ~Particle();
        Eigen::Vector3d getPosition() const;
        Eigen::Vector3d getVelocity() const;
        void integrateTimestep(const Eigen::Vector3d acceleration, const double timestep);

    private:
        Eigen::Vector3d _position;
        Eigen::Vector3d _velocity;
    };
}

#endif