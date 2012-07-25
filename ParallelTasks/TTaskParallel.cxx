//
// Class TTaskParallel
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TRandom.h>
#include <TThread.h>
#include "TTaskParallel.h"

ClassImp(TTaskParallel)

//_________________________________________________________________________________________________
TTaskParallel::TTaskParallel(const char *name, const char *title) :
		TTask(name, title) {
	//
	// Std constructor
	//
}

//_________________________________________________________________________________________________
TTaskParallel::~TTaskParallel() {
	//
	// Destructor
	//
}

//_________________________________________________________________________________________________
TTaskParallel::TTaskParallel(const TTaskParallel &obj) :
		TTask(obj)

{
	//
	// Copy constructor
	//
}

//_________________________________________________________________________________________________
TTaskParallel &TTaskParallel::operator=(const TTaskParallel &obj) {
	//
	// Assigned operator
	//

	if (&obj != this) {
		TTask::operator=(obj);
	}
	return *this;

}

//_________________________________________________________________________________________________
void TTaskParallel::Exec(Option_t *option) {
	//
	// Exec of manager task
	//

	TString n(GetTitle());
	UInt_t seed = 0;
	if (!n.IsNull()) seed =  n.Atoll();
	TRandom r(seed);
	UInt_t time = (UInt_t)10000*r.Uniform(1);
	Printf("[%s] %s (%ld)", option,GetName(),time);

	gSystem->Sleep(time);

}
