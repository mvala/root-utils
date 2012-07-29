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

ClassImp(TTaskParallel)

//_________________________________________________________________________________________________
TTaskParallel::TTaskParallel(const char *name, const char *title) :
		TTask(name, title),fParent(0), fNumOfThreads(1) {
	//
	// Std constructor
	//
}

//_________________________________________________________________________________________________
TTaskParallel::~TTaskParallel() {
	//
	// Destructor
	//

	// TODO is it enough
//	delete fgThreadPool;
//	delete fgThreadTask;
}

//_________________________________________________________________________________________________
TTaskParallel::TTaskParallel(const TTaskParallel &obj) :
		TTask(obj),fParent(obj.fParent), fNumOfThreads(obj.fNumOfThreads)

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
		fParent = obj.fParent;
		fNumOfThreads = obj.fNumOfThreads;
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
   TTaskParallel *tp = (TTaskParallel *)task;
   tp->SetParent(this);
}

//_________________________________________________________________________________________________
void TTaskParallel::Exec(Option_t *option) {
	//
	// Exec of manager task
	//



	Printf("%s [START] [%ld] %p", GetName(), fNumOfThreads,fgThreadPool);

//	ExecuteTasks(option);

	Printf("%s [ DONE] [%ld]", GetName(), fNumOfThreads);

}
