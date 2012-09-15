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

#include <TCut.h>

class TCutObj : public TCut {

public:
   TCutObj(const char *name = "cut", const char *title = "Cut Title");
   virtual ~TCutObj();

   virtual Bool_t IsSelected(TObject *obj) { return kTRUE; }
private:
   ClassDef(TCutObj, 1)
};

#endif
