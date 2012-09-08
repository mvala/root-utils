//
// Class TTaskManager
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TROOT.h>
#include <TThread.h>
#include <TStopwatch.h>
#include <TThreadPool.h>

#include "TTaskPoolManager.h"
#include "TTaskThread.h"
#include "TTaskParallel.h"

#include "TTaskManager.h"

TTaskManager *TTaskManager::fgTaskManager = 0;

ClassImp(TTaskManager)

//_________________________________________________________________________________________________
TTaskManager::TTaskManager(const char *name, const char *title) :
   TTaskParallel(name, title),
   fTaskThreadPools(0),
   fIsAllAssigned(kFALSE),
   fDepCondition()
{
   // Std constructor

   for (Int_t i=0; i<kAllTypes; i++) {
      fNumOfThreads[i] = 0;
   }

   fgTaskManager = this;

//   ResetCounters();

}

//_________________________________________________________________________________________________
TTaskManager::~TTaskManager() {
   // Destructor

}

//_________________________________________________________________________________________________
void TTaskManager::Exec(Option_t *option) {
   // Exec of manager task

   if (!fParent) {

      // We are SuperManager and we do Init
      fTaskThreadPools = new TObjArray();
      for (Int_t i=0; i<kAllTypes; i++) {
         fTaskThreadPools->Add(new TTaskPoolManager(fNumOfThreads[i]));
      }
   }

   TTaskPoolManager *tpm;
   for (Int_t i=0; i<kAllTypes; i++) {
      tpm = (TTaskPoolManager *) fTaskThreadPools->At(i);
      tpm->Print();
   }

//   TTaskManager *tm = TTaskManager::GetTaskManager();
//   if (!tm) {
//      Printf("Error: Create TaskManager first !!!!");
//      return;
//   } else {
//      tm->AddDependency(this);
//   }

   // Loops until not all tasks are assigned
   Int_t counter=0;
   while (1) {
      TThread::Lock();
      Printf("Manager loop %d",counter++);
      SetAllAssigned();
      RunTask(option);
      TThread::UnLock();
      if (fIsAllAssigned) break;
      else fDepCondition.Wait();
   }

   // waiting for tasks to finish
   TIter next(fTaskThreadPools);
   TTaskPoolManager *pool;
   while ((pool = (TTaskPoolManager *)next())) {
      pool->Stop(kTRUE);
   }

   Printf("Done");

   //   ExecuteParallelTasks(option);

}

//_________________________________________________________________________________________________
void TTaskManager::PushTask(TTaskParallel *t) {

   TTaskPoolManager *taskPoolMgr =  (TTaskPoolManager *)fTaskThreadPools->At(t->GetType());
   taskPoolMgr->PushTask(t);
}

