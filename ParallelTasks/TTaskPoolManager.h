//
// Class TTaskPoolManager
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TTaskPoolManager
#define ROOT_TTaskPoolManager

#include <Rtypes.h>
#include <RQ_OBJECT.h>
#include "TTaskParallel.h"

class TTaskPoolManager : public TObject {
   RQ_OBJECT("TTaskPoolManager")
public:
   TTaskPoolManager(Int_t numThreads=1);
   virtual ~TTaskPoolManager();

   void Init();
   virtual void Print(Option_t *option = "") const;

   void PushTask(TTaskParallel *t);
   void Stop(Bool_t wait=kFALSE) { fThreadPool->Stop(wait);}

private:

   Int_t                             fNumThreads; // number of threads
   TTaskThread                      *fThreadTask; // thread wrapper for TThreadPool
   TThreadPool<TTaskThread, TTask *> *fThreadPool; // thread pool

   ClassDef(TTaskPoolManager, 1)

};

#endif
