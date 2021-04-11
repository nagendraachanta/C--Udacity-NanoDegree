#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include<iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using std::stof;
using std::stol;
using std::stoi;

//Constructer
Process::Process(int pid){
    pid_=pid;
    }

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {  
    string path=("/proc/"+to_string(pid_)+"/stat");
    std::ifstream stream(path);
    string line;
    string input;
    vector<string>line_content{};
    std::getline(stream,line);
    std::istringstream buffer(line);
    while(buffer>>input){
        if (input!=" ")
        line_content.push_back(input);
        else
        continue;
        
    }
    float utime=stof(line_content[13]);
    float stime=stof(line_content[14]);
    float cutime=stof(line_content[15]);
    float cstime=stof(line_content[16]);
    float starttime=stof(line_content[21]);
    float uptime=LinuxParser::UpTime();
    float freq=sysconf(_SC_CLK_TCK);
    float total_time=utime+stime+cutime+cstime;
    float seconds=uptime-(starttime/freq);
    float result=((total_time/freq)/seconds);
    
    return result;


 }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return (this->pid_<a.pid_); }