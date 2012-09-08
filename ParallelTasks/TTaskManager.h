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
#include <TObjArray.h>
#include "TTaskParallel.h"

class TTaskManager : public TTaskParallel {
   RQ_OBJECT("TTaskManager")
public:
   TTaskManager(const char *name = "TaskManager", const char *title = "Task Manager");
   virtual ~TTaskManager();

   virtual void Exec(Option_t *option);

   void FinishServingTasks() { Emit("FinishServingTasks()");}
   void TaskCompleted() { Emit("TaskCompleted()"); fDepCondition.Signal();}


   void SetParallel(Int_t num,TTaskParallel::ETaskType type=TTaskParallel::kCpu) { fNumOfThreads[type] = num; }

   void PushTask(TTaskParallel *t);

   void SetAllAssigned(Bool_t isAllAssigned=kTRUE) {fIsAllAssigned = isAllAssigned;}

   static TTaskManager *GetTaskManager() { return fgTaskManager; }


private:

   static TTaskManager *fgTaskManager;

   TObjArray *fTaskThreadPools;         // list of thread pools
   Int_t      fNumOfThreads[kAllTypes]; // number of threads reserved for different type
   Bool_t     fIsAllAssigned;           // flag if all tasks are done
   TCondition fDepCondition;            // dependency condition



   ClassDef(TTaskManager, 1)

};

#endif
