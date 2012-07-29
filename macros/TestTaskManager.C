#ifndef __CINT__
#include "TTaskManager.h"
#include "TTaskParallel.h"
#include "TTaskStress.h"
#endif

void TestTaskManager() {

	Printf("Starting TaskManager ...");

	TTaskManager *taskMgr = new TTaskManager("TaskMgr","TaskManager");
	taskMgr->SetParallel(2);
	TTaskStress::EStressType stressType = TTaskStress::kSleep;
//	stressType = TTaskStress::kCpu;

	const Int_t numTasks = 10;
	Int_t types[numTasks] = {0,0,1,1,1,1,0,1,0,1};


	TTaskStress *task=0;
	for (Int_t i = 0; i < numTasks; i++) {
		task = new TTaskStress(TString::Format("Task%d",i+1).Data(), TString::Format("%d",i+1).Data());
		stressType = (TTaskStress::EStressType)types[i];
		task->SetStressType(stressType);
		taskMgr->Add(task);
	}

//	TTask *task1 = new TTaskParallel("Task1","1");
//	taskMgr->Add(task1);
//	TTask *task2 = new TTaskParallel("Task2","2");
//	taskMgr->Add(task2);
//	TTask *task3 = new TTaskParallel("Task3","3");
//	taskMgr->Add(task3);
//	TTask *task4 = new TTaskParallel("Task4","4");
//	taskMgr->Add(task4);
	taskMgr->Exec("");
//	taskMgr->ExecuteTasks("");

//	taskMgr->Exec("");

	Printf("Done TaskManager ...");

}
