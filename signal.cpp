#include"signal.hpp"
#include"params.hpp"
#include<iostream>
#include<cmath>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <cstdlib>


std::vector<double>& Signal::getTime(){
    return this->time;
}

std::vector<double>& Signal::getSamples(){
    return this->samples;
}


Signal SignalGenerator::sine(double amplitude, double frequency, double duration, double sampleRate){
    int N = static_cast<int>(duration * sampleRate);
    Signal z(sampleRate, duration);
    for (int i = 0; i < N ; i++)
    {
        double t = i / sampleRate;
        z.getTime().push_back(t);

        double value = amplitude * std::sin(2 * PI * frequency * t);
        z.getSamples().push_back(value);
    }
    SignalGenerator::save(z);
    return z;
}

Signal SignalGenerator::cosine(double amplitude, double frequency, double duration, double sampleRate){
    int N = static_cast<int>(duration * sampleRate);
    Signal z(sampleRate, duration);
    for (int i = 0; i < N ; i++)
    {
        double t = i / sampleRate;
        z.getTime().push_back(t);
        
        double value = amplitude * std::cos(2 * PI * frequency * t);
        z.getSamples().push_back(value);
    }
    SignalGenerator::save(z);
    return z;
}


void SignalGenerator::save(Signal &s){

    std::string currentPath = std::filesystem::current_path();
    std::string path = currentPath + "/result";

    std::filesystem::create_directories(path);

    std::string TimePath = path + "/time.csv";
    std::string SignalPath = path + "/signal.csv";
    std::string PlotPath = path + "/plot.png";

    std::string pythonScriptCommand = ".venv/bin/python plotsignal.py \"" 
        + TimePath + "\" \"" 
        + SignalPath + "\" \"" 
        + PlotPath + "\"";

    std::ofstream SampleFile(SignalPath);
    std::ofstream TimeFile(TimePath);

    int s_size = s.getSamples().size();
    int t_size = s.getTime().size();

    for (size_t i = 0; i < s_size; i++)
    {
        SampleFile << s.getSamples()[i] << std::endl;
    }

    for (size_t i = 0; i < t_size; i++)
    {
        TimeFile << s.getTime()[i] << std::endl;
    }

    SampleFile.close();
    TimeFile.close();

    std::cout << "file created!" << "\n";

    int plot = std::system(pythonScriptCommand.c_str());

    if (plot != 0) {
        std::cerr << "Errore durante il plotting\n";
        return;
    }

    std::cout << "Grafico generato!\n";

}
