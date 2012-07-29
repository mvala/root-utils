/*
 * TTaskThread.cxx
 *
 *  Created on: Jul 24, 2012
 *      Author: mvala
 */
#include <TClass.h>
#include <TThread.h>
#include "TTaskParallel.h"
#include "TTaskThread.h"

bool TTaskThread::runTask(TTask *task) {
	TTaskParallel *t = (TTaskParallel*) task;
	fThreadID = TThread::SelfId();
	t->SetStatusType(TTaskParallel::kRunning);
	t->Exec(TString::Format("%lld", fThreadID).Data());
	if (t->GetStatusType() == TTaskParallel::kRunning) t->SetStatusType(TTaskParallel::kDone);
	return true;
}

ULong_t TTaskThread::ThreadID() const {
	return fThreadID;
}
