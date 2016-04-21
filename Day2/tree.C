//////////////////////////////////////////////////////////////////////////
// Caltech SURF Tutorial 3
// tree.C
//
// Inspired from
// $ROOTSYS/tutorials/tree/tree1.C
//
// 05/2013 - Javier Duarte
/////////////////////////////////////////////////////////////////////////
#include "Riostream.h"
void tree()
{
   ifstream in;
   in.open("basic.dat");

   Float_t x,y,z;
   Int_t nlines = 0;

   //create the file, the Tree and a few branches
   TFile f("tree.root","recreate");
   TTree tree("tree","a simple Tree with simple variables");
   Int_t ev;
   Float_t d;
   tree.Branch("x",&x,"x/F");
   tree.Branch("y",&y,"y/F");
   tree.Branch("z",&z,"z/F");
   tree.Branch("ev",&ev,"ev/I");

   while (true) {
      in >> x >> y >> z;
      if (!in.good()) break;
      if (nlines < 5) printf("x=%8f, y=%8f, z=%8f\n",x,y,z);
      ev = nlines;

      tree.Fill();
      nlines++;
   }
   
   f->cd();
   tree->Write();
}
