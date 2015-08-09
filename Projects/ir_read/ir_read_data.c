#include <stdio.h>
#include <sys/ioctl.h>


#define RGAP_US    10
#define HHT_US     3600
#define HLT_US     3600
#define IHT_US     400
#define ILT_US    1000
#define OHT_US     400
#define OLT_US     400

int main()
{
   unsigned int i,j,k;
   unsigned int rdata[10];
	
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
   // skip AGC burst
   for (i=HHT_US/RGAP_US; i>0; i--)
   {
      if(ioctl(fd,RGAP_US,0)) break;
   }
   if (i>0)
   {
      printf("AGC error\n");
      return -1;
   }
   while (!ioctl(fd,0,0));
   // skip space
  for(i=HLT_US/RGAP_US; i>0; i--)
  {
   if (!ioctl(fd,RGAP_US,0)) break;
  }
   if (i>0)
  {
   printf("space error\n");
   return -1;
  }
  while(ioctl(fd,0,0));
  for(i=0; i<4; i++)
   {
     rdata[i] = 0;
     for (j=0; j<8; j++)
     {
      k = 0;
      rdata[i] <<= 1;
      while(!ioctl(fd,RGAP_US,0));
      while(ioctl(fd,RGAP_US,0)) 
        k++;
      if (k>ILT_US/RGAP_US)
        rdata[i] |= 0x01;
     }
   }
   printf("  %d %d %d %d  \n", rdata[0],rdata[1],rdata[2],rdata[3]);
   
   close(fd);
    }
   return 0;
}
