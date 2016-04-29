#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
#include <TSystem.h>                      // interface to OS
#include <TFile.h>                        // file handle class
#include <TTree.h>                        // class to access ntuples
#include <TH1F.h>                         // histograms containing floats
#include <TCanvas.h>                      // class for ROOT drawing canvases
#include <vector>                         // STL vector class
#include <iostream>                       // standard I/O
#include <iomanip>                        // functions to format standard I/O
#include <fstream>                        // functions for file I/O
#include <string>                         // C++ string class
#include <sstream>                        // class for parsing strings
#endif

void tutorial1() {

  cout << "Hello world!" << endl;

  ifstream in; 
  in.open("basic.dat");

  TFile *f = new TFile("output.root","recreate");

  TH1F *h = new TH1F("hist", "1D hist", 100, -5, 5);

  float x;
  while (true) {
    if (!in.good()) {
      break;
    }
    in >> x;
    //cout << x << endl;
    h->Fill(x);
  }

  TCanvas *c = new TCanvas("c", "canvas",800, 600);

  h->Draw();

  c->SaveAs("tutorial1.png");
  f->Write();
  f->Close();
}
