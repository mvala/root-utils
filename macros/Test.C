#ifndef __CINT__
#include <TString.h>
#include <TStopwatch.h>
#endif

void Test(Bool_t runParallel = kTRUE) {

   gSystem->Load("libThread.so");
   gSystem->Load("libParallelTasks.so");

   gSystem->AddIncludePath("-I/home/mvala/git/root-utils/ParallelTasks/");

   TStopwatch timer;
   timer.Start();

//   gROOT->ProcessLine(".L TestThreadPool.C+");
//   TestThreadPool(false);

   gROOT->ProcessLine(".L TestTaskManager.C+");
   TestTaskManager();

   timer.Stop();
   timer.Print();
}
