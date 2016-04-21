#define RazorAnalyzer_cxx
#include "RazorAnalyzer.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"

using namespace std;

void RazorAnalyzer::DummyAnalysis()
{
    if (fChain == 0) return;
    
    //Define new histograms
    TH1D* h_njets = new TH1D("h_njets","njets histogram", 15, 0, 15);
    TH1D* h_met = new TH1D("h_met","MET histogram", 100, 0, 1000);
    TH1D* h_vecjetpt = new TH1D("h_vecjetpt","vecjetpt histogram", 100, 0, 1000);

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        if(jentry % 10000 == 0) cout << "Processing entry " << jentry << endl;

        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;

        //Dummy example: print out the MET and the number of jets
        cout << "MET = " << metPt << "; Number of jets = " << nJets << endl;

	//Fill the histograms
	h_met->Fill(metPt);
	h_njets->Fill(nJets);
	double vecjetpx = 0;
	double vecjetpy = 0;
	for (int iJet=0; iJet<nJets; iJet++){
	  vecjetpx += jetPt[iJet]*TMath::Cos(jetPhi[iJet]);
	  vecjetpy += jetPt[iJet]*TMath::Sin(jetPhi[iJet]);
	}	
	h_vecjetpt->Fill( TMath::Sqrt(vecjetpx*vecjetpx + vecjetpy*vecjetpy) );
    }
    TFile* output = TFile::Open("output.root","recreate");
    output->cd();
    h_met->Write();
    h_njets->Write();
    h_vecjetpt->Write();
    output->Close();
}
