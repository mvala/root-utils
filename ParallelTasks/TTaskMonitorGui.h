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

class fSocket;
class TTaskMonitorMsg;
class TRootEmbeddedCanvas;
class TGTextButton;
class TGLabel;
class TTaskMonitorGui : public TGMainFrame {

public:
   TTaskMonitorGui(const TGWindow *p,UInt_t w,UInt_t h);
   virtual ~TTaskMonitorGui();

   void ConnectDisconnect();
   void Refresh();
   void Quit(Bool_t quit=kTRUE);

   void HandleMessage(TString msgStr);
   void DrawMonitorWindow();

   TGGroupFrame *CreateInfoFrame(TGWindow *p);

private:

   TSocket *fSocket;
   TTaskMonitorMsg *fMonMsg;

   TGTextButton *fConnectButton;
   TGTextButton *fRefreshButton;

   TGLabel *fLabelNumThreads[3];

   TRootEmbeddedCanvas *fEcanvas;

   ClassDef(TTaskMonitorGui, 1)
};

#endif
