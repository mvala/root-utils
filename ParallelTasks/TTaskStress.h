//
// Class TTaskStress
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TTaskStress
#define ROOT_TTaskStress

#include "TTaskParallel.h"

class TTaskStress : public TTaskParallel {

public:
	enum EStressType {kSleep=0, kCpu=1, kIO=2 };

	TTaskStress(const char *name = "Task", const char *title = "Task");
	TTaskStress(const TTaskStress &obj);
	TTaskStress &operator=(const TTaskStress &obj);
	virtual ~TTaskStress();

	virtual void Exec(Option_t *option);

	void SetMaxNum(Int_t num) { fMaxNum = num;}
	Int_t GetMaxNum() { return fMaxNum; }

	void SetStressType(EStressType t) { fType = t;}

private:

	EStressType fType;
	Int_t fMaxNum; // max num to sum
	ClassDef(TTaskStress, 1)
};

#endif
