//
// Class TCutSet
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TFormula.h>
#include <TList.h>

#include "TCutObj.h"

#include "TCutSet.h"

ClassImp(TCutSet)

//_________________________________________________________________________________________________
TCutSet::TCutSet(const char *name, const char *title) :
TCutObj(name, title),
fCuts(0),
fFormula(0)
//
// Std constructor
//
{
}

//_________________________________________________________________________________________________
TCutSet::~TCutSet() {
   //
   // Destructor
   //
   delete fFormula;
   delete fCuts;
}

//______________________________________________________________________________
TCutSet& TCutSet::operator=(const TCutSet& rhs)
{
   // Assignment.

   if (this != &rhs) TCut::operator=(rhs);
   delete fFormula;
   fFormula = new TFormula(TString::Format("formula_%s",GetName()).Data(),GetTitle());
   return *this;
}

//______________________________________________________________________________
TCutSet& TCutSet::operator=(const char *rhs)
{
   // Assignment.

   fTitle = rhs;
   delete fFormula;
   fFormula = new TFormula(TString::Format("formula_%s",GetName()).Data(),GetTitle());
   return *this;
}

//_________________________________________________________________________________________________
void TCutSet::AddCut(TCutObj *cut) {

   // check for non zero pointer of cut
   if (!cut) return;

   // creates array of cuts when not done yet
   if (!fCuts) fCuts = new TList();

   // sets title to parameter id
   cut->SetTitle(TString::Format("[%d]",fCuts->GetEntries()).Data());

   // adding cut
   fCuts->Add(cut);
}

//_________________________________________________________________________________________________
void TCutSet::AddCut(TCutObj &cut) {

   // creates array of cuts when not done yet
   if (!fCuts) fCuts = new TList();

   // sets title to parameter id
   cut.SetTitle(TString::Format("[%d]",fCuts->GetEntries()).Data());

   // adding cut
   fCuts->Add(&cut);
}

//_________________________________________________________________________________________________
Bool_t TCutSet::IsSelected(TObject*obj) {

   TCutObj *cut;
   for (Int_t i=0;i<fCuts->GetEntries();i++) {
      cut = (TCutObj*)fCuts->At(i);
//      Printf("%s=%d",cut->GetName(),cut->IsSelected(obj));
      fFormula->SetParameter(i,cut->IsSelected(obj));
   }

//   Printf("fFormula : %s",fFormula->GetExpFormula("p").Data());
   return fFormula->Eval(0);
}
