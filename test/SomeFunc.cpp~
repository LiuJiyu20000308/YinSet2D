#include "../src/Spajor.h"
#include <iostream>
#include<fstream>
#include <string>
using namespace std;

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

Spajor<2> GetPanda(){
  
  vector<Segment<2>> Curve1 = InputCurve2("test/data/pandadata/Curve1.txt");
  vector<Segment<2>> Curve2 = InputCurve2("test/data/pandadata/Curve2.txt");
  vector<Segment<2>> Curve3 = InputCurve2("test/data/pandadata/Curve3.txt");
  vector<Segment<2>> Curve4 = InputCurve2("test/data/pandadata/Curve4.txt");
  vector<Segment<2>> Curve5 = InputCurve2("test/data/pandadata/Curve5.txt");
  vector<Segment<2>> Curve6 = InputCurve2("test/data/pandadata/Curve6.txt");
  vector<Segment<2>> Curve7 = InputCurve2("test/data/pandadata/Curve7.txt");
  vector<Segment<2>> Curve8 = InputCurve2("test/data/pandadata/Curve8.txt");
  vector<Segment<2>> Curve9 = InputCurve2("test/data/pandadata/Curve9.txt");
  vector<Segment<2>> Curve10 = InputCurve2("test/data/pandadata/Curve10.txt");

  vector<Jordan_Curve<2>> panda{};
  panda.push_back({Curve1});
  panda.push_back({Curve2});
  panda.push_back({Curve3});
  panda.push_back({Curve4});
  panda.push_back({Curve5});                  
  panda.push_back({Curve6});
  panda.push_back({Curve7});
  panda.push_back({Curve8});
  panda.push_back({Curve9});
  panda.push_back({Curve10});
  Spajor<2> Panda{panda};
  return Panda;
}

Spajor<2> GetMickey(){
  vector<Segment<2>> Curve1 = InputCurve2("test/data/mickeydata/Curve1.txt");
  vector<Segment<2>> Curve2 = InputCurve2("test/data/mickeydata/Curve2.txt");
  vector<Segment<2>> Curve3 = InputCurve2("test/data/mickeydata/Curve3.txt");
  vector<Segment<2>> Curve4 = InputCurve2("test/data/mickeydata/Curve4.txt");
  vector<Segment<2>> Curve5 = InputCurve2("test/data/mickeydata/Curve5.txt");
  vector<Segment<2>> Curve6 = InputCurve2("test/data/mickeydata/Curve6.txt");
  vector<Jordan_Curve<2>> mickey{};
  mickey.push_back({Curve1});
  mickey.push_back({Curve2});
  mickey.push_back({Curve3});
  mickey.push_back({Curve4});
  mickey.push_back({Curve5});
  mickey.push_back({Curve6});
  
  Spajor<2> Mickey{mickey};
  return Mickey;
  
}

void Out(Spajor<2> spajor,string Filename){
  ofstream out(Filename);
  if(out.is_open()){
    int num = 1;
    for(auto i=spajor.atom().begin();i!=spajor.atom().end();i++){
      for(auto j=(*i).curve().begin();j!=(*i).curve().end();j++){
        out<<"\n"<<num<<"\n"<<std::endl;
        num++;
        for(auto k=(*j).seg().begin();k!=(*j).seg().end();k++){
          out<<(*k).StartingPoint()[0]<<" "<<(*k).StartingPoint()[1]<<std::endl;
        }
        auto k = (*j).seg().end()-1;
        out<<(*k).EndingPoint()[0]<<" "<<(*k).EndingPoint()[1]<<std::endl;
        out<<(*j).orientation()<<std::endl;
      }
      out<<"\n\n\n";
    }
    out.close();
  }
}

