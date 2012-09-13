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

class TTaskMonitorServ;
class TTaskPoolManager;
class TTaskManager : public TTaskParallel {
   RQ_OBJECT("TTaskManager")
public:
   TTaskManager(const char *name = "TaskManager", const char *title = "Task Manager");
   virtual ~TTaskManager();

   virtual void Exec(Option_t *option);

   void TaskStatusChanged(Int_t type,Int_t status);
   void FinishServingTasks() { Emit("FinishServingTasks()");}
   void SetParallel(Int_t num,TTaskParallel::ETaskType type=TTaskParallel::kCpu);
   void PushTask(TTaskParallel *t);
   void SetAllAssigned(Bool_t isAllAssigned=kTRUE) {fIsAllAssigned = isAllAssigned;}
   static TTaskManager *GetTaskManager() { return fgTaskManager; }

   void UseMonitoring(Bool_t useMon = kTRUE) { fUseMonitoring = useMon; }
   void StartMonitoringServer();

private:

   static TTaskManager *fgTaskManager;    // global manager

   TObjArray *fTaskThreadPools;           // list of thread pools
   Int_t      fNumOfThreads[kAllTypes+1]; // number of threads reserved for different type
   Bool_t     fIsAllAssigned;             // flag if all tasks are done
   TCondition fDepCondition;              // dependency condition

   Bool_t fUseMonitoring;                  // flag if monitoring should be used
   TTaskPoolManager *fMonThreadPool;       // thread pool for monitoring
   TTaskMonitorServ *fTaskMon;             // monitoring task



   ClassDef(TTaskManager, 1)

};

#endif
