#include "TAnalysisManager.h"

#include "TAnalysisSelector.h"

ClassImp(TAnalysisSelector)

TAnalysisSelector::TAnalysisSelector(TTree * /*tree*/) : TSelector(),
fChain(0),
fAnalysisManager(0)
{

}

void TAnalysisSelector::Init(TTree *tree)
{
   if (!tree) return;
   fChain = tree;
}

void TAnalysisSelector::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

   fAnalysisManager = (TAnalysisManager*) fInput->FindObject("AM");
   if (fAnalysisManager) fAnalysisManager->Print();
}

Bool_t TAnalysisSelector::Process(Long64_t entry)
{

//   GetEntry(entry);
   fAnalysisManager->Process(fChain,entry);
   return kTRUE;
}

void TAnalysisSelector::Terminate()
{

}
