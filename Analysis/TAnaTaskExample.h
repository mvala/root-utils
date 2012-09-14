//
// Class TAnaTaskExample
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TAnaTaskExample
#define ROOT_TAnaTaskExample

#include "TAnalysisTask.h"

class TAnaTaskExample : public TAnalysisTask {

public:

   TAnaTaskExample(const char *name = "defaultAT", const char *title = "Default Analysis Task");
   TAnaTaskExample(const TAnaTaskExample &obj);
   TAnaTaskExample &operator=(const TAnaTaskExample &obj);
   virtual ~TAnaTaskExample();

   virtual void Exec(Option_t *option);

   virtual Bool_t BeginEvent(TTree*tree,Long64_t entry) = 0;
   virtual Bool_t ProcessEvent(TTree*tree,Long64_t entry) = 0;
   virtual Bool_t TerminateEvent(TTree*tree,Long64_t entry) = 0;

private:

   ClassDef(TAnaTaskExample, 1)
};

#endif
