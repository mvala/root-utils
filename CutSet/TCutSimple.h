//
// Class TCutSimple
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TCutSimple
#define ROOT_TCutSimple

#include "TCutObj.h"

class TCutSimple : public TCutObj {

public:
   TCutSimple(const char *name = "cut", const char *title = "Cut Title");

   virtual Bool_t IsSelected(TObject *obj);

   ClassDef(TCutSimple, 1)
};

#endif
