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

#include "TCutObj.h"

class TFormula;
class TList;
class TCutObj;
class TCutSet : public TCutObj {

public:
   TCutSet(const char *name = "cutSet", const char *title = "Cut Set Title");
   virtual ~TCutSet();

   TCutSet    &operator=(const TCutSet &rhs);
   TCutSet    &operator=(const char *rhs);

   void AddCut(TCutObj *cut);
   void AddCut(TCutObj &cut);

   virtual Bool_t IsSelected(TObject *obj);

   TFormula *GetFormula() { return fFormula; }

private:

   TList        *fCuts;    // list of cuts
   TFormula     *fFormula; // common formula

   ClassDef(TCutSet, 1)
};

#endif
