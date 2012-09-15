#ifndef TTaskMonitorMsg_H
#define TTaskMonitorMsg_H

#include <TString.h>
#include <TObject.h>

#include "TTaskParallel.h"
#include "TTaskParallel.h"

class TTaskMonitorMsg : public TObject {
public:
   TTaskMonitorMsg();
   virtual ~TTaskMonitorMsg();

   void Reset();
   virtual void Print(Option_t *option = "") const;

   void IncrementThread(TTaskParallel::ETaskType type, TTaskParallel::ETaskStatusType status) { fNumberOfThreads[type][status]++;}
   Int_t GetNumThreads(TTaskParallel::ETaskType type, TTaskParallel::ETaskStatusType status) { return fNumberOfThreads[type][status];}

private:

   Int_t fNumberOfThreads[TTaskParallel::kAllTypes][TTaskParallel::kAllStatusTypes];

   ClassDef(TTaskMonitorMsg, 1)
};

#endif
