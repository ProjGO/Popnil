//
// Created by yuhaorong on 2019/9/3.
//

#include "../common/include/include.h"
#include "../common/include/rio.h"
#include "../common/include/define.h"
#include "tools.h"


extern int fd_chat;
extern rio_t rio_chat;

extern SunGtkCList* idx2list[100];
extern GtkWidget* idx2window[100];
extern int opend_list_idx2id[100];
extern int max_chat_window_idx;

int id2idx(int id)
{
    for(int i=0; i < max_chat_window_idx; i++)
        if(opend_list_idx2id[i] == id)
            return i;
    return -1;    
}

void *thread_recv_msg(void *vargp)
{
    while(1)
    {
        OP_TYPE op;
        rio_readnb(&rio_chat, &op, sizeof(OP_TYPE));
        switch(op){
            case TEXT_trans:{
                text_pack_t recved_text_pack;
                char recved_text[MAX_MSG_LEN];
                rio_readnb(&rio_chat, &recved_text_pack, sizeof(text_pack_t));
                int source_id = recved_text_pack.id;
                strcpy(recved_text, recved_text_pack.text);
                //opend_list_idx2id[0]= 4;

                int idx = id2idx(source_id);
                sungtk_clist_append(idx2list[idx], recved_text, "../client/images/head_48.png", "F**K YOU",source_id);
                gtk_widget_show_all(idx2window[idx]);
                
                break;
            }
        }
    }
}
