Int_t SETUP(TList *input = 0) {
  
  if (gSystem->Load("libAnalysis.so")<0) return 1;
  
  // Set the include paths
  gROOT->ProcessLine(".include Analysis");

  // Set our location, so that other packages can find us
  gSystem->Setenv("Analysis_INCLUDE", "Analysis");
  
  return 0;
}
