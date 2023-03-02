#ifndef Segment_h
#define Segment_h

#include "Point.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

double eps=1e-8;
template<int _Dim>
class Segment{
public:
  
  enum{ Dim=_Dim };
  using iPoint=Point<double,Dim>;
  using Point2D = Point<double,2>;
protected:
  iPoint StartPoint;
  iPoint EndPoint;

public:

  //Constructors
  Segment() = default;
  Segment(const iPoint Point1,const iPoint Point2):StartPoint{Point1},
                                       EndPoint{Point2}{};

  Segment<Dim> &operator=(const Segment<Dim> &p){
    StartPoint = p.StartPoint;
    EndPoint = p.EndPoint;
    return *this;
  }

  virtual ~Segment()=default;
  
  //Print for Test
  friend std::ostream &operator<<(std::ostream &os, const Segment<Dim> &p){
    os<<"Start Point:"<<p.StartPoint<<", End Point:"<<p.EndPoint;
    return os;
  }
  //Friend Function
  
  //Some Func
  double slope();
  const double slope() const;
  
  void SetStartPoint(iPoint start);
  void SetEndPoint(iPoint end);
  
  iPoint &StartingPoint(){ return StartPoint; };
  const iPoint& StartingPoint() const{return StartPoint;};
  
  iPoint &EndingPoint() { return EndPoint; };
  const iPoint &EndingPoint() const{return EndPoint;};
  
  void Reverse();
};

template<>
double Segment<2>::slope(){

  double x1 = StartPoint[0];
  double y1 = StartPoint[1];

  double x2 = EndPoint[0];
  double y2 = EndPoint[1];
  if(x1==x2){
    throw std::runtime_error("The slope is infinity");
  }
  else{
    double k = (y2-y1)/(x2-x1);
    return k;
  }
}

template<>
const double Segment<2>::slope() const{

  double x1 = StartPoint[0];
  double y1 = StartPoint[1];

  double x2 = EndPoint[0];
  double y2 = EndPoint[1];
  if(x1==x2){
    throw std::runtime_error("The slope is infinity");
  }
  else{
    double k = (y2-y1)/(x2-x1);
    return k;
  }
}

template<int _Dim>
void Segment<_Dim>::SetStartPoint(iPoint start){
  StartPoint = start;
}

template<int _Dim>
void Segment<_Dim>::SetEndPoint(iPoint end){
  EndPoint = end;
}

template<int _Dim>
void Segment<_Dim>::Reverse(){
  Point<double,2> A{StartPoint};
  StartPoint = EndPoint;
  EndPoint = A;
}

bool operator==(const Segment<2> & Seg1,const Segment<2> &Seg2){
  if(Seg1.StartingPoint()==Seg2.StartingPoint() && Seg1.EndingPoint() == Seg2.EndingPoint()){
    return true;
  }
  else{
    return false;
  }
}

bool operator!=(const Segment<2> & Seg1,const Segment<2> &Seg2){
  if(Seg1.StartingPoint()!=Seg2.StartingPoint() || Seg1.EndingPoint() != Seg2.EndingPoint()){
    return true;
  }
  else{
    return false;
  }
}

//--------------------------------------------------------------------
//Position Judging for 2d Segment and Point.

