#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include<fstream>
#include<sstream>

#include "linux_parser.h"


using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::stoi;
using std::stol;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel,version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >>version>> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string title;
  string memvalue;
  float MemTotal;
  float MemFree;
  string unit;
  std::ifstream stream(kProcDirectory+kMeminfoFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      while(linestream>>title>>memvalue>>unit){
        if(title=="MemTotal:"){
          if (memvalue==" ")
          MemTotal=0;
          else
          MemTotal=stof(memvalue);
          }
        if(title=="MemFree:"){
          
          if (memvalue==" ")
          MemFree=0;
          else
          MemFree=stof(memvalue);
          }
      }
    }
    
  }
  return (100.0*((MemTotal-MemFree)/MemTotal/1000.0));
 }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  string uptime;
  string idletime;
  long out;
  std::ifstream stream(kProcDirectory+kUptimeFilename);
  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);
    linestream>>uptime>>idletime;
    }
  
  out=stol(uptime);
  return out;
 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string processes;
  string totalprocesses;
  int out;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::istringstream linestream(line);
      while(linestream>>processes){
        if (processes=="processes"){
          linestream>>totalprocesses;
          if (totalprocesses==" ")
          out=0;
          else
          out=stoi(totalprocesses);
          break;
        }
      }
    }
  }
  return out;
 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string text;
  string runprocesses;
  
  int out;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
    std::istringstream stream(line);
    stream>>text>>runprocesses;

    if(text!="procs_running")
      continue;
    else {
      out=stoi(runprocesses);
      break;
      }
    }
  }
  return out;
}
 
 

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;
  string out;
  std::ifstream stream(kProcDirectory+to_string(pid)+kCmdlineFilename);
  if (stream.is_open()){
    while(std::getline(stream,line)){out=line;}
  }
  return out;
 }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string text;
  string Ramvalue;
  int Ramivalue;
  string unit;
  std::ifstream stream(kProcDirectory+to_string(pid)+kStatusFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream>>text>>Ramvalue>>unit;
      if(text=="VmSize:"){
        //if (Ramvalue==" ")
        //Ramfvalue=0;
        //else
        Ramivalue=(stoi(Ramvalue)/1000);
        break;
      }
    }
  }
  return to_string(Ramivalue);
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string Uid;
  string Uidval;
  string out;
  std::ifstream stream(kProcDirectory+to_string(pid)+kStatusFilename);
  if(stream.is_open()){
    while(std::getline(stream,line)){
      std::istringstream linestream(line);
      linestream>>Uid>>Uidval;
      if(Uid=="Uid:"){out= Uidval;}
    }
  }
  return out;
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line;
  string Username;
  string Uid;
  string var;
  string Uid_;
  string out;
  Uid=LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  if(filestream.is_open()){
    while(std::getline(filestream,line)){
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream linestream(line);
      linestream>>Username>>var>>Uid_;
      if(Uid_==Uid){out= Username;}
    }
  }
  return out;
 }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;
  long uptime;
  string uptime_;
  vector<string>vec;
  std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
  if(filestream.is_open()){
    std::getline(filestream,line);
    std::istringstream linestream(line);
    while(linestream>>uptime_){
      vec.push_back(uptime_);
    }
    if(vec[21]==" ")
    uptime=0;
    else
    uptime=(stol(vec[21])/sysconf(_SC_CLK_TCK));
  }
  return uptime;
 }