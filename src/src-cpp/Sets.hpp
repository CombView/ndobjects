
#ifndef NDOBJECTS_SETS_HPP
#define NDOBJECTS_SETS_HPP

#include <algorithm>
#include <cstdarg>
#include <iostream>
#include <sstream>
#include <vector>


#include "Native.hpp"
#include "Util.hpp"

using namespace std;

namespace combview {

/*
 The "same" structure in combview can mean different things on ndobjects programming library.

 Declaration typically indicates the most specific implementation.

 Example:
 - set<index> := {0..9};
    - CSet a set of consecutive elements, of Index type, indexed as 0..card-1 (card=10)
 - set<index> := {10..19};
    - CSet a set of consecutive elements, of Index type, indexed as 10..19 (card=10)
 - set<index> := {1,3,5,7,9};
    - GSet<Index> a general set of Index type, indexed for each of the values (card=5)
*/


// interface for a combview "set<$x>"
// it must satisfy the ndobjects "cv_set" concept
template<class X>
class ISet : public NDObject
{
public:
   // element 'e' of type 'X' in set or not
   virtual bool in(const X& e) const = 0;

   // cardinality (number of elements) of set
   virtual Index card() const = 0;

   //virtual string toString() const = 0;

   //virtual void print() const = 0;
};



// no need to pass template parameters here... 
// keep it stack (compatibility between CSet classes)
// contiguous set
class CSet : public ISet<Index>
{
public:
   Index min;
   Index max;

   CSet(Index _min, Index _max) :
      min(_min), max(_max)
   {
   }

   bool in(const Index& e) const override
   {
      return e>=min && e<=max;
   }

   Index card() const override
   {
      // allowing min > max... empty set.
      return (min>=max)?0:max-min+1;
   }

   string toString() const override
   {
      stringstream ss;
      ss << "CSet(min=" << min << ";" << "max=" << max << ")";
      return ss.str();
   }
};



// set of $X

// general set

template<class X>
class GSet : public ISet<X>
{
public:
   vector<uptr<X>> elements;

   // TODO: could accept something with reference types,
   //   and create uptr inside here.

   GSet(vector<uptr<X>>&& _elements) :
      elements(std::move(_elements))
   {
   }

   bool in(const X& x) const override
   {
      for (const uptr<X>& k : elements)
         if (x == *k)
            return true;
      return false;
   }

   Index card() const override
   {
      return elements.size();
   }

   virtual ~GSet()
   {
   }

   string toString() const override
   {
      stringstream ss;
      ss << "GSet({";
      for(unsigned i=0; i< ((int)elements.size())-1; i++)
         ss << *elements[i] << ",";
      if(elements.size() > 0)
         ss << *elements[elements.size()-1];
      ss << "})";
      return ss.str();
   }
};

} // namespace combview

#endif // NDOBJECTS_SETS_HPP