#ifndef TAnalysisManager_H
#define TAnalysisManager_H

#include <TTaskManager.h>

class TTree;
class TAnalysisManager : public TTaskManager {
public:
   TAnalysisManager();
   TAnalysisManager(const char *name, const char *title = "Analysis Manager");
   virtual ~TAnalysisManager();

   void Process(TTree *tree, Long64_t entry);

   ClassDef(TAnalysisManager, 1)
};

#endif
