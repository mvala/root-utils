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

#include "TTaskParallel.h"

class TServerSocket;
class TMonitor;
class TSocket;
class TTaskMonitorMsg;
class TTaskMonitorServ : public TTaskParallel {

   RQ_OBJECT("TTaskMonitorServ")

public:
   TTaskMonitorServ(const char *name = "Task", const char *title = "Task");
   virtual ~TTaskMonitorServ();

   virtual void Exec(Option_t *option);

   void StopMonitoring();

   void PrepareMonitoringMessage(TTaskMonitorMsg*msg);
   void DisconnectAllClients();

private:

   TServerSocket *fServSocket;
   TMonitor *fMonitor;
   TSocket  *fSocket;
   TSocket  *fSocketInternal;

   ClassDef(TTaskMonitorServ, 1)
};

#endif
