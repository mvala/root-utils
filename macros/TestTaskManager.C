#ifndef __CINT__
#include <TTaskManager.h>
#include <TTaskParallel.h>
#endif

void TestTaskManager() {

	TTaskManager *taskMgr = new TTaskManager("TaskMgr","TaskManager",2);

	Int_t numTasks = 10;
	TTask *task=0;
	for (Int_t i = 0; i < numTasks; i++) {
		task = new TTaskParallel(TString::Format("Task%d",i+1).Data(), TString::Format("%d",i+1).Data());
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

//	taskMgr->ExecuteTasks("");
	taskMgr->Exec("");

}
