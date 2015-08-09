#include <stdio.h>
#include <sys/ioctl.h>

#define RBUF_SIZE  10000
#define RGAP_US    10
#define FILENAME   "ir_timing.dat"


int main()
{
    const char* fname = FILENAME;
	FILE *fp;
	int rbuf[RBUF_SIZE];
	unsigned int i;
	
   int fd;
   if((fd=open("/dev/ir",0))<0)
   {
     printf ("%d ",fd);
     printf ("open /dev/ir failed\n");
   }
   else
   {
   printf("ir_read...\n");
   while(ioctl(fd,0,0));  //  waite for IR
   for (i=0; i<RBUF_SIZE; i++)
   {
      rbuf[i] =  ioctl(fd,RGAP_US,0);
   }
   fp = fopen (fname, "w");
   fprintf(fp, "#IR timing data, one point per %dus\n",RGAP_US);
   for (i=0; i<RBUF_SIZE; i++)
   {
   fprintf( fp,"%d %d\n",i*RGAP_US,rbuf[i]);
   }
   fclose(fp);
   printf("data is store in %s\n", fname);
   
   close(fd);
    }
   return 0;
}
