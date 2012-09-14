//
// Class TAnaInputHandler
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TAnaInputHandler
#define ROOT_TAnaInputHandler

#include "TAnalysisTask.h"

class TAnaInputHandler : public TAnalysisTask {

public:

   TAnaInputHandler(const char *name = "defaultAT", const char *title = "Default Analysis Task");
   TAnaInputHandler(const TAnaInputHandler &obj);
   TAnaInputHandler &operator=(const TAnaInputHandler &obj);
   virtual ~TAnaInputHandler();

   virtual void Exec(Option_t *option);

   virtual Bool_t BeginEvent(TTree*tree,Long64_t entry);
//   virtual Bool_t ProcessEvent(TTree*tree,Long64_t entry) = 0;
//   virtual Bool_t TerminateEvent(TTree*tree,Long64_t entry) = 0;

   TObject *GetEvent() { return fEvent; }
private:

   TObject *fEvent;

   ClassDef(TAnaInputHandler, 1)
};

#endif
