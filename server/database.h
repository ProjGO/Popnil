//
// Created by willwang on 19-9-1.
//

#ifndef LINPOP_DATABASE_H
#define LINPOP_DATABASE_H

#include <stdbool.h>
#endif //LINPOP_DATABASE_H

#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <stdbool.h>
#include "../common/include/define.h"
//enum Permission
//{
//  owner,
//  admin,
//  none
//};

MYSQL* connect_db (void);
bool isuser (const int id, const char passwd[]);
int adduser (const char nick[], const char passwd[]);
int addgroup (const int ownerid, const char name[]);
bool addfriendship (const int idA, const int idB);
bool deletefriendship (const int idA, const int idB);
bool addmembership (const int gid, const int uid);
bool deletemembership (const int gid, const int uid);
bool setpermission (const int gid, const int uid, enum Permission permission);
bool setpermission (const int gid, const int uid, enum Permission permission);
bool addusermessage (const time_t t, const int masterid, const int goalid, const char text[]);
bool addgroupmessage (const time_t t, const int masterid, const int goalid, const char text[]);

