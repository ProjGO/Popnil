//
// Created by yuhaorong on 2019/9/4.
//

#include "../include/client_utils.h"

client_info get_info_by_id(int id)
{
    client_info result;
    client_info *client_info_list = (client_info*)friendlist.data;
    for(int i = 0; i < MAX_USR_NUM; i++)
        if(client_info_list[i].id == id)
            return client_info_list[i];
    printf("info not found by id\n");
    exit(-1);
}

//根据头像编号返回头像图片id
char* get_portrait_filename_by_idx(int idx)
{
    char *filename;
    filename = (char*)malloc(MAX_FILENAME_LENGTH);
    sprintf(filename, "../client/images/list_portrait/%d.png", idx);
    return filename;
}