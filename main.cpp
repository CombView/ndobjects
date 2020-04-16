// TODO: delete this file!
// should only rely on tests/ for basic testing

#include <iostream>

#include "src/src-cpp/Arrays.hpp"
#include "src/src-cpp/Sets.hpp"

using namespace combview;
using namespace std;

int
main()
{
   cout << "main(): NDObjects basic testing" << endl;
   //
   // [combview] set<index> : set1 := {0..9};
   CSet set1(0, 9);
   set1.print(); // CSet(min=0;max=9)
   //
   // [combview] index: szset1 := card(set1);     # 10 (global function 'card')
   cout << set1.card() << endl;
   //
   // [combview] boolean: b := in(7, set1);       # true (global function 'in')
   cout << set1.in(7) << endl;
   // [combview] boolean: b := in(0, set1);       # true (global function 'in')
   cout << set1.in(0) << endl;
   // [combview] boolean: b := in(9, set1);       # true (global function 'in')
   cout << set1.in(9) << endl;
   // [combview] boolean: b := in(10, set1);      # false (global function 'in')
   cout << set1.in(10) << endl;
   // [combview] boolean: b := in(-1, set1);
   //  # should throw interpretation (or execution) error in combview (filter error on 'index')
   //  # on ndobjects, due to runtime verifications (or not) on native types, it will just be 'false'
   cout << set1.in(-1) << endl;
   // [combview] set<index> : set2 := {2..5};
   CSet set2(2, 5);
   set2.print(); // CSet(min=2;max=5)
   // [combview] index: szset2 := card(set2);     # 4 (global function 'card')
   cout << set2.card() << endl;
   //
   // [combview] set<index> : set3 := {3,5,7,9};
   vector<uptr<Index>> vset3; // initializer list not working, unfortunately (will C++20 fix this?)
   vset3.push_back(uptr<Index>(new Index(3)));
   vset3.push_back(uptr<Index>(new Index(5)));
   vset3.push_back(uptr<Index>(new Index(7)));
   vset3.push_back(uptr<Index>(new Index(9)));
   //
   GSet set3(std::move(vset3));
   set3.print(); // GSet({3,5,7,9})
   //
   // [combview] index: szset3 := card(set3);     # 3 (global function 'card')
   cout << set3.card() << endl;
   // [combview] boolean: b := in(7, set3);       # true (global function 'in')
   cout << set3.in(7) << endl;
   // [combview] boolean: b := in(6, set3);       # false (global function 'in')
   cout << set3.in(6) << endl;
   //
   // [combview] array<index> : array1 := [3,5,7,9];
   vector<uptr<Index>> varray1; // initializer list not working, unfortunately (will C++20 fix this?)
   varray1.push_back(uptr<Index>(new Index(3)));
   varray1.push_back(uptr<Index>(new Index(5)));
   varray1.push_back(uptr<Index>(new Index(7)));
   varray1.push_back(uptr<Index>(new Index(9)));
   //
   ZArray array1(std::move(varray1));
   array1.print(); // ZArray([3,5,7,9])
   // [combview] index: szarray1 := size(array1);  # 4 (global function 'size')
   cout << array1.size() << endl;
   // [combview] index: b := at(0, array1);        # 3 (global function 'at')
   cout << array1.get(0) << endl;
   // [combview] index: b := at(3, array1);        # 9 (global function 'at')
   cout << array1.get(3) << endl;
   //

   cout << "finished successfully" << endl;
   return 0;
}