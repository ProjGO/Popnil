
#include "../common/include/database.h"

#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <stdbool.h>


#include <time.h>

const char DB_HOST[] = "localhost";
const char DB_USER[] = "ProjGO";
const char DB_PASSWD[] = "1234";
const char DB_NAME[] = "linpop";


MYSQL* connect_db (void)
{
  MYSQL* pconn;

  pconn = (MYSQL*) malloc (sizeof (MYSQL));
  mysql_init(pconn);
  if ( mysql_real_connect (pconn, DB_HOST, DB_USER, DB_PASSWD, DB_NAME, 0, NULL, 0) )
    {
      fprintf (stderr, "Sucessfully");
    }
  else
    {
      fprintf (stderr, "Failed");
      free (pconn);
      pconn = NULL;
    }
  fprintf (stderr, " connect to %s at %s@%s\n", DB_NAME, DB_USER, DB_HOST);
  return pconn;


}


bool isuser (const int id, const char passwd[])
{
  MYSQL *pconn;
  MYSQL_RES *res;
  bool ans = false;

  if ( (pconn = connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `userinfo` where `id` = %d and `passwd` = '%s';", id, passwd);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          ans = ( mysql_num_rows (res) > 0 );
          mysql_free_result (res);
        }
      else
        {
          fputs ("Failed to query while judging user!\n", stderr);
        }
    }
  mysql_close (pconn);
  free (pconn);
  return ans;
}

int adduser (const char nick[], const char passwd[])
{
  MYSQL *pconn;
  MYSQL_RES *res;
  int id = -1;

  if ( (pconn = connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `userinfo`;");
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          id = mysql_num_rows (res);
          sprintf (comm, "insert into `userinfo` values (%d, '%s', '%s', 1, '', curdate(), 0, 0);", id, passwd, nick);
          puts (comm);
          if ( mysql_query (pconn, comm) )
            {
              fputs ("Failed to query while adding user!\n", stderr);
              id = -1;
            }
          mysql_free_result (res);
        }
      else
        {
          fputs ("Failed to query while counting users!\n", stderr);
        }
      mysql_close (pconn);
      free (pconn);
    }

  return id;
}

client_info getuser (const int id)
{
  MYSQL *pconn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  client_info ans = {id, "", "", "", "", 0};

  if ( (pconn = connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `userinfo` where `id` = %d;", id);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          if ( mysql_num_rows (res) > 0 )
            {
              row = mysql_fetch_row (res);
              mysql_free_result (res);

              strcpy (ans.passwd, row[1]);
              strcpy (ans.nickname, row[2]);
              ans.portrait_idx = atoi (row[3]);
              strcpy (ans.bio, row[4]);
              strcpy (ans.birthday, row[5]);
            }
          else
            {
              ans.id = -1;
            }
        }
      else
        {
          fputs ("Failed to query while getting user!\n", stderr);
          ans.id=-1;//标识查无此人
        }
      mysql_close (pconn);
      free (pconn);
    }
  return ans;
}

int addgroup (const int ownerid, const char name[])
{
  MYSQL *pconn;
  MYSQL_RES *res;
  int id = -1;

  if ( ( pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `groupinfo`;");
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          id = mysql_num_rows (res);
          sprintf (comm, "insert into `groupinfo` values (%d, '%s', 1, curdate());", id, name);
          puts (comm);
          if ( mysql_query (pconn, comm) )
            {
              fputs ("Failed to query while adding group!\n", stderr);
              id = -1;
            }
          else
            {
              addmembership (id, ownerid);
              setpermission (ownerid, id, owner);
            }
          mysql_free_result (res);
       }
      else
        {
          fputs ("Failed to query while counting groups!\n", stderr);
        }
      mysql_close (pconn);
      free (pconn);
    }
  return id;
}

bool addfriendship (const int idA, const int idB)
{
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `friendship` where (`idA` = %d and `idB` = '%d') or (`idA` = %d and `idB` = %d);", idA, idB, idB, idA);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          if ( mysql_num_rows (res) > 0 )
            {
              suc = true;
            }
          else
            {
              sprintf (comm, "insert into `friendship` values (%d, %d, curdate()), (%d, %d, curdate());", idA, idB, idB, idA);
              puts (comm);
              if ( !mysql_query (pconn, comm) )
                {
                  suc = true;
                }
              else
                {
                  fputs ("Failed to query while adding friendship!\n", stderr);
                }
            }
          mysql_free_result (res);
        }
      else
        {
          fputs ("Failed to query while counting friendships!\n", stderr);
        }
      mysql_close (pconn);
      free (pconn);
    }
  return suc;
}

