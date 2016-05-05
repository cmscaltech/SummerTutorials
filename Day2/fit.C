//////////////////////////////////////////////////////////////////////////
// Caltech SURF Tutorial 2
// fit.C
//
// Inspired from
// $ROOTSYS/tutorials/tree/basic.C
//
// 05/2013 - Javier Duarte
/////////////////////////////////////////////////////////////////////////
#include "Riostream.h"
void fit()
{

  gStyle->SetOptFit(1);
  TFile* file = TFile::Open("tree.root","read");
  TTree* tree = (TTree*) file->Get("tree");

  
  TH1F* histo_x = new TH1F("histo_x","histo_x", 50, -5, 5);  
  TH1F* histo_y = new TH1F("histo_y","histo_y", 50, -5, 5);  
  TH1F* histo_z = new TH1F("histo_z","histo_z", 50, 0, 20);
  TH2F* histo_xyz = new TH2F("histo_xyz","histo_xyz", 50, -5, 5, 50, -5, 5);
  tree->Project("histo_x","x");
  tree->Project("histo_y","y");
  tree->Project("histo_z","z");
  tree->Project("histo_xyz","y:x","z");

  TCanvas *c = new TCanvas("c","canvas",600,500);
  c->Divide(2,2);
  c->cd(1);
  histo_x->Draw("");
  histo_x->Fit("gaus");
  c->cd(2);
  histo_y->Draw("");
  histo_y->Fit("gaus");
  c->cd(3);
  histo_xyz->Draw("colz");
  c->cd(4);
  histo_z->Draw("");
  TF1* chi2pdf = new TF1("chi2pdf", "[0]*ROOT::Math::chisquared_pdf(x,[1])",0,20);
  chi2pdf->SetParameter(0,200);
  chi2pdf->SetParameter(1,2);
  histo_z->Fit("chi2pdf");
  c->Print("c.pdf");  
   
}
