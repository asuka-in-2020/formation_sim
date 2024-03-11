#include "Simulator.h"

using namespace formation_sim;
Simulator::Simulator(float rate)
{
    formations_.emplace_back(Formation(this));
    formations_[0].setPos(Eigen::Vector2f(250.0f, 250.0f));
    formations_[0].addAgent(0, Eigen::Vector2f(0.0f, 50.0f));
    formations_[0].addAgent(1, Eigen::Vector2f(-50.0f, 0.0f));
    formations_[0].addAgent(2, Eigen::Vector2f(0.0f, -50.0f));
    formations_[0].addAgent(3, Eigen::Vector2f(50.0f, 0.0f));
    // formations_[0].addAgent(4, Eigen::Vector2f(0.0f, 0.0f));
    agents_.emplace_back(10,2, agents_.size(), 1/rate, Eigen::Vector2f(250.0f+50.0f, 250.0f));
    agents_.emplace_back(10,2, agents_.size(), 1/rate,Eigen::Vector2f(250.0f+100.0f, 250.0f+50.0f));
    agents_.emplace_back(10,2, agents_.size(), 1/rate,Eigen::Vector2f(250.0f-100.0f, 250.0f+50.0f));
    agents_.emplace_back(10,2, agents_.size(), 1/rate,Eigen::Vector2f(250.0f, 250.0f+0.0f));
    // agents_.emplace_back(10,2, agents_.size(), 1/rate,Eigen::Vector2f(250.0f, 350.0f+0.0f));

    videoWriter.open(outputPath, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(500, 500));
    if(!videoWriter.isOpened()) {
        std::cerr << "Error: Could not open the video writer." << std::endl;
    }

    ROS_INFO("DONE");







}   

Simulator* Simulator::p=nullptr;
std::mutex Simulator::lock_;
Simulator::CGarbo Garbo;


Simulator *Simulator::instance(float rate)
{
    if (p == nullptr)
    {
        std::lock_guard<std::mutex> guard(lock_);
        if (p == nullptr)
            p = new Simulator(rate);
    }
    return p;
}


void Simulator::doStep(){
    formations_[0].updateTarget();

    for (auto & a: agents_){
        a.computeControl(agents_);
        // if (a.getNo()==2){
        // std::cout<<"No."<<a.getNo()<<std::endl;
        //     std::cout<<"Vel:"<<a.Vel_<<std::endl<<std::endl;
        //     std::cout<<"Pos:"<<a.Pos_<<std::endl;
        //     std::cout<<"Tar:"<<a.TargetPos_<<std::endl;
        // }
    }

    for (auto & a: agents_){
        a.evolution();
    }

    trajPlot();
}
void Simulator::trajPlot(){

    // ROS_INFO("PLOT%d",agents_[0].traj_.size());

    cv::Mat background(500,
                500, CV_8UC3,
                cv::Scalar(255, 255, 255));
    for (auto const&a: agents_){
        for (size_t i = 0; i < a.traj_.size() - 1; ++i) {
            cv::line(background, cv::Point(static_cast<int>(a.traj_[i].x()), static_cast<int>(a.traj_[i].y())), cv::Point(static_cast<int>(a.traj_[i+1].x()), static_cast<int>(a.traj_[i+1].y())), cv::Scalar(255, 0, 0), 1);
        }
        // std::cout<<a.traj_.back();
        cv::circle(background, cv::Point(static_cast<int>(a.traj_.back().x()), static_cast<int>(a.traj_.back().y())), a.R_, cv::Scalar(0, 0, 255), 1);
        cv::circle(background, cv::Point(static_cast<int>(a.traj_.back().x()), static_cast<int>(a.traj_.back().y())), a.r_, cv::Scalar(255, 0, 255), -1);

    }
    if(!background.empty()) {
        videoWriter.write(background);
    }
    cv::imshow("img", background);

    cv::waitKey(2);
}