bool addtag (const int masterid, const int goalid, const char text[])
{
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "insert into `tag` values (%d, %d, '%s');", masterid, goalid, text);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          suc = true;
        }
      else
        {
          fputs ("Failed to query while adding tag.\n", stderr);
        }
      mysql_close (pconn);
      free (pconn);
    }
  return suc;
}

general_array listtag (const int masterid, const int goalid)
{

}

general_array listfriendship (const int id)
{
  MYSQL *pconn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  general_array friends;
  friends.size = sizeof (int);
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select `idB` from `friendship` where `idA` = %d;", id);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          friends.num = mysql_num_rows (res);
          friends.data = (int*)calloc (friends.num, friends.size);
          for (int i = 0; i < friends.num ; i++)
            {
              row = mysql_fetch_row (res);
              ((int*)friends.data)[i] = atoi (row[0]);
            }
          mysql_free_result (res);
        }
      else
        {
          fputs ("Failed to query while counting friendships!\n", stderr);
        }
    }
  mysql_close (pconn);
  free (pconn);
  return friends;
}

bool deletefriendship (const int idA, const int idB)
{
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `friendship` where (`idA` = %d and `idB` = '%d') or (`idA` = %d and `idB` = %d);", idA, idB, idB, idA);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          if ( mysql_num_rows (res) == 0)
            {
              suc = true;
            }
          else
            {
              sprintf (comm, "delete from `usermessage` where (`masterid` = %d and `goalid` = %d) or (`masterid` = %d and `goalid` = %d);", idA, idB, idB, idA);
              puts (comm);
              if ( !mysql_query (pconn, comm) )
                {
                  sprintf (comm, "delete from `tag` where (`masterid` = %d and `goalid` = %d) or (`masterid` = %d and `goalid` = %d);", idA, idB, idB, idA);
                  puts (comm);
                  if ( !mysql_query (pconn, comm) )
                    {
                      sprintf (comm, "delete from `friendship` where (`idA` = %d and `idB` = '%d') or (`idA` = %d and `idB` = %d);", idA, idB, idB, idA);
                      puts (comm);
                      if ( !mysql_query (pconn, comm) )
                        {
                          suc = true;
                        }
                      else
                        {
                          fputs ("Failed to query while deleting friendships!\n", stderr);
                        }
                    }
                  else
                    {
                      fputs ("Failed to query while deleting tags!\n", stderr);
                    }
                }
              else
                {
                  fputs ("Failed to query while deleting usermessages!\n", stderr);
                }
            }
          mysql_free_result (res);
        }
      else
        {
          fputs ("Failed to query while counting friendships!\n", stderr);
        }
      mysql_close (pconn);
      free (pconn);
    }
  return suc;
}

bool addmembership (const int gid, const int uid)
{
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `membership` where `gid` = %d and `uid` = '%d';", gid, uid);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          if ( mysql_num_rows (res) > 0)
            {
              suc = true;
            }
          else
            {
              sprintf (comm, "insert into `membership` values (%d, %d, %d, curdate());", gid, uid, none);
              puts (comm);
              if ( !mysql_query (pconn, comm) )
                {
                  suc = true;
                }
              else
                {
                  fputs ("Failed to query while adding membership!\n", stderr);
                }
            }
          mysql_free_result (res);
        }
      else
        {
          fputs ("Failed to query while counting memberships!\n", stderr);
        }
      mysql_close (pconn);
      free (pconn);
    }
  return suc;
}

bool setpermission (const int gid, const int uid, const Permission permission)
{
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `membership` where `gid` = %d and `uid` = '%d';", gid, uid);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          if ( mysql_num_rows (res) == 0)
            {
              suc = true;
            }
          else
            {
              sprintf (comm, "update `membership` set permission = %d where `gid` = %d and `uid` = %d;", permission, gid, uid);
              puts (comm);
              if ( !mysql_query (pconn, comm) )
                {
                  suc = true;
                }
              else
                {
                  fputs ("Failed to query while setting permission!\n", stderr);
                }
            }
          mysql_free_result (res);
       }
      else
        {
          fputs ("Failed to query while counting memberships!\n", stderr);
        }
      mysql_close (pconn);
      free (pconn);
    }
  return suc;
}

