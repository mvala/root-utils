Int_t SETUP(TList *input = 0) {
  
  if (gSystem->Load("libThread.so")<0) return 1;
  if (gSystem->Load("libParallelTasks.so")<0) return 1;
  
  // Set the include paths
  gROOT->ProcessLine(".include ParallelTasks");

  // Set our location, so that other packages can find us
  gSystem->Setenv("ParallelTasks_INCLUDE", "ParallelTasks");
  
  return 0;
}
