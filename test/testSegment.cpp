#include "../src/Segment.h"
#include <iostream>


int main(){
  using Point2D = Point<double,2>;
  Point2D a{1.2,1.3};
  Point2D b{2,3};
  Segment<2> AA{a,b};
  Segment<2> BB(AA);
  BB.StartingPoint().SetCoord(0,3);

  //test member function
  std::cout<<BB<<std::endl;
  std::cout<<"The slope of AA is "<<AA.slope()<<std::endl;

  // test position judgement
  Point2D c{1.7,1.3+0.5*AA.slope()};
  if(IsInclude(AA,c)){
    std::cout<<"AA includes c"<<std::endl;
  }

  Point2D A{1,4}; Point2D B{4,4};
  Point2D C{1,3}; Point2D D{4,5};
  Point2D E{2,4}; Point2D F{5,4};
  Point2D G{1,5}; Point2D H{5,5};
  Point2D I{1,2}; Point2D J{2,5};
  
  Segment<2> AB(A,B); Segment<2> IG{I,G};
  Segment<2> CD{C,D}; Segment<2> EJ{E,J};
  Segment<2> EB{E,B}; Segment<2> EF{E,F};
  Segment<2> GH{G,H}; Segment<2> IA{I,A}; 
  
  std::cout<<"AB,CD:"<<Position(AB,CD)<<std::endl;
  std::cout<<"AB,EB:"<<Position(AB,EB)<<std::endl;
  std::cout<<"AB,EF:"<<Position(AB,EF)<<std::endl;
  std::cout<<"AB,GH:"<<Position(AB,GH)<<std::endl;
  std::cout<<"AB,IA:"<<Position(AB,IA)<<std::endl;
  std::cout<<"AB,IG:"<<Position(AB,IG)<<std::endl;
  std::cout<<"AB,EJ:"<<Position(AB,EJ)<<std::endl;


  // test Angle.

  Point2D A1{1,1};  Point2D B1{-1,1};
  Point2D C1{1,0};  Point2D O{0,0};
  Segment<2> A1O{A1,O};
  Segment<2> OB1{O,B1};
  Segment<2> OC1{O,C1};
  Segment<2> OA1{O,A1};
  std::cout<<"A1O,OB1:"<<Angle(A1O,OB1)<<std::endl;
  std::cout<<"A1O,OC1:"<<Angle(A1O,OC1)<<std::endl;
  std::cout<<"A1O,OA1:"<<Angle(A1O,OA1)<<std::endl;
  
 

  return 0;
}
