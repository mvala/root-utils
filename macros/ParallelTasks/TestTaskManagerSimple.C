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
//   useDeps = kTRUE;

   // using monitoring
   //   taskMgr->UseMonitoring();

   TTaskStress *task1, *task2;
   TTaskStress::EStressType stressType = TTaskStress::kSleep;
//   stressType = TTaskStress::kCpu;

   TTaskStress::EStressType stressType2 = TTaskStress::kSleep;
   //   stressType2 = TTaskStress::kCpu;

   Int_t nTasks = 4;
   Int_t nSubTasks = 3;
   Int_t depTaskEvery = 5;
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

   Int_t nExec = 1e5;
   Int_t refresh = 100;
   for (Int_t iExec = 0; iExec < nExec; iExec++) {
      if (iExec%refresh==0) Printf("Exec %d",iExec);
      taskMgr->Exec("");
//      taskMgr->RestoreManager();

//         gSystem->Sleep(5000);
   }
}
