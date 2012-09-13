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
fSocketInternal(0),
fMonMsg(0)
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

   delete fServSocket;
   delete fMonitor;
   delete fSocketInternal;
   delete fMonMsg;
}

//_________________________________________________________________________________________________
void TTaskMonitorServ::Exec(Option_t *option) {

   TTaskManager *tm = TTaskManager::GetTaskManager();
   if (tm) {
      tm->Connect("TaskCompleted(Int_t)", "TTaskMonitorServ", this, "SendMonitoringMsg(Int_t)");
      tm->Connect("FinishServingTasks()", "TTaskMonitorServ", this, "StopMonitoring()");
   }

   fServSocket = new TServerSocket(9090, kTRUE);
   fMonitor = new TMonitor;
   fMonitor->Add(fServSocket);

   fSocketInternal = new TSocket("localhost", 9090);

   Printf("Server is ON ...");


   TSocket *sCur = 0;
   TSocket *sServCur = 0;
   TMessage *msgCur = 0;
   while (1) {
      sCur = fMonitor->Select();
      if (!sCur) break;

      if (sCur->IsA() == TServerSocket::Class()) {
         // we have server socket
         Printf("We have TServerSocket ...");
         sServCur = ((TServerSocket *)sCur)->Accept();
         if (sServCur) {

            TInetAddress adr = sServCur->GetInetAddress();
            Printf("New connection accepted from %s(%s) ...",adr.GetHostName(),adr.GetHostAddress());
            fMonitor->Add(sServCur);
            // sending 'connected' string
            sServCur->Send("connected");
            Printf("We sent 'connected' message");
            TMessage message(kMESS_OBJECT);
            message.WriteObject(fMonMsg);
            sServCur->Send(message);

         }
      } else {
         // socket is NOT server socket

         // let's what we get
         sCur->Recv(msgCur);
         if (!msgCur) continue;
         if (msgCur->What() == kMESS_STRING) {
            char str[64];
            msgCur->ReadString(str, 64);
            TString msg = str;
            if (!msg.CompareTo("disconnect")) {fMonitor->Remove(sCur);}
            else if (!msg.CompareTo("end")) {
               fMonitor->Remove(sCur);
               DisconnectAllClients();
               break;
            }
            else if (!msg.CompareTo("info")) {
               //               PrepareMonitoringMessage(TTaskParallel::kCpu);
               TMessage message(kMESS_OBJECT);
               message.WriteObject(fMonMsg);
               sCur->Send(message);
            }
            else Printf("*** Unexpected message ***");

         }
         delete msgCur;
         sServCur = 0;
      }

   }
   fMonitor->RemoveAll();

   Printf("Server is OFF ...");
}

//_________________________________________________________________________________________________
void TTaskMonitorServ::StopMonitoring()
{
   // send end signal
   fSocketInternal->Send("end");
   fSocketInternal->Close();
   fServSocket->Close();
}

//_________________________________________________________________________________________________
void TTaskMonitorServ::SendMonitoringMsg(TTaskParallel::ETaskType type)
{
   if (!fMonMsg) fMonMsg = new TTaskMonitorMsg();
   fMonMsg->IncrementThreadDone(type);

   TList *l = fMonitor->GetListOfActives();
   if (l) {
      TIter next(l);
//      Printf("NumConnections %d",l->GetEntries());
      TSocket *s;
      while((s = (TSocket*)next())) {
         if (s->IsA() == TServerSocket::Class()) continue;
         if (s == fSocketInternal) continue;
         Printf("Sending...");
         TMessage message(kMESS_OBJECT);
         message.WriteObject(fMonMsg);
         s->Send(message);
      }
   }
}

//_________________________________________________________________________________________________
void TTaskMonitorServ::DisconnectAllClients()
{

   fMonitor->Remove(fSocketInternal);
   TList *l = fMonitor->GetListOfActives();
   if (l) {
      TIter next(l);
      TSocket *s;
      while((s = (TSocket*)next())) {
         if (s->IsA() == TServerSocket::Class()) continue;
         s->Send("disconnect",kMESS_STRING);
      }
   }
}
