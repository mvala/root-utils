//
// Class TAnaTaskExample
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include "TAnaTaskExample.h"

ClassImp(TAnaTaskExample)

//_________________________________________________________________________________________________
TAnaTaskExample::TAnaTaskExample(const char *name, const char *title) :
   TAnalysisTask(name, title) {
   //
   // Std constructor
   //
}

//_________________________________________________________________________________________________
TAnaTaskExample::~TAnaTaskExample() {
   //
   // Destructor
   //
}

//_________________________________________________________________________________________________
TAnaTaskExample::TAnaTaskExample(const TAnaTaskExample &obj) :
   TAnalysisTask(obj)

{
   //
   // Copy constructor
   //
}

//_________________________________________________________________________________________________
TAnaTaskExample &TAnaTaskExample::operator=(const TAnaTaskExample &obj) {
   //
   // Assigned operator
   //

   if (&obj != this) {
      TAnalysisTask::operator=(obj);
   }
   return *this;

}

//_________________________________________________________________________________________________
void TAnaTaskExample::Exec(Option_t *option) {
   //
   // Exec of manager task
   //

   Printf("Running Task %s opt=%s", GetName(),option);

}
