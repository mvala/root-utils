#ifndef __CINT__
#include <TString.h>
#include <TTaskManager.h>
#include <TTaskMonitorServ.h>
#include <TTaskStress.h>
#endif

void TestTaskManagerSimple() {
   Printf("TestTaskManagerSimple ...");

//   TTaskMonitor *taskMon = new TTaskMonitor("mon","Task Monitor");
//   taskMon->Exec("");
//   return;

   TTaskManager *taskMgr = new TTaskManager("TaskMgr","TaskManager");
   taskMgr->SetParallel(4,TTaskParallel::kCpu);
   taskMgr->SetParallel(2,TTaskParallel::kIO);
   taskMgr->SetParallel(10,TTaskParallel::kFake);

   Bool_t useDeps = kFALSE;
   useDeps = kTRUE;

   taskMgr->UseMonitoring();

   TTaskMonitorServ *taskMon = new TTaskMonitorServ("monServ","Task Monitor Serv");
//   taskMon->Exec("");
//   taskMgr->Add(taskMon);

   TTaskStress *task1,*task2,*task3;
   TTaskStress::EStressType stressType = TTaskStress::kSleep;
   stressType = TTaskStress::kCpu;

   TTaskStress::EStressType stressType2 = TTaskStress::kSleep;

   task1 = new TTaskStress("task100", "1");
   task1->SetStressType(stressType);
   taskMgr->Add(task1);

   task1 = new TTaskStress("task200", "2");
   task1->SetStressType(stressType);
   taskMgr->Add(task1);

   task1 = new TTaskStress("task300", "3");
   task1->SetStressType(stressType);
   task3 = task1;

   task2 = new TTaskStress("task310", "4");
   task2->SetStressType(stressType);
   if (useDeps) task2->AddDependency(task1);
   task1->Add(task2);

   task2 = new TTaskStress("task320", "5");
   task2->SetStressType(stressType);
   if (useDeps) task2->AddDependency(task1);
   task1->Add(task2);

   task2 = new TTaskStress("task330", "6");
   task2->SetStressType(stressType);
   if (useDeps) task2->AddDependency(task1);
   task1->Add(task2);

   taskMgr->Add(task1);

   task1= new TTaskStress("task400", "10");
//   if (useDeps) task1->AddDependency(task3);
   task1->SetStressType(stressType);

   task2 = new TTaskStress("task410", "11");
   task2->SetStressType(stressType2);
   task2->SetType(TTaskParallel::kIO);
   if (useDeps) task2->AddDependency(task1);
   task1->Add(task2);

   task2 = new TTaskStress("task420", "12");
   task2->SetStressType(stressType2);
   task2->SetType(TTaskParallel::kIO);
   if (useDeps) task2->AddDependency(task1);
   task1->Add(task2);

   task2 = new TTaskStress("task430", "13");
   task2->SetStressType(stressType2);
   task2->SetType(TTaskParallel::kIO);
   if (useDeps) task2->AddDependency(task1);
   task1->Add(task2);

   taskMgr->Add(task1);

   task1 = new TTaskStress("task500", "9");
   task1->SetStressType(stressType);
   taskMgr->Add(task1);



   taskMgr->Exec("");
}
