#ifndef TPeacVerifierSel_H
#define TPeacVerifierSel_H
#include <TChain.h>

#include <TSelector.h>

class TFileCollection;
class TPeacVerifierSel : public TSelector {

public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   TPeacVerifierSel(TTree *tree =0);
   virtual ~TPeacVerifierSel() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree */*tree*/) {;}
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SlaveTerminate() {;}
   virtual void    Terminate();

private:

   TString          fPrefix;
   TFileCollection *fFcIn;
   TFileCollection *fFcOut;

   void VerifyViaLs();
   void VerifyViaXargs();

   ClassDef(TPeacVerifierSel,1);
};

#endif
