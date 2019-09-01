//
// Created by willwang on 19-9-1.
//

#include "login_reg_server.h"
#include "database.h"

response_s2c* check_login(login_info* temp)
{
    response_s2c * s=(response_s2c*)malloc(sizeof(s));
    if(isuser(temp->id,temp->pwd))
    {
        s->return_val=1;
    }
    else
    {
        s->return_val=0;
        strcpy(s->err_msg,"密码错误");
    }
    return s;
}

response_s2c* reg(reg_info_c2s* temp)
{
    response_s2c * s=(response_s2c*)malloc(sizeof(s));
    if(adduser(temp->name,temp->pwd)>=0)
    {
        s->return_val=1;
    }
    else
    {
        s->return_val=0;
        strcpy(s->err_msg,"注册出错");
    }
    return s;
}