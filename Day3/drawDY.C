{

  const Double_t MUON_MASS = 0.105658369;

  TFile *f = new TFile("DY_tutorial.root");
  TTree *t = (TTree*) f->Get("ntuples/RazorEvents");

  UInt_t          eventNum;
  Int_t           nMuons;
  Float_t         muonE[40];   //[nMuons]
  Float_t         muonPt[40];   //[nMuons]
  Float_t         muonEta[40];   //[nMuons]
  Float_t         muonPhi[40];   //[nMuons]
  Int_t           muonCharge[40];   //[nMuons]

  t->SetBranchAddress("eventNum",   &eventNum);
  t->SetBranchAddress("nMuons",     &nMuons);
  t->SetBranchAddress("muonE",      muonE);
  t->SetBranchAddress("muonPt",     muonPt);
  t->SetBranchAddress("muonEta",    muonEta);
  t->SetBranchAddress("muonPhi",    muonPhi);
  t->SetBranchAddress("muonCharge", muonCharge);

  TH1D *hNumMuons = new TH1D("hNumMuons","hNumMuons",5,0,5);

  TH1D *hPtMuons = new TH1D("hPtMuons", "hPtMuons",10,0,50);
  TH1D *hEtaMuons = new TH1D("hEtaMuons", "hEtaMuons",10,-5,5);
  TH1D *hPhiMuons = new TH1D("hPhiMuons", "hPhiMuons",6,-3,3);

  TH1D *hZMass = new TH1D("hZMass", "hZMass", 30,60,120);

  for (Int_t i=0; i<t->GetEntries(); i++) {
    t->GetEntry(i);

  }

  /*TCanvas *c1 = new TCanvas ("c", "c", 800, 600);

  hNumMuons->SetTitle("");
  hNumMuons->GetXaxis()->SetTitle("# of muons");
  hNumMuons->GetYaxis()->SetTitle("Events");
  hNumMuons->GetYaxis()->SetRangeUser(0, 1.2*hNumMuons->GetMaximum());
  hNumMuons->Draw("");
  c1->SaveAs("num_muons.png");

  hPtMuons->SetTitle("");
  hPtMuons->GetXaxis()->SetTitle("muon p_{T}");
  hPtMuons->GetYaxis()->SetTitle("Events");
  hPtMuons->GetYaxis()->SetRangeUser(0, 1.2*hPtMuons->GetMaximum());
  hPtMuons->Draw("");
  c1->SaveAs("muon_pt.png");

  hEtaMuons->SetTitle("");
  hEtaMuons->GetXaxis()->SetTitle("muon #eta");
  hEtaMuons->GetYaxis()->SetTitle("Events");
  hEtaMuons->GetYaxis()->SetRangeUser(0, 1.2*hEtaMuons->GetMaximum());
  hEtaMuons->Draw("");
  c1->SaveAs("muon_eta.png");

  hPhiMuons->SetTitle("");
  hPhiMuons->GetXaxis()->SetTitle("muon #phi");
  hPhiMuons->GetYaxis()->SetTitle("Events");
  hPhiMuons->GetYaxis()->SetRangeUser(0, 1.2*hPhiMuons->GetMaximum());
  hPhiMuons->Draw("");
  c1->SaveAs("muon_phi.png");
  
  hZMass->SetTitle("");
  hZMass->GetXaxis()->SetTitle("m_Z");
  hZMass->GetYaxis()->SetTitle("Events");
  hZMass->GetYaxis()->SetRangeUser(0, 1.2*hZMass->GetMaximum());
  hZMass->Draw("");
  c1->SaveAs("z_mass.png");*/

}
