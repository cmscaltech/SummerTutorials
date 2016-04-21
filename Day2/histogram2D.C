//////////////////////////////////////////////////////////////////////////
// Caltech SURF Tutorial 2
// histogram2D.C
//
// Inspired from
// $ROOTSYS/tutorials/tree/basic.C
//
// 05/2013 - Javier Duarte
/////////////////////////////////////////////////////////////////////////
#include "Riostream.h"
void histogram2D()
{
   ifstream in;
   in.open("basic.dat");

   Float_t x,y,z;
   Int_t nlines = 0;
   TFile *f = new TFile("histogram2D.root","RECREATE");
   TH2F* histo2d = new TH2F("histo2D","2D histogram", 50, -5, 5, 50, -5, 5);
   while (true) {
      in >> x >> y >> z;
      if (!in.good()) break;
      if (nlines < 5) printf("x=%8f, y=%8f, z=%8f\n",x,y,z);
      histo2D->Fill(x,y);
      nlines++;
   }
   
   TCanvas *c = new TCanvas("c","canvas",600,500);
   histo2D->Draw("colz");

   f->cd();
   histo2D->Write();
}
