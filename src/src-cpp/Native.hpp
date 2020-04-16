
#ifndef NDOBJECTS_NATIVE_HPP
#define NDOBJECTS_NATIVE_HPP

#include "Util.hpp"

using namespace std;

namespace combview {

class NDObject
{
public:
   virtual string toString() const = 0;

   virtual void print() const final
   {
      std::cout << toString() << std::endl;
   }
};

// named constrained tuple
class NamedCTuple : public NDObject
{
public:
   string name;
};

// should native types inherit from NDObject ?
// we need to keep higher possible performance here.

class Integer : public NDObject
{
public:
   int value;
};

// ===========================
//           Index
// ===========================
// [combview] # type index = integer i | i >= 0; # theoretical
// [combview]   type index = native;             # favoring 'native' version
typedef unsigned Index; // uint32

// ===========================

} // namespace combview

#endif // NDOBJECTS_NATIVE_HPP