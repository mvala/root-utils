Int_t SETUP(TList *input = 0) {

   if (gSystem->Load("libPeacUtils.so") < 0) return 1;

   // Set the include paths
   gROOT->ProcessLine(".include PeacUtils");

   // Set our location, so that other packages can find us
   gSystem->Setenv("PeacUtils_INCLUDE", "PeacUtils");

   return 0;
}
