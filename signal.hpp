#ifndef SIGNAL_HPP
#define SIGNAL_HPP
#include<iostream>
#include<vector>
#include"params.hpp"

class Signal{
    private:
        std::vector<double> samples;
        double duration;
        double sampleRate;
        double amplitude;
        double frequency;
        std::vector<double> time;


    public:
        explicit Signal(double sampleRate, double duration){
            this->sampleRate = sampleRate;
            this->duration = duration;

            std::cout << "init signal with:\n" << 
            "sample rate = " << this->sampleRate << "\n" <<
            "length = " << this->duration << "\n";
        }

        void generate(double amplitude, double frequency, std::string &SignalForm);
        std::vector<double> &getTime();
        std::vector<double> &getSamples();
};

class SignalGenerator {
    public:
        static Signal sine(double amplitude, double frequency, double duration, double sampleRate);
        static Signal cosine(double amplitude, double frequency, double duration, double sampleRate);
    private:
        static void save(Signal &s);
};

#endif 