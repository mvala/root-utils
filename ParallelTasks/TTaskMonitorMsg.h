#ifndef TTaskMonitorMsg_H
#define TTaskMonitorMsg_H

#include <TString.h>

#include <TObject.h>

class TTaskMonitorMsg : public TObject {
public:
   TTaskMonitorMsg();
   virtual ~TTaskMonitorMsg();

   Int_t GetNum() {return fNum;}
   void SetNum(Int_t num) { fNum = num ;}
private:
   Int_t fNum;

   ClassDef(TTaskMonitorMsg,1)
};

#endif
