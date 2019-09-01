#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <stdbool.h>

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
      printf ("Sucessfully");
    }
  else
    {
      printf ("Failed");
      free (pconn);
      pconn = NULL;
    }
  printf (" connect to %s at %s@%s\n", DB_NAME, DB_USER, DB_HOST);
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
          puts ("Failed to query while judging user!");
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

      if ( !mysql_query (pconn, comm))
        {
          res = mysql_store_result (pconn);
          id = mysql_num_rows (res);
          sprintf (comm, "insert into `userinfo` values (%d, '%s', '%s', null, null, null, null);", id, passwd, nick);
          if ( mysql_query (pconn, comm))
            {
              puts ("Failed to query while adding user!");
              id = -1;
            }
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          puts ("Failed to query while counting users!");
        }
    }

  return id;
}

bool addfriendship (int idA, int idB)
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
              if ( !mysql_query (pconn, comm))
                {
                  suc = true;
                }
              else
                {
                  puts ("Failed to query while adding friendship!");
                }
            }
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          puts ("Failed to query while counting friendships!");
        }
    }
  return suc;
}

bool deletefriendship (int idA, int idB)
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
      if ( !mysql_query (pconn, comm))
        {
          res = mysql_store_result (pconn);
          if ( mysql_num_rows (res) == 0)
            {
              suc = true;
            }
          else
            {
              sprintf (comm, "delete from `friendship` where `idord` = %d and `idnew` = %d;", idord, idnew);
              if ( !mysql_query (pconn, comm))
                {
                  suc = true;
                }
              else
                {
                  puts ("Failed to query while deleting friendships!");
                }
            }
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          puts ("Failed to query while counting friendships!");
        }
    }
  return suc;
}

int main ()
{
  if ( deletefriendship (0, 1) )
    {
      puts("👀");
    }
  else
    {
      puts("😂");
    }
  return 0;
}
