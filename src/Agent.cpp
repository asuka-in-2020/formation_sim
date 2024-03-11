
#include "Agent.h"

using namespace formation_sim;

Agent::Agent(const float R, const float r,  size_t No, const float T,Eigen::Vector2f iniPos):deltaT_(T), R_(R), r_(r), No_(No), Pos_(iniPos){

};


Eigen::Vector2f Agent::computeControl(const std::vector<Agent>& agents){
    for(Agent const& a : agents){
        u_ -=  Pos_ - TargetPos_ -(a.Pos_ - a.TargetPos_) + gamma_*(Vel_ - a.Vel_) + 5*Vel_;
        u_ *= 0.05;
        Eigen::Vector2f dV = dVdp(Pos_, a.Pos_);
        if (dV.norm()<10)
            u_ -= dV;
        else{
            u_ -= 10/dV.norm()*dV;
        }



        // std::cout<<"deri:"<<dVdp(Pos_, a.Pos_)<<std::endl;

    }
}

Eigen::Vector2f Agent::dVdp(const Eigen::Vector2f& pi, const Eigen::Vector2f& pj){
    Eigen::Vector2f deri=Eigen::Vector2f();
    float dis = (pi -pj).norm();

    // ROS_INFO("dis%f", dis);

    if (dis <R_ && dis > r_){
        ROS_INFO("CHECK");
        deri = 4*(pow(R_, 2) - pow(r_ ,2 ))*(pow(dis,2) - pow(R_,2))/(pow(dis,2) - pow(r_,2)) * (pi-pj);
        Eigen::Rotation2D<float> rot(M_PI / 6);
        deri = rot*deri;
    }

    return deri;


}

void Agent::evolution(){
    Vel_ += deltaT_*u_;
    Pos_ += deltaT_*Vel_;
    traj_.push_back(Pos_);
}

void Agent::setTarget(Eigen::Vector2f pos){
    TargetPos_ = pos ;
}