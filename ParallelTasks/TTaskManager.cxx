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

#include "TTaskThread.h"

#include "TTaskManager.h"

ClassImp(TTaskManager)

//_________________________________________________________________________________________________
TTaskManager::TTaskManager(const char *name, const char *title) :
TTaskParallel(name, title) {
	//
	// Std constructor
	//
}

//_________________________________________________________________________________________________
TTaskManager::~TTaskManager() {
	//
	// Destructor
	//


}

//_________________________________________________________________________________________________
void TTaskManager::Exec(Option_t *option) {
	// Exec of manager task

	if (!fParent) {
		// Init thread pool
		if (!fgThreadPool) fgThreadPool = new TThreadPool<TTaskThread, TTask*>(fNumOfThreads, kFALSE);
		if (!fgThreadTask) fgThreadTask = new TTaskThread();
	}

	ExecuteTasks(option);

}

//_________________________________________________________________________________________________
void TTaskManager::ExecuteTasks(Option_t *option) {
	// Execute all the subtasks of a task.
	TIter next(fTasks);
	TTask *task;
	while ((task = (TTask*) next())) {
		if (!task->IsActive()) continue;

		while (1) {
			if (fgThreadPool->TasksCount()-fgThreadPool->SuccessfulTasks() < fNumOfThreads) break;
			else gSystem->Sleep(100);
		}

		fgThreadPool->PushTask(*fgThreadTask, task);
//		task->Exec(option);
//		task->ExecuteTasks(option);

	}

	fgThreadPool->Stop(true);
	Printf("NumThreads %lu/%lu", fgThreadPool->TasksCount(), fgThreadPool->SuccessfulTasks());
}
