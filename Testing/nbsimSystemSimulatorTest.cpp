/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/
#include "catch.hpp"
#include "nbsimParticle.h"
#include "nbsimMassiveParticle.h"
#include <math.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

TEST_CASE("particle class without acceleration","[Particle]"){
    Eigen::Vector3d pos0(0,0,0),pos1(1,4,7),pos2(3,-1,4.5);
    Eigen::Vector3d vel0(1.5,1,2.5),vel1(0,-1,0),vel2(2,0,-3.5);
    Eigen::Vector3d acc0(0,0,0),acc1(0,0,0),acc2(0,0,0);
    
    Eigen::Vector3d posRes0,posRes1,posRes2;
    Eigen::Vector3d velRes0,velRes1,velRes2;
    Eigen::Vector3d posExpected0(7.5,5,12.5),posExpected1(1,-6,7),posExpected2(5,-1,1);
    Eigen::Vector3d velExpected0(1.5,1,2.5),velExpected1(0,-1,0),velExpected2(2,0,-3.5);

    nbsim::Particle particle0(pos0,vel0);
    nbsim::Particle particle1(pos1,vel1);
    nbsim::Particle particle2(pos2,vel2);
    particle0.integrateTimestep(acc0,5);
    particle1.integrateTimestep(acc1,10);
    particle2.integrateTimestep(acc2,1);
    
    posRes0 = particle0.getPosition();  
    posRes1 = particle1.getPosition(); 
    posRes2 = particle2.getPosition(); 
    velRes0 = particle0.getVelocity();  
    velRes1 = particle1.getVelocity(); 
    velRes2 = particle2.getVelocity(); 

    REQUIRE(posRes0.isApprox(posExpected0,0.001));
    REQUIRE(velRes0.isApprox(velExpected0,0.001));
    REQUIRE(posRes1.isApprox(posExpected1,0.001));
    REQUIRE(velRes1.isApprox(velExpected1,0.001));
    REQUIRE(posRes2.isApprox(posExpected2,0.001));
    REQUIRE(velRes2.isApprox(velExpected2,0.001));
}

TEST_CASE("particle class with const acceleration","[Particle]"){
    Eigen::Vector3d pos0(0,0,0),pos1(1,4,7),pos2(3,-1,4.5);
    Eigen::Vector3d vel0(1.5,1,2.5),vel1(0,-1,0),vel2(2,0,-3.5);
    Eigen::Vector3d acc0(-1,1,0),acc1(3,4,7),acc2(0,2.5,0);
    
    Eigen::Vector3d posRes0,posRes1,posRes2;
    Eigen::Vector3d velRes0,velRes1,velRes2;
    Eigen::Vector3d posExpected0(7.5,5,12.5),posExpected1(1,-6,7),posExpected2(5,-1,1);
    Eigen::Vector3d velExpected0(-3.5,6,2.5),velExpected1(30,39,70),velExpected2(2,2.5,-3.5);

    nbsim::Particle particle0(pos0,vel0);
    nbsim::Particle particle1(pos1,vel1);
    nbsim::Particle particle2(pos2,vel2);
    particle0.integrateTimestep(acc0,5);
    particle1.integrateTimestep(acc1,10);
    particle2.integrateTimestep(acc2,1);
    
    posRes0 = particle0.getPosition();  
    posRes1 = particle1.getPosition(); 
    posRes2 = particle2.getPosition(); 
    velRes0 = particle0.getVelocity();  
    velRes1 = particle1.getVelocity(); 
    velRes2 = particle2.getVelocity(); 

    REQUIRE(posRes0.isApprox(posExpected0,0.001));
    REQUIRE(velRes0.isApprox(velExpected0,0.001));
    REQUIRE(posRes1.isApprox(posExpected1,0.001));
    REQUIRE(velRes1.isApprox(velExpected1,0.001));
    REQUIRE(posRes2.isApprox(posExpected2,0.001));
    REQUIRE(velRes2.isApprox(velExpected2,0.001));
}


TEST_CASE("particle class with centripetal acceleration","[Particle]"){
    Eigen::Vector3d pos(1,0,0);
    Eigen::Vector3d vel(0,1,0);
    
    Eigen::Vector3d posRes;
    Eigen::Vector3d posExpected(1,0,0);

    double pi = 3.14159265359;
    double timestep = 10000;

    nbsim::Particle particle1(pos,vel);

    for (int i = 1 ;i<=20000;i++){
        posRes = particle1.getPosition();
        particle1.integrateTimestep(-posRes,pi/timestep);
    }
    posRes = particle1.getPosition();    
    REQUIRE(posRes.isApprox(posExpected,0.001)==1);
}


