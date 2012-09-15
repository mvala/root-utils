/*
 * TTaskThread.h
 *
 *  Created on: Jul 24, 2012
 *      Author: mvala
 */

#ifndef ROOT_TTaskThread
#define ROOT_TTaskThread

#include <TMutex.h>
#include <TTask.h>
#include <TThreadPool.h>

class TTaskThread : public TThreadPoolTaskImp<TTaskThread, TTask *> {
public:
   bool runTask(TTask *task);
   ULong_t ThreadID() const ;

private:
   ULong_t          fThreadID;  // thread id
   TMutex           fMutex;     // mutex

};

#endif /* TTASKTHREAD_H_ */
