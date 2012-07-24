//
// Class TTaskParallel
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TTaskParallel
#define ROOT_TTaskParallel

#include <TTask.h>
#include <Rtypes.h>

class TTaskParallel : public TTask {
public:
   TTaskParallel(const char *name = "Task", const char *title = "Task");
   TTaskParallel(const TTaskParallel &obj);
   TTaskParallel &operator=(const TTaskParallel &obj);
   virtual ~TTaskParallel();

   virtual void Exec(Option_t *option);

private:

   ClassDef(TTaskParallel, 1)

};

#endif