TEST_CASE("massive particle class without acceleration","[MassiveParticle]"){
    Eigen::Vector3d pos0(0,0,0),pos1(3,4,5),pos2(-1,0,-1);
    Eigen::Vector3d vel0(1,0.5,2),vel1(-2,-3,5),vel2(0,0.5,-1);

    double mu[3] ={1,1,1};
    double stepsize = 1e-7;
    
    Eigen::Vector3d posRes0,posRes1,posRes2;
    Eigen::Vector3d velRes0,velRes1,velRes2;
    Eigen::Vector3d posExpected0(0.1,0.05,0.2),posExpected1(2.8,3.7,5.5),posExpected2(-1,0.05,-1.1);
    Eigen::Vector3d velExpected0(1,0.5,2),velExpected1(-2,-3,5),velExpected2(0,0.5,-1);

    nbsim::MassiveParticle massiveParticle0(pos0,vel0,mu[0]);
    nbsim::MassiveParticle massiveParticle1(pos1,vel1,mu[1]);
    nbsim::MassiveParticle massiveParticle2(pos2,vel2,mu[2]);

    massiveParticle0.calculateAcceleration(1);
    massiveParticle1.calculateAcceleration(1);
    massiveParticle2.calculateAcceleration(1);

    for (int i=0;i<1e6;i++){
        massiveParticle0.integrateTimestep(stepsize);
        massiveParticle1.integrateTimestep(stepsize);
        massiveParticle2.integrateTimestep(stepsize);
    }
    
    posRes0 = massiveParticle0.getPosition();  
    posRes1 = massiveParticle1.getPosition(); 
    posRes2 = massiveParticle2.getPosition(); 
    velRes0 = massiveParticle0.getVelocity();  
    velRes1 = massiveParticle1.getVelocity(); 
    velRes2 = massiveParticle2.getVelocity(); 

    REQUIRE(posRes0.isApprox(posExpected0,0.001));
    REQUIRE(velRes0.isApprox(velExpected0,0.001));
    REQUIRE(posRes1.isApprox(posExpected1,0.001));
    REQUIRE(velRes1.isApprox(velExpected1,0.001));
    REQUIRE(posRes2.isApprox(posExpected2,0.001));
    REQUIRE(velRes2.isApprox(velExpected2,0.001));
}

TEST_CASE("massive particle class with acceleration due to mutual attraction","[MassiveParticle]"){
    Eigen::Vector3d pos0(1,0,0);
    Eigen::Vector3d vel0(0,0.5,0);

    Eigen::Vector3d pos1(-1,0,0);
    Eigen::Vector3d vel1(0,-0.5,0);

    Eigen::Vector3d posRes0;
    Eigen::Vector3d velRes0;
    Eigen::Vector3d accelerationRes0;

    Eigen::Vector3d posRes1;
    Eigen::Vector3d velRes1;
    Eigen::Vector3d accelerationRes1;

    double pi = 3.14159265359;
    double timesteps = 1e4;
    double stepsize = 1e-4;
    double mu[2] = {1, 1};

    nbsim::MassiveParticle massiveParticle0(pos0,vel0,mu[0]);
    nbsim::MassiveParticle massiveParticle1(pos1,vel1,mu[1]);

    massiveParticle0.addAttractor(massiveParticle1);
    massiveParticle1.addAttractor(massiveParticle0);

    for (int i=0;i<timesteps;i++){
        massiveParticle0.calculateAcceleration(1);
        massiveParticle1.calculateAcceleration(1);
        massiveParticle0.integrateTimestep(stepsize);
        massiveParticle1.integrateTimestep(stepsize);
    }
    posRes0 = massiveParticle0.getPosition();
    velRes0 = massiveParticle0.getVelocity();
    
    posRes1 = massiveParticle1.getPosition();
    velRes1 = massiveParticle1.getVelocity();
    double distance = sqrt((posRes0 - posRes1).dot(posRes0 - posRes1));

    REQUIRE(distance - 2.0 <= 1e-2);    
}



