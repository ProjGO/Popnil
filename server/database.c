
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

  if ( (pconn= connect_db ()) != NULL )
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

  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `userinfo`;");
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          id = mysql_num_rows (res);
          sprintf (comm, "insert into `userinfo` values (%d, '%s', '%s', null, null, null, null, null);", id, passwd, nick);
          puts ("comm");
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

int addgroup (const int ownerid, const char name[])
{
  MYSQL *pconn;
  MYSQL_RES *res;
  int id = -1;

  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `groupinfo`;");
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          res = mysql_store_result (pconn);
          id = mysql_num_rows (res);
          sprintf (comm, "insert into `groupinfo` values (%d, '%s', curdate());", id, name);
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
  int idold, idnew;
  if ( idA < idB )
    {
      idold = idA;
      idnew = idB;
    }
  else
    {
      idold = idB;
      idnew = idA;
    }
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `friendship` where `idold` = %d and `idnew` = '%d';", idold, idnew);
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
              sprintf (comm, "insert into `friendship` values (%d, %d, curdate());", idold, idnew);
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

general_array listfriendship (const int id)
{
  MYSQL *pconn;
  MYSQL_RES *resnew, *resold;
  MYSQL_ROW row;
  int nold, nnew;
  general_array friends;
  friends.size = sizeof (int);
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select `idold` from `friendship` where `idnew` = %d;", id);
      puts (comm);
      if ( !mysql_query (pconn, comm) )
        {
          resold = mysql_store_result (pconn);
          nold = mysql_num_rows (resold);
          sprintf (comm, "select `idnew` from `friendship` where `idold` = %d;", id);
          puts (comm);
          if ( !mysql_query (pconn, comm) )
            {
              resnew = mysql_store_result (pconn);
              nnew = mysql_num_rows (resnew);
              friends.num = nold + nnew;
              friends.data = (int*)calloc (friends.num, friends.size);
              for (int i = 0; i < nold; i++)
                {
                  row = mysql_fetch_row (resold);
                  ((int*)friends.data)[i] = atoi (row[0]);
                }
              for (int i = nold; i < friends.num ; i++)
                {
                  row = mysql_fetch_row (resnew);
                  ((int*)friends.data)[i] = atoi (row[0]);
                }
              puts ("new");
              mysql_free_result (resold);
              puts ("resold");
              mysql_free_result (resnew);
              puts ("resnew");
            }
          else
            {
              fputs ("Failed to query while counting new friendships!\n", stderr);
            }
        }
      else
        {
          fputs ("Failed to query while counting old friendships!\n", stderr);
        }
    }
  mysql_close (pconn);
  free (pconn);
  return friends;
}

bool deletefriendship (const int idA, const int idB)
{
  int idold, idnew;
  if ( idA < idB )
    {
      idold = idA;
      idnew = idB;
    }
  else
    {
      idold = idB;
      idnew = idA;
    }
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `friendship` where `idold` = %d and `idnew` = '%d';", idold, idnew);
      puts (comm);
      if ( !mysql_query (pconn, comm))
        {
          res = mysql_store_result (pconn);
          if ( mysql_num_rows (res) == 0)
            {
              suc = true;
            }
          else
            {
              sprintf (comm, "delete from `usermessage` where (`masterid` = %d and `goalid` = %d) or (`goalid` = %d and `masterid` = %d);", idold, idnew, idold, idnew);
              puts (comm);
              if ( !mysql_query (pconn, comm))
                {
                  sprintf (comm, "delete from `friendship` where `idold` = %d and `idnew` = %d;", idold, idnew);
                  puts (comm);
                  if ( !mysql_query (pconn, comm))
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
      if ( !mysql_query (pconn, comm))
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
              if ( !mysql_query (pconn, comm))
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
      if ( !mysql_query (pconn, comm))
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
              if ( !mysql_query (pconn, comm))
                {
                  sprintf (comm, "delete from `membership` where `gid` = %d and `uid` = %d;", gid, uid);
                  puts (comm);
                  if ( !mysql_query (pconn, comm))
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
      if ( !mysql_query (pconn, comm))
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
              if ( !mysql_query (pconn, comm))
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
      if ( !mysql_query (pconn, comm))
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
      if ( !mysql_query (pconn, comm))
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


int main ()
{
  int gid;
  printf("%ld\n", time (NULL));
  if ( (gid = addgroup (0, "orzlz")) != -1 )
    {
      puts("👀");
      addmembership (gid, 1);
      setpermission (gid, 1, admin);
      addgroupmessage (time (NULL), 1, gid, "Hi!");
      deletemembership (gid, 1);
    }
  else
    {
      puts("😂");
    }
  addfriendship (1, 0);
  addusermessage (time (NULL), 1, 0, "I am lz.");
  general_array res = listfriendship (1);
  puts ("Start.");
  for (int i = 0; i < res.num; i++)
    {
      printf("%d\n", ((int*)res.data)[i]);
    }
  free (res.data);
  return 0;
}

//int main ()
//{
//  if ( deletefriendship (0, 1) )
//    {
//      puts("👀");
//    }
//  else
//    {
//      puts("😂");
//    }
//  return 0;
//}

