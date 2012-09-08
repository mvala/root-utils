//
// Class TTaskMonitorServ
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//
#include <TServerSocket.h>
#include <TMonitor.h>
#include <TMessage.h>
#include <TClass.h>

#include "TTaskMonitorMsg.h"
#include "TTaskManager.h"

#include "TTaskMonitorServ.h"

ClassImp(TTaskMonitorServ)

//_________________________________________________________________________________________________
TTaskMonitorServ::TTaskMonitorServ(const char *name, const char *title) :
TTaskParallel(name, title),
fServSocket(0),
fMonitor(0),
fSocket(0),
fSocketFinish(0)
{
   //
   // Std constructor
   //

   SetType(kFake);

}

//_________________________________________________________________________________________________
TTaskMonitorServ::~TTaskMonitorServ() {
   //
   // Destructor
   //
}

//_________________________________________________________________________________________________
void TTaskMonitorServ::Exec(Option_t *option) {

   TTaskManager *tm = TTaskManager::GetTaskManager();
   if (tm) {
      tm->Connect("FinishServingTasks()", "TTaskMonitorServ", this, "StopMonitoring()");
   }

   fServSocket = new TServerSocket(9090, kTRUE);
   fMonitor = new TMonitor;
   fMonitor->Add(fServSocket);

   // init connection
   fSocketFinish = new TSocket("localhost", 9090);

   TSocket *s0 = 0;
   TMessage *mess = 0;
   while (1) {
      fSocket = fMonitor->Select();
      if (!fSocket) continue;
      if (!fSocket->IsValid()) continue;

      if (fSocket->IsA() == TServerSocket::Class()) {
         s0 = ((TServerSocket *)fSocket)->Accept();
         if (s0) {
//            Printf("New connection ...");
            fMonitor->Add(s0);
         }
         continue;
      }
      if (!fSocket->IsValid()) continue;
      fSocket->Recv(mess);
      if (!mess) continue;
      TThread::Lock();
      if (mess->What() == kMESS_STRING) {
         char str[64];
         mess->ReadString(str, 64);
         TString msg = str;
         if (!msg.CompareTo("done")) break;
         else if (!msg.CompareTo("info")) {
//            Printf("info");
            TTaskMonitorMsg *msgMon = new TTaskMonitorMsg();
            PrepareMonitoringMessage(msgMon);
            TMessage message(kMESS_OBJECT);
            message.WriteObject(msgMon);
            fSocket->Send(message);
            delete msgMon;
         } else if (!msg.CompareTo("disconnect")) {
            fMonitor->Remove(fSocket);
         }
         //         fMonitor->Remove(fSocket);
         //         if (fMonitor->GetActive() == 0) {
         //            Printf("No more active clients... stopping");
         //            break;
         //         }
      } else {
         Printf("*** Unexpected message ***");
      }
      delete mess;
      TThread::UnLock();

   }

   //   fMonitor->Remove(s0);
//   fMonitor->RemoveAll();

}

//_________________________________________________________________________________________________
void TTaskMonitorServ::StopMonitoring()
{
   fSocketFinish->Send("done");
   fSocketFinish->Close();
   if (fSocket) fMonitor->Remove(fSocket);
//   fMonitor->Remove(fServSocket);
   fMonitor->RemoveAll();
   fServSocket->Close();
   delete fSocketFinish;
   delete fServSocket;
   Printf("TTaskMonitorServ stoped ...");
}

//_________________________________________________________________________________________________
void TTaskMonitorServ::PrepareMonitoringMessage(TTaskMonitorMsg*msg)
{
   msg->SetNum(4);
}
