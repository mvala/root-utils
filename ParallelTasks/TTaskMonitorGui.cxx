//
// Class TTaskMonitorGui
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//


#include <TCanvas.h>
#include <TGLayout.h>
#include <TGButton.h>
#include <TRootEmbeddedCanvas.h>
#include <TSocket.h>
#include <TMessage.h>
#include <TApplication.h>

#include "TTaskMonitorMsg.h"

#include "TTaskMonitorGui.h"

ClassImp(TTaskMonitorGui)

//_________________________________________________________________________________________________
TTaskMonitorGui::TTaskMonitorGui(const TGWindow *p,UInt_t w,UInt_t h) :
TGMainFrame(p,w,h),fSocket(0),fEcanvas(0)
{
   //
   // Std constructor
   //

   fEcanvas = new TRootEmbeddedCanvas("ECanvas", this, 600, 400);
   AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 1, 1, 1, 1));

   //   // Create a horizontal frame widget with buttons
   TGHorizontalFrame *hframe = new TGHorizontalFrame(this,600,40);
   TGTextButton *connect = new TGTextButton(hframe,"&Connect");
   connect->Connect("Clicked()","TTaskMonitorGui",this,"Connect()");
   hframe->AddFrame(connect, new TGLayoutHints(kLHintsCenterX,5,5,3,4));

   TGTextButton *refresh = new TGTextButton(hframe,"&Refresh");
   refresh->Connect("Clicked()","TTaskMonitorGui",this,"RefreshMonitorInfo()");
   hframe->AddFrame(refresh, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   TGTextButton *exit = new TGTextButton(hframe,"&Exit");
   exit->Connect("Clicked()","TTaskMonitorGui",this,"Quit()");
   hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
   AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

   SetWindowName("Task Monitoring GUI");
   MapSubwindows();
   Resize(GetDefaultSize());
   MapWindow();
}

//_________________________________________________________________________________________________
TTaskMonitorGui::~TTaskMonitorGui() {
   //
   // Destructor
   //

   //      fSocket->Close();
   //      delete fSocket;
   //      fSocket = 0;
}

//_________________________________________________________________________________________________
void TTaskMonitorGui::RefreshMonitorInfo() {
   // Open connection to server
//   if (fSocket && !fSocket->IsValid()) return;

   if (!fSocket) return;

   // Wait till we get the start message
   fSocket->Send("info");

   TMessage *message;
   fSocket->Recv(message);
   if (!message) return;
   if (message->What() == kMESS_STRING) {
      char str[32];
      message->ReadString(str, 32);
      TString msg = str;
      if (!msg.CompareTo("disconnect")) {
         fSocket->Close();
         delete fSocket;
         fSocket = 0;
      } else {
         Printf("Str is %s",str);
      }
   } else if (message->What() == kMESS_OBJECT) {
      TTaskMonitorMsg *msgMon = (TTaskMonitorMsg*) message->ReadObject(message->GetClass());
      if (msgMon) Printf("Num is %d",msgMon->GetNum());
      delete msgMon;
   }
   delete message;


   //   char str[32];
   //   Int_t ret = socket->Recv(str, 32);
   //
   //   if (ret>=0) {
   //      Printf("Str %d is %s",ret,str);
   //      socket->Send("OK");
   //      //      ret = sock->Recv(str, 32);
   //      //      Printf("Str2 %d is %s",ret,str);
   //   }

   //   fSocket->Close();
   //   delete fSocket;
   //   fSocket = 0;
}

//_________________________________________________________________________________________________
void TTaskMonitorGui::Connect() {
   if (!fSocket) fSocket = new TSocket("localhost", 9090);
}
//_________________________________________________________________________________________________
void TTaskMonitorGui::Quit() {
   fSocket->Send("disconnect");
   fSocket->Close();
   delete fSocket;
   fSocket = 0;
   gApplication->Terminate(0);
}
