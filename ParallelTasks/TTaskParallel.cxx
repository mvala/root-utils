//
// Class TTaskParallel
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TRandom.h>
//#include <TThread.h>
#include "TTaskParallel.h"

TTaskThread *TTaskParallel::fgThreadTask = 0;
TThreadPool<TTaskThread, TTask*> *TTaskParallel::fgThreadPool = 0;
Int_t TTaskParallel::fgNumOfThreads[] = { 0 };
Int_t TTaskParallel::fgTaskTypeCount[] = { 0 };

ClassImp(TTaskParallel)

//_________________________________________________________________________________________________
TTaskParallel::TTaskParallel(const char *name, const char *title) :
		TTask(name, title), fTaskStatusType(kWaiting), fTaskType(kCpu), fParent(0) {
	// Std constructor

}

//_________________________________________________________________________________________________
TTaskParallel::~TTaskParallel() {
	//
	// Destructor
	//

	// TODO is it enough
	delete fgThreadPool;
	fgThreadPool = 0;
	delete fgThreadTask;
	fgThreadTask = 0;
}

//_________________________________________________________________________________________________
TTaskParallel::TTaskParallel(const TTaskParallel &obj) :
		TTask(obj), fTaskStatusType(obj.fTaskStatusType), fTaskType(obj.fTaskType), fParent(obj.fParent)

{
	//
	// Copy constructor
	//
}

//_________________________________________________________________________________________________
TTaskParallel &TTaskParallel::operator=(const TTaskParallel &obj) {
	//
	// Assigned operator
	//

	if (&obj != this) {
		TTask::operator=(obj);
		fTaskStatusType = obj.fTaskStatusType;
		fTaskType = obj.fTaskType;
		fParent = obj.fParent;
	}
	return *this;

}

//_________________________________________________________________________________________________
void TTaskParallel::Add(TTask *task) {
	//
	// Adds task
	//

	if (!task) return;

	//   Printf("Adding Task %s (parent=%s)",task->GetName(),GetName());
	fTasks->Add(task);
	TTaskParallel *tp = (TTaskParallel *) task;
	tp->SetParent(this);
}

//_________________________________________________________________________________________________
void TTaskParallel::Exec(Option_t *option) {
	//
	// Exec of manager task
	//

//	Printf("%s [START] [%ld] %p", GetName(), fNumOfThreads,fgThreadPool);
//	Printf("%s [ DONE] [%ld]", GetName(), fNumOfThreads);

}

//_________________________________________________________________________________________________
void TTaskParallel::ExecuteParallelTasks(Option_t *option) {
	//
	// Exec of manager task
	//

	Bool_t isAllDone = kTRUE;
	TIter next(fTasks);
	TTask *task;
	TTaskParallel *t;

	if (GetStatusType() == TTaskParallel::kWaiting) {
		if (fgThreadPool->TasksCount() - fgThreadPool->SuccessfulTasks() <= fgNumOfThreads[kCpu]) {
			fgThreadPool->PushTask(*fgThreadTask, this);
		}
	}
	fgTaskTypeCount[GetStatusType()]++;

	while ((task = (TTask*) next())) {
		if (!task->IsActive()) continue;
		t = (TTaskParallel*) task;

		if (t->GetStatusType() == TTaskParallel::kWaiting) {
			if (fgThreadPool->TasksCount() - fgThreadPool->SuccessfulTasks() <= fgNumOfThreads[kCpu]) {
				fgThreadPool->PushTask(*fgThreadTask, t);
				t->ExecuteParallelTasks(option);
			}
		}
	}

}

//_________________________________________________________________________________________________
const char* TTaskParallel::GetStatusTypeName(ETaskStatusType t) {

	switch (t) {
	case kWaiting:
		return "W";
	case kRunning:
		return "R";
	case kDoneServing:
		return "DS";
	case kDone:
		return "D";
	}

	return "";
}

//_________________________________________________________________________________________________
const char* TTaskParallel::GetTypeName(ETaskType t) {

	switch (t) {
	case kCpu:
		return "CPU";
	case kIO:
		return "IO";
	case kFake:
		return "FAKE";
	}
	return "";
}

