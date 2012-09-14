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
   TTaskParallel *t = (TTaskParallel *) task;
   fThreadID = TThread::SelfId();
   TThread::Lock();
   TTaskManager *mgr = TTaskManager::GetTaskManager();
   t->SetStatusType(TTaskParallel::kRunning);
//   gSystem->Sleep(100);
//   mgr->TaskStatusChanged((Int_t)t->GetType(),(Int_t)TTaskParallel::kRunning);
   TTaskMonitorMsg *msg = mgr->GetTaskMonitor();
   msg->IncrementThread(t->GetType(),TTaskParallel::kRunning);
//   gSystem->Sleep(100);
   TThread::UnLock();

   // executing task
   t->Exec(TString::Format("%lld", fThreadID).Data());

   if (t->GetStatusType() == TTaskParallel::kRunning) {
      t->SetStatusType(TTaskParallel::kDone);
      TThread::Lock();
      msg->IncrementThread(t->GetType(),TTaskParallel::kDone);
      mgr->TaskStatusChanged((Int_t)t->GetType(),(Int_t)TTaskParallel::kDone);
      TThread::UnLock();

   }
   return true;
}

ULong_t TTaskThread::ThreadID() const {
   return fThreadID;
}
