#include "TClass.h"
#include "TROOT.h"
Int_t SETUP() {
   if (!TClass::GetClass("TPBReadType")) {
      gROOT->ProcessLine(".L TProofBenchTypes.h+");
   }
   gROOT->ProcessLine(".L Event.cxx+");
   gROOT->ProcessLine(".L TSelHandleDataSet.cxx+");
   gROOT->ProcessLine(".L TSelEvent.cxx+");
   gROOT->ProcessLine(".L TSelEventGen.cxx+");
   return 0;
}
