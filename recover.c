#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(void)
{               

unsigned char buffer[512] = {0};
char jpgName[8] = {0};
int jpgcounter = 0;
FILE* outptr = NULL;

FILE* inptr = fopen("card.raw", "rb");
if (inptr == NULL)
{
    printf("Could not open %s.\n", "card.raw");
    return 1;
}   

while(fread(buffer, sizeof(buffer), 1, inptr) == 1)
{                                   

        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {   
            if(NULL!=outptr)                   
            {
              fclose(outptr);
              outptr = NULL;
            }

            sprintf(jpgName,"%03d.jpg", jpgcounter);

            outptr = fopen(jpgName, "wb");         
            if (NULL == outptr)
            {
              printf("Could not open %s.\n", jpgName);
              return 1;
            }                     

            fwrite(buffer, sizeof(buffer), 1, outptr);

            jpgcounter++;
         }
          else 
         {
             if(NULL != outptr)
                fwrite(buffer, sizeof(buffer), 1, outptr);                              
         }   
    }
 
    if(NULL != outptr)
      fclose(outptr);
    if(NULL != inptr)
      fclose(inptr);

    return 0;   
}
