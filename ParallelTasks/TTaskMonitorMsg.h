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

   Int_t GetNumThreadsDone(TTaskParallel::ETaskType type) {return fNumberOfThreadsDone[type];}
   void SetNumThredsDone(Int_t num,TTaskParallel::ETaskType type) { fNumberOfThreadsDone[type] = num ;}

   void IncrementThreadDone(TTaskParallel::ETaskType type) { fNumberOfThreadsDone[type]++;}
private:
   Int_t fNumberOfThreadsDone[TTaskParallel::kAllTypes];

   ClassDef(TTaskMonitorMsg,1)
};

#endif
