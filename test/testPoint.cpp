#include<iostream>
#include"../src/Point.h"

int main(){

  Point<double,2> A;
  A.SetCoord(0,1.3);
  A.SetCoord(1,1.2);
  std::cout<<A<<std::endl;

  Point<double,3> B{1,2,3};
  B.SetCoord(0,2);
  std::cout<<B<<std::endl;

  Point<double,2> C=A;
  std::cout<<C<<std::endl;
  return 0;
}
