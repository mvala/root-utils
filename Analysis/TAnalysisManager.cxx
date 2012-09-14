#include <TTree.h>
//#include <TIter.h>

#include "TAnalysisTask.h"

#include "TAnalysisManager.h"

ClassImp(TAnalysisManager)

TAnalysisManager::TAnalysisManager() : TTaskManager() {
}

TAnalysisManager::TAnalysisManager(const char* name,const char *title) : TTaskManager(name,title) {
}

TAnalysisManager::~TAnalysisManager() {
}

void TAnalysisManager::Process(TTree *tree,Long64_t entry) {


   // Begin Event
   TIter next(fTasks);
   TAnalysisTask *t;
   while ((t = (TAnalysisTask *) next())) {
      if (!t->IsActive()) continue;
      t->BeginEvent(tree,entry);
   }

//   // Process Event
//  next.Reset();
//   while ((t = (TAnalysisTask *) next())) {
//      if (!t->IsActive()) continue;
//      t->ProcessEvent(tree,entry);
//   }

   SetParallel(4);

   Exec("");

   // Terminate Event
   next.Reset();
   while ((t = (TAnalysisTask *) next())) {
      if (!t->IsActive()) continue;
      t->TerminateEvent(tree,entry);
   }

//   Printf("restoring Manager");
   RestoreManager();

}
