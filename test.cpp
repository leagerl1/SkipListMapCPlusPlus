#include "Map.hpp"
#include<cassert>
using namespace cs540;

int main(){
  Map<std::string, int> m;
  std::pair<std::string,int> foo;
  std::cout <<"INITIAL SIZE: "<< m.size() << std::endl;
  std::cout<<"IITIALLY EMPTY: " << m.empty() << std::endl;
  m.find("HI");
  foo = std::make_pair("HI",41);
  m.insert(foo);
  m.insert(foo);
  foo = std::make_pair("WE", 7);
  m.insert(foo);
  foo = std::make_pair("A", 33);
  m.insert(foo);
  m.find("HI");
  m.find("HIT");
  m.find("WE");
  m.find("A");
  std::cout << "FINAL SIZE: " <<m.size() << std::endl;
  std::cout<< "FINAL EMPTY: " <<m.empty() << std::endl;
  std::cout<< "A = "<< m["A"] << std::endl;
  m["A"]++;
  std::cout<< "A = "<< m["A"] << std::endl;
  m["B"] = 5;
  std::cout<<  "B = " << m["B"] << std::endl;
  m.print();
  m.rprint();
  Map<std::string, int> m2;
  m2.insert(std::pair<std::string,int>("A", 33));
  //  Map<std::string, int> m3(m);
  std::cout<<"Maps are equal: "<< (m == m) << std::endl;
  std::cout<<"Maps are unequal: "<< (m != m2) << std::endl;
  Map<std::string, int> m4{{"HI",41},{"WE",7},{"A", 34}, {"B",5}};
  Map<std::string, int> m5{{"HI",41},{"WE",7},{"A", 34}, {"B",5}};
  Map<std::string, int> m6{{"HI",41},{"WE",7},{"A", 34}, {"B",5}};
  m4.print();
  m5.print();
  std::cout<<"m5 != m4: "<< (m5 != m4) << std::endl;
  std::cout<<"m5 == m: "<< ( m5 ==m) << std::endl;
  m.clear();
  std::cout << "Empty SIZE: " <<m.size() << std::endl;
  std::cout<< "Empty EMPTY: " <<m.empty() << std::endl;
  m["G"] = 5;
  m["H"] = 3;
  m["I"] = 2;
  m.print();
  m.erase("H");
  m.print();
  /*  for(auto it = m.rbegin(); it != m.rend(); it++){
    std::cout<< it->first << std::endl;
    }*/
  return 0;
}
