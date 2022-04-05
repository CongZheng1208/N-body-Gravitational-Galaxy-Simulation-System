/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef nbsimParticleGenerator_h
#define nbsimParticleGenerator_h

#include "nbsimMassiveParticle.h"

#include <iostream>
#include <string.h>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

/**
* \file nbsimParticleGenerator.h
* \brief Various Utilities.
* \ingroup utilities
*/

namespace nbsim{

    class Generator{

        public:
            Generator( );
            Generator(int numberOfParticle);
            ~Generator();
            MassiveParticle* generateParticleCluster(MassiveParticle particleCluster[]);
            
        private:
            int _numberOfParticle;
    };

    class SolarSystemGenerator:public Generator{

        public:
            SolarSystemGenerator( );
            SolarSystemGenerator(int numberOfParticle);
            ~SolarSystemGenerator();
            MassiveParticle* generateParticleCluster(MassiveParticle particleCluster[]);
            
        private:
            int _numberOfParticle;
    };

    class RandomParticleClusterGenerator:public Generator{

        public:
            RandomParticleClusterGenerator( );
            RandomParticleClusterGenerator(int numberOfParticle);
            ~RandomParticleClusterGenerator();
            MassiveParticle* generateParticleCluster(MassiveParticle particleCluster[]);
            
        private:
            int _numberOfParticle;
    };
}

#endif