void TaskMonitoringGui() {

   gSystem->Load("libGui.so");
   gSystem->Load("libParallelTasks.so");
   TTaskMonitorGui *gui = new TTaskMonitorGui(gClient->GetRoot(),600,400);
}
