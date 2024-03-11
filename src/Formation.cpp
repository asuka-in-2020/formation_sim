#include "Formation.h"

using namespace formation_sim;
Formation::Formation(Simulator* p):p_(p){}

void Formation::addAgent(size_t agentNo, Eigen::Vector2f slot){
    slots_[agentNo] = slot;
}



void Formation::updateTarget(){
    for (auto const& slot: slots_){
        p_->agents_[slot.first].setTarget(slot.second + Pos_);
    }
}

