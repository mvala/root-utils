#ifndef __CINT__
#include <TString.h>
#include <TProof.h>
#include <TStopwatch.h>
#include "TAnalysisManager.h"
#include "TAnaEventInputHandler.h"
#include "TAnaEventTaskExample.h"

#endif

void RunEventAnalysis() {

//  TProof *p = TProof::Open("skaf.saske.sk:1099","workers=2x");
  TProof *p = TProof::Open("lite://");
  p->SetParallel(1);
  
  p->UploadPackage("pars/ParallelTasks.par");
  if (p->EnablePackage("ParallelTasks")) return;
  
  p->UploadPackage("pars/Analysis.par");
  if (p->EnablePackage("Analysis")) return;
  
  p->UploadPackage("pars/EventAnalysis.par");
  if (p->EnablePackage("EventAnalysis")) return;

  TAnalysisManager *mgr = new TAnalysisManager("AM","Analysis Manager");

  TAnaEventInputHandler *ih = new TAnaEventInputHandler("eventIH","Event Input Handler");
  mgr->Add(ih);

  Int_t nTasks = 30;
  TAnaEventTaskExample *task1;
  for (Int_t i=0;i<nTasks;i++) {
     task1 = new TAnaEventTaskExample(TString::Format("Task%d",i).Data(),TString::Format("My Task %d",i).Data());
     task1->AddDependency(ih);
     task1->SetNLoops(200);
     mgr->Add(task1);
  }

//  mgr->SetParallel(1);
//  mgr->Exec("");
  p->AddInput(mgr);

//  TStopwatch timer;
//  timer.Start();

  p->Process("myDS","TAnalysisSelector","");
//  p->Process("myDS","TAnalysisSelector","",1e4);

//  timer.Stop();
//  timer.Print();
}
