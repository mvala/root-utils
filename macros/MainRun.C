#ifndef __CINT__
#include <TString.h>
#include <TStopwatch.h>
#endif

void MainRun(TString macro="",TString projectDir="") {

   gSystem->Load("libThread.so");
   gSystem->Load("libGui.so");
   gSystem->Load("libParallelTasks.so");
   gSystem->Load("libCutSet.so");
   gSystem->Load("libProof.so");
   gSystem->Load("libPeacUtils.so");

   gSystem->AddIncludePath(TString::Format("-I%sParallelTasks",projectDir.Data()).Data());
   gSystem->AddIncludePath(TString::Format("-I%sCutSet",projectDir.Data()).Data());
   gSystem->AddIncludePath(TString::Format("-I%sPeacUtils",projectDir.Data()).Data());

   TStopwatch timer;
   timer.Start();

   gROOT->ProcessLine(TString::Format(".x %s+",macro.Data()).Data());

   timer.Stop();
   timer.Print();
}