general_array listmembership (const int gid)
{
  MYSQL *pconn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  general_array members;

  members.size = sizeof (int);
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select `uid` from `membership` where `gid` = %d;", gid);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          members.num = mysql_num_rows (res);
          members.data = (int*)calloc (members.num, members.size);
          for (int i = 0; i < members.num ; i++)
            {
              row = mysql_fetch_row (res);
              ((int*)members.data)[i] = atoi (row[0]);
            }
          mysql_free_result (res);
        }
      else
        {
          fputs ("Failed to query while counting memberships!\n", stderr);
        }
    }
  mysql_close (pconn);
  free (pconn);
  return members;
}

general_array listgroup (const int uid)
{
  MYSQL *pconn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  general_array groups;

  groups.size = sizeof (int);
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select `gid` from `membership` where `uid` = %d;", uid);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          groups.num = mysql_num_rows (res);
          groups.data = (int*)calloc (groups.num, groups.size);
          for (int i = 0; i < groups.num ; i++)
            {
              row = mysql_fetch_row (res);
              ((int*)groups.data)[i] = atoi (row[0]);
            }
          mysql_free_result (res);
        }
      else
        {
          fputs ("Failed to query while counting groups!\n", stderr);
        }
    }
  mysql_close (pconn);
  free (pconn);
  return groups;
}

general_array listadministrator (const int gid)
{
  MYSQL *pconn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  general_array administrators;

  administrators.size = sizeof (int);
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select `uid` from `membership` where `gid` = %d and `permission` < %d;", gid, none);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          administrators.num = mysql_num_rows (res);
          administrators.data = (int*)calloc (administrators.num, administrators.size);
          for (int i = 0; i < administrators.num ; i++)
            {
              row = mysql_fetch_row (res);
              ((int*)administrators.data)[i] = atoi (row[0]);
            }
          mysql_free_result (res);
        }
      else
        {
          fputs ("Failed to query while counting administrators!\n", stderr);
        }
    }
  mysql_close (pconn);
  free (pconn);
  return administrators;
}
int getowner (const int gid)
{
  MYSQL *pconn;
  MYSQL_RES *res;
  MYSQL_ROW row;
  int ans;

  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select `uid` from `membership` where `gid` = %d and `permission` = %d;", gid, owner);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          row = mysql_fetch_row (res);
          ans = atoi (row[0]);
          mysql_free_result (res);
        }
      else
        {
          fputs ("Failed to query while searching owwner!\n", stderr);
        }
    }
  mysql_close (pconn);
  free (pconn);
  return ans;
}

bool deletemembership (const int gid, const int uid)
{
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `membership` where `gid` = %d and `uid` = '%d';", gid, uid);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          if ( mysql_num_rows (res) == 0)
            {
              suc = true;
            }
          else
            {
              sprintf (comm, "delete from `groupmessage` where (`masterid` = %d and `goalid` = %d);", uid, gid);
              puts (comm);
              if ( !mysql_query (pconn, comm) )
                {
                  sprintf (comm, "delete from `membership` where `gid` = %d and `uid` = %d;", gid, uid);
                  puts (comm);
                  if ( !mysql_query (pconn, comm) )
                    {
                      suc = true;
                    }
                  else
                    {
                      fputs ("Failed to query while deleting memberships!\n", stderr);
                    }
                }
              else
                {
                  fputs ("Failed to query while deleting groupmessages!\n", stderr);
                }
            }
          mysql_free_result (res);
        }
      else
        {
          fputs ("Failed to query while counting memberships!\n", stderr);
        }
      mysql_close (pconn);
      free (pconn);
    }
  return suc;
}

bool addusermessage (const time_t t, const int masterid, const int goalid, const char text[])
{
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "insert into `usermessage` values (from_unixtime(%ld), %d, %d, '%s');", t, masterid, goalid, text);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          suc = true;
        }
      else
        {
          fputs ("Failed to query while adding user message.\n", stderr);
        }
      mysql_close (pconn);
      free (pconn);
    }
  return suc;
}

bool addgroupmessage (const time_t t, const int masterid, const int goalid, const char text[])
{
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "insert into `groupmessage` values (from_unixtime(%ld), %d, %d, '%s');", t, masterid, goalid, text);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          suc = true;
        }
      else
        {
          fputs ("Failed to query while adding group message.\n", stderr);
        }
      mysql_close (pconn);
      free (pconn);
    }
  return suc;
}



//int main ()
//{
//
//  general_array ad = listgroup (1);
//  for (int i = 0; i < ad.num; i++)
//    {
//      printf("%d\n", ((int*)ad.data)[i]);
//    }
//  //printf("owner: %d\n", getowner (0));
//  return 0;
//}

