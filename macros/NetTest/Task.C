#ifndef __CINT__
#include <TString.h>
#include <TList.h>
#include <TServerSocket.h>
#include <TMonitor.h>
#include <TMessage.h>
#include <TTaskMonitorMsg.h>

#endif

// something like SERVER
void Task() {
   TServerSocket *fServSocket = new TServerSocket(9090, kTRUE);
   TMonitor *fMonitor = new TMonitor;
   fMonitor->Add(fServSocket);



   Printf("Server is ON ...");

   TSocket *sCur = 0;
   TSocket *sServCur = 0;
   TMessage *msgCur = 0;
   //   while (1) {
   sCur = fMonitor->Select();
   //      if (!sCur) break;

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
   }
   //      } else {
   Printf("Sending 1");
   sCur->Send("aaa");
   Printf("Sending 2");
   sCur->Send("aaa");
   Printf("Sending 3");
   //         break;
   //      }

   //   }



   //   TList *l = fMonitor->GetListOfActives();
   //   if (l) {
   //      TIter next(l);
   //      Printf("NumConnections %d",fMonitor->GetListOfActives()->GetEntries());
   //      TSocket *s;
   //      while((s = (TSocket*)next())) {
   //         s->Send("disconnect");
   //      }
   //   }

   //   fMonitor->RemoveAll();

   Printf("Server is OFF ...");
}
