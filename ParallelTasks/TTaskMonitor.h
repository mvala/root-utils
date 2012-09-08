//
// Class TTaskMonitor
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TTaskMonitor
#define ROOT_TTaskMonitor

#include <TGFrame.h>
#include <TRootEmbeddedCanvas.h>
#include <RQ_OBJECT.h>

#include "TTaskParallel.h"

class TH1I;
class TTaskMonitor : public TTaskParallel {

   RQ_OBJECT("TTaskMonitor")

public:
   TTaskMonitor(const char *name = "Task", const char *title = "Task");
   virtual ~TTaskMonitor();

   virtual void Exec(Option_t *option);

   void ShowWindow(const TGWindow *p,UInt_t w, UInt_t h);

   void RefreshMonitorInfo();
   void StopMonitoring();

private:
   TGMainFrame *fMain;
   TRootEmbeddedCanvas *fEcanvas;
   TH1I *fHist;
   Bool_t fIsUp;

   ClassDef(TTaskMonitor, 1)
};

#endif
