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
#include <TGLabel.h>
#include <TGInputDialog.h>

#include <TRootEmbeddedCanvas.h>
#include <TSocket.h>
#include <TMonitor.h>
#include <TMessage.h>
#include <TApplication.h>

#include "TTaskParallel.h"
#include "TTaskMonitorMsg.h"

#include "TTaskMonitorGui.h"

ClassImp(TTaskMonitorGui)

//_________________________________________________________________________________________________
TTaskMonitorGui::TTaskMonitorGui(const TGWindow *p, UInt_t w, UInt_t h) :
   TGMainFrame(p, w, h),
   fSocketMonitor(0),
   fHost(""),
   fPort(9090),
   fNumConnectRetry(10),
   fSocket(0),
   fMonMsg(0),
   fConnectButton(0),
   fRefreshButton(0),
   fEcanvas(0)
{
   //
   // Std constructor
   //

   TGVerticalFrame *infoFrameMain = new TGVerticalFrame(this, 600, 400, kHorizontalFrame);

   infoFrameMain->AddFrame(CreateInfoFrame(infoFrameMain), new TGLayoutHints(kLHintsExpandY    | kLHintsExpandX, 2, 2, 2, 2));

   //   fEcanvas = new TRootEmbeddedCanvas("ECanvas", infoFrameMain, 400, 400);
   //   infoFrameMain->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 1, 1, 1, 1));

   AddFrame(infoFrameMain, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 1, 1, 1, 1));

   // Create a horizontal frame widget with buttons
   TGHorizontalFrame *hframe = new TGHorizontalFrame(this, 600, 40);
   fConnectButton = new TGTextButton(hframe, "Dis&connect");
   fConnectButton->Connect("Clicked()", "TTaskMonitorGui", this, "ConnectDisconnect()");
   hframe->AddFrame(fConnectButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));

   fRefreshButton = new TGTextButton(hframe, "&Refresh");
   fRefreshButton->Connect("Clicked()", "TTaskMonitorGui", this, "Refresh()");
   fRefreshButton->SetEnabled(kFALSE);
   hframe->AddFrame(fRefreshButton, new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));
   TGTextButton *exit = new TGTextButton(hframe, "&Exit");
   exit->Connect("Clicked()", "TTaskMonitorGui", this, "Quit()");
   hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX, 5, 5, 3, 4));
   AddFrame(hframe, new TGLayoutHints(kLHintsCenterX, 2, 2, 2, 2));

   SetWindowName("Task Monitoring GUI");
   MapSubwindows();
   Resize(GetDefaultSize());
   MapWindow();
   fConnectButton->SetText("&Connect");

   fSocketMonitor = new TMonitor();

   Connect("SetConnected()", "TTaskMonitorGui", this, "WaitFormInfoMessage()");



}

//_________________________________________________________________________________________________
TGGroupFrame *TTaskMonitorGui::CreateInfoFrame(TGWindow *p) {
   TGGroupFrame *infoGroupFrame = new TGGroupFrame(p, "MY info");
   infoGroupFrame->SetTitlePos(TGGroupFrame::kCenter);
   //   infoGroupFrame->SetLayoutManager(new TGVerticalLayout(infoGroupFrame));

   TTaskParallel t;
   TGLabel *l;
   TGHorizontalFrame *hFrame;
   for (Int_t i = 0; i < TTaskParallel::kAllTypes; i++) {
      hFrame = new TGHorizontalFrame(infoGroupFrame, 400, 100, kHorizontalFrame);

      l = new TGLabel(hFrame, TString::Format("%s ", t.GetTypeName((TTaskParallel::ETaskType)i)).Data());
      hFrame->AddFrame(l, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 1, 1, 1, 1));

      l = new TGLabel(hFrame, " : ");
      hFrame->AddFrame(l, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 1, 1, 1, 1));

      fLabelNumThreads[i] = new TGLabel(hFrame, "0");
      hFrame->AddFrame(fLabelNumThreads[i], new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX | kLHintsExpandY, 1, 1, 1, 1));

      infoGroupFrame->AddFrame(hFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop | kLHintsExpandX, 1, 1, 1, 1));
   }

   return infoGroupFrame;
}

