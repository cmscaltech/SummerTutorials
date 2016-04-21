//////////////////////////////////////////////////////////////////////////
// Caltech SURF Tutorial 4
// Zee.C
//
// See http://arxiv.org/pdf/hep-ex/0509008.pdf
// and http://pdg.lbl.gov/2012/reviews/rpp2012-rev-light-neutrino-types.pdf
// 
// Determining the number of light neutrinos
//
// 06/2013 - Javier Duarte
/////////////////////////////////////////////////////////////////////////
using namespace RooFit ;

void Zee()
{
  // Create observables
  RooRealVar mee("mee","mass(e+e-)",60,120) ;
  
  // Open File, retrieve Tree
  TFile *file = TFile::Open("treeArray.root");
  TTree *tree = (TTree*)file->Get("tree");
  
  // Create dataset
  RooDataSet *data = new RooDataSet("data","invariant mass(e+e-) data", RooArgSet(mee),Import(*tree));

  // Plot
  TCanvas* c = new TCanvas("c","c",500,500);
  RooPlot* frame = mee.frame();
  data->plotOn(frame);
  frame->Draw();
  c->Print("Zee.pdf");
}
