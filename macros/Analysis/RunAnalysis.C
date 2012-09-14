#ifndef __CINT__
#include <TString.h>
#include <TProof.h>
#include "TAnalysisManager.h"
#include "TAnaInputHandler.h"
#include "TAnaTaskExample.h"

#endif

void RunAnalysis() {

  TProof *p = TProof::Open("lite://");
  
  p->UploadPackage("pars/ParallelTasks.par");
  if (p->EnablePackage("ParallelTasks")) return;
  
  p->UploadPackage("pars/Analysis.par");
  if (p->EnablePackage("Analysis")) return;
  
  p->UploadPackage("pars/EventAnalysis.par");
  if (p->EnablePackage("pars/Analysis.par")) return;

  TAnalysisManager *mgr = new TAnalysisManager("AM","Analysis Manager");

  TAnaInputHandler *ih = new TAnaInputHandler("eventIH","Event Input Handler");
  mgr->Add(ih);


  p->AddInput(mgr);

  p->Process("myDS","TAnalysisSelector");

}
