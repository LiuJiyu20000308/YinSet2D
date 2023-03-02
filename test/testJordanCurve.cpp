#include "../src/Jordan_Curve.h"
#include <iostream>
#include<fstream>
#include <string>
using namespace std;

vector<Segment<2>> InputCurve2(string Filename);
int main(){

  vector<Segment<2>> Curve1 = InputCurve2("test/data/pandadata/Curve1.txt");
  vector<Segment<2>> Curve2 = InputCurve2("test/data/mickeydata/Curve1.txt");
  vector<Segment<2>> Curve3 = InputCurve2("test/data/pandadata/Curve2.txt");
  
  Jordan_Curve<2> J1{Curve1};
  Jordan_Curve<2> J2{Curve2};
  Jordan_Curve<2> J3{Curve3};
  
  if(IsIntersect(J1,J2)){
    vector<Point<double,2>> Inter = Intersect_Point(J1,J2);
    cout<<"The intersections of J1 and J2:"<<endl;
    for(auto i=Inter.begin();i!=Inter.end();i++){
      cout<<*i<<endl;
    }
  }
  else{
    cout<<"No intersections!"<<endl;
  }
  cout<<endl;
  cout<<"J1 include J3?: "<<IsInclude(J1,J3)<<endl;

  return 0;
}



vector<Segment<2>> InputCurve2(string Filename){
  ifstream in(Filename,ios::in);
  vector<Segment<2>> Curve;
  if(in.is_open()){
    double x1,x2,y1,y2;
    in >> x1; in>>y1; in>>x2; in>>y2;
    Curve.push_back({{0,0},{0,0}});
    while(x1!=x2){
      Curve.push_back({{0,0},{0,0}});
      in >> x2; in>>y2;
    }
    
    in.seekg(0,in.beg);
    in >> x1; in >> y1; in>>x2; in>>y2;
    double x=x1; double y=y1;
    auto i=Curve.begin();
    while(x2!=x){
      (*i).StartingPoint().SetCoord(0,x1); (*i).StartingPoint().SetCoord(1,y1);
      (*i).EndingPoint().SetCoord(0,x2); (*i).EndingPoint().SetCoord(1,y2);
      i++;
      x1=x2; y1=y2;
      in >> x2; in >> y2;
    }
    (*i).StartingPoint().SetCoord(0,x1);
    (*i).EndingPoint().SetCoord(0,x);
    (*i).StartingPoint().SetCoord(1,y1);
    (*i).EndingPoint().SetCoord(1,y);
  }
  return Curve; 
}
