#include "thread.h"
#include "migration_thread.h"
#include "global.h"
#include "helper.h"
#include "manager.h"
#include "math.h"
#include "message.h"
#include "msg_queue.h"
#include "query.h"
#include "txn.h"
#include "wl.h"

void MigrationThread::init(uint64_t thd_id, uint64_t node_id, Workload * workload, uint64_t part_id_src,uint64_t part_id_des){
  _thd_txn_id = thd_id;
  _node_id = node_id;
  _wl = workload;
  part_id_src = part_id_src;
  part_id_des = part_id_des;
}

RC MigrationThread::run(){
  return RCOK;
}

RC MigrationThread::process_send_migration(Message* msg){
  DEBUG("SEND MIGRATION %ld\n",msg->get_txn_id());
  ((MigrationDataMessage*)msg)->copy_to_txn(txn_man);
  //m_wl.part_node_map[((MigrationDataMessage*)msg)->part_id] = ((MigrationDataMessage*)msg)->part_id_des;
  RC rc = RCOK;
  return rc;
}

RC MigrationThread::process_recv_migration(Message* msg){
  /*
  DEBUG("RECV MIGRATION %ld\n",msg->get_txn_id());
  ((MigrationDataMessage*)msg)->copy_to_txn(txn_man);
  for (size_t i=0;i<((MigrationDataMessage*)msg)->rows_size;i++){ //释放锁
    Row_lock* row_lock = (Row_lock*)malloc(sizeof(Row_lock));
    row_lock->init(&((MigrationDataMessage*)msg)->rowsdata[i]);
    ((MigrationDataMessage*)msg)->rowsdata[i].manager = row_lock;
  }
  */
  RC rc = RCOK;
  return rc;
}