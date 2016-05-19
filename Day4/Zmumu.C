//////////////////////////////////////////////////////////////////////////
// Caltech SURF Tutorial 4
// Zmumu.C
//
// See http://arxiv.org/pdf/hep-ex/0509008.pdf
// and http://pdg.lbl.gov/2012/reviews/rpp2012-rev-light-neutrino-types.pdf
// 
// Determining the number of light neutrinos
//
// 06/2013 - Javier Duarte
/////////////////////////////////////////////////////////////////////////
using namespace RooFit ;

void Zmumu()
{
  // Create observables
  RooRealVar mMuMu("mMuMu","mass(mu+mu-)",60,120) ;

  // Open File, retrieve Tree
  TFile *file = TFile::Open("treeArray.root");
  TTree *tree = (TTree*)file->Get("tree");
    
  // Create dataset
  RooDataSet *data = new RooDataSet("data","invariant mass(mu+mu-) data", RooArgSet(mMuMu),Import(*tree));
  

  // Plot
  TCanvas* c = new TCanvas("c","c",500,500);
  RooPlot* frame = mMuMu.frame();
  data->plotOn(frame);
  frame->Draw();
  c->Print("Zmumu.pdf");
}
