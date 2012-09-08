//
// Class TTaskMonitor
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#include <TStopwatch.h>
#include <TH1.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TThread.h>
#include <TRandom.h>
#include <TGLayout.h>
#include "TTaskManager.h"

#include "TTaskMonitor.h"

ClassImp(TTaskMonitor)

//_________________________________________________________________________________________________
TTaskMonitor::TTaskMonitor(const char *name, const char *title) :
		TTaskParallel(name, title), fMain(0), fEcanvas(0), fHist(0), fIsUp(kFALSE) {
	//
	// Std constructor
	//
}

//_________________________________________________________________________________________________
TTaskMonitor::~TTaskMonitor() {
	//
	// Destructor
	//
	if (fMain) {
		fMain->Cleanup();
		delete fMain;
	}
	delete fHist;
}

//_________________________________________________________________________________________________
void TTaskMonitor::Exec(Option_t *option) {
	// Exec of monitor task
	Printf("Running monitor task ...");
	ShowWindow(gClient->GetRoot(), 600, 400);
	SetStatusType(kDoneServing);
	fIsUp = kTRUE;
	Printf("Window is on ...");

	while (fIsUp) {
		RefreshMonitorInfo();
		gSystem->Sleep(1000);
	}

}

//_________________________________________________________________________________________________
void TTaskMonitor::ShowWindow(const TGWindow *p, UInt_t w, UInt_t h) {

	if (fMain) {
		fMain->Cleanup();
		delete fMain;
	}

	fMain = new TGMainFrame(p, w, h);
	fEcanvas = new TRootEmbeddedCanvas("ECanvas", fMain, 600, 400);
	fMain->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX || kLHintsExpandY, 1, 1, 1, 1));

	TTaskManager *tm = (TTaskManager*) fParent;
	tm->Connect("FinishServingTasks()", "TTaskMonitor", this, "StopMonitoring()");
	tm->Connect("TaskCompleted()", "TTaskMonitor", this, "RefreshMonitorInfo()");

	fMain->SetWindowName("Task Monitoring");
	fMain->MapSubwindows();
	fMain->Resize(fMain->GetDefaultSize());
	fMain->MapWindow();

}

//_________________________________________________________________________________________________
void TTaskMonitor::StopMonitoring() {

	fIsUp = kFALSE;
	SetStatusType(kDone);
//	gSystem->Sleep(10000);

}

//_________________________________________________________________________________________________
void TTaskMonitor::RefreshMonitorInfo() {
//	if (!fHist) fHist = new TH1I("monHist", "Monitor Hist", kAllStatusTypes, 0, kAllStatusTypes);
//	TCanvas *c = fEcanvas->GetCanvas();
//	if (c) {
//		fHist->Reset();
//		fHist->SetBinContent(kWaiting + 1, (Double_t) fgTaskTypeCount[kWaiting]);
//		fHist->SetBinContent(kRunning + 1, (Double_t) fgTaskTypeCount[kRunning]);
//		fHist->SetBinContent(kDoneServing + 1, (Double_t) fgTaskTypeCount[kDoneServing]);
//		fHist->SetBinContent(kDone + 1, (Double_t) fgTaskTypeCount[kDone]);
//		fHist->Draw();
//
//		c->cd();
//		c->Update();
//	}
}
