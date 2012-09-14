//
// Class TTaskMonitorServ
//
// TODO
//
// authors:
//          Martin Vala (martin.vala@cern.ch)
//

#ifndef ROOT_TTaskMonitorServ
#define ROOT_TTaskMonitorServ

#include <RQ_OBJECT.h>

#include "TTaskMonitorMsg.h"

#include "TTaskParallel.h"

class TServerSocket;
class TMonitor;
class TSocket;
class TTaskMonitorServ : public TTaskParallel {

   RQ_OBJECT("TTaskMonitorServ")

public:
   TTaskMonitorServ(const char *name = "Task", const char *title = "Task");
   virtual ~TTaskMonitorServ();

   virtual void Exec(Option_t *option);

   void StopMonitoring();

   void SendMonitoringMsg(Int_t val,Int_t val2);
   void DisconnectAllClients();

   TTaskMonitorMsg *GetMonMsg() { return &fMonMsg; }

private:

   TServerSocket *fServSocket;
   TMonitor *fMonitor;
   TSocket  *fSocket;
   TSocket  *fSocketInternal;
   TTaskMonitorMsg fMonMsg;

   ClassDef(TTaskMonitorServ, 1)
};

#endif
