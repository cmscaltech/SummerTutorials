//////////////////////////////////////////////////////////////////////////
// Caltech SURF Tutorial 2
// tutorial2.C
//
// Inspired from
// $ROOTSYS/tutorials/tree/basic.C
//
// 05/2013 - Javier Duarte
/////////////////////////////////////////////////////////////////////////
#include "Riostream.h"
void tutorial2()
{
   ifstream in;
   in.open("basic.dat");

   Float_t x,y,z;
   Int_t nlines = 0;
   while (true) {
      in >> x >> y >> z;
      if (!in.good()) break;
      if (nlines < 5) printf("x=%8f, y=%8f, z=%8f\n",x,y,z);
      nlines++;
   }
   
}
