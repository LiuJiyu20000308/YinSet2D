#ifndef AtomSpajor_h
#define AtomSpajor_h

#include "Jordan_Curve.h"

template<int _Dim>
class Atom_Spajor{
public:
  enum{Dim=_Dim};
  using iSegment = Segment<Dim>;
  using iPoint = Point<double,Dim>;
  using JCurve = Jordan_Curve<Dim>;

protected:
  std::vector<JCurve> Curve;
  
public:
  
  Atom_Spajor() = default;
  Atom_Spajor(std::vector<JCurve> iCurve):Curve{iCurve}{ };

  Atom_Spajor<Dim> &operator=(const Atom_Spajor<Dim> A){
    Curve = A.Curve;
  }
  
  virtual ~Atom_Spajor()=default;

  
  std::vector<JCurve> &curve(){ return Curve;};
  const std::vector<JCurve> &curve() const{ return Curve;};
  void SetCurve(std::vector<JCurve> curve){ Curve = curve;};
  
  //print for test
  
  friend std::ostream &operator<<(std::ostream &os,
                                  const Atom_Spajor<Dim> &AAtom_Spajor){
    for(auto i=AAtom_Spajor.curve().begin();i!=AAtom_Spajor.curve().end();i++){
      os<<*i<<std::endl;
    }
    return os;
  }
};


bool IsInclude(const Atom_Spajor<2> spajor, const Segment<2> segm){
  for(auto i=spajor.curve().begin();i!=spajor.curve().end();i++){
    if(!Ori_IsInclude(*i,segm)){
      return false;
    }
  }
  return true;
}

#endif
