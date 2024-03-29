
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);

  // NumberWithUnits a{2, "km"};   // 2 kilometers
  // cout << a << endl;           // Prints "2[km]".
  // cout << (-a) << endl;    // Prints "-2[km]"
  // cout << (3*a) << endl;    // Prints "6[km]"

  // NumberWithUnits b{300, "m"};  // 300 meters
  // cout << (a+b) << endl;   // Prints "2.3[km]". Note: units are determined by first number (a).
  // cout << (b-a) << endl;   // Prints "-1700[m]". Note: units are determined by first number (b).

  // cout << boolalpha; // print booleans as strings from now on:
  // cout << (a>b) << endl;  // Prints "true"
  // cout << (a<=b) << endl;  // Prints "false"
  // cout << (a==NumberWithUnits{2000, "m"}) << endl;  // Prints "true"

  // istringstream sample_input{"700 [ kg ]"};
  // sample_input >> a;
  // cout << a << endl;   // Prints "700[kg]"
  // cout << (a += NumberWithUnits{1, "ton"}) << endl;  // prints "1700[kg]"
  // cout << a << endl;   // Prints "1700[kg]". Note that a has changed.

  // try {
  //   cout << (a+b) << endl;  
  // } catch (const std::exception& ex) {
  //   cout << ex.what() << endl; // Prints "Units do not match - [m] cannot be converted to [kg]"
  // }





NumberWithUnits a1{2, "min"};
NumberWithUnits a2{0, "min"};

cout << "(a1==a2)= "<<(a1==NumberWithUnits{2, "min"}) << endl;
cout << "(a1=!!!=a2)= "<<(a2==a1) << endl;

// NumberWithUnits b1{1, "day"};
// NumberWithUnits b2{23, "hour"};

// cout << "(b1<b2)"<<(b1<b2) << endl;
// cout << "(b1>b2)"<<(b1>b2) << endl;

  cout << "End of demo!" << endl;
  return 0;
}






//make clean && clear && make main && ./main