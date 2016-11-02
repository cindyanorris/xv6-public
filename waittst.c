#include "types.h"
#include "stat.h"
#include "user.h"
int stdout = 1;
int
main(int argc, char * argv[])
{
   int rpid, pid, i, j;
   blk_t b[] = { BLOCK, BLOCK, NOBLOCK, NOBLOCK};

   //test waitpid four times
   //twice on BLOCK and twice on NOBLOCK
   //once each with pid = -1 
   for (j = 0; j < 4; j++)
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

      if (b[j] == BLOCK) printf(stdout, "BLOCK test\n");  
      else printf(stdout, "NOBLOCK test\n");

      if ((j % 2) == 1)
      { 
         pid = -1;
         printf(stdout, "Wait for any child\n");
      }

      while ((rpid = waitpid(pid, b[j])) == 0)
      {
         //you won't see this output for the BLOCK test
         printf(stdout, "Waiting for process %d to finish\n", pid);
         sleep(10);
      }
      printf(stdout, "Process %d is finished\n", rpid);
   }
   //Test waitpid on a made up pid
   if (waitpid(23456, BLOCK) == -1)
      printf(stdout, "waitpid(23456, BLOCK) passed\n");
   if (waitpid(23457, NOBLOCK) == -1)
      printf(stdout, "waitpid(23457, NOBLOCK) passed\n");
   exit();
}

