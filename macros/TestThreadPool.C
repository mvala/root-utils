#ifndef __CINT__
#include <vector>
#include <TTask.h>
#include <TTaskParallel.h>
#include <TThreadPool.h>
#include <TTaskThread.h>

#endif
void TestThreadPool(Bool_t needDbg=kFALSE) {

	size_t numThreads = 5;
	size_t numTasks = 10;

	TThreadPool<TTaskThread, TTask*> threadPool(numThreads, needDbg);

//   vector <TTaskThread> taskList(1);
   TTaskThread taskList;
   vector <TTaskParallel> myTaskList(numTasks*2);

   for (size_t i = 0;i < numTasks; ++i) {
   	myTaskList[i].SetName(TString::Format("%ld",i).Data());
   	threadPool.PushTask(taskList,&myTaskList[i]);
   }

   gSystem->Sleep(20000);
//   threadPool.Stop(true);

   for (size_t i = 0;i < numTasks; ++i) {
   	myTaskList[i+numTasks].SetName(TString::Format("%ld",i+numTasks).Data());
   	threadPool.PushTask(taskList,&myTaskList[i+numTasks]);
   }

   threadPool.Stop(true);

}
