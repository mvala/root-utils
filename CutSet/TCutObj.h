//
// Class TCutObj
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TCutObj
#define ROOT_TCutObj

#include "TCut.h"

class TCutObj : public TCut {

public:
   TCutObj(const char *name = "Task", const char *title = "Task");
   virtual ~TCutObj();
private:
   ClassDef(TCutObj, 1)
};

#endif
