#include "TTaskMonitorMsg.h"

ClassImp(TTaskMonitorMsg)

TTaskMonitorMsg::TTaskMonitorMsg() : TObject() {

   Reset();
}

TTaskMonitorMsg::~TTaskMonitorMsg() {
}

void TTaskMonitorMsg::Reset() {
   Int_t i,j;
   for(i=0;i<TTaskParallel::kAllTypes;i++) {
      for(j=0;j<TTaskParallel::kAllStatusTypes;j++) {
      fNumberOfThreads[i][j] = 0;
      }
   }

   fNumberOfThreads[0][TTaskParallel::kRunning] = 4;
}