//_________________________________________________________________________________________________
TTaskMonitorGui::~TTaskMonitorGui() {
   //
   // Destructor
   //

   Quit(kFALSE);
}

//_________________________________________________________________________________________________
void TTaskMonitorGui::Refresh() {
   // Open connection to server
   //   if (fSocket && !fSocket->IsValid()) return;

   HandleMessage("info");
}

//_________________________________________________________________________________________________
void TTaskMonitorGui::ConnectDisconnect() {

   if (!fSocket) {


      if (fHost.IsNull()) {
         // input box
         char ret[64];
         TGInputDialog id(gClient->GetRoot(), this, "Enter hostname", "localhost", ret);
         fHost = ret;
      }

      for (Int_t iTry = 0; iTry < fNumConnectRetry; iTry++) {
         fSocket = new TSocket(fHost.Data(), fPort);
         if (!fSocket->IsValid()) {
            fSocketMonitor->Remove(fSocket);
            delete fSocket;
            fSocket = 0;
         } else {
            TMessage::EnableSchemaEvolutionForAll(kTRUE);
            fSocketMonitor->Add(fSocket);
            HandleMessage("");
            break;
         }
         gSystem->Sleep(1000);
      }
   } else {
      Quit(kFALSE);
   }

   if (fSocket && fSocket->IsValid()) {
      fConnectButton->SetText("Dis&connect");
      fRefreshButton->SetEnabled(kTRUE);
      WaitFormInfoMessage();
   }

}
//_________________________________________________________________________________________________
void TTaskMonitorGui::Quit(Bool_t quit) {
   if (fSocket) {
      fSocket->Send("disconnect");
      fSocketMonitor->Remove(fSocket);
      fSocket->Close();
      delete fSocket;
      fSocket = 0;
      fConnectButton->SetText("&Connect");
      fRefreshButton->SetEnabled(kFALSE);
   }

   if (quit) { gApplication->Terminate(0); }
}

//_________________________________________________________________________________________________
void TTaskMonitorGui::HandleMessage(TString msgStr) {

   if (!fSocket) return;
   if (!fSocket->IsValid()) return;

   // Wait till we get the start message
   if (!msgStr.IsNull()) fSocket->Send(msgStr.Data());
   TMessage *msgCur;
   fSocket->Recv(msgCur);
   if (!msgCur) return;
   if (msgCur->What() == kMESS_STRING) {

      char str[32];
      msgCur->ReadString(str, 32);
      TString msg = str;
      //      Printf("We have string '%s'",msg.Data());
      if (!msg.CompareTo("connected")) {
         TInetAddress adr = fSocket->GetInetAddress();
         Printf("We are connected to %s", adr.GetHostAddress());
      } else if (!msg.CompareTo("disconnect")) {
         TInetAddress adr = fSocket->GetInetAddress();
         Printf("Server %s was disconnected", adr.GetHostAddress());
         Quit(kFALSE);
      }
   } else if (msgCur->What() == kMESS_OBJECT) {
      //      Printf("We have object");
      fMonMsg = (TTaskMonitorMsg *) msgCur->ReadObject(msgCur->GetClass());
      DrawMonitorWindow();
      delete fMonMsg;
      fMonMsg = 0;
   }
}

//_________________________________________________________________________________________________
void TTaskMonitorGui::DrawMonitorWindow() {

   if (!fMonMsg) return;

   Int_t running, done;
   for (Int_t i; i < TTaskParallel::kAllTypes; i++) {
      running = fMonMsg->GetNumThreads((TTaskParallel::ETaskType)i, TTaskParallel::kRunning);
      done = fMonMsg->GetNumThreads((TTaskParallel::ETaskType)i, TTaskParallel::kDone);
      fLabelNumThreads[i]->SetText(TString::Format("%d (%d)", running - done, done).Data());
//      fLabelNumThreads[i]->SetText(TString::Format("%d (%d)",running,done).Data());
   }

}

//_________________________________________________________________________________________________
void TTaskMonitorGui::WaitFormInfoMessage() {
   TSocket *socket;
//   TMessage *msgCur;
   while (1) {
      socket = fSocketMonitor->Select();
      if (socket) HandleMessage("");
   }
}
