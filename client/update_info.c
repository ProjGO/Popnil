////
//// Created by yuhaorong on 2019/9/2.
////
//
//#include "../common/include/database.h"
//#include "../common/include/include.h"
//
////向服务器请求同步该用户所有好友的信息，返回保存这些信息的链表的头指针(头指针中无有效内容,只是指向下一个)
//general_array update_my_and_friend_info_c(rio_t *rio_log, int fd_log)
//{
//    OP_TYPE type = UPDATE;
//    int friend_num;
//    //client_info friend_info_buf;
//    general_array friend_info_array;
//
//    rio_writen(fd_log, &type, sizeof(OP_TYPE)); // 向服务器发送请求同步的op
//    rio_readnb(rio_log, &friend_num, sizeof(int)); // 从服务器接收有几个好友
//    friend_info_array.num = friend_num;
//    friend_info_array.data = malloc(sizeof(friend_info)); // 申请内存
//    for(int i = 0; i < friend_num; i++)
//        rio_readnb(rio_log, &friend_info_array.data[i], sizeof(friend_info)); // 填进去
//    return friend_info_array;
//}
//
////服务器向客户端发送所有相关id和信息
//int update_friend_info_s(int fd_log, rio_t *rio_log)
//{
//    int user_id;
//    client_info cur_friend_info;
//    rio_readnb(rio_log, &user_id, sizeof(int)); // 从客户端接收用户id
//    general_array related_ids_array = listfriendship(user_id);
//    int related_ids_num = related_ids_array.num;
//    int *related_ids = (int*)related_ids_array.data;
//    rio_writen(fd_log, &related_ids_num, sizeof(int)); // 告诉客户端有几个要传
//    for(int i = 0; i < related_ids_num; i++)
//    {
//        ///zzk changed
//        cur_friend_info.id = related_ids[i];
//        client_info tem;
//        tem = getuser(cur_friend_info.id);
//        rio_writen(fd_log,&tem, sizeof(client_info));
//        //向客户端逐条发好友信息
//    }
//}