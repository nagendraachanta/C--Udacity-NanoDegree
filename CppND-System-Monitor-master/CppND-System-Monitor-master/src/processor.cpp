#include "processor.h"
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<unistd.h>
using std::string;
using std::stof;




vector<string> Processor::getterfunction(){
    string line;
    string str;
    vector<string>vec;
    std::ifstream filestream("/proc/stat");
    if(filestream.is_open()){
        std::getline(filestream,line);
        std::istringstream stream(line);
        while(stream>>str){
            if(str==" "||str=="cpu")
            continue;
            else
            vec.push_back(str);
        }
        
    }
    
   return vec; 
}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    vector<string>currentval;
    vector<string>prevval;
    unsigned int microseconds=100000;
    prevval=Processor::getterfunction();
    usleep(microseconds);
    currentval=Processor::getterfunction();
   float Idle=stof(currentval[3])+stof(currentval[4]);
   float PrevIdle=stof(prevval[3])+stof(prevval[4]);
   float PrevNonIdle=stof(prevval[0])+stof(prevval[1])+stof(prevval[2])+stof(prevval[5])+stof(prevval[6])+stof(prevval[7]);
   float NonIdle=stof(currentval[0])+stof(currentval[1])+stof(currentval[2])+stof(currentval[5])+stof(currentval[6])+stof(currentval[7]);
   float PrevTotal=PrevIdle+PrevNonIdle;
   float Total=Idle+NonIdle;
   float totald=Total-PrevTotal;
   float idled=Idle-PrevIdle;
   float CPU_Percentage=(totald-idled) /totald;
   return CPU_Percentage;

 }