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
#include "TTaskThread.h"

bool TTaskThread::runTask(TTask *task) {
   TTaskParallel *t = (TTaskParallel *) task;
   fThreadID = TThread::SelfId();
   TTaskManager *mgr = TTaskManager::GetTaskManager();
   t->SetStatusType(TTaskParallel::kRunning);
   TThread::Lock();
   mgr->TaskStatusChanged((Int_t)t->GetType(),(Int_t)TTaskParallel::kRunning);
   TThread::UnLock();

   // executing task
   t->Exec(TString::Format("%lld", fThreadID).Data());

   if (t->GetStatusType() == TTaskParallel::kRunning) {
      t->SetStatusType(TTaskParallel::kDone);
      TThread::Lock();
      mgr->TaskStatusChanged((Int_t)t->GetType(),(Int_t)TTaskParallel::kDone);
      TThread::UnLock();

   }
   return true;
}

ULong_t TTaskThread::ThreadID() const {
   return fThreadID;
}
