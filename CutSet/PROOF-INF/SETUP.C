Int_t SETUP(TList *input = 0) {
  
  if (gSystem->Load("libCutSet.so")<0) return 1;
  
  // Set the include paths
  gROOT->ProcessLine(".include CutSet");

  // Set our location, so that other packages can find us
  gSystem->Setenv("CutSet_INCLUDE", "CutSet");
  
  return 0;
}
