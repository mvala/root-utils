/*
 * TTaskThread.cxx
 *
 *  Created on: Jul 24, 2012
 *      Author: mvala
 */
#include <TClass.h>
#include <TThread.h>
#include "TTaskParallel.h"
#include "TTaskManager.h"
#include "TTaskMonitorServ.h"
#include "TTaskMonitorMsg.h"
#include "TTaskThread.h"

bool TTaskThread::runTask(TTask *task) {

   TTaskParallel *t;
   TTaskManager *mgr = TTaskManager::GetTaskManager();
   TTaskMonitorMsg *msg = mgr->GetTaskMonitor();
   {
      TLockGuard lock(&fMutex);
      t = (TTaskParallel *) task;
      fThreadID = TThread::SelfId();
      t->SetStatusType(TTaskParallel::kRunning);
      msg->IncrementThread(t->GetType(), TTaskParallel::kRunning);
   }
   // executing task
   t->Exec(TString::Format("%ld", fThreadID).Data());

   {
      TLockGuard lock(&fMutex);
      if (t->GetStatusType() == TTaskParallel::kRunning) {
         t->SetStatusType(TTaskParallel::kDone);
         msg->IncrementThread(t->GetType(), TTaskParallel::kDone);
         mgr->TaskStatusChanged((Int_t) t->GetType(), (Int_t) TTaskParallel::kDone);
      }
   }
   return true;
}

ULong_t TTaskThread::ThreadID() const {
   return fThreadID;
}
