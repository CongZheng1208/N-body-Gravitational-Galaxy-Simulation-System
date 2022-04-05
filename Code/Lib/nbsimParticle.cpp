/*==================================================== ===============================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

===================================================== ==============================*/

#include "nbsimParticle.h"
#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

namespace nbsim
{
    Particle::Particle( ) {
        
    };
    Particle::Particle( Eigen::Vector3d position, Eigen::Vector3d velocity){
        /**
        * Based on the given initial Position vector and Velocity vector, this function is used to initialize the Particle
        */
        _position = position;
        _velocity = velocity;
    };
    Particle::~Particle(){

    };
    Eigen::Vector3d Particle::getPosition() const{
        /**
        * This function is used to obtain the Position vector corresponding to the Particle
        */
        return _position;
    };
    Eigen::Vector3d Particle::getVelocity() const{
        /**
        * This function is used to obtain the Velocity vector corresponding to the Particle
        */
        return _velocity;
    };
    void Particle::integrateTimestep(const Eigen::Vector3d acceleration, const double timestep){
        /**
        * Based on the given acceleration vector and time step, this function is used to calculate the updated Position and Velocity vectors of the Particle
        */
        _position = _position + timestep*_velocity;
        _velocity = _velocity + timestep*acceleration;
    };   
}