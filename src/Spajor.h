#ifndef Spajor_h
#define Spajor_h

#include "Atom_Spajor.h"

template<int _Dim>
class Spajor{
public:
  enum{Dim=_Dim};
  using iSegment = Segment<Dim>;
  using iPoint = Point<double,Dim>;
  using JCurve = Jordan_Curve<Dim>;

protected:
  std::vector<JCurve> Curve;
  std::vector<Atom_Spajor<2>> Atom;
public:
  
  Spajor() = default;
  Spajor(std::vector<JCurve> iCurve):Curve{iCurve}{ SetAtom();};

  Spajor<Dim> &operator=(const Spajor<Dim> A){
    Curve = A.Curve;
    Atom = A.Atom;
  }
  
  virtual ~Spajor()=default;

  
  std::vector<JCurve> &curve(){ return Curve;};
  const std::vector<JCurve> &curve() const{ return Curve;};
  void SetCurve(std::vector<JCurve> curve){ Curve = curve;};

  std::vector<Atom_Spajor<2>> &atom(){ return Atom;};
  const std::vector<Atom_Spajor<2>> &atom() const{ return Atom;};
  void SetAtom(std::vector<Atom_Spajor<2>> atom){ Atom = atom;};

  void SetAtom();
  //print for test
  
  friend std::ostream &operator<<(std::ostream &os, const Spajor<Dim> &ASpajor){
    for(auto i=ASpajor.atom().begin();i!=ASpajor.atom().end();i++){
      for(auto j=(*i).curve().begin();j!=(*i).curve().end();j++){
        os<<*j<<std::endl;
      }
      os<<"\n\n"<<std::endl;
    }
    return os;
  }

  friend bool IsCover(const Spajor<2> spajor, const Jordan_Curve<2> curve1,
                      const Jordan_Curve<2> curve2);
};

template<>
void Spajor<2>::SetAtom(){
  Atom ={};
  std::vector<Jordan_Curve<2>> Tmp = Curve;
  while(!Tmp.empty()){
    int flag=0;
    for(auto i=Tmp.begin();i!=Tmp.end();i++){
      flag=0;
      if((*i).orientation()==0){ continue;}
      else{
        flag=1;
        std::vector<Jordan_Curve<2>> curvetmp;
        curvetmp.push_back(*i);
        for(auto j=Tmp.begin();j!=Tmp.end();j++){
          if((*i)==(*j)){ continue;}
          if(IsCover(*this,*i,*j)){
            curvetmp.push_back(*j);
          }
        }
        Atom_Spajor<2> Atomtmp{curvetmp};
        Atom.push_back(Atomtmp);
        for(auto p=curvetmp.begin();p!=curvetmp.end();p++){
          auto q=find(Tmp.begin(),Tmp.end(),*p);
          Tmp.erase(q);
        }
        break;
      }
    }
    if(flag==0){
      std::vector<Jordan_Curve<2>> curvetmp{};
      for(auto i=Tmp.begin();i!=Tmp.end();i++){
        curvetmp.push_back(*i);
      }
      Atom_Spajor<2> Atomtmp{curvetmp};
      Atom.push_back(Atomtmp);
      for(auto p=curvetmp.begin();p!=curvetmp.end();p++){
        auto q=find(Tmp.begin(),Tmp.end(),*p);
        Tmp.erase(q);
      }
    }
  }  
}


bool IsCover(const Spajor<2> spajor, const Jordan_Curve<2> curve1,
             const Jordan_Curve<2> curve2){
  if(IsInclude(curve1,curve2)){
    for(auto i=spajor.curve().begin();i!=spajor.curve().end();i++){
      if((*i)==curve1 || (*i)==curve2){ continue;}
      else{
        if(IsInclude(curve1,*i) && IsInclude(*i,curve2)){
          return false;
        }
      }
    }
    return true;
  }
  else{
    return false;
  }
}


