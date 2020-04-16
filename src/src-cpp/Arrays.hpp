
#ifndef NDOBJECTS_ARRAYS_HPP
#define NDOBJECTS_ARRAYS_HPP

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
 - array<index> := [3,4,5,6];
    - ZArray a zero-index array of consecutive elements, of Index type, indexed as 0..size-1 (size=4)
 - iarray<M, index> := [3,5,7,9]; # given M := {1..4}
    - MArray an array of Index type with mapped indexes to set M, indexed as 1..4 (size=4)
 - matrix<2, index> := [[1,2,3],[4,5,6]];
    - Array with two dimensions (TODO)
*/


// interface for a combview "set<$x>"
// it must satisfy the ndobjects "cv_set" concept
template<class X>
class IArray : public NDObject
{
public:
   // element at position 'pos' of type 'X'
   virtual X& get(Index pos) const = 0;

   // number of elements of set
   virtual Index size() const = 0;

   //virtual string toString() const = 0;

   //virtual void print() const = 0;
};


// zero-index Array
template<class X>
class ZArray : public IArray<X>
{
public:
   vector<uptr<X>> sequence;

   // TODO: could accept something with reference types,
   //   and create uptr inside here.

   ZArray(vector<uptr<X>>&& _sequence) :
      sequence(std::move(_sequence))
   {
   }

   X& get(Index pos) const override
   {
      return *sequence[pos];
   }

   Index size() const override
   {
      return sequence.size();
   }

   virtual ~ZArray()
   {
   }

   string toString() const override
   {
      stringstream ss;
      ss << "ZArray([";
      for(unsigned i=0; i< ((int)sequence.size())-1; i++)
         ss << *sequence[i] << ",";
      if(sequence.size() > 0)
         ss << *sequence[size()-1];
      ss << "])";
      return ss.str();
   }
};

} // namespace combview


// ======================== TODO: review =======================

namespace old_combview
{


// array of $X
template<class X>
class Array
{
public:
   vector<X*> elements;
   vector<unsigned> dimensions;

   Array(unsigned dim)
   {
      dimensions = vector<unsigned>(dim, 0);
   }

   X& get(const unsigned numargs, ...) const
   {
      va_list arguments;
      va_start(arguments, numargs);
      unsigned val = 0;
      for (int i = 0; i < numargs; i++) {
         val = va_arg(arguments, unsigned);
      }

      va_end(arguments);

      return *elements[val];
   }
};

// sequence of $X
template<class X>
class Sequence : public Array<X>
{
public:
   Sequence()
     : Array<X>(1)
   {
   }

   X& at(unsigned pos) const
   {
      return this->get(1, pos);
   }

   unsigned size() const
   {
      return this->dimensions[0];
   }
};

// matrix2 of $X
template<class X>
class Matrix2 : public Array<X>
{
public:
   Matrix2()
     : Array<X>(2)
   {
   }

   X& at(unsigned i, unsigned j) const
   {
      return this->get(2, i, j);
   }

   unsigned rows() const
   {
      return this->dimensions[0];
   }

   unsigned cols() const
   {
      return this->dimensions[1];
   }
};

} // old_combview

#endif // NDOBJECTS_ARRAYS_HPP