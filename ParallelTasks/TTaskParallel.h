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
   enum ETaskStatusType {kWaiting = 0, kAssigned = 1, kRunning = 2, kDoneServing = 3, kDone = 4, kAllStatusTypes };
   enum ETaskType {kCpu = 0, kIO = 1, kFake = 2, kAllTypes };
   TTaskParallel(const char *name = "Task", const char *title = "Task");
   TTaskParallel(const TTaskParallel &obj);
   TTaskParallel &operator=(const TTaskParallel &obj);
   virtual ~TTaskParallel();

   virtual void Add(TTask *task);
   virtual void Exec(Option_t *option);

   void AddDependency(TTask *t);
   TList *GetDependencyList() { return fListDeps; }

   TTask *GetParent() { return fParent;}
   void SetParent(TTask *task) { fParent = task; }

   void SetStatusType(ETaskStatusType t, Bool_t recursivly = kFALSE);
   void SetType(ETaskType t) { fTaskType = t;}

   const char *GetStatusTypeName(ETaskStatusType t);
   const char *GetStatusTypeName() { return GetStatusTypeName(fTaskStatusType);}
   ETaskStatusType GetStatusType() { return fTaskStatusType; }

   const char *GetTypeName(ETaskType t);
   const char *GetTypeName() { return GetTypeName(fTaskType);}
   ETaskType GetType() { return fTaskType; }

   void RunTask(Option_t *option, TTaskParallel::ETaskType type = TTaskParallel::kCpu);

   Bool_t HasDependency();
   TMutex *GetMutex() { return &fMutex;}


protected:

   ETaskStatusType      fTaskStatusType;     // Status tyoe
   ETaskType            fTaskType;           // task type
   TTask               *fParent;             // partent taks
   TList               *fListDeps;           // dependency list
   TMutex               fMutex;              // mutex for manager

   ClassDef(TTaskParallel, 1)

};

#endif
