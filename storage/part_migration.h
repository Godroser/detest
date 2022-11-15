#ifndef _PART_MIGRATION_H_
#define _PART_MIGRATION_H_

#include <stdint.h>
#include <vector>
#include <map>

#include "global.h"
#include "storage/catalog.h"
#include "storage/table.h"
#include "benchmarks/ycsb.h"
#include "storage/index_btree.h"
#include "storage/index_hash.h"

/*
    0.找到partition内涉及的所有表的行
    1.给row数据加一列数据，维护该row的迁移情况
    2.封装迁移消息，把这些表数据发送到消息队列里，发给目标节点
    //3.重新构建源节点的索引
    //4.重新构建目标节点的索引
*/

class Part_Migration{
public:
    /*获取要迁移的所有的表的信息*/
    void get_table_id(){}

    /*获取要迁移的所有row的信息*/
    void get_row_id(uint32_t table_id){}

    /*初始化row的迁移信息，初始值未迁移*/
    void init_row_status(){}    
    
    /*设置row的迁移信息*/
    void set_row_status(){}

    /*生成迁移信息*/
    void init_migration_message(){}

private:
    uint64_t part_id_src,part_id_des;
    //std::vector<uint32_t> table_id;
    //std::vector<uint64_t> row_id[10]; //数组对应表的数量，一个table对应一个row_id vector
    
};

class Part_Migration_ycsb : public Part_Migration{
public:

    Part_Migration_ycsb(uint64_t part_id_src,uint64_t part_id_des,INDEX* index) : part_id_src(part_id_src),part_id_des(part_id_des),index(index){}

    /*获取要迁移的所有的表的信息*/
    //table_t* get_table_id(){}
    
    /*获取要迁移的所有row的信息*/
    RC get_row_id(uint64_t part_id,INDEX* index,vector<row_t*> rows, vector<row_t> rows_data);

    /*初始化row的迁移信息，初始值未迁移*/
    RC init_row_status(uint64_t part_id);
    
    /*设置row的迁移信息*/
    RC set_row_status(uint64_t part_id,int status);

    /*生成迁移信息*/
    RC init_migration_message();

private:
    uint64_t part_id_src,part_id_des;
    //std::vector<uint32_t> table_id;
    INDEX* index;
    std::vector<row_t*> rows;
};

class Part_Migration_tpcc : public Part_Migration{
public:

    Part_Migration_tpcc(uint64_t part_id_src,uint64_t part_id_des) : part_id_src(part_id_src),part_id_des(part_id_des){}

    /*获取要迁移的所有的表的信息*/
    //table_t* get_table_id(){}
    
    /*获取要迁移的所有row的信息*/
    RC get_row_id();

    /*初始化row的迁移信息，初始值未迁移*/
    RC init_row_status();
    
    /*设置row的迁移信息*/
    RC set_row_status();

    /*生成迁移信息*/
    RC init_migration_message();

private:
    uint64_t part_id_src,part_id_des;
    std::vector<table_t*> tables;
    std::vector<row_t*> rows[10];  //tpcc的表数量
};

#endif