//
// Class TMyTaskTest
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TStopwatch.h>
#include <TH1.h>
#include <TThread.h>

#include "TMyTaskTest.h"

ClassImp(TMyTaskTest)

//_________________________________________________________________________________________________
TMyTaskTest::TMyTaskTest(const char *name, const char *title) :
   TTaskParallel(name, title),
   fMaxNum(1)
{
   //
   // Std constructor
   //
}

//_________________________________________________________________________________________________
TMyTaskTest::~TMyTaskTest()
{
   //
   // Destructor
   //
}

//_________________________________________________________________________________________________
TMyTaskTest::TMyTaskTest(const TMyTaskTest &obj) :
   TTaskParallel(obj),
   fMaxNum(obj.fMaxNum)

{
   //
   // Copy constructor
   //
}

//_________________________________________________________________________________________________
TMyTaskTest &TMyTaskTest::operator=(const TMyTaskTest &obj )
{
   //
   // Assigned operator
   //

   if (&obj != this) {
      TTaskParallel::operator=(obj);
      fMaxNum = obj.fMaxNum;
   }
   return *this;

}

//_________________________________________________________________________________________________
void TMyTaskTest::Exec(Option_t *option)
{
   //
   // Exec of manager task
   //


   TTaskParallel::Exec(option);

   TStopwatch timer;
   timer.Start();
   
   Int_t base=1e8*fMaxNum;
   
   Int_t numThreads = TThread::Exists();
   Printf("Running %s::Exec(\"%s\") num=%d [START] %d",GetName(),option,fMaxNum, numThreads);
   Long64_t sum = 0;
   TH1D h("h","Hist",100,-10,10);
   h.SetDirectory(0);
   h.FillRandom("gaus",base);

   numThreads = TThread::Exists();
   if (numThreads<0) numThreads=0;
   Printf("Running %s::Exec(\"%s\") num=%d  [DONE] %d",GetName(),option,fMaxNum, numThreads);
   timer.Stop();
//   timer.Print();

}
