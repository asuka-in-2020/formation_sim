#pragma once


#include "ros/ros.h"
#include <Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include <cmath>
#include <vector>
#include <string>
// #include "Vector2.h"


namespace formation_sim{
    class Agent {
        private:

            // const Eigen::Vector2f initialPos_;
            Eigen::Vector2f Vel_, Pos_, u_;
            Eigen::Vector2f TargetPos_;
            size_t No_;
            const float deltaT_,R_,r_,gamma_=10.0f;
            std::vector<Eigen::Vector2f> traj_;


        public:
            Agent(const float R, const float r, size_t No, const float T=0.1,Eigen::Vector2f iniPos=Eigen::Vector2f());
            Eigen::Vector2f computeControl(const std::vector<Agent>& agents);
            size_t inline getNo() const { return No_;}
            void evolution();
            void setTarget(Eigen::Vector2f pos);
            Eigen::Vector2f dVdp(const Eigen::Vector2f& pi, const Eigen::Vector2f& pj);
    
        friend class Simulator;
    };
}
