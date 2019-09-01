#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>

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
  printf (" connect to %s at %s@%s", DB_NAME, DB_USER, DB_HOST);
  return pconn;


}

int isuser (const int id, const char passwd[])
{
  MYSQL *pconn;
  MYSQL_RES *res;
  int ans = 0;

  if ( (pconn= connect_db ()) != NULL )
    {
      char comm[1024] = "\0";
      sprintf (comm, "select * from `userinfo` where `id` = %d and `passwd` = '%s';", id, passwd);
      if ( !mysql_query (pconn, comm))
        {
          res = mysql_store_result (pconn);
          ans = mysql_num_rows (res);
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          puts ("Failed to query!");
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
          sprintf (comm, "insert into `userinfo` values (%d, '%s', '%s', null, null, null, null;", id, nick, passwd);
          if ( mysql_query (pconn, comm))
            {
              puts ("Failed to query!");
              id = -1;
            }
          mysql_free_result (res);
          mysql_close (pconn);
          free (pconn);
        }
      else
        {
          puts ("Failed to query!");
        }
    }

  return id;
}
