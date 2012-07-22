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

#include <TTask.h>
#include <Rtypes.h>

class TTaskManager : public TTask {
public:
   TTaskManager(const char *name = "TaskManager", const char *title = "Task Manager");
   TTaskManager(const TTaskManager &obj);
   TTaskManager &operator=(const TTaskManager &obj);
   virtual ~TTaskManager();

   virtual void Exec(Option_t *option);

private:

   ClassDef(TTaskManager, 1)

};

#endif
