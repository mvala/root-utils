//
// Class TAnaEventInputHandler
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TAnaEventInputHandler
#define ROOT_TAnaEventInputHandler

#include "TAnalysisTask.h"
class TChain;
class TAnaEventInputHandler : public TAnalysisTask {

public:

   TAnaEventInputHandler(const char *name = "defaultAT", const char *title = "Default Analysis Task");
   TAnaEventInputHandler(const TAnaEventInputHandler &obj);
   TAnaEventInputHandler &operator=(const TAnaEventInputHandler &obj);
   virtual ~TAnaEventInputHandler();

   virtual void Exec(Option_t *option);

   virtual Bool_t BeginEvent(TTree *tree, Long64_t entry);
   //   virtual Bool_t ProcessEvent(TTree*tree,Long64_t entry) = 0;
   //   virtual Bool_t TerminateEvent(TTree*tree,Long64_t entry) = 0;

   TObject *GetEvent() { return fEvent; }
private:

   TObject *fEvent;
   TChain  *fTree;
   Long64_t fEntry;

   ClassDef(TAnaEventInputHandler, 1)
};

#endif
