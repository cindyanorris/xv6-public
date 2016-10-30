#include "types.h"
#include "stat.h"
#include "user.h"
int stdout = 1;
int
main(int argc, char * argv[])
{
   int rpid, pid, i, j;
   blk_t b = BLOCK;

   //test waitpid twice
   //once on BLOCK and once on NOBLOCK
   for (j = 0; j < 2; j++)
   {
      pid = fork();
      if (pid == 0)
      {
         for (i = 0; i < 100; i++)
         {
            sleep(1);
         }
         exit();
      }

      if (b == BLOCK) printf(stdout, "BLOCK test\n");  
      else printf(stdout, "NOBLOCK test\n");

      while ((rpid = waitpid(pid, b)) == -1)
      {
         //you won't see this output for the BLOCK test
         printf(stdout, "Waiting for process %d to finish\n", pid);
         sleep(10);
      }
      printf(stdout, "Process %d is finished\n", pid);
      b = NOBLOCK;
   }
   //Test waitpid on a made up pid
   if (waitpid(23456, BLOCK) == -1)
      printf(stdout, "waitpid(23456, BLOCK) passed\n");
   if (waitpid(23457, NOBLOCK) == -1)
      printf(stdout, "waitpid(23457, NOBLOCK) passed\n");
   exit();
}

