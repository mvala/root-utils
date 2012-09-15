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
   fTaskMon("monServ", "Task Monitor Serv")
{
   // Std constructor

   for (Int_t i = 0; i < kAllTypes; i++) {
      fNumOfThreads[i] = 0;
   }
   if (!fgTaskManager) fgTaskManager = this;
}

//_________________________________________________________________________________________________
TTaskManager::~TTaskManager() {
   // Destructor

   if (fTaskThreadPools) fTaskThreadPools->Delete();
   delete fTaskThreadPools;
   delete fMonThreadPool;
}

//_________________________________________________________________________________________________
void TTaskManager::Exec(Option_t *option) {
   // Exec of manager task

   Printf("TTaskManager::Exec START ...");

   if (!fParent && !fTaskThreadPools) {

      Printf("TTaskManager::SHouldBeInit ...");
      TLockGuard lock(&fMutex);
      TTaskPoolManager *tpm;
      fTaskThreadPools = new TObjArray();

      if (fUseMonitoring) {
         if (!fMonThreadPool) fMonThreadPool =  new TTaskPoolManager(1);
         StartMonitoringServer();
      }

      // We are SuperManager and we do Init
      Int_t i;
      for (i = 0; i < kAllTypes; i++) {
         tpm = new TTaskPoolManager(fNumOfThreads[i]);
         fTaskThreadPools->Add(tpm);
         tpm->Print();
      }

   }

   // Loops until not all tasks are assigned
   Int_t counter = 0;
   while (1) {
      TLockGuard lock(&fMutex);
      Printf("Manager loop %d", counter++);
      SetAllAssigned();
      RunTask(option);
      if (fIsAllAssigned) break;
      fDepCondition.Wait();
   }

   TIter next(fTaskThreadPools);
   TTaskPoolManager *pool;
   while ((pool = (TTaskPoolManager *)next())) {
      pool->Stop(kTRUE);
   }
   //
   //////      TODO Serving tasks
   ////      FinishServingTasks();
   ////
   // wait untill serving task are are finished
   next.Reset();
   while ((pool = (TTaskPoolManager *)next())) {
      pool->Stop(kTRUE);
   }
   //
   //   // sync monitoring
   //   if (fUseMonitoring) fMonThreadPool->Stop(kTRUE);
   //
   if (!fParent) RestoreManager();

   Printf("Done");
}

//_________________________________________________________________________________________________
void TTaskManager::PushTask(TTaskParallel *t) {

   TTaskPoolManager *taskPoolMgr = (TTaskPoolManager *)fTaskThreadPools->At(t->GetType());
   taskPoolMgr->PushTask(t);
}

//_________________________________________________________________________________________________
void TTaskManager::SetParallel(Int_t num, TTaskParallel::ETaskType type) {
   if ((type < 0) || (type >= TTaskParallel::kAllTypes)) {
      Printf("Error: Wrong type !!! Skipping ...");
      return;
   }
   if (num <= 0) {
      Printf("Error: Not setting!!! Number of threads has to be > 0. Skipping ...");
      return;
   }
   fNumOfThreads[type] = num;
}

//_________________________________________________________________________________________________
void TTaskManager::TaskStatusChanged(Int_t type, Int_t status) {
   Long_t val[2];
   val[0] = (Long_t)type;
   val[1] = (Long_t)status;
   Emit("TaskStatusChanged(Int_t,Int_t)", val);
   if (status == (Int_t)TTaskParallel::kDone) {
      fDepCondition.Signal();
   }
}

//_________________________________________________________________________________________________
void TTaskManager::StartMonitoringServer() {

   if (!fMonThreadPool) fMonThreadPool =  new TTaskPoolManager(1);
   fMonThreadPool->PushTask(&fTaskMon);
}

//_________________________________________________________________________________________________
TTaskMonitorMsg *TTaskManager::GetTaskMonitor() {
   if (!fMonThreadPool) fMonThreadPool =  new TTaskPoolManager(1);
   return fTaskMon.GetMonMsg();
}

//_________________________________________________________________________________________________
void TTaskManager::RestoreManager() {

   TLockGuard lock(&fMutex);
   SetStatusType(TTaskParallel::kWaiting, kTRUE);
   TIter next(fTaskThreadPools);
   TTaskPoolManager *pool;
   Printf("Restore Manager Pools %lld %s", fTaskThreadPools->GetEntries(), GetName());
   while ((pool = (TTaskPoolManager *)next())) {
      pool->SetStop(kFALSE);
   }


   //   Printf("Main Task Manager sleeping ");
   //   gSystem->Sleep(5000);

   // TMP fix for reusing threadPools
   //   fTaskThreadPools->Delete();
   //   delete fTaskThreadPools;
   //   fTaskThreadPools = 0;
   //
   //   delete fMonThreadPool;
   //   fMonThreadPool=0;
}
