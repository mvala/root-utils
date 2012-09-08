//
// Class TTaskStress
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TStopwatch.h>
#include <TH1.h>
#include <TThread.h>
#include <TRandom.h>

#include "TTaskStress.h"

ClassImp(TTaskStress)

//_________________________________________________________________________________________________
TTaskStress::TTaskStress(const char *name, const char *title) :
TTaskParallel(name, title), fType(kSleep), fMaxNum(1) {
   //
   // Std constructor
   //
}

//_________________________________________________________________________________________________
TTaskStress::~TTaskStress() {
   //
   // Destructor
   //
}

//_________________________________________________________________________________________________
TTaskStress::TTaskStress(const TTaskStress &obj) :
		            TTaskParallel(obj), fType(obj.fType), fMaxNum(obj.fMaxNum)

{
   //
   // Copy constructor
   //
}

//_________________________________________________________________________________________________
TTaskStress &TTaskStress::operator=(const TTaskStress &obj) {
   //
   // Assigned operator
   //

   if (&obj != this) {
      TTaskParallel::operator=(obj);
      fType = obj.fType;
      fMaxNum = obj.fMaxNum;

   }
   return *this;

}

//_________________________________________________________________________________________________
void TTaskStress::Exec(Option_t *option) {
   //
   // Exec of manager task
   //

   TStopwatch timer;
   timer.Start();

   TString n(GetTitle());
   UInt_t seed = 0;
   if (!n.IsNull()) seed = n.Atoll();
   TRandom r(seed);

   TTaskParallel *t = (TTaskParallel*) GetParent();
   TTaskParallel *tTest;
   TString prefix="";
   while(t) {
      prefix.Append(" ");
      tTest = t;
      t = (TTaskParallel*)tTest->GetParent();
   }


   if (fType == kSleep) {
      TThread::Lock();
      UInt_t time = (UInt_t) r.Uniform(10000);
      TThread::UnLock();
      Printf("[%s]%s%s S (%ld)", option,prefix.Data(), GetName(), time);
      gSystem->Sleep(time);
      Printf("[%s]%s%s D (%ld)", option,prefix.Data(), GetName(), time);
   } else if (fType == kCpu) {
      TH1D h(TString::Format("myTaskStress_%s", GetName()).Data(), "My Stress task hist", 100, -10, 10);
      h.SetDirectory(0);
      UInt_t entries = (UInt_t) r.Uniform(1e8);
      Printf("[%s]%s%s S %.2f", option, prefix.Data(),GetName(), (Double_t) entries / 1e6);
      h.FillRandom("gaus", entries);
      Printf("[%s]%s%s D %.2f", option, prefix.Data(),GetName(), (Double_t) entries / 1e6);
   }
   timer.Stop();
   //	timer.Print();

   //
   //   Int_t base=1e8*fMaxNum;
   //
   //   Int_t numThreads = TThread::Exists();
   //   Printf("Running %s::Exec(\"%s\") num=%d [START] %d",GetName(),option,fMaxNum, numThreads);
   //   Long64_t sum = 0;
   //   TH1D h("h","Hist",100,-10,10);
   //   h.SetDirectory(0);
   //   h.FillRandom("gaus",base);
   //
   //   numThreads = TThread::Exists();
   //   if (numThreads<0) numThreads=0;
   //   Printf("Running %s::Exec(\"%s\") num=%d  [DONE] %d",GetName(),option,fMaxNum, numThreads);
   //   timer.Stop();
   ////   timer.Print();


}
