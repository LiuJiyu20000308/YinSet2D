#ifndef JordanCurve_h
#define JordanCurve_h

#include "Segment.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

template<int _Dim>
class Jordan_Curve{
public:
  enum{Dim=_Dim};
  using iSegment = Segment<Dim>;
  using iPoint = Point<double,Dim>;
  using Point2D = Point<double,2>;
  using Segment2D = Segment<2>;
protected:
  std::vector<iSegment> Seg;
  int Orientation; //0 is positive, 1 is negative.

public:
  Jordan_Curve() = default;
  Jordan_Curve(std::vector<iSegment> Edge):Seg{Edge}{ SetOrientation();};

  Jordan_Curve<Dim> &operator=(const Jordan_Curve<Dim> & A){
    Seg.clear();
    for(auto i=A.seg().begin();i!=A.seg().end();i++){
      Seg.push_back(*i);
    }
    Orientation = A.Orientation;
    return *this;
  }
  
  virtual ~Jordan_Curve() = default;

  //Print for test
  friend std::ostream &operator<<(std::ostream &os, const Jordan_Curve<Dim> &Curve){
     for(auto i=Curve.Seg.begin();i!=Curve.Seg.end();i++){
      os<<*i<<std::endl;
    }
    std::cout<<"Orientation:"<<Curve.orientation()<<std::endl;
    return os;
  }

  void SetOrientation(int i){ Orientation = i;};
  void SetOrientation();

  double Max_X();
  const double Max_X() const;
  
  int &orientation(){ return Orientation;};
  const int &orientation() const{return Orientation;};

  std::vector<iSegment> &seg(){ return Seg;};
  const std::vector<iSegment> &seg() const { return Seg;};
  
  bool IsJordanCurve();
  void Reverse();
};


//------------------ Memeber Function
template<int _Dim>
double Jordan_Curve<_Dim>::Max_X(){
  double imax=(*(Seg.begin())).StartingPoint()[0];
  for(auto i=Seg.begin();i!=Seg.end();i++){
    if((*i).StartingPoint()[0]>imax){
      imax=(*i).StartingPoint()[0];
    }
  }
  return imax;
}

template<int _Dim>
const double Jordan_Curve<_Dim>::Max_X() const{
  double imax=(*(Seg.begin())).StartingPoint()[0];
  for(auto i=Seg.begin();i!=Seg.end();i++){
    if((*i).StartingPoint()[0]>imax){
      imax=(*i).StartingPoint()[0];
    }
  }
  return imax;
}

template<int _Dim>
void Jordan_Curve<_Dim>::Reverse(){
  std::vector<Segment<2>> newSeg;
  for(auto i=Seg.rbegin();i!=Seg.rend();i++){
    Point<double,2> tmpp = (*i).EndingPoint();
    (*i).SetEndPoint((*i).StartingPoint());
    (*i).SetStartPoint(tmpp);
    newSeg.push_back(*i);
  }
  Seg.clear();
  for(auto j=newSeg.begin();j!=newSeg.end();j++){
    Seg.push_back(*j);
  }
  Orientation = (Orientation==0) ? 1 : 0;
}



template<>
void Jordan_Curve<2>::SetOrientation(){
  double d =0;
  for(auto i=Seg.begin();i!=Seg.end();i++){
    d+=-0.5*((*i).StartingPoint()[1]+(*i).EndingPoint()[1])*
      ((*i).EndingPoint()[0]-(*i).StartingPoint()[0]);
  }
  if(d>0){
    Orientation = 1;
  }
  else{
    Orientation = 0;
  }
}

