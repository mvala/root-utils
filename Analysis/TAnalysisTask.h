//
// Class TAnalysisTask
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TAnalysisTask
#define ROOT_TAnalysisTask

#include "TTaskParallel.h"
class TTree;
class TAnalysisTask : public TTaskParallel {

public:

   TAnalysisTask(const char *name = "defaultAT", const char *title = "Default Analysis Task");
   TAnalysisTask(const TAnalysisTask &obj);
   TAnalysisTask &operator=(const TAnalysisTask &obj);
   virtual ~TAnalysisTask();

//   virtual void Exec(Option_t *option);

   virtual Bool_t BeginEvent(TTree */*tree*/, Long64_t /*entry*/) { return kTRUE; }
   virtual Bool_t ProcessEvent(TTree */*tree*/, Long64_t /*entry*/) { return kTRUE; }
   virtual Bool_t TerminateEvent(TTree */*tree*/, Long64_t /*entry*/) { return kTRUE; }

   ClassDef(TAnalysisTask, 1)
};

#endif
