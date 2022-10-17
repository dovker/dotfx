#pragma once
#include <chrono>

namespace Game2D
{
    class BenchmarkTimer
    {
    public:
        BenchmarkTimer(const std::string& name)
        {
            m_Name = name;

            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }
        ~BenchmarkTimer()
        {
            Stop();
        }
        void Stop()
        {
            auto endTimePoint = std::chrono::high_resolution_clock::now();

            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
            
            auto duration = end-start;
            double ms = duration*0.001;
            
            CLAP_INFO(m_Name, " Time taken: ", ms);
        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        std::string m_Name;
    };
}