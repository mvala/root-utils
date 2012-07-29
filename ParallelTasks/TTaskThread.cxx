/*
 * TTaskThread.cxx
 *
 *  Created on: Jul 24, 2012
 *      Author: mvala
 */
#include <TClass.h>
#include <TThread.h>

#include "TTaskThread.h"

bool TTaskThread::runTask(TTask *task) {
	fThreadID = TThread::SelfId();
	task->Exec(TString::Format("%lld",fThreadID).Data());
	return true;
}

ULong_t TTaskThread::ThreadID() const {
	return fThreadID;
}