std::vector<Point<double,2>> Intersect_Point(const Spajor<2> spajor1,
                                             const Spajor<2> spajor2){
  std::vector<Point<double,2>> Inters{};
  for(auto i=spajor1.curve().begin();i!=spajor1.curve().end();i++){
    for(auto j=spajor2.curve().begin();j!=spajor2.curve().end();j++){
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
  return Inters;
}




std::vector<Point<double,2>> SelfIntersection(const Spajor<2> spajor){
  std::vector<Point<double,2>> Inters{};
  for(auto i=spajor.curve().begin();i!=spajor.curve().end();i++){
    for(auto j=i+1;j!=spajor.curve().end();j++){
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
  return Inters;
}

std::vector<Segment<2>> Cut(const Spajor<2> spajor,
                            std::vector<Point<double,2>> cuttingpoints){
  std::vector<Segment<2>> Cutting;
  for(auto i=spajor.curve().begin();i!=spajor.curve().end();i++){
    std::vector<Segment<2>> CutSeg = Cut(*i,cuttingpoints);
    Cutting.insert(Cutting.end(),CutSeg.begin(),CutSeg.end());
  }
  return Cutting;
}

std::vector<Segment<2>> Find_in(std::vector<Segment<2>> Edges, Point<double,2> point){
  std::vector<Segment<2>> Inedges{};
  for(auto i=Edges.begin();i!=Edges.end();i++){
    if((*i).EndingPoint() == point){
      Inedges.push_back(*i);
    }
  }
  return Inedges;
}

std::vector<Segment<2>> Find_out(std::vector<Segment<2>> Edges, Point<double,2> point){
  std::vector<Segment<2>> Outedges{};
  for(auto i=Edges.begin();i!=Edges.end();i++){
    if((*i).StartingPoint() == point){
      Outedges.push_back(*i);
    }
  }
  return Outedges;
}

Segment<2> MaxAngleEdge(std::vector<Segment<2>> Edges, Segment<2> edge){
  auto i=Edges.begin();
  double angle = Angle(edge,*i);
  Segment<2> maxx = *i;
  for(i=Edges.begin();i!=Edges.end();i++){
    if(Angle(edge,*i)>angle){
      angle = Angle(edge,*i);
      maxx = *i;
    }
  }
  return maxx;
}

Segment<2> MinAngleEdge(std::vector<Segment<2>> Edges, Segment<2> edge){
  auto i=Edges.begin();
  double angle = Angle(edge,*i);
  Segment<2> minn = *i;
  for(i=Edges.begin();i!=Edges.end();i++){
    if(Angle(edge,*i)<angle){
      angle = Angle(edge,*i);
      minn = *i;
    }
  }
  return minn;
}


Spajor<2> Pasting(std::vector<Point<double,2>> Cuttingpoints,
                  std::vector<Segment<2>> Edges){
  Spajor<2> spajor;

  //S2R-B
  while(!Edges.empty()){
    if(!Cuttingpoints.empty()){
      Point<double,2> v = *(Cuttingpoints.begin());
      std::vector<Segment<2>> v_in = Find_in(Edges,v);
      if(v_in.empty()){
        Cuttingpoints.erase(Cuttingpoints.begin());
        continue;
      }
      else{
        Jordan_Curve<2> Curvetmp;
        Segment<2> inedge = *(v_in.begin());
        Curvetmp.seg().push_back(inedge);
      
        Point<double,2> startp = inedge.StartingPoint();
        std::vector<Segment<2>> v_out = Find_out(Edges,v);
        Segment<2> outedge = MinAngleEdge(v_out,inedge);
        Point<double,2> endp = outedge.EndingPoint();
      
        while(endp != startp){
          Curvetmp.seg().push_back(outedge);
          std::vector<Segment<2>> endp_out=Find_out(Edges,endp);
          outedge = MinAngleEdge(endp_out,outedge);
          endp = outedge.EndingPoint();
        }
        Curvetmp.seg().push_back(outedge);

        //S2R-C
        if(Curvetmp.IsJordanCurve()){
          Curvetmp.SetOrientation();
          spajor.curve().push_back(Curvetmp);
          for(auto i=Curvetmp.seg().begin();i!=Curvetmp.seg().end();i++){
            auto j=find(Edges.begin(),Edges.end(),*i);
            Edges.erase(j);
          }
        }
        else{
          
          std::vector<Point<double,2>> selff = SelfIntersect(Curvetmp);
          while(!selff.empty()){
          
            Jordan_Curve<2> Curvetmpp;
            Point<double,2> pp = *(selff.begin());
            std::vector<Segment<2>> pp_in = Find_in(Curvetmp.seg(),pp);
            if(pp_in.empty()){
              selff.erase(selff.begin());
              continue;
            }
            std::vector<Segment<2>> pp_out = Find_out(Curvetmp.seg(),pp);
          
            Segment<2> pp_inseg = *(pp_in.begin());
            Curvetmpp.seg().push_back(pp_inseg);
          
            Segment<2> pp_outseg = MaxAngleEdge(pp_out,pp_inseg);
            Point<double,2> startpp = pp_inseg.StartingPoint();
            Point<double,2> endpp = pp_outseg.EndingPoint();

            while(endpp != startpp){
              Curvetmpp.seg().push_back(pp_outseg);
              std::vector<Segment<2>> endpp_out = Find_out(Curvetmp.seg(),endpp);
              pp_outseg = MaxAngleEdge(endpp_out,pp_outseg);
              endpp = pp_outseg.EndingPoint();
            }
            Curvetmpp.seg().push_back(pp_outseg);

            Curvetmpp.SetOrientation();
            spajor.curve().push_back(Curvetmpp);
            for(auto i=Curvetmpp.seg().begin();i!=Curvetmpp.seg().end();i++){
              auto j=find(Edges.begin(),Edges.end(),*i);
              auto j1 = find(Curvetmp.seg().begin(),Curvetmp.seg().end(),*i);
              Edges.erase(j); Curvetmp.seg().erase(j1);
            }
          }
        }
      }
    }
    else{
      while(!Edges.empty()){
        Jordan_Curve<2> Curvee;
        auto i=Edges.begin(); Segment<2> firstEdge = *i;
        Point<double,2> firstPoint = firstEdge.StartingPoint();
        Curvee.seg().push_back(firstEdge);
        i++; Segment<2> endEdge = *i;
        Point<double,2> endPoint = endEdge.EndingPoint();
        while(endPoint != firstPoint){
          Curvee.seg().push_back(endEdge);
          i++; endEdge=*i;
          endPoint = endEdge.EndingPoint();
        }
        Curvee.seg().push_back(endEdge);
      
        Curvee.SetOrientation();
        spajor.curve().push_back(Curvee);
        for(auto i=Curvee.seg().begin();i!=Curvee.seg().end();i++){
          auto j=find(Edges.begin(),Edges.end(),*i);
          Edges.erase(j);
        }
      }
    }
  }
  spajor.SetAtom();
  return spajor;
}

Spajor<2> Complementation(Spajor<2> spajor){
  std::vector<Point<double,2>> selfintersect = SelfIntersection(spajor);
  std::vector<Segment<2>> CutEdge = Cut(spajor,selfintersect);
  for(auto i=CutEdge.begin();i!=CutEdge.end();i++){
    (*i).Reverse();
  }
  std::reverse(CutEdge.begin(),CutEdge.end());
  Spajor<2> newspajor = Pasting(selfintersect,CutEdge);
  return newspajor;
}



bool OnSpajor(const Spajor<2> spajor, const Segment<2> Segm){
 for(auto i=spajor.curve().begin();i!=spajor.curve().end();i++){
    for(auto j=(*i).seg().begin();j!=(*i).seg().end();j++){
      if((*j)==Segm){return true;}
    }
  }
 return false;
}
  
bool InSpajor(const Spajor<2> spajor, const Segment<2> Segm){
  for(auto i=spajor.atom().begin();i!=spajor.atom().end();i++){
    if(IsInclude(*i,Segm)){ return true;}
  }
  return false;
}


Spajor<2> Meet(Spajor<2> spajor1, Spajor<2> spajor2){
  std::vector<Point<double,2>> V = Intersect_Point(spajor1,spajor2);
  std::vector<Segment<2>> Edge{};
  
  std::vector<Segment<2>> tmpedge1 = Cut(spajor1,V);
  for(auto i=tmpedge1.begin();i!=tmpedge1.end();i++){
    if(InSpajor(spajor2,*i)|| OnSpajor(spajor2,*i)){
      Edge.push_back(*i);
    }
  }
  std::vector<Segment<2>> tmpedge2 = Cut(spajor2,V);
  for(auto j=tmpedge2.begin();j!=tmpedge2.end();j++){ 
    if(InSpajor(spajor1,*j)){
      Edge.push_back(*j);
    }
  }
  Spajor<2> spajor = Pasting(V,Edge);
  return spajor;
}

Spajor<2> Join(Spajor<2> spajor1, Spajor<2> spajor2){
  Spajor<2> comp1 = Complementation(spajor1);
  Spajor<2> comp2 = Complementation(spajor2);
  Spajor<2> tmp = Meet(comp1,comp2);
  Spajor<2> join = Complementation(tmp);
  return join;
}





#endif
