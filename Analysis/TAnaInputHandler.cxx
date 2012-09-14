//
// Class TAnaInputHandler
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TTree.h>
#include "TAnaInputHandler.h"

ClassImp(TAnaInputHandler)

//_________________________________________________________________________________________________
TAnaInputHandler::TAnaInputHandler(const char *name, const char *title) :
TAnalysisTask(name, title),
fEvent(0)
{
   //
   // Std constructor
   //
}

//_________________________________________________________________________________________________
TAnaInputHandler::~TAnaInputHandler() {
   //
   // Destructor
   //

   // DON'T delete it (it's user's responibility)
//   delete fEvent;
}

//_________________________________________________________________________________________________
TAnaInputHandler::TAnaInputHandler(const TAnaInputHandler &obj) :
      TAnalysisTask(obj),fEvent(obj.fEvent)

{
   //
   // Copy constructor
   //
}

//_________________________________________________________________________________________________
TAnaInputHandler &TAnaInputHandler::operator=(const TAnaInputHandler &obj) {
   //
   // Assigned operator
   //

   if (&obj != this) {
      TAnalysisTask::operator=(obj);
      fEvent = obj.fEvent;
   }
   return *this;

}

//_________________________________________________________________________________________________
void TAnaInputHandler::Exec(Option_t *option) {
   //
   // Exec of manager task
   //

   Printf("Running Task %s",GetName());

}

//_________________________________________________________________________________________________
Bool_t  TAnaInputHandler::BeginEvent(TTree*tree,Long64_t entry) {

   // let's init event
   Printf("Opening event %lld",entry);
   tree->GetEntry(entry, 0);
   return kTRUE;
}




