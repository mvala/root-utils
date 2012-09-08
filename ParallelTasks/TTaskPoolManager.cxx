//
// Class TTaskPoolManager
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//
#include <TThreadPool.h>
#include "TTaskThread.h"

#include "TTaskPoolManager.h"

ClassImp(TTaskPoolManager)

//_________________________________________________________________________________________________
TTaskPoolManager::TTaskPoolManager(Int_t numThreads) : TObject(),
fNumThreads(numThreads),
fThreadTask(0),
fThreadPool(0)
{
   // Std constructor
   Init();
}

//_________________________________________________________________________________________________
TTaskPoolManager::~TTaskPoolManager() {
   // Destructor

}

//_________________________________________________________________________________________________
void TTaskPoolManager::Init() {
   if (!fThreadPool) fThreadPool = new TThreadPool<TTaskThread, TTask *>(fNumThreads, kFALSE);
   if (!fThreadTask) fThreadTask = new TTaskThread();
}

//_________________________________________________________________________________________________
void TTaskPoolManager::Print(Option_t *option) const {

   Printf("NumberOfThreads = %d",fNumThreads);
}

//_________________________________________________________________________________________________
void TTaskPoolManager::PushTask(TTaskParallel *t) {

   fThreadPool->PushTask(*fThreadTask, t);
}

//_________________________________________________________________________________________________
void TTaskPoolManager::Stop(Bool_t wait) {
   fThreadPool->Stop(wait);
}

