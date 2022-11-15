#include <stdint.h>
#include <vector>
#include <map>

#include "storage/part_migration.h"
#include "storage/table.h"
#include "storage/row.h"


RC Part_Migration_ycsb::get_row_id(uint64_t part_id,INDEX* index, vector<row_t*> rows, vector<row_t> rows_data){
    uint64_t rows_per_part = g_synth_table_size / g_part_cnt;
    uint64_t key;
    RC rc = RCOK;
    for (uint64_t i=0;i<rows_per_part;i++){
        key=part_id_src+i*g_part_cnt;
        itemid_t* item;
        item->type=DT_row;
        #if INDEX == index_btree
            rc = index->index_read(key,item,part_id);
            rows.emplace_back((row_t*)item->location);
            rows_data.emplace_back(*(row_t*)item->location);
        #endif
    }
    return rc;
}

RC Part_Migration_ycsb::init_row_status(uint64_t part_id){
    RC rc;
    vector<row_t*>::iterator it;
    for (it=rows.begin();it!=rows.end();it++){
        (*it)->migration_status=1;
    }
    rc = RCOK;
    return rc;
}

RC Part_Migration_ycsb::set_row_status(uint64_t part_id,int status){
    RC rc;
    vector<row_t*>::iterator it;
    for (it=rows.begin();it!=rows.end();it++){
        (*it)->migration_status=status;
    }
    rc = RCOK;
    return rc;
}

