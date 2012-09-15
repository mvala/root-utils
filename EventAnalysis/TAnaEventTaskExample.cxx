//
// Class TAnaEventTaskExample
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TH1.h>

#include "Event.h"
#include "TAnalysisManager.h"
#include "TAnaEventInputHandler.h"

#include "TAnaEventTaskExample.h"

ClassImp(TAnaEventTaskExample)

//_________________________________________________________________________________________________
TAnaEventTaskExample::TAnaEventTaskExample(const char *name, const char *title) :
   TAnalysisTask(name, title), fNLoops(1), fHist(0) {
   //
   // Std constructor
   //
}

//_________________________________________________________________________________________________
TAnaEventTaskExample::~TAnaEventTaskExample() {
   //
   // Destructor
   //
}

//_________________________________________________________________________________________________
TAnaEventTaskExample::TAnaEventTaskExample(const TAnaEventTaskExample &obj) :
   TAnalysisTask(obj), fNLoops(obj.fNLoops), fHist(obj.fHist)
{
   //
   // Copy constructor
   //
}

//_________________________________________________________________________________________________
TAnaEventTaskExample &TAnaEventTaskExample::operator=(const TAnaEventTaskExample &obj) {
   //
   // Assigned operator
   //

   if (&obj != this) {
      TAnalysisTask::operator=(obj);
      fNLoops = obj.fNLoops;
      fHist = obj.fHist;
   }
   return *this;

}

//_________________________________________________________________________________________________
void TAnaEventTaskExample::Exec(Option_t *option) {
   //
   // Exec of manager task
   //

//   Printf("Running Task %s",GetName());
   if (!fHist) fHist = new TH1D(TString::Format("myTaskStress_%s", GetName()).Data(), "My Stress task hist", 200, -100, 100);

   TAnalysisManager *mgr = (TAnalysisManager *) TAnalysisManager::GetTaskManager();
   TAnaEventInputHandler *ih = (TAnaEventInputHandler *) mgr->GetListOfTasks()->FindObject("eventIH");
   if (!ih) return;
   Event *ev = (Event *)ih->GetEvent();
   if (!ev) return;

   Track *track = 0;
   Event *myEvent = (Event *)ev;
   for (Int_t iLoop = 0; iLoop < fNLoops; iLoop++) {
      for (Int_t iTrack = 0; iTrack < myEvent->GetNtrack(); iTrack++) {
         track = (Track *)(myEvent->GetTracks())->At(iTrack);
         if (!track) continue;
         fHist->Fill(track->GetPx());
      }
   }



}
