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
fSocketInternal(0)
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
               TTaskMonitorMsg *msgMon = new TTaskMonitorMsg();
               PrepareMonitoringMessage(msgMon);
               TMessage message(kMESS_OBJECT);
               message.WriteObject(msgMon);
               sCur->Send(message);
               delete msgMon;
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
void TTaskMonitorServ::PrepareMonitoringMessage(TTaskMonitorMsg*msg)
{
   msg->SetNum(4);
}
//_________________________________________________________________________________________________
void TTaskMonitorServ::DisconnectAllClients()
{

   fMonitor->Remove(fSocketInternal);
   TList *l = fMonitor->GetListOfActives();
   if (l) {
      TIter next(l);
      Printf("NumConnections %d",l->GetEntries());
      TSocket *s;
      while((s = (TSocket*)next())) {
         if (s->IsA() == TServerSocket::Class()) continue;
         s->Send("disconnect",kMESS_STRING);
      }
   }
}
