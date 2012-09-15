//
// Class TCutSimple
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include "TCutSimple.h"

ClassImp(TCutSimple)

//_________________________________________________________________________________________________
TCutSimple::TCutSimple(const char *name, const char *title) :
   TCutObj(name, title)
//
// Std constructor
//
{
}

//_________________________________________________________________________________________________
Bool_t TCutSimple::IsSelected(TObject *obj) {

   TNamed *namedObj = (TNamed *) obj;
   TString ret = namedObj->GetTitle();

   if (ret.Contains("1")) return kTRUE;

   return kFALSE;
}

