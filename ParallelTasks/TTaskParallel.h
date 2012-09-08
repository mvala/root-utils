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
	enum ETaskStatusType {kWaiting=0, kRunning=1, kDoneServing=2, kDone=3, kAllStatusTypes };
	enum ETaskType {kCpu=0, kIO=1, kFake=2, kAllTypes };
	TTaskParallel(const char *name = "Task", const char *title = "Task");
	TTaskParallel(const TTaskParallel &obj);
	TTaskParallel &operator=(const TTaskParallel &obj);
	virtual ~TTaskParallel();

	virtual void Add(TTask* task);
	virtual void Exec(Option_t *option);

	TTask *GetParent() { return fParent;}
	void SetParent(TTask*task) { fParent = task; }

	void SetStatusType(ETaskStatusType t) { fTaskStatusType = t;}
	void SetType(ETaskType t) { fTaskType = t;}

	const char *GetStatusTypeName(ETaskStatusType t);
	const char *GetStatusTypeName() { return GetStatusTypeName(fTaskStatusType);}
	ETaskStatusType GetStatusType() { return fTaskStatusType; }

	const char *GetTypeName(ETaskType t);
	const char *GetTypeName() { return GetTypeName(fTaskType);}
	ETaskType GetType() { return fTaskType; }

    void RunTask(Option_t *option,TTaskParallel::ETaskType type=TTaskParallel::kCpu);


protected:

	ETaskStatusType fTaskStatusType;
	ETaskType fTaskType;

	TTask	*fParent;

ClassDef(TTaskParallel, 1)

};

#endif
