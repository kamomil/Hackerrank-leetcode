#include <unordered_map>
#include <iostream>

//Factory example based on https://www.codeproject.com/Articles/363338/Factory-Pattern-in-Cplusplus
class Shape
{
public:
  virtual void print(void) = 0;
  virtual ~Shape(void)=0;//this is mandatory for the destructor of the derivatives to be called
};
Shape::~Shape(){}//see https://www.geeksforgeeks.org/pure-virtual-destructor-c/

class Line : public Shape
{
public:
  Line()
  {
    std::cout << "Line ctor\n";
  }
  ~Line()
  {
    std::cout << "Line dtor\n";
  }
  void print(){std::cout << "----------\n";}

  static Shape* Create() { std::cout<<"line create\n"; return new Line(); }

};

class Point : public Shape
{
public:
  Point()
  {
    std::cout << "Point ctor\n";
  }

  static Shape* Create() { return new Point(); }

  ~Point()
  {
    std::cout << "Point dtor\n";
  }
  void print(){std::cout << ".\n";}

};


template<class T>
class Factory
{

private:
  std::unordered_map<int,T (*)(void)> objects;

public:
  void regist(int id, T (*create)(void)){
    objects[id] = create;
  }

  T produce(int id){
    return objects[id]();
  }
};

Shape* get_point(){return new Point();}
int main()
{

  Factory<Shape*> f;

  f.regist(1,Point::Create);
  f.regist(2,Line::Create);

  Shape* s1 = f.produce(1);
  Shape* s2 = f.produce(2);
  s1->print();
  s2->print();
  delete s1;//Note!! this does not work, the constructors are not called !
  delete s2;
  Point* p = new Point();
  delete p;

  Shape* pp = get_point();
  delete pp;

  //s1->print();
  return 0;
}
