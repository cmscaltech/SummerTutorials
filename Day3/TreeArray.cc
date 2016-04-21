{
  
  gROOT->Reset();
  
  ifstream myfile ("Zee.txt");
  
  TFile* f = new TFile("treeArray.root","RECREATE");

  TTree* tree = new TTree("tree","Tree Array");

  int nZ;
  int charge[500];
  float EleE[500], ElePx[500], ElePy[500], ElePz[500];
  float mee;
  
  tree->Branch("nZ", &nZ, "nZ/I");
  tree->Branch("charge", charge, "charge[nZ]/I");
  tree->Branch("EleE", EleE, "EleE[nZ]/F");
  tree->Branch("ElePx", ElePx, "ElePx[nZ]/F");
  tree->Branch("ElePy", ElePy, "ElePy[nZ]/F");
  tree->Branch("ElePz", ElePz, "ElePz[nZ]/F");
  tree->Branch("mee", &mee, "mee/F");
  
  int ctr = 0;
  
  if( myfile.is_open() ){
    
    while( myfile.good() ){
      
      myfile >> nZ >> charge[ctr] >> EleE[ctr] >> ElePx[ctr] >> ElePy[ctr] >> ElePz[ctr];
      mee = 0;
      ctr++;
      if( ctr == nZ ){
	if (nZ == 2){
	  mee = sqrt(pow(EleE[0]+EleE[1],2) - pow(ElePx[0]+ElePx[1],2) - pow(ElePy[0]+ElePy[1],2) - pow(ElePz[0]+ElePz[1],2));
	  tree->Fill();
	}
	ctr = 0;     
      }
      
    }
    
    myfile.close();
    
  }else cout << "Unable to open file"; 
  
  tree->Write("tree");
  f->Close();
}