template<>
bool Jordan_Curve<2>::IsJordanCurve(){
  if((*(Seg.begin())).StartingPoint()!= (*(Seg.end()-1)).EndingPoint()){
    return false;
  }
  for(auto i=Seg.begin();i!=Seg.end();i++){
    for(auto j=i+1;j!=Seg.end();j++)
      if(IsIntersect(*i,*j)){
        std::vector<Point<double,2>> inter = Intersect_Point(*i,*j);
        if(inter.size()>1){
          return false;
        }
        else if(inter.size()==1){
          Point<double,2> pointt = *(inter.begin());
          if(pointt == (*i).StartingPoint()){
            if(pointt == (*j).EndingPoint()){}
            else{
              return false;
            }
          }
          else if(pointt == (*i).EndingPoint()){
            if(pointt == (*j).StartingPoint()){}
            else{
              return false;
            }
          }
          else{
            return false;
          }
        }
      }
  }
  return true;
}

//------------------------------------

bool operator==(const Jordan_Curve<2> curve1, const Jordan_Curve<2> curve2){
  if(curve1.seg().size()!=curve2.seg().size()){
    return false;
  }
  else{
    auto i=curve1.seg().begin(); auto j=curve2.seg().begin();
    for(;i!=curve1.seg().end();i++,j++){
      if((*i)!=(*j)){
        return false;
      }
    }
    return true;
  }
}

bool operator!=(const Jordan_Curve<2> curve1, const Jordan_Curve<2> curve2){
  return !(curve1==curve2);
}

//----------------------------------------
// Position Judging for 2d Jordan_Curve with Segment or Point.

bool IsIntersect(const Jordan_Curve<2> &Curve,const Segment<2> &Segm){
  for(auto i=Curve.seg().begin();i!=Curve.seg().end();i++){
    if(IsIntersect(*i,Segm)){
      return true;
    }
  }
  return false;
}

bool IsIntersect(const Jordan_Curve<2> &Curve1,const Jordan_Curve<2> &Curve2){
  for(auto i=Curve1.seg().begin();i!=Curve1.seg().end();i++){
    for(auto j=Curve2.seg().begin();j!=Curve2.seg().end();j++){
      if(IsIntersect(*i,*j)){
        return true;
      }
    }
  }
  return false;
}

std::vector<Point<double,2>> Intersect_Point(const Jordan_Curve<2> &Curve,
                                             const Segment<2> &Segm){
  if(!IsIntersect(Curve,Segm)){   
    throw std::runtime_error("Curve does not intersect with Segment!");
  }
  else{
    std::vector<Point<double,2>> Inter{};
    for(auto i=Curve.seg().begin();i!=Curve.seg().end();i++){
      if(IsIntersect(*i,Segm)){
        // std::cout<<(*i)<<Segm<<std::endl;
        std::vector<Point<double,2>> inter = Intersect_Point(*i,Segm) ;
        for(auto p = inter.begin(); p != inter.end(); p++){
          if(Inter.size()==0){ Inter.push_back(*p);}
          else{
            int flag=0;
            for(auto q = Inter.begin(); q!=Inter.end();q++){
              if((*p)==(*q)){ flag=1; break;}
            }
            if(flag==0){ Inter.push_back(*p);}
          }
        }
      }
    }
    return Inter;
  }
}

std::vector<Point<double,2>> Intersect_Point(const Jordan_Curve<2> &Curve1,
                                             const Jordan_Curve<2> &Curve2){
  if(!IsIntersect(Curve1,Curve2)){
    throw std::runtime_error("Curve1 does not intersect with Curve2!");
  }
  else{
    std::vector<Point<double,2>> Inter{};
    for(auto i=Curve1.seg().begin();i!=Curve1.seg().end();i++){
      for(auto j=Curve2.seg().begin();j!=Curve2.seg().end();j++){
        if(IsIntersect(*i,*j)){

          //std::cout<<*i<<"\n"<<*j<<std::endl;

          std::vector<Point<double,2>> inter = Intersect_Point(*i,*j);
          for(auto p = inter.begin(); p != inter.end(); p++){
            if(Inter.size()==0){

              //  std::cout<<*p<<std::endl;

              Inter.push_back(*p);
            }
            else{
              int flag=0;
              for(auto q = Inter.begin(); q!=Inter.end();q++){
                if((*p)==(*q)){ flag=1; break;}
              }
              if(flag==0){

                //     std::cout<<*p<<std::endl;
                
                Inter.push_back(*p);
              }
            }
          }
        }
      }
    }
    return Inter;
  }
}

