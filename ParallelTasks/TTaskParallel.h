//
// Class TTaskParallel
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TTaskParallel
#define ROOT_TTaskParallel

#include <Rtypes.h>
#include <TTask.h>
#include <TThreadPool.h>
#include "TTaskThread.h"

class TTaskParallel : public TTask {
public:
	TTaskParallel(const char *name = "Task", const char *title = "Task");
	TTaskParallel(const TTaskParallel &obj);
	TTaskParallel &operator=(const TTaskParallel &obj);
	virtual ~TTaskParallel();

	virtual void Add(TTask* task);
	virtual void Exec(Option_t *option);

	void SetParent(TTask*task) { fParent = task; }
	void SetParallel(UInt_t numThreads=1) { fNumOfThreads = numThreads; }

protected:
	TTask	*fParent;
	UInt_t fNumOfThreads;  // number of threads
	static TTaskThread *fgThreadTask;   // thread wrapper for TThreadPool
	static TThreadPool<TTaskThread, TTask*> *fgThreadPool;   // thread pool

private:

ClassDef(TTaskParallel, 1)

};

#endif
