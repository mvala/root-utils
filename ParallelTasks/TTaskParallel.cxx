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
#include "TTaskManager.h"

//TTaskThread *TTaskParallel::fgThreadTask = 0;
//TThreadPool<TTaskThread, TTask*> *TTaskParallel::fgThreadPool = 0;
//Int_t TTaskParallel::fgNumOfThreads[] = { 0 };
//Int_t TTaskParallel::fgTaskTypeCount[] = { 0 };

ClassImp(TTaskParallel)

//_________________________________________________________________________________________________
TTaskParallel::TTaskParallel(const char *name, const char *title) :
TTask(name, title), fTaskStatusType(kWaiting), fTaskType(kCpu), fParent(0),
fListDeps(0)
{
   // Std constructor

}

//_________________________________________________________________________________________________
TTaskParallel::~TTaskParallel() {
   //
   // Destructor
   //
}

//_________________________________________________________________________________________________
TTaskParallel::TTaskParallel(const TTaskParallel &obj) :
         TTask(obj), fTaskStatusType(obj.fTaskStatusType), fTaskType(obj.fTaskType), fParent(obj.fParent),fListDeps(obj.fListDeps)

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
      fTaskStatusType = obj.fTaskStatusType;
      fTaskType = obj.fTaskType;
      fParent = obj.fParent;
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
   TTaskParallel *tp = (TTaskParallel *) task;
   tp->SetParent(this);
}

//_________________________________________________________________________________________________
void TTaskParallel::AddDependency(TTask *task) {
   //
   // Adds task
   //

   if (!task) return;
   if (!fListDeps) fListDeps = new TList();
   fListDeps->Add(task);

}

//_________________________________________________________________________________________________
void TTaskParallel::Exec(Option_t *option) {
   //
   // Exec of manager task
   //

   // Printf("%s [START] [%ld] %p", GetName(), fNumOfThreads,fgThreadPool);
   // Printf("%s [ DONE] [%ld]", GetName(), fNumOfThreads);

   RunTask(option);

}

//_________________________________________________________________________________________________
void TTaskParallel::RunTask(Option_t *option,TTaskParallel::ETaskType type) {

   TIter next(fTasks);
   TTask *task;
   TTaskParallel *t;
   TTaskManager *taskMgr = TTaskManager::GetTaskManager();
   while ((task = (TTask *) next())) {
      if (!task->IsActive()) continue;
      t = (TTaskParallel *) task;
//      Printf("Testing %s [%s]",t->GetName(),t->GetStatusTypeName());
      if (t->GetStatusType() == TTaskParallel::kWaiting) {
         if (t->HasDependency()) {
            // task was not assigned
            taskMgr->SetAllAssigned(kFALSE);
         } else {
            t->SetStatusType(TTaskParallel::kAssigned);
//            Printf("Pushing task %s [%s]",t->GetName(),t->GetStatusTypeName());
            taskMgr->PushTask(t);
         }
      }
//      gSystem->Sleep(100);
      t->RunTask(option);
   }

}
//_________________________________________________________________________________________________
Bool_t TTaskParallel::HasDependency() {

   TIter next(fListDeps);
   TTaskParallel*t;
   while ((t = (TTaskParallel*)next())) {
      if (t->GetStatusType() != TTaskParallel::kDone) return kTRUE;
   }

   return kFALSE;
}

//_________________________________________________________________________________________________
void TTaskParallel::SetStatusType(ETaskStatusType t,Bool_t recursivly) {
   fTaskStatusType = t;
   if (recursivly) {
      TIter next(fTasks);
      TTaskParallel*task;
      while ((task = (TTaskParallel*)next())) {
         task->SetStatusType(t,recursivly);
      }
   }
}

//_________________________________________________________________________________________________
const char *TTaskParallel::GetStatusTypeName(ETaskStatusType t) {

   switch (t) {
   case kWaiting:
      return "W";
   case kAssigned:
      return "A";
   case kRunning:
      return "R";
   case kDoneServing:
      return "DS";
   case kDone:
      return "D";
   default:
      return "";
   }
   return "";
}

//_________________________________________________________________________________________________
const char *TTaskParallel::GetTypeName(ETaskType t) {

   switch (t) {
   case kCpu:
      return "CPU";
   case kIO:
      return "IO";
   case kFake:
      return "FAKE";
   default:
      return "";
   }
   return "";
}

