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
	// Std constructor

	ResetCounters();

}

//_________________________________________________________________________________________________
TTaskManager::~TTaskManager() {
	// Destructor

}

//_________________________________________________________________________________________________
void TTaskManager::Exec(Option_t *option) {
	// Exec of manager task

	if (!fParent) {

		// TODO - How many tasks are fake,CPU,IO and then reseve threads

		// Init thread pool
		Printf("NumberOfThreads %ld", fgNumOfThreads);
		if (!fgThreadPool) fgThreadPool = new TThreadPool<TTaskThread, TTask*>(fgNumOfThreads[kCpu], kFALSE);
		if (!fgThreadTask) fgThreadTask = new TTaskThread();
	}

	ExecuteParallelTasks(option);

}

//_________________________________________________________________________________________________
void TTaskManager::ExecuteParallelTasks(Option_t *option) {
	// Execute all the subtasks of a task.

	if (!fgThreadPool) {
		Printf("Please setup ThreadPool first !!!");
		return;
	}

	TIter next(fTasks);
	TTask *task;
	TTaskParallel *t;

	Int_t maxLoops = 2000;
	Int_t iLoop = 0;
	while (iLoop < maxLoops) {
//		Printf("Starting Loop [%d] ...", iLoop);
		ResetCounters();
		next.Reset();
		while ((task = (TTask*) next())) {
			if (!task->IsActive()) continue;
			t = (TTaskParallel*) task;
			t->ExecuteParallelTasks(option);

		}

//		Printf("Done Loop [%d] -> added %d ...", iLoop, taskAdded);
		if (iLoop % 10 == 0) {
			Printf("[%d] W=%d, R=%d, SD=%d D=%d", iLoop, fgTaskTypeCount[0], fgTaskTypeCount[1], fgTaskTypeCount[2],
					fgTaskTypeCount[3]);
//			Printf("[%d] %ld, %ld", iLoop, fgThreadPool->TasksCount(), fgThreadPool->SuccessfulTasks());
		}
		gSystem->Sleep(100);
		iLoop++;

		// we break when there is no task waiting or processing
		if (fgTaskTypeCount[kWaiting] == 0) break;
//		if (fgTaskTypeCount[kWaiting]+fgTaskTypeCount[kRunning]+fgTaskTypeCount[kDoneServing]==0) break;
	}

	FinishServingTasks();
	fgThreadPool->Stop(true);

	fgTaskTypeCount[3] = fgThreadPool->SuccessfulTasks();
	fgTaskTypeCount[0] = 0;
	fgTaskTypeCount[1] = 0;
	fgTaskTypeCount[2] = 0;

	Printf("NumThreads %lu/%lu", fgThreadPool->TasksCount(), fgThreadPool->SuccessfulTasks());
	Printf("W=%d, R=%d, SD=%d D=%d", fgTaskTypeCount[0], fgTaskTypeCount[1], fgTaskTypeCount[2], fgTaskTypeCount[3]);
	TaskCompleted();
}
