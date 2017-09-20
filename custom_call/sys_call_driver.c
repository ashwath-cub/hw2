#include<unistd.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    uint32_t i=0, loop_index=0;
    FILE* fp;
    fp=fopen("output.txt", "a");
    if(fp==NULL)
         perror("fopen failed\n");
    int32_t* array;
    
    while(loop_index<3)
    {
         uint32_t buffer_size=(256+ rand()%256)*sizeof(int32_t);

         fprintf(fp, "Allocating a buffer of size:%u\n", buffer_size);
         array=(int32_t*)malloc(buffer_size);
         
         if(array==NULL)
              perror("call to malloc failed\n");
         
         fprintf(fp, "unsorted buff:\n ");

         for(i=0; i<buffer_size; i++)
         {
              *(array+i)=rand()%1000;
              fprintf(fp, "%d\t", *(array+i));
         }
   
         fprintf(fp, "\nreturn value: %ld\n", syscall(333, array, buffer_size));
         fprintf(fp, "\nsorted buff:\n   ");
    
         for(i=0; i<buffer_size; i++)
              fprintf(fp, "%d\t", *(array+i));
    
         fprintf(fp, "\n");
         //free(array);
         loop_index++;
    }
    /*invalid arguments*/
    array=NULL; 
    fprintf( fp, "\n\nCalling the syscall with NULL ptr\nreturn value: %ld\n", syscall(333, array, 4));
    fclose(fp);
    return 0;
}
