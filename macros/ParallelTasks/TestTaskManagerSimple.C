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

   TTaskManager *taskMgr = new TTaskManager("TaskMgr", "TaskManager");
   taskMgr->SetParallel(4, TTaskParallel::kCpu);
   taskMgr->SetParallel(2, TTaskParallel::kIO);
   taskMgr->SetParallel(10, TTaskParallel::kFake);

   Bool_t useDeps = kFALSE;
   useDeps = kTRUE;

   // using monitoring
   //   taskMgr->UseMonitoring();

   TTaskStress *task1, *task2;
   TTaskStress::EStressType stressType = TTaskStress::kSleep;

   TTaskStress::EStressType stressType2 = TTaskStress::kSleep;
   //   stressType2 = TTaskStress::kCpu;

   Int_t nTasks = 2;
   Int_t nSubTasks = 3;
   Int_t depTaskEvery = 4;
   for (Int_t i = 1; i <= nTasks; i++) {
      task1 = new TTaskStress(TString::Format("task%02d", i * 10).Data(), TString::Format("%d", i + 10).Data());
      task1->SetStressType(stressType);
      //      task1->SetType(TTaskParallel::kIO);

      if (i % depTaskEvery == 0) {
         for (Int_t j = 1; j <= nSubTasks; j++) {
            task2 = new TTaskStress(TString::Format("task%02d", i * 10 + j).Data(),
                                    TString::Format("%d", i + j).Data());
            task2->SetStressType(stressType2);
            if (useDeps) task2->AddDependency(task1);
            task1->Add(task2);
         }
      }

      taskMgr->Add(task1);
   }

   //
   //
   //   task1 = new TTaskStress("task200", "2");
   //   task1->SetStressType(stressType);
   //   taskMgr->Add(task1);
   //
   //   task1 = new TTaskStress("task300", "3");
   //   task1->SetStressType(stressType);
   //
   //   task2 = new TTaskStress("task310", "4");
   //   task2->SetStressType(stressType);
   //   if (useDeps) task2->AddDependency(task1);
   //   task1->Add(task2);
   //
   //   task2 = new TTaskStress("task320", "5");
   //   task2->SetStressType(stressType);
   //   if (useDeps) task2->AddDependency(task1);
   //   task1->Add(task2);
   //
   //   task2 = new TTaskStress("task330", "6");
   //   task2->SetStressType(stressType);
   //   if (useDeps) task2->AddDependency(task1);
   //   task1->Add(task2);
   //
   //   taskMgr->Add(task1);
   //
   //   task1= new TTaskStress("task400", "10");
   //   task1->SetStressType(stressType);
   //
   //   task2 = new TTaskStress("task410", "11");
   //   task2->SetStressType(stressType2);
   //   task2->SetType(TTaskParallel::kIO);
   //   if (useDeps) task2->AddDependency(task1);
   //   task1->Add(task2);
   //
   //   task2 = new TTaskStress("task420", "12");
   //   task2->SetStressType(stressType2);
   //   task2->SetType(TTaskParallel::kIO);
   //   if (useDeps) task2->AddDependency(task1);
   //   task1->Add(task2);
   //
   //   task2 = new TTaskStress("task430", "13");
   //   task2->SetStressType(stressType2);
   //   task2->SetType(TTaskParallel::kIO);
   //   if (useDeps) task2->AddDependency(task1);
   //   task1->Add(task2);
   //
   //   taskMgr->Add(task1);
   //
   //   task1 = new TTaskStress("task500", "9");
   //   task1->SetStressType(stressType);
   //   taskMgr->Add(task1);
   //
   //

   Int_t nExec = 2;
   for (Int_t iExec = 0; iExec < nExec; iExec++) {
      taskMgr->Exec("");
//      taskMgr->RestoreManager();
      //   Printf("Sleeping");
//         gSystem->Sleep(1000);
   }
}
