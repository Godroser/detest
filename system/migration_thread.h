#ifndef _IOTHREAD_H_
#define _IOTHREAD_H_

#include "global.h"
#include "message.h"
#include "thread.h"

class MigrationThread : public Thread {
public:
    void init(uint64_t thd_id, uint64_t node_id, Workload * workload,
              uint64_t part_id_src,uint64_t part_id_des);
    RC run();
    RC process_send_migration(Message* msg);
    RC process_recv_migration(Message* msg);

public:
    uint64_t part_id_src,part_id_des;
    uint64_t _node_id;
    Workload * _wl;
private:
    uint64_t _thd_txn_id;
    TxnManager * txn_man;
};

#endif
