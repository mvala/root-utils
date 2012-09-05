//
// Class TCutSet
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TCutSet
#define ROOT_TCutSet

#include "TCut.h"

class TCutSet : public TCut {

public:
   TCutSet(const char *name = "Task", const char *title = "Task");
   virtual ~TCutSet();
private:
   ClassDef(TCutSet, 1)
};

#endif
