#include "../src/Spajor.h"
#include <iostream>

using namespace std;
int main(){
  using Point2D=Point<double,2>;

  Point2D A{2,5};  Point2D B{3,0};
  Point2D C{2,-5}; Point2D D{1,0};
  Point2D E{-2,5}; Point2D F{-1,0};
  Point2D G{-2,-5};Point2D H{-3,0};
  Point2D I{-6,0}; Point2D J{-4,-6};
  Point2D K{4,-6}; Point2D L{6,0};

  Segment<2> AB{A,B}; Segment<2> BC{B,C};
  Segment<2> CD{C,D}; Segment<2> DA{D,A};
  Segment<2> AE{A,E}; Segment<2> EF{E,F};
  Segment<2> FG{F,G}; Segment<2> GH{G,H};
  Segment<2> HE{H,E}; Segment<2> EI{E,I};
  Segment<2> IJ{I,J}; Segment<2> JK{J,K};
  Segment<2> KL{K,L}; Segment<2> LA{L,A};

  Jordan_Curve<2> Test{{AB,BC,CD,DA,AE,EF,FG,GH,HE,EI,IJ,JK,KL,LA}};

  if(Test.IsJordanCurve()){ cout<<"It is a Jordan_Curve."<<endl;}
  else{ cout<<"It is not a Jordan Curve!"<<endl;}
  
  vector<Point2D> Inter = SelfIntersect(Test);
  for(auto i=Inter.begin();i!=Inter.end();i++)
    cout<<*i<<endl;

  cout<<Test<<endl;
  
  Spajor<2> spajor = Pasting(Inter,{AB,BC,CD,DA,AE,EF,FG,GH,HE,EI,IJ,JK,KL,LA});
  cout<<spajor<<endl;

  return 0;
}
