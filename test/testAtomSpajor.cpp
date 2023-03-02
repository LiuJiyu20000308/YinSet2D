#include "../src/Atom_Spajor.h"
#include <iostream>
#include<fstream>
#include <string>
using namespace std;

vector<Segment<2>> InputCurve2(string Filename);

int main(){
  vector<Segment<2>> Curve1 = InputCurve2("test/data/pandadata/Curve1.txt");
  vector<Segment<2>> Curve2 = InputCurve2("test/data/pandadata/Curve2.txt");
  vector<Segment<2>> Curve3 = InputCurve2("test/data/pandadata/Curve3.txt");

  Atom_Spajor<2> atomspajor{{Curve1,Curve2,Curve3}};
  
  Point<double,2> A{0,0};
  Point<double,2> B{1,0.5};
  Segment<2> AB{A,B};

  Segment<2> AA = *(Curve2.begin());
  
  cout<<"AA is in Curve2?:"<<IsInclude(atomspajor,AA)<<endl;
  
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

