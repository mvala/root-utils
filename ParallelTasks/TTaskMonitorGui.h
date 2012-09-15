//
// Class TTaskMonitor
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TTaskMonitorGui
#define ROOT_TTaskMonitorGui

#include <TGFrame.h>

class TMonitor;
class fSocket;
class TTaskMonitorMsg;
class TRootEmbeddedCanvas;
class TGTextButton;
class TGLabel;
class TTaskMonitorGui : public TGMainFrame {

public:
   TTaskMonitorGui(const TGWindow *p, UInt_t w, UInt_t h);
   virtual ~TTaskMonitorGui();

   void ConnectDisconnect();
   void Refresh();
   void SetConnected() {Emit("SetConnected()");}
   void WaitFormInfoMessage();
   void Quit(Bool_t quit = kTRUE);

   void HandleMessage(TString msgStr);
   void DrawMonitorWindow();

   TGGroupFrame *CreateInfoFrame(TGWindow *p);

   void SetNumberConnectionRetry(Int_t numRetry = 5) { fNumConnectRetry = numRetry;}
   void SetServer(TString host = "localhost", Int_t port = 9090) {fHost = host; fPort = port;}

private:

   TMonitor *fSocketMonitor;
   TString fHost;
   Int_t fPort;
   Int_t fNumConnectRetry;
   TSocket *fSocket;
   TTaskMonitorMsg *fMonMsg;

   TGTextButton *fConnectButton;
   TGTextButton *fRefreshButton;

   TGLabel *fLabelNumThreads[3];

   TRootEmbeddedCanvas *fEcanvas;

   ClassDef(TTaskMonitorGui, 1)
};

#endif
