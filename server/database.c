#include "database.h"

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
      if ( !mysql_query (pconn, comm))
        {
          res = mysql_store_result (pconn);
          ans = ( mysql_num_rows (res) > 0 );
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          fputs ("Failed to query while judging user!", stderr);
        }
    }

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
      if ( !mysql_query (pconn, comm))
        {
          res = mysql_store_result (pconn);
          id = mysql_num_rows (res);
          sprintf (comm, "insert into `userinfo` values (%d, '%s', '%s', null, null, null, null);", id, passwd, nick);
          puts ("comm");
          if ( mysql_query (pconn, comm))
            {
              fputs ("Failed to query while adding user!", stderr);
              id = -1;
            }
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          fputs ("Failed to query while counting users!", stderr);
        }
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
      if ( !mysql_query (pconn, comm))
        {
          res = mysql_store_result (pconn);
          id = mysql_num_rows (res);
          sprintf (comm, "insert into `groupinfo` values (%d, '%s', curdate());", id, name);
          puts (comm);
          if ( mysql_query (pconn, comm))
            {
              fputs ("Failed to query while adding group!", stderr);
              id = -1;
            }
          else
            {
              addmembership (id, ownerid);
              setpermission (ownerid, id, owner);
            }
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          fputs ("Failed to query while counting groups!", stderr);
        }
    }

  return id;
}

bool addfriendship (const int idA, const int idB)
{
  int idord, idnew;
  if ( idA < idB )
    {
      idord = idA;
      idnew = idB;
    }
  else
    {
      idord = idB;
      idnew = idA;
    }
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `friendship` where `idord` = %d and `idnew` = '%d';", idord, idnew);
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
              sprintf (comm, "insert into `friendship` values (%d, %d, curdate());", idord, idnew);
              puts (comm);
              if ( !mysql_query (pconn, comm))
                {
                  suc = true;
                }
              else
                {
                  fputs ("Failed to query while adding friendship!", stderr);
                }
            }
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          fputs ("Failed to query while counting friendships!", stderr);
        }
    }
  return suc;
}

bool deletefriendship (const int idA, const int idB)
{
  int idord, idnew;
  if ( idA < idB )
    {
      idord = idA;
      idnew = idB;
    }
  else
    {
      idord = idB;
      idnew = idA;
    }
  MYSQL *pconn;
  MYSQL_RES *res;
  bool suc = false;
  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `friendship` where `idord` = %d and `idnew` = '%d';", idord, idnew);
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
              sprintf (comm, "delete from `usermessage` where (`masterid` = %d and `goalid` = %d) or (`goalid` = %d and `masterid` = %d);", idord, idnew, idord, idnew);
              puts (comm);
              if ( !mysql_query (pconn, comm))
                {
                  sprintf (comm, "delete from `friendship` where `idord` = %d and `idnew` = %d;", idord, idnew);
                  puts (comm);
                  if ( !mysql_query (pconn, comm))
                    {
                      suc = true;
                    }
                  else
                  {
                    fputs ("Failed to query while deleting friendships!", stderr);
                  }
                }
              else
                {
                  fputs ("Failed to query while deleting usermessages!", stderr);
                }
            }
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          fputs ("Failed to query while counting friendships!", stderr);
        }
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
                  fputs ("Failed to query while adding membership!", stderr);
                }
            }
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          fputs ("Failed to query while counting memberships!", stderr);
        }
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
                    fputs ("Failed to query while deleting memberships!", stderr);
                  }
                }
              else
                {
                  fputs ("Failed to query while deleting groupmessages!", stderr);
                }
            }
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          fputs ("Failed to query while counting memberships!", stderr);
        }
    }
  return suc;
}
bool setpermission (const int gid, const int uid, enum Permission permission)
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
                  fputs ("Failed to query while setting permission!", stderr);
                }
            }
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          fputs ("Failed to query while counting memberships!", stderr);
        }
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
          fputs ("Failed to query while adding user message.", stderr);
        }
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
          fputs ("Failed to query while adding group message.", stderr);
        }
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
  deletefriendship (1, 0);
  return 0;
}
