#pragma once

#include "ros/ros.h"

#include <string>
#include <vector>
#include <unordered_map>
#include "Agent.h"
#include "Simulator.h"
using namespace std;
namespace formation_sim{
    class Simulator;
    class Formation {
        private:

        Simulator *p_;
        unordered_map<size_t, Eigen::Vector2f> slots_;

        Eigen::Vector2f Pos_;


        public:
        Formation(Simulator *p);
        void updateTarget();            //delievery each agent's Pos
        void inline setPos(Eigen::Vector2f Pos){ Pos_=Pos;};       //set central Pos of formation
        void addAgent(size_t agentNo, Eigen::Vector2f slot);     //add agent constraint
        // void Solution();
            
    };
}