std::vector<Point<double,2>> SelfIntersect(const Jordan_Curve<2> &Curve1){
  std::vector<Point<double,2>> Inters{};
  for(auto i=Curve1.seg().begin();i!=Curve1.seg().end();i++){
    for(auto j=i+1; j!=Curve1.seg().end();j++){
      if((*i).StartingPoint() == (*j).EndingPoint() ||
         (*i).EndingPoint() == (*j).StartingPoint()){
        continue;
      }
      else{
        if(IsIntersect(*i,*j)){
          std::vector<Point<double,2>> inter = Intersect_Point(*i,*j);
          for(auto p = inter.begin(); p != inter.end(); p++){
            if(Inters.size()==0){ Inters.push_back(*p);}
            else{
              int flag=0;
              for(auto q = Inters.begin(); q!=Inters.end();q++){
                if((*p)==(*q)){ flag=1; break;}
              }
              if(flag==0){ Inters.push_back(*p);}
            }
          }
        }
      }
    }
  }
  return Inters;
}

bool OnCurve(const Jordan_Curve<2> &Curve,const Point<double,2> &p1){
  for(auto i=Curve.seg().begin();i!=Curve.seg().end();i++){
    if(IsInclude(*i,p1)){
      return true;
    }
  }
  return false;
}

bool IsInclude(const Jordan_Curve<2> &Curve, const Point<double,2> &p1){
  if(OnCurve(Curve,p1)){
    return true;
  }
  
  double Maxx=Curve.Max_X()+1;
  Point<double,2> p2{Maxx,p1[1]};
  Segment<2> PP{p1,p2};
  if(IsIntersect(Curve,PP)){
    std::vector<Point<double,2>> Improper_Inter;
    for(auto i=Curve.seg().begin();i!=Curve.seg().end();i++){
      if(IsIntersect(*i,PP)){
        if(!Intersect_Endpoint(*i,PP)){
          std::vector<Point<double,2>> inter = Intersect_Point(*i,PP);
          for(auto p = inter.begin(); p != inter.end(); p++){
            if(Improper_Inter.size()==0){Improper_Inter.push_back(*p);}
            else{
              int flag=0;
              for(auto q = Improper_Inter.begin(); q!=Improper_Inter.end();q++){
                if((*p)==(*q)){ flag=1; break;}
              }
              if(flag==0){Improper_Inter.push_back(*p);}
            }
          }
        }
        else{
          std::vector<Point<double,2>> inter = Intersect_Point(*i,PP);
          Point<double,2> pointt = *(inter.begin());
          auto j= (i==Curve.seg().end()-1) ? Curve.seg().begin() : i+1;
          if((p1[1]-(*j).EndingPoint()[1])*(p1[1]-(*i).StartingPoint()[1])<=0){
            for(auto p = inter.begin(); p != inter.end(); p++){
              if(Improper_Inter.size()==0){Improper_Inter.push_back(*p);}
              else{
                int flag=0;
                for(auto q = Improper_Inter.begin(); q!=Improper_Inter.end();q++){
                  if((*p)==(*q)){ flag=1; break;}
                }
                if(flag==0){Improper_Inter.push_back(*p);}
              }
            }
          }
          if(i==Curve.seg().end()-1){}
          else{ i++;}
        }
      }
    }
    auto num = Improper_Inter.size();
    if(num % 2 ==0){
      return false;
    }
    else{
      return true;
    }
  }
  else{
    return false;
  }
}

