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

  // Crystal Ball parameters
  RooRealVar cbBias ("cbBias", "CB Bias", -.5, -10, 10);
  RooRealVar cbSigma("cbSigma", "CB Width", 5.7, 0.02, 10.0);
  RooRealVar cbCut  ("cbCut","CB Cut",1.05, 0.1, 3.0);                              
  RooRealVar cbPower("cbPower","CB Order", 2.45, 0.1, 20.0);

  // Breit Wigner parameters
  RooRealVar bwMean("mZ","BW Mean", 91.1876, 80, 100);
  RooRealVar bwWidth("GammaZee", "BW Width", 2.4952, 0, 10);

  // Fix the Breit-Wigner parameters to PDG values
  // bwMean.setConstant(kTRUE);
  // bwWidth.setConstant(kTRUE);
                                                                                                    
  // Construct pdfs
  RooBreitWigner bw("bw", "bw", mee, bwMean, bwWidth);
  RooCBShape  cball("cball", "Crystal Ball", mee, cbBias, cbSigma, cbCut, cbPower);
  RooFFTConvPdf model("model", "bw X crystal ball", mee, bw, cball);

  // Open File, retrieve Tree
  TFile *file = TFile::Open("treeArray.root");
  TTree *tree = (TTree*)file->Get("tree");
    
  // Create dataset
  RooDataSet *data = new RooDataSet("data","invariant mass(e+e-) data", RooArgSet(mee),Import(*tree));
  
  // Fit
  // Using BW only:
  // RooFitResult* rf = bw.fitTo(*data,Save());
  RooFitResult* rf = model.fitTo(*data,Save());
  rf->Print("v");

  // Plot
  TCanvas* c = new TCanvas("c","c",500,500);
  RooPlot* frame = mee.frame();
  data->plotOn(frame);
  // Using BW only:
  // bw.plotOn(frame);
  model.plotOn(frame);
  frame->Draw();
  c->Print("Zee.pdf");
}
