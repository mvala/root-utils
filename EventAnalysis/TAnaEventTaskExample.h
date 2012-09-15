//
// Class TAnaEventTaskExample
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TAnaEventTaskExample
#define ROOT_TAnaEventTaskExample

#include "TAnalysisTask.h"
class TH1D;
class TAnaEventTaskExample : public TAnalysisTask {

public:

   TAnaEventTaskExample(const char *name = "defaultAT", const char *title = "Default Analysis Task");
   TAnaEventTaskExample(const TAnaEventTaskExample &obj);
   TAnaEventTaskExample &operator=(const TAnaEventTaskExample &obj);
   virtual ~TAnaEventTaskExample();

   virtual void Exec(Option_t *option);

//   virtual Bool_t BeginEvent(TTree*tree,Long64_t entry) = 0;
//   virtual Bool_t ProcessEvent(TTree*tree,Long64_t entry) = 0;
//   virtual Bool_t TerminateEvent(TTree*tree,Long64_t entry) = 0;

   void SetNLoops(Int_t n) { n > 0 ? fNLoops = n : fNLoops = 1; }

private:

   Int_t fNLoops;
   TH1D *fHist;

   ClassDef(TAnaEventTaskExample, 1)
};

#endif
