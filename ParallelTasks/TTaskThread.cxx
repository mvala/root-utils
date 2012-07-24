/*
 * TTaskThread.cxx
 *
 *  Created on: Jul 24, 2012
 *      Author: mvala
 */
#include <TClass.h>
#include <TThread.h>

//#include "TTaskParallel.h"
#include "TTaskThread.h"

bool TTaskThread::runTask(TTask *task) {
	fThreadID = TThread::SelfId();
	if (!task->IsActive()) return false;

//	TThread::Lock();
//	TClass *c = task->IsA();
//	Printf("[%lld] TASK=%s (%s)",fThreadID,task->GetName(),c->GetName());
//	TThread::UnLock();

	task->Exec(TString::Format("%ldd",fThreadID).Data());
	return true;
}

ULong_t TTaskThread::ThreadID() const {
	return fThreadID;
}