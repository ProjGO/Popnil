//
// Created by willwang on 19-9-1.
//

#include "friend_group_server.h"
#include "../common/include/database.h"
#include "../common/include/define.h"

int operate_friend(oper_friend_info * s)
{
    //将两者id存入数据库
    switch(s->type)
    {
        case SEARCH_FRIEND: //查找好友
        {
            client_info* c=(client_info*)malloc(sizeof(client_info));
            *c=getuser(s->id_re);
            write(s->fd_app,c,sizeof(client_info));
            free(c);
            return 1;
        }
        case ADD_FRIEND: //添加好友
        {
            client_info* new_friend=(client_info*)malloc(sizeof(client_info));
            *new_friend=getuser(s->id_re);
            write(s->fd_app,new_friend,sizeof(client_info)); //返回好友信息
            free(new_friend);
            return(addfriendship(s->id_app,s->id_re));
        }
        case DELETE_FRIEND:return(deletefriendship(s->id_app,s->id_re));
    }
}
int operate_group(oper_group_info*s)
{
    switch(s->type)
    {
        case ADD_GROUP:return(addgroup(s->owner_id,s->group_name));
//        case DELETE_GROUP;return()
        case JOIN_GROUP:return(addmembership(s->group_id,s->client_id));
        case QUIT_GROUP:return(deletemembership(s->group_id,s->client_id));
    }
}