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

//   TTask::Exec(option);
	TString n(GetName());

	TRandom r(n.Atof());
	Double_t time = 10000*r.Uniform(1);
	Printf("[%s] %s (%f)", option,GetName(),time);

	gSystem->Sleep(time);

}
