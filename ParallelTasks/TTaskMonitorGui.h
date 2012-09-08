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

class TRootEmbeddedCanvas;
class fSocket;
class TTaskMonitorGui : public TGMainFrame {

public:
   TTaskMonitorGui(const TGWindow *p,UInt_t w,UInt_t h);
   virtual ~TTaskMonitorGui();

   void Connect();
   void RefreshMonitorInfo();
   void Quit();

private:

   TSocket *fSocket;
   TRootEmbeddedCanvas *fEcanvas;

   ClassDef(TTaskMonitorGui, 1)
};

#endif
