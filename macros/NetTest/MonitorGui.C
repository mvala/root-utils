#ifndef __CINT__
#include <TString.h>
#include <TSystem.h>
#include <TServerSocket.h>
#include <TMonitor.h>
#include <TMessage.h>
#include <TTaskMonitorMsg.h>
#endif
void MonitorGui() {

   TSocket *sock = new TSocket("localhost", 9090);
   if (!sock->IsValid()) return;
   TMessage::EnableSchemaEvolutionForAll(kTRUE);
   TMessage *msgCur;


   while (1) {

      sock->Recv(msgCur);
      if (msgCur->What() == kMESS_STRING) {
         char str[32];
         msgCur->ReadString(str, 32);
         TString msg = str;
         if (!msg.CompareTo("connected")) {
            TInetAddress adr = sock->GetInetAddress();
            Printf("We are connected to %s",adr.GetHostAddress());
         } else if (!msg.CompareTo("disconnect")) {
            TInetAddress adr = sock->GetInetAddress();
            Printf("Server %s was disconnected",adr.GetHostAddress());
            break;

         }
      } else if (msgCur->What() == kMESS_OBJECT) {
         TTaskMonitorMsg *msgMon = (TTaskMonitorMsg*) msgCur->ReadObject(msgCur->GetClass());
         if (msgMon) Printf("Num is %d",msgMon->GetNum());
         delete msgMon;
      }
      sock->Send("info");
      gSystem->Sleep(1000);
   }

   sock->Send("disconnect");
   sock->Close();

   //   // sleeping for 3 sec
   //   gSystem->Sleep(20000);
   //
   //   sock = new TSocket("localhost", 9090);
   //   sock->Send("end");
   //   sock->Close();
}
