#ifndef TAnalysisSelector_H
#define TAnalysisSelector_H

#include <TTree.h>
#include <TSelector.h>

class TAnalysisManager;
class TAnalysisSelector : public TSelector {

public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   TAnalysisSelector(TTree *tree =0);
   virtual ~TAnalysisSelector() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree */*tree*/) {;}
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify() { return kTRUE;}
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SlaveTerminate() {;}
   virtual void    Terminate();
private:
   TAnalysisManager *fAnalysisManager; //! Analysis manager

   ClassDef(TAnalysisSelector,1);
};

#endif
