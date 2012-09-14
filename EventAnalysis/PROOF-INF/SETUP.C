Int_t SETUP(TList *input = 0) {
  
  if (gSystem->Load("libEventAnalysis.so")<0) return 1;
  
  // Set the include paths
  gROOT->ProcessLine(".include EventAnalysis");

  // Set our location, so that other packages can find us
  gSystem->Setenv("EventAnalysis_INCLUDE", "EventAnalysis");
  
  return 0;
}
