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

#include "TTaskMonitorServ.h"
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
fDepCondition(),
fUseMonitoring(kFALSE),
fMonThreadPool(0),
fTaskMon(0)
{
   // Std constructor

   for (Int_t i=0; i<kAllTypes; i++) {
      fNumOfThreads[i] = 0;
   }

   fgTaskManager = this;
}

//_________________________________________________________________________________________________
TTaskManager::~TTaskManager() {
   // Destructor

   fTaskThreadPools->Delete();
   delete fTaskThreadPools;
   delete fMonThreadPool;
   delete fTaskMon;
}

//_________________________________________________________________________________________________
void TTaskManager::Exec(Option_t *option) {
   // Exec of manager task

   if (!fParent) {

      if (fUseMonitoring) StartMonitoringServer();

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

   // Loops until not all tasks are assigned
   Int_t counter=0;
   while (1) {
      TThread::Lock();
      Printf("Manager loop %d",counter++);
      SetAllAssigned();
      RunTask(option);
      TThread::UnLock();
      if (fIsAllAssigned) break;
      fDepCondition.Wait();
   }

   // waiting for tasks to finish
   for (Int_t i=0; i<kAllTypes; i++) {
      tpm = (TTaskPoolManager *) fTaskThreadPools->At(i);
      if (i == TTaskParallel::kFake) FinishServingTasks();
      tpm->Stop(kTRUE);
   }

   TIter next(fTaskThreadPools);
   TTaskPoolManager *pool;
   while ((pool = (TTaskPoolManager *)next())) {
      pool->Stop(kTRUE);
   }

   // sync monitoring
   if (fUseMonitoring) fMonThreadPool->Stop(kTRUE);

   Printf("Done");
}

//_________________________________________________________________________________________________
void TTaskManager::PushTask(TTaskParallel *t) {

   TTaskPoolManager *taskPoolMgr =  (TTaskPoolManager *)fTaskThreadPools->At(t->GetType());
   taskPoolMgr->PushTask(t);
}

//_________________________________________________________________________________________________
void TTaskManager::SetParallel(Int_t num,TTaskParallel::ETaskType type) {
   if ((type < 0) || (type >= TTaskParallel::kAllTypes )) {
      Printf("Error: Wrong type !!! Skipping ...");
      return;
   }
   if (num<=0) {
      Printf("Error: Not setting!!! Number of threads has to be > 0. Skipping ...");
      return;
   }
   fNumOfThreads[type] = num;
}

//_________________________________________________________________________________________________
void TTaskManager::TaskStatusChanged(Int_t type,Int_t status){
   Long_t val[2];
   val[0] = (Long_t)type;
   val[1] = (Long_t)status;
   Emit("TaskStatusChanged(Int_t,Int_t)",val);

   if (status == (Int_t)TTaskParallel::kDone) {
      fDepCondition.Signal();
   }
}

//_________________________________________________________________________________________________
void TTaskManager::StartMonitoringServer() {

   fMonThreadPool =  new TTaskPoolManager(1);
   if (!fTaskMon) fTaskMon = new TTaskMonitorServ("monServ","Task Monitor Serv");
   fMonThreadPool->PushTask(fTaskMon);
}