bool Ori_IsInclude(const Jordan_Curve<2> &Curve, const Point<double,2> &p1){
  if(OnCurve(Curve,p1)){
    return true;
  }
  else{
    return (Curve.orientation()==1) ? IsInclude(Curve,p1) : !IsInclude(Curve,p1);
  }
}



bool OnCurve(const Jordan_Curve<2> &Curve,const Segment<2> &Segm){
  for(auto i=Curve.seg().begin();i!=Curve.seg().end();i++){
    if(IsInclude(*i,Segm.StartingPoint()) &&
       IsInclude(*i,Segm.EndingPoint())){
      return true;
    }
  }
  return false;
}


bool IsInclude(const Jordan_Curve<2> &Curve,const Segment<2> & Segm){
  if(IsIntersect(Curve,Segm)){
    std::vector<Point<double,2>> Inter=Intersect_Point(Curve,Segm);

    if(Inter.size()>2){
      //  std::cout<<Segm<<std::endl;
      return false;
    }
    else if(Inter.size()==2){
      if(OnCurve(Curve,Segm.StartingPoint()) &&
         OnCurve(Curve,Segm.StartingPoint())){
        Point<double,2> midp{(Segm.StartingPoint()[0]+Segm.EndingPoint()[0])/2,
            (Segm.StartingPoint()[1]+Segm.EndingPoint()[1])/2,};
        if(IsInclude(Curve,midp)){ return true;}
        else{return false;}
      }
      else{
        return false;
      }
    }
    else{
      Point<double,2> p = *(Inter.begin());
      if( p== Segm.StartingPoint()){
        if(IsInclude(Curve,Segm.EndingPoint())){
          return true;
        }
        else{
          //    std::cout<<Segm<<std::endl;
          return false;
        }
      }
      else if( p== Segm.EndingPoint()){
        if(IsInclude(Curve,Segm.StartingPoint())){
          return true;
        }
        else{
          //std::cout<<Segm<<std::endl;
          return false;
        }
      }
      //  std::cout<<Segm<<std::endl;
      return false;
    }
  }
  else{
    if(IsInclude(Curve,Segm.StartingPoint()))
      return true;
    else{
      //std::cout<<Segm<<std::endl;
      return false;
    }
  }
}


bool Ori_IsInclude(const Jordan_Curve<2> &Curve, const Segment<2> &Segm){
  if(OnCurve(Curve,Segm))
    return false;
  else    
    return (Curve.orientation()==1) ?  IsInclude(Curve,Segm)
      : !IsInclude(Curve,Segm);
}

bool IsInclude(const Jordan_Curve<2> &Curve1,const Jordan_Curve<2> & Curve2){
  Point<double,2> pointt = (*(Curve2.seg().begin())).StartingPoint();
  if(IsInclude(Curve1,pointt)){
    return true;
  }
  else{
    return false;
  }
}

bool IsIncomparable(const Jordan_Curve<2> &Curve1, const Jordan_Curve<2> & Curve2){
  if(IsIntersect(Curve1,Curve2) || IsInclude(Curve1,Curve2) ||
     IsInclude(Curve2,Curve1))
    return false;
  else
    return true;
}

//--------------------------------------------


std::vector<Segment<2>> Cut(const Jordan_Curve<2> Curve,
                            std::vector<Point<double,2>> CuttingPoint){
  std::vector<Segment<2>> Edges = Curve.seg();
  for(auto i=CuttingPoint.begin();i!=CuttingPoint.end();i++){
    for(auto j=Edges.begin();j!=Edges.end();j++){
      if(IsInclude(*j,*i)){
        if((*i)==(*j).StartingPoint() || (*i)==(*j).EndingPoint()){}
        else{
          auto p =Edges.insert(j,{{0,0},{0,0}});
          (*p).SetStartPoint((*(p+1)).StartingPoint());
          (*p).SetEndPoint(*i);
          (*(p+1)).SetStartPoint(*i);
          break;
        }
      }
    }
  }
  return Edges;
}




#endif
