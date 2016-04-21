//////////////////////////////////////////////////////////////////////////
// Caltech SURF Tutorial 5
// twobells.C
//
// Inspired from
// 'MULTIDIMENSIONAL MODELS' RooFit tutorial macro #316
// 
// Computing CLs to determine if one can exclude a particular 
// signal+background model from a background-only model
//
// 07/2008 - Wouter Verkerke 
// 05/2012 - Javier Duarte
/////////////////////////////////////////////////////////////////////////
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
using namespace RooFit ;

const Int_t nToys = 50;
void twobells()
{
  RooRandom::randomGenerator()->SetSeed(314159);
  // C r e a t e   1 D   p d f   a n d   d a t a 
  // -------------------------------------------

  // Create observables
  RooRealVar x("x","x",-5,5) ;
  RooRealVar mean("mean","mean",0,-1,1);
  RooRealVar std("std","std",1,0,2);
  RooRealVar c1("c1","c1",-0.1,-1,1);
  RooRealVar c2("c2","c2",0.004,-1,1);


  // Create signal pdf gauss(x)
  RooGaussian sig("sig","sig",x,mean,std) ;

  // Create background pdf poly(x)
  RooPolynomial bkg("bkg","bkg",x,RooArgSet(c1,c2)) ;

  // Create composite pdf sig+bkg
  RooRealVar fsig("fsig","signal fraction",0.02,0.,1.) ;
  RooAddPdf sigbkg("sigbkg","sigbkg",RooArgList(sig,bkg),fsig);

  fsig.setVal(0);
  RooDataSet* data = sigbkg.generate(RooArgSet(x),20000) ;
  fsig.setVal(0.02);

  // P r o j e c t   p d f   a n d   d a t a   o n   x
  // -------------------------------------------------

  // Make plain projection of data and pdf on x observable
  RooPlot* frame = x.frame(Title("sig+bkg"),Bins(40)) ;
  data->plotOn(frame) ;
  RooFitResult* sigbkg_data = sigbkg.fitTo(*data,Save()) ;
  sigbkg.plotOn(frame,LineColor(kRed)) ;
  sigbkg.plotOn(frame,Components("bkg"),LineStyle(kDashed),LineColor(kBlue)) ;
  Double_t sigbkg_data_Nll = sigbkg_data->minNll();

  RooPlot* frame2 = x.frame(Title("bkg-only"),Bins(40)) ;
  data->plotOn(frame2) ;
  RooFitResult* bkg_data = bkg.fitTo(*data,Save()) ;
  bkg.plotOn(frame2,LineColor(kBlue)) ;  
  Double_t bkg_data_Nll = bkg_data->minNll();
  

  RooArgSet* sigbkgParams = sigbkg.getParameters(*data) ; 
  RooArgSet* bkgParams = bkg.getParameters(*data) ; 

  RooArgList& fitSigbkgParams = sigbkg_data->floatParsFinal();
  RooArgList& fitBkgParams = bkg_data->floatParsFinal();
  
  Double_t Lz_bkg_array[nToys];
  Double_t Lz_sigbkg_array[nToys];
  TH1D* Lz_bkg = new TH1D("Lz_bkg","Lz_bkg",100,-40,40);
  TH1D* Lz_sigbkg = new TH1D("Lz_sigbkg","Lz_sigbkg",100,-40,40);
  Double_t Lz_data = -2*(bkg_data_Nll - sigbkg_data_Nll);

  for (Int_t i = 0; i<nToys; i++){
    c1.setConstant(kFALSE);
    c2.setConstant(kFALSE);
    mean.setConstant(kFALSE);
    std.setConstant(kFALSE);
    fsig.setConstant(kFALSE);
    RooArgList& ranSigbkgParams = sigbkg_data->randomizePars();
    *sigbkgParams = ranSigbkgParams;

    RooDataSet* toysigbkg = sigbkg.generate(RooArgSet(x),20000) ;

    RooArgList& ranBkgParams = bkg_data->randomizePars();
    *bkgParams = ranBkgParams;

    RooDataSet* toybkg = bkg.generate(RooArgSet(x),20000) ;

    *sigbkgParams = fitSigbkgParams;
    c1.setConstant(kTRUE);
    c2.setConstant(kTRUE);
    mean.setConstant(kTRUE);
    std.setConstant(kTRUE);
    fsig.setConstant(kTRUE);
    RooFitResult* sigbkg_toybkg = sigbkg.fitTo(*toybkg,Save());
    Double_t sigbkg_toybkg_Nll = sigbkg_toybkg->minNll();
    RooFitResult* sigbkg_toysigbkg = sigbkg.fitTo(*toysigbkg,Save());
    Double_t sigbkg_toysigbkg_Nll = sigbkg_toysigbkg->minNll();

    *bkgParams = fitBkgParams;
    c1.setConstant(kTRUE);
    c2.setConstant(kTRUE);
    mean.setConstant(kTRUE);
    std.setConstant(kTRUE);
    fsig.setConstant(kTRUE);
    RooFitResult* bkg_toybkg = bkg.fitTo(*toybkg,Save());
    Double_t bkg_toybkg_Nll = bkg_toybkg->minNll();
    RooFitResult* bkg_toysigbkg = bkg.fitTo(*toysigbkg,Save());
    Double_t bkg_toysigbkg_Nll = bkg_toysigbkg->minNll();

    Lz_bkg_array[i] = -2.*(bkg_toybkg_Nll - sigbkg_toybkg_Nll);
    Lz_sigbkg_array[i] = -2.*(bkg_toysigbkg_Nll - sigbkg_toysigbkg_Nll);

    //Clean up objects
    bkg_toysigbkg.Delete();
    bkg_toybkg.Delete();
    sigbkg_toysigbkg.Delete();
    sigbkg_toybkg.Delete();
    toybkg.Delete();
    toysigbkg.Delete();
    // delete bkg_toysigbkg;
    // delete bkg_toybkg;
    // delete sigbkg_toysigbkg;
    // delete sigbkg_toybkg;
    // delete toybkg;
    // delete toysigbkg;
  }
  
  for (Int_t i = 0; i<nToys;i++)
    {
      //Fill histograms
      Lz_bkg->Fill(Lz_bkg_array[i]);
      Lz_sigbkg->Fill(Lz_sigbkg_array[i]);
    }

  TCanvas* c = new TCanvas("models","models",800,400) ;
  c->Divide(2) ;
  c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; frame->Draw() ;
  c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;

  TCanvas* d = new TCanvas("twobells","twobells",800,400) ;
  //Normalize bells
  Lz_bkg->Scale(1.0/Lz_bkg->Integral());
  Lz_sigbkg->Scale(1.0/Lz_sigbkg->Integral());
  //Plot bells
  gStyle->SetOptStat(0000);
  Lz_bkg->SetTitle("");
  Lz_bkg->SetXTitle("-2log[L(s+b)/L(b)]");
  Lz_bkg->SetLineWidth(2);
  Lz_sigbkg->SetLineColor(kRed);
  Lz_sigbkg->SetLineWidth(2);
  Lz_bkg->Draw("hist");  Lz_sigbkg->Draw("histsame");

  //Make line from data ``critical value Lz''
  TLine* line = new TLine(Lz_data,0,Lz_data,0.075);
  line->SetLineColor(kBlack);
  line->SetLineWidth(2);
  line->Draw("lsame");

  //Calculate CLs

  Int_t dataBin = Lz_sigbkg->FindBin(Lz_data);
  Int_t numBins = Lz_sigbkg->GetNbinsX();
  Double_t CLsb = Lz_sigbkg->Integral(dataBin,numBins);
  Double_t CLb = Lz_bkg->Integral(dataBin,numBins);
  Double_t CLs = 1.0;
  if (CLb!=0.0)  CLs = CLsb/CLb;
 
  cout << "\n CLs = " << CLs << endl;

  leg = new TLegend(0.7,0.7,0.9,0.9);
  leg->AddEntry("Lz_bkg","bkg toys","l");
  leg->AddEntry("Lz_sigbkg","sig+bkg toys","l");
  leg->AddEntry("line","data","l");
  leg->SetFillColor(kWhite);
  leg->Draw();
}
