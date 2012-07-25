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

#include "TTaskParallel.h"

#include "TTaskManager.h"

ClassImp(TTaskManager)

//_________________________________________________________________________________________________
TTaskManager::TTaskManager(const char *name, const char *title, UInt_t numThreads) :
		TTask(name, title), fNumOfThreads(numThreads), fThreadTask(0), fThreadPool(0) {
	//
	// Std constructor
	//
}

//_________________________________________________________________________________________________
TTaskManager::~TTaskManager() {
	//
	// Destructor
	//

	// TODO is it enough
	delete fThreadPool;
	delete fThreadTask;
}

//_________________________________________________________________________________________________
TTaskManager::TTaskManager(const TTaskManager &obj) :
		TTask(obj), fNumOfThreads(obj.fNumOfThreads), fThreadTask(obj.fThreadTask), fThreadPool(obj.fThreadPool) {
	//
	// Copy constructor
	//
}

//_________________________________________________________________________________________________
TTaskManager &TTaskManager::operator=(const TTaskManager &obj) {
	// Assigned operator
	if (&obj != this) {
		TTask::operator=(obj);
		fNumOfThreads = obj.fNumOfThreads;
		fThreadTask = obj.fThreadTask;
		fThreadPool = obj.fThreadPool;
	}
	return *this;
}

//_________________________________________________________________________________________________
void TTaskManager::Exec(Option_t *option) {
	// Exec of manager task

	// Init thread pool
	if (!fThreadPool) fThreadPool = new TThreadPool<TTaskThread, TTask*>(fNumOfThreads, kFALSE);
	if (!fThreadTask) fThreadTask = new TTaskThread();

	Printf("Manager %s [START] [%ld]", GetName(), fNumOfThreads);

	ExecuteTasks(option);

	Printf("Manager %s [ DONE] [%ld]", GetName(), fNumOfThreads);

}

//_________________________________________________________________________________________________
void TTaskManager::ExecuteTasks(Option_t *option) {
	// Execute all the subtasks of a task.
	TIter next(fTasks);
	TTask *task;
	while ((task = (TTask*) next())) {
		if (!task->IsActive()) continue;

		while (1) {
			if (fThreadPool->TasksCount()-fThreadPool->SuccessfulTasks() < fNumOfThreads) break;
			else gSystem->Sleep(100);
		}

		fThreadPool->PushTask(*fThreadTask, task);
//		task->Exec(option);
//		task->ExecuteTasks(option);

	}

	fThreadPool->Stop(true);
	Printf("NumThreads %lu/%lu", fThreadPool->TasksCount(), fThreadPool->SuccessfulTasks());
}
