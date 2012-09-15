//
// Class TAnaEventInputHandler
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TChain.h>
#include "Event.h"

#include "TAnaEventInputHandler.h"

ClassImp(TAnaEventInputHandler)

//_________________________________________________________________________________________________
TAnaEventInputHandler::TAnaEventInputHandler(const char *name, const char *title) :
   TAnalysisTask(name, title),
   fEvent(0),
   fTree(0),
   fEntry(0)
{
   //
   // Std constructor
   //
}

//_________________________________________________________________________________________________
TAnaEventInputHandler::~TAnaEventInputHandler() {
   //
   // Destructor
   //

   // DON'T delete it (it's user's responibility)
   //   delete fEvent;
}

//_________________________________________________________________________________________________
TAnaEventInputHandler::TAnaEventInputHandler(const TAnaEventInputHandler &obj) :
   TAnalysisTask(obj), fEvent(obj.fEvent), fTree(obj.fTree),
   fEntry(obj.fEntry)

{
   //
   // Copy constructor
   //
}

//_________________________________________________________________________________________________
TAnaEventInputHandler &TAnaEventInputHandler::operator=(const TAnaEventInputHandler &obj) {
   //
   // Assigned operator
   //

   if (&obj != this) {
      TAnalysisTask::operator=(obj);
      fEvent = obj.fEvent;
      fTree = obj.fTree;
      fEntry = obj.fEntry;
   }
   return *this;

}

//_________________________________________________________________________________________________
void TAnaEventInputHandler::Exec(Option_t *option) {
   //
   // Exec of manager task
   //

//   Printf("Running Task %s",GetName());
//   Printf("Opening event %lld",fEntry);
   fTree->GetTree()->GetEntry(fEntry, 0);

}

//_________________________________________________________________________________________________
Bool_t  TAnaEventInputHandler::BeginEvent(TTree *tree, Long64_t entry) {


   fTree = (TChain *)tree;
   fEntry = entry;

   // let's init event
   if (!fEvent) {
      Event *ev = new Event();
      fEvent = ev;
      fTree->SetBranchAddress("event", &fEvent);
   }


   return kTRUE;
}




