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
#include "TTaskParallel.h"

class TTaskManager : public TTaskParallel {
public:
	TTaskManager(const char *name = "TaskManager", const char *title = "Task Manager");
	virtual ~TTaskManager();

	virtual void Exec(Option_t *option);
	virtual void ExecuteTasks(Option_t *option);

private:

ClassDef(TTaskManager, 1)

};

#endif
