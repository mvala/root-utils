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
}

void TTaskMonitorMsg::Print(Option_t */*opt*/) const {

   TTaskParallel t;
   Int_t i,j;
   for(i=0;i<TTaskParallel::kAllTypes;i++) {
      printf("Task %s",t.GetTypeName((TTaskParallel::ETaskType)i));
      for(j=0;j<TTaskParallel::kAllStatusTypes;j++) {
         printf(" %d",fNumberOfThreads[i][j]);
      }
      Printf("");
   }
}

