#pragma once

#include <mutex>
#include <opencv2/opencv.hpp>
#include "Formation.h"
namespace formation_sim
{
    class Formation;
    class Agent;
    
    class Simulator
    {
    private:
        /* data */
        static Simulator *p;
        static std::mutex lock_;

        std::vector<Formation> formations_;
        std::vector<Agent> agents_;

        const std::string outputPath = "output.avi";

        cv::VideoWriter videoWriter;

        Simulator(float rate);
        ~Simulator() = default;

    public:
        static Simulator *instance(float rate);

        void trajPlot();
        void doStep();




        class CGarbo
        {
        public:
            ~CGarbo()
            {
                if (Simulator::p){
                    p->videoWriter.release();
                    std::cout<<"SAVED"<<std::endl;
                    delete Simulator::p;

                }
                    
            }
        };
        static CGarbo Garbo; // 定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数从而释放单例对象

        friend class Agent;
        friend class Formation;
    };
    

}