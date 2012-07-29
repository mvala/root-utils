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
#include <RQ_OBJECT.h>
#include "TTaskParallel.h"

class TTaskManager : public TTaskParallel {
	RQ_OBJECT("TTaskManager")
public:
	TTaskManager(const char *name = "TaskManager", const char *title = "Task Manager");
	virtual ~TTaskManager();

	virtual void Exec(Option_t *option);
	virtual void ExecuteParallelTasks(Option_t *option);

	void FinishServingTasks() { Emit("FinishServingTasks()");}
	void TaskCompleted() { Emit("TaskCompleted()");}

private:



ClassDef(TTaskManager, 1)

};

#endif
