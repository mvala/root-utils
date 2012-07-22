//
// Class TMyTaskTest
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TMyTaskTest
#define ROOT_TMyTaskTest

#include "TTaskParallel.h"

class TMyTaskTest : public TTaskParallel {
public:
   TMyTaskTest(const char *name = "Task", const char *title = "Task");
   TMyTaskTest(const TMyTaskTest &obj);
   TMyTaskTest &operator=(const TMyTaskTest &obj);
   virtual ~TMyTaskTest();

   virtual void Exec(Option_t *option);

   void SetMaxNum(Int_t num) { fMaxNum = num;}
   Int_t GetMaxNum() { return fMaxNum; }
   
private:

   Int_t fMaxNum; // max num to sum
   ClassDef(TMyTaskTest, 1)
};

#endif
