//
// Created by willwang on 19-9-1.
//

#include "friend_group_server.h"
#include "database.h"
int operate_friend(oper_friend_info * s)
{
    //将两者id存入数据库
    switch(s->type)
    {
        case ADD_FRIEND:return(addfriendship(s->id_app,s->id_re));
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