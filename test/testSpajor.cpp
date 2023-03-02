#include "SomeFunc.cpp"
#include <iostream>
#include<fstream>
#include <string>
using namespace std;

/**
vector<Segment<2>> InputCurve(string Filename);
vector<Segment<2>> InputCurve2(string Filename);
Spajor<2> GetPanda();
Spajor<2> GetMickey();
void Out(Spajor<2> spajor,string Filename);
**/

int main(){

  Spajor<2> Panda = GetPanda();
  Spajor<2> Mickey= GetMickey();


  Spajor<2> Panda1 = Complementation(Panda);
  Spajor<2> Intersect = Meet(Panda,Mickey);
  Spajor<2> join = Join(Panda,Mickey);
  
  Out(Panda1,"test/Result/ComplementResult/complementresult.txt");  
  Out(Intersect,"test/Result/MeetResult/meetresult.txt");
  Out(join,"test/Result/JoinResult/joinresult.txt");


  return 0;
}


