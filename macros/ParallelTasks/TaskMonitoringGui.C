#ifndef __CINT__
#include <TString.h>
#include <TSystem.h>
#include <TSocket.h>
#include <TTaskMonitorGui.h>
#endif
void TaskMonitoringGui() {
    new TTaskMonitorGui(gClient->GetRoot(),600,400);
}
