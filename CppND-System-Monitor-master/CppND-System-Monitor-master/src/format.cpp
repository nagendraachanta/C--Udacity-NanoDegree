#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long times) {
 int HH, MM,SS;
 string HHs,MMs,SSs;
HH=times/3600;
MM=((times%3600)/60);
SS=times-HH*3600-MM*60;
if(HH<10){
    HHs=to_string(0)+to_string(HH);}
else
{
    HHs=to_string(HH);
}

if(MM<10){
    MMs=to_string(0)+to_string(MM);}
else
{
    MMs=to_string(MM);
}

if(SS<10){
    SSs=to_string(0)+to_string(SS);}
else
{
    SSs=to_string(SS);
}

string out=(HHs+":"+MMs+":"+SSs);
return out;

}