//
// Class TAnalysisTask
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include "TAnalysisTask.h"

ClassImp(TAnalysisTask)

//_________________________________________________________________________________________________
TAnalysisTask::TAnalysisTask(const char *name, const char *title) :
   TTaskParallel(name, title) {
   //
   // Std constructor
   //
}

//_________________________________________________________________________________________________
TAnalysisTask::~TAnalysisTask() {
   //
   // Destructor
   //
}

//_________________________________________________________________________________________________
TAnalysisTask::TAnalysisTask(const TAnalysisTask &obj) :
   TTaskParallel(obj)

{
   //
   // Copy constructor
   //
}

//_________________________________________________________________________________________________
TAnalysisTask &TAnalysisTask::operator=(const TAnalysisTask &obj) {
   //
   // Assigned operator
   //

   if (&obj != this) {
      TTaskParallel::operator=(obj);
   }
   return *this;

}

////_________________________________________________________________________________________________
//void TAnalysisTask::Exec(Option_t *option) {
//   //
//   // Exec of manager task
//   //
//
//   Printf("Running Task %s",GetName());
//
//}
