#ifndef Point_h
#define Point_h

#include<initializer_list>
#include<iostream>
#include <cmath>

template<class T,int _Dim>
class Point{
protected:
  T coord[_Dim];

public:
  enum {Dim = _Dim};

  Point() = default;
  
  Point(std::initializer_list<T> l){
    auto j=l.begin();
    for(int d=0;d<Dim;++d)
      coord[d]=*j++;
  }

  void SetCoord(int _d, T t){ coord[_d]=t; }

  //accessors
  
  T &operator[](int _d){ return coord[_d]; }
  
  const T &operator[](int _d) const {return coord[_d]; }

  //print
  
  friend std::ostream &operator<<(std::ostream &os,const Point<T,Dim> &p){
    os<<"("<<p[0];
    for(int d=1;d<Dim;d++)
      os<<","<<p[d];
    os<<")";
    return os;
  }
  
  Point<T,Dim> &operator=(const Point<T,Dim> &p){
    for(int i=0;i<Dim;i++)
      coord[i]=p.coord[i];
    return *this;
  }

};

template<int Dim>
bool operator==(const Point<double,Dim> &p1,const Point<double,Dim> &p2){
  double epss=1e-6;
  for(int i=0;i<Dim;i++){
    if(fabs(p1[i]-p2[i])>epss){
      return false;
    }
  }
  return true;
}

template<int Dim>
bool operator!=(const Point<double,Dim> &p1,const Point<double,Dim> &p2){
  double epss=1e-6;
  for(int i=0;i<Dim;i++){
    if(fabs(p1[i]-p2[i])>epss){
      return true;
    }
  }
  return false;
}


#endif
