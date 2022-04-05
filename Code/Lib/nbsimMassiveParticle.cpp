/*==================================================== ===============================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

===================================================== ==============================*/

#include "nbsimMassiveParticle.h"
#include <iostream>
#include <omp.h>

namespace nbsim{

    MassiveParticle::MassiveParticle( ){

    }
    MassiveParticle::MassiveParticle( Eigen::Vector3d position, Eigen::Vector3d velocity, double mu){
        /**
        * Based on the given initial Position vector, Velocity vector and mu value, this function is used to initialize the MassiveParticle
        */
        _position = position;
        _velocity = velocity;
        _acceleration = Eigen::Vector3d(0.0,0.0,0.0);
        _mu = mu;
    }
    MassiveParticle::~MassiveParticle(){

    }
    Eigen::Vector3d MassiveParticle::getPosition(){
        /**
        * This function is used to obtain the Position vector corresponding to the Particle
        */
        return _position;
    }
    Eigen::Vector3d MassiveParticle::getVelocity(){
        /**
        * This function is used to obtain the Velocity vector corresponding to the Particle
        */
        return _velocity;
    }
    Eigen::Vector3d MassiveParticle::getAcceleration(){
        /**
        * This function is used to obtain the Acceleration vector corresponding to the Particle
        */
        return _acceleration;
    }
    double MassiveParticle::getMu(){
        /**
        * This function is used to get the Mu value corresponding to the Particle
        */
        return _mu;
    }

    std::vector<Eigen::Vector3d> MassiveParticle::getAttractorPositions(){
        /**
        * This function is used to obtain the Position vector corresponding to all Attractors of the Particle
        */
        return _attractor_position;
    }

    std::vector<double> MassiveParticle::getAttractorMus(){
        /**
        * This function is used to get the Mu value corresponding to all Attractors of the Particle
        */
        return _attractor_mu;
    }


    void MassiveParticle::addAttractor(MassiveParticle massiveParticle){
        /**
        * This function is used to add an Attractor to the Particle, that is, to save the Position vector and Mu value corresponding to the given Attractor
        */
        _attractor_position.push_back(massiveParticle.getPosition());
        _attractor_mu.push_back(massiveParticle.getMu());
    }

    void MassiveParticle::removeAttractor(MassiveParticle massiveParticle){
        /**
        * This function is used to delete an Attractor for the Particle, that is, delete the Position vector and Mu value corresponding to the given Attractor
        */
        // Traverse the Attractor list in the Particle
        for (int i=0;i<_attractor_position.size();i++) {
            //If the requested Particle is found, delete it
            if (_attractor_position[i].isApprox(massiveParticle.getPosition()) && _attractor_mu[i]==massiveParticle.getMu()){
                _attractor_position.erase(_attractor_position.begin() + i);
                _attractor_mu.erase(_attractor_mu.begin() + i);
                break;
            }else{
                continue;
            }
        }
    }

    void MassiveParticle::calculateAcceleration(int nthreads){
        /**
        * Based on all Attractors of the Particle, this function is used to calculate the Acceleration vector of the Particle
        */
        //For each Attractor in the Attractor list
        /*
        int h = _attractor_position.size()/nthreads;
        Eigen::Vector3d partial_acceleration[nthreads];

        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            for (int i=tid*h;i<(tid+1)*h;i++) {
                Eigen::Vector3d r = _position-_attractor_position[i];
                partial_acceleration[tid] += -_attractor_mu[i]/(r.dot(r))*(r.normalized());
            }
        }
        for (int i = 0; i < nthreads; i++) {
            _acceleration += partial_acceleration[i];
        }*/
        _acceleration = Eigen::Vector3d(0.0,0.0,0.0);

        for (int i=0;i<_attractor_position.size();i++) {
            Eigen::Vector3d r = _position-_attractor_position[i];
            _acceleration += -_attractor_mu[i]/(r.dot(r))*(r.normalized());
        }
    }

    void MassiveParticle::integrateTimestep(double timestep){
        /**
        * Based on the given time step, this function is used to calculate the updated Position and Velocity vectors of the Particle
        */
        _position = _position + timestep*_velocity;
        _velocity = _velocity + timestep*_acceleration;
    }

    double CalculateKineticEnergy(MassiveParticle solarSystem[], int numberOfParticles){
        /**
        * Based on a given particle cluster and its size, this function is used to calculate the total energy corresponding to the cluster
        */
        double eKinetic;
        //For each celestial body, calculate its kinetic energy
        for (int i=0;i<numberOfParticles;i++){
            //Calculate the Kinetic energy of the celestial body and accumulate it
            eKinetic += solarSystem[i].getMu()*pow((sqrt(solarSystem[i].getVelocity().dot(solarSystem[i].getVelocity()))),2);
        }

        return 0.5*eKinetic;
    }

    double CalculatePotentialEnergy(MassiveParticle solarSystem[], int numberOfParticles){
        /**
        * Based on a given particle cluster and its size, this function is used to calculate the total energy corresponding to the cluster
        */
        double ePotential;
        //For each celestial body, calculate its kinetic energy and potential energy, and calculate the total energy of the entire galaxy
        for (int i=0;i<numberOfParticles;i++){
            //For every other celestial body of this celestial body
            for (int j=0;j<numberOfParticles;j++){
                if (j != i){
                    //Calculate the Potential energy of the celestial body and the other celestial body, and accumulate
                    ePotential = ePotential+(solarSystem[i].getMu()*solarSystem[j].getMu())/sqrt((solarSystem[i].getPosition()-solarSystem[j].getPosition()).dot(solarSystem[i].getPosition()-solarSystem[j].getPosition()));
                }else{
                    continue;
                }
            }
        }

        return -0.5*ePotential;
    }

    
    double CalculateKineticEnergyOpenMp(MassiveParticle solarSystem[], int numberOfParticles){
        /**
        * Based on a given particle cluster and its size, this function is used to calculate the total energy corresponding to the cluster
        */
        double eKinetic;
        //For each celestial body, calculate its kinetic energy
        #pragma omp parallel for reduction(+: eKinetic)
        for (int i=0;i<numberOfParticles;i++){
            //Calculate the Kinetic energy of the celestial body and accumulate it
            eKinetic += solarSystem[i].getMu()*pow((sqrt(solarSystem[i].getVelocity().dot(solarSystem[i].getVelocity()))),2);
        }

        return 0.5*eKinetic;
    }

    double CalculatePotentialEnergyOpenMp(MassiveParticle solarSystem[], int numberOfParticles){
        /**
        * Based on a given particle cluster and its size, this function is used to calculate the total energy corresponding to the cluster
        */
        double ePotential;
        //For each celestial body, calculate its kinetic energy and potential energy, and calculate the total energy of the entire galaxy
        #pragma omp parallel for reduction(+: ePotential)
        for (int i=0;i<numberOfParticles;i++){
            //For every other celestial body of this celestial body
            for (int j=0;j<numberOfParticles;j++){
                if (j != i){
                    //Calculate the Potential energy of the celestial body and the other celestial body, and accumulate
                    ePotential = ePotential+(solarSystem[i].getMu()*solarSystem[j].getMu())/sqrt((solarSystem[i].getPosition()-solarSystem[j].getPosition()).dot(solarSystem[i].getPosition()-solarSystem[j].getPosition()));
                }else{
                    continue;
                }
            }
        }

        return -0.5*ePotential;
    }
}
