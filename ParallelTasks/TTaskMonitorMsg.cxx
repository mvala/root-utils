#include "TTaskMonitorMsg.h"

ClassImp(TTaskMonitorMsg)

TTaskMonitorMsg::TTaskMonitorMsg() : TObject() {

   Reset();
}

TTaskMonitorMsg::~TTaskMonitorMsg() {
}

void TTaskMonitorMsg::Reset() {
   for(Int_t i;i<TTaskParallel::kAllTypes;i++) {
      fNumberOfThreadsDone[i] = 0;
   }
}
