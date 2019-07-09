#include <stdio.h>
#include <math.h>

#define SCALE_X 0.29
#define SCALE_Y 0.1953125

int main(int argc, char* argv[])
{
  printf("double scalex[512]={\n");
  for (int i=0;i<512;i++)
    {
      printf("%f,\n",i*SCALE_X);
    }
  printf("}\n");

  printf("double scaley[512]={\n");
  for (int i=0;i<512;i++)
    {
      printf("%f,\n",i*SCALE_Y);
    }
  printf("}\n");
}
