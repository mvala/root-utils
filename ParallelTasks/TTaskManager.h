//
// Class TTaskManager
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TTaskManager
#define ROOT_TTaskManager

#include <Rtypes.h>
#include <TTask.h>
#include <TThreadPool.h>
#include "TTaskThread.h"

class TTaskManager : public TTask {
public:
	TTaskManager(const char *name = "TaskManager", const char *title = "Task Manager",UInt_t numThreads=1);
	TTaskManager(const TTaskManager &obj);
	TTaskManager &operator=(const TTaskManager &obj);
	virtual ~TTaskManager();

	virtual void Exec(Option_t *option);
	virtual void ExecuteTasks(Option_t *option);

private:

	UInt_t 									fNumOfThreads; // number of threads
	TTaskThread 							*fThreadTask;   // thread wrapper for TThreadPool
	TThreadPool<TTaskThread,TTask*> 	*fThreadPool;   // thread pool

ClassDef(TTaskManager, 1)

};

#endif
