//
// Created by yuhaorong on 2019/9/4.
//

#ifndef LINPOP_CLIENT_UTILS_H
#define LINPOP_CLIENT_UTILS_H

#include "./define.h"
#include "./include.h"

extern general_array friendlist;

client_info get_info_by_id(int id);

//根据头像编号返回头像图片id
char* get_portrait_filename_by_idx(int idx);

#endif //LINPOP_CLIENT_UTILS_H
