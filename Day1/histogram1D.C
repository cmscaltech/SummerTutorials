//////////////////////////////////////////////////////////////////////////
// Caltech SURF Tutorial 1
// histogram1D.C
//
// Inspired from
// $ROOTSYS/tutorials/tree/basic.C
//
// 05/2013 - Javier Duarte
/////////////////////////////////////////////////////////////////////////
#include "Riostream.h"
void histogram1D()
{
   ifstream in;
   in.open("basic.dat");

   Float_t x,y,z;
   Int_t nlines = 0;
   TFile *f = new TFile("histogram1D.root","RECREATE");
   TH1F* histo1d = new TH1F("histo1D","1D histogram", 100, -5, 5);
   while (true) {
      in >> x >> y >> z;
      if (!in.good()) break;
      if (nlines < 5) printf("x=%8f, y=%8f, z=%8f\n",x,y,z);
      histo1D->Fill(x);
      nlines++;
   }
   
   TCanvas *c = new TCanvas("c","canvas",600,500);
   histo1D->Draw();

   f->cd();
   histo1D->Write();
}
