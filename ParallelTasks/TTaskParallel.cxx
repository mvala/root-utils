//
// Class TTaskParallel
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TThread.h>
#include "TTaskParallel.h"

ClassImp(TTaskParallel)

//_________________________________________________________________________________________________
TTaskParallel::TTaskParallel(const char *name, const char *title) :
   TTask(name, title),
   fThread(0)
{
   //
   // Std constructor
   //
}

//_________________________________________________________________________________________________
TTaskParallel::~TTaskParallel()
{
   //
   // Destructor
   //
}

//_________________________________________________________________________________________________
TTaskParallel::TTaskParallel(const TTaskParallel &obj) :
   TTask(obj),
   fThread(obj.fThread)

{
   //
   // Copy constructor
   //
}

//_________________________________________________________________________________________________
TTaskParallel &TTaskParallel::operator=(const TTaskParallel &obj )
{
   //
   // Assigned operator
   //

   if (&obj != this) {
      TTask::operator=(obj);
      fThread = obj.fThread;
   }
   return *this;

}

//_________________________________________________________________________________________________
void TTaskParallel::Exec(Option_t *option)
{
   //
   // Exec of manager task
   //

   TTask::Exec(option);

}

//_________________________________________________________________________________________________
void *TTaskParallel::Thread0(void *arg)
{
   TTaskParallel *task = (TTaskParallel *)arg;
   if (task) {
      if (task->IsActive())  {
         task->Exec(task->GetOption());
      }
   }
   return 0;
}