bool IsInclude(const Segment<2> & Seg,const Point<double,2> & p){
  if(p==Seg.StartingPoint() || p==Seg.EndingPoint()){
    return true;
  }
  else if(Seg.StartingPoint()[0]==Seg.EndingPoint()[0]){
    if(p[0]==Seg.StartingPoint()[0] &&
       (p[1]-Seg.StartingPoint()[1])*(p[1]-Seg.EndingPoint()[1])<=0){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    double k = Seg.slope();
    double k1= (p[1]-Seg.StartingPoint()[1])/(p[0]-Seg.StartingPoint()[0]);
    double k2= (Seg.EndingPoint()[1]-p[1])/(Seg.EndingPoint()[0]-p[0]);
    if( fabs(k-k1)<eps && fabs(k-k2)<eps &&
        (p[0]-Seg.StartingPoint()[0])*(p[0]-Seg.EndingPoint()[0])<=0){
      return true;
    }
    else{
      return false;
    }
  }
}

bool IsParallel(const Segment<2> & Seg1,const Segment<2> &Seg2){
  if(Seg1.StartingPoint()[0]==Seg1.EndingPoint()[0]||
     Seg2.StartingPoint()[0]==Seg2.EndingPoint()[0]){
      if(Seg1.StartingPoint()[0]==Seg1.EndingPoint()[0] &&
         Seg2.StartingPoint()[0]==Seg2.EndingPoint()[0]){
        return true;
      }
      else{
        return false;
      }
  }
  else if(fabs(Seg1.slope()-Seg2.slope())<eps){
    return true;
  }
  else{
    return false;
  }
}

bool InTheSameLine(const Segment<2> & Seg1,const Segment<2> &Seg2){
  if(!IsParallel(Seg1,Seg2)){
    return false;
  }
  else if(Seg1.StartingPoint()[0]==Seg1.EndingPoint()[0] &&
          Seg2.StartingPoint()[0]==Seg2.EndingPoint()[0]){
    if(Seg1.StartingPoint()[0]==Seg2.StartingPoint()[0]){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    double k=Seg1.slope();
    double b1=Seg1.StartingPoint()[1]-k*Seg1.EndingPoint()[0];
    double b2=Seg2.StartingPoint()[1]-k*Seg2.EndingPoint()[0];
    if(fabs(b1-b2)<eps){
      return true;
    }
    else{
      return false;
    }
  }
}

bool IsOverlap(const Segment<2> & Seg1,const Segment<2> &Seg2){
  if(InTheSameLine(Seg1,Seg2) &&
     (IsInclude(Seg1,Seg2.EndingPoint())|| IsInclude(Seg1,Seg2.StartingPoint()))){
    return true;
  }
  else{
    return false;
  }
}

std::vector<Point<double,2>> Intersect_Point(const Segment<2> & Seg1,
                                             const Segment<2> &Seg2){
  std::vector<Point<double,2>> Inter{};
  if(IsParallel(Seg1,Seg2)){
    if(IsOverlap(Seg1,Seg2)){
      if(IsInclude(Seg1,Seg2.EndingPoint())){
        Inter.push_back(Seg2.EndingPoint());
      }
      else{
        Inter.push_back(Seg2.StartingPoint());
      }
      if(IsInclude(Seg2,Seg1.EndingPoint())){
        Inter.push_back(Seg1.EndingPoint());
      }
      else{
        Inter.push_back(Seg1.StartingPoint());
      }
      auto i=Inter.begin(); auto j=i+1;
      if(*i==*j)
        Inter.pop_back();
      return Inter;
    }
  }
  else{
    if(Seg1.StartingPoint()[0]==Seg1.EndingPoint()[0]){
      double k2=Seg2.slope();
      double b2=Seg2.StartingPoint()[1]-k2*Seg2.StartingPoint()[0];
      double x=Seg1.StartingPoint()[0];
      double y=k2*x+b2;
      Point<double,2> intersect_Point{x,y};
      if(IsInclude(Seg1,intersect_Point) && IsInclude(Seg2,intersect_Point)){
        Inter.push_back(intersect_Point);
      }
    }
    else if(Seg2.StartingPoint()[0]==Seg2.EndingPoint()[0]){
      double k1=Seg1.slope();
      double b1=Seg1.StartingPoint()[1]-k1*Seg1.StartingPoint()[0];
      double x=Seg2.StartingPoint()[0];
      double y=k1*x+b1;
      Point<double,2> intersect_Point{x,y};
      if(IsInclude(Seg1,intersect_Point) && IsInclude(Seg2,intersect_Point)){
        Inter.push_back(intersect_Point);
      }
    }
    else{
      double k1=Seg1.slope();
      double k2=Seg2.slope();
      double b1=Seg1.StartingPoint()[1]-k1*Seg1.StartingPoint()[0];
      double b2=Seg2.StartingPoint()[1]-k2*Seg2.StartingPoint()[0];
      double x=(b2-b1)/(k1-k2);
      double y=k1*x+b1;
      Point<double,2> intersect_Point{x,y};
      if(IsInclude(Seg1,intersect_Point) && IsInclude(Seg2,intersect_Point)){
        Inter.push_back(intersect_Point);
      }
    }
    return Inter;
  }
}

bool Normal_Intersect(const Segment<2> & Seg1,const Segment<2> &Seg2){
  if(IsParallel(Seg1,Seg2)){
    return false;
  }
  else{
    std::vector<Point<double,2>> Inter = Intersect_Point(Seg1,Seg2);
    if(Inter.size()==0){
      return false;
    }
    else{
      Point<double,2> intersect_Point = *(Inter.begin());
      if(intersect_Point!=Seg1.StartingPoint() && intersect_Point!=Seg1.EndingPoint()
         && intersect_Point!=Seg2.StartingPoint() &&
         intersect_Point!=Seg2.EndingPoint()){
        return true;
      }
      else{
        return false;
      }
    }
  }
}

bool Intersect_Endpoint(const Segment<2> & Seg1,const Segment<2> &Seg2){
   if(IsParallel(Seg1,Seg2)){
    return false;
  }
  else{
    std::vector<Point<double,2>> Inter = Intersect_Point(Seg1,Seg2);
    if(Inter.size()==0){
      return false;
    }
    else{
      Point<double,2> intersect_Point = *(Inter.begin());
      if(intersect_Point==Seg1.StartingPoint() || intersect_Point==Seg1.EndingPoint()
      || intersect_Point==Seg2.StartingPoint() || intersect_Point==Seg2.EndingPoint()){
        return true;
      }
      else{
        return false;
      }
    }
  }
}

bool IsIntersect(const Segment<2> & Seg1,const Segment<2> &Seg2){
  if(IsParallel(Seg1,Seg2)){
    if(IsOverlap(Seg1,Seg2)){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    if(Normal_Intersect(Seg1,Seg2) || Intersect_Endpoint(Seg1,Seg2)){
      return true;
    }
    else{
      return false;
    }
  }
}

std::string Position(const Segment<2> &Seg1,const Segment<2> &Seg2){

  if(!IsIntersect(Seg1,Seg2)){
    if(IsParallel(Seg1,Seg2))
      return "ParallelWithNoIntersect";
    else
      return "NotNormalIntersect";
  }
  else{
    if(IsOverlap(Seg1,Seg2)){
      return "Overlap";
    }
    else if(Normal_Intersect(Seg1,Seg2)){
      return "NormalIntersect";
    }
    else if(Intersect_Endpoint(Seg1,Seg2)){
      return "IntersectEndpoint";
    }
  }
}

// -----------------------------------------------------


double AnglewithX(const Segment<2> Seg){
    double x=Seg.EndingPoint()[0]-Seg.StartingPoint()[0];
    double y=Seg.EndingPoint()[1]-Seg.StartingPoint()[1];
    if(x==0){
      if(y>0)
        return atan(1)*2;
      else
        return atan(1)*6;
    }
    else{
      double k=y/x;
      double theta=atan(k);
      if(theta>0){
        if(x<0)
          theta+=atan(1)*4;
      }
      if(theta<0){
        if(x<0)
          theta+=atan(1)*4;
      }
      return theta;
    }
}
double Angle(const Segment<2> Seg1, const Segment<2> Seg2){

  if(!(Seg1.EndingPoint()==Seg2.StartingPoint())){
    std::cout<<Seg1<<"\n"<<Seg2<<std::endl;
    throw std::runtime_error("Seg1 Endingpoint should be the same as Seg2 StartingPoint()!");
  }
  else{
    Segment<2> Seg3 =Seg1;
    Seg3.Reverse();
    double theta1 = AnglewithX(Seg3);
    double theta2 = AnglewithX(Seg2);
    double theta = (theta1<theta2 ? 8*atan(1)-theta2+theta1 : theta1-theta2);
    return theta;
  }
}

#endif
