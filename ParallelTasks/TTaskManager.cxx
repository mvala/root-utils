//
// Class TTaskManager
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//
#include <TThread.h>
#include <TStopwatch.h>

#include "TTaskParallel.h"

#include "TTaskManager.h"

ClassImp(TTaskManager)

//_________________________________________________________________________________________________
TTaskManager::TTaskManager(const char *name, const char *title) :
		TTask(name, title) {
	//
	// Std constructor
	//
}

//_________________________________________________________________________________________________
TTaskManager::~TTaskManager() {
	//
	// Destructor
	//
}

//_________________________________________________________________________________________________
TTaskManager::TTaskManager(const TTaskManager &obj) :
		TTask(obj) {
	//
	// Copy constructor
	//
}

//_________________________________________________________________________________________________
TTaskManager &TTaskManager::operator=(const TTaskManager &obj) {
	//
	// Assigned operator
	//
	if (&obj != this) {
		TTask::operator=(obj);
	}
	return *this;
}

//_________________________________________________________________________________________________
void TTaskManager::Exec(Option_t *option) {
	//
	// Exec of manager task
	//

	TTask::Exec(option);
}
