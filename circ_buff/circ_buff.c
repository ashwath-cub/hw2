/* 
 * Author:       Ashwath Gundepally, CU ECEE
 * 
 * File:         circ_buff.c
 * 
 * Description:  Contains an implementation of a circular buffer
 *               that supports basic operations like write an item,
 *               read an item, find size, etc.
 *
 * */


#include "circ_buff.h"
#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<inttypes.h>




/*								                
 * Function:     circ_buff_init(circ_buff_ptr* circ_buff_pointer, int16_t size)
 * -----------------------------------------------------------------------------
 * Description:  Assigns memory specified by 'size' to the circular buffer 
 *               structure pointed to by the pointer argument on the heap. 
 *               Also initialises various parameters to this buffer, like the 
 *               head, tail, total size, and size_occupied, etc.  
 *              
 *           
 * Usage:        Pass a pointer to the ptr of the circular buffer struc which 
 *               needs to be allocated memory on the heap, and a uin32_t type 
 *               specifying the size in that order.
 * 
 * Returns:      Error codes:
 *               CIRC_BUFF_NULL_POINTER: The pointer passed is detected to be a 
 *               null. The function halts execution and returns w/o completion.   
 *                  
 *               CIRC_BUFF_BAD_DATA: The size parameter is less than or equal 
 *               to zero.
 *               
 *               CIRC_BUFF_MALLOC_FAIL: The call to malloc fails.
 *
 *               CIRC_BUFF_SUCCESS: The funcion returns successfully.
 */
circ_buff_code circ_buff_init(circ_buff_ptr* circ_buff_pointer, int32_t size)
{
    /*check if the pointer is NULLi*/
    if(circ_buff_pointer==NULL)                                                 
         return CIRC_BUFF_NULL_PTR;   

    /*assign the circ buff struct on the heap*/
    *(circ_buff_pointer)=(circ_buff_ptr)malloc(sizeof(circ_buff));
    if((*circ_buff_pointer)==NULL)
         return CIRC_BUFF_MALLOC_FAIL;

    /*access the buff pointer and allocate memory on the heap*/ 
    (*circ_buff_pointer)->base=(uint32_t*)malloc(size);                             
    if((*circ_buff_pointer)->base==NULL)
         return CIRC_BUFF_MALLOC_FAIL;

    /*Initialise total and current size to the allocated memory*/
    (*circ_buff_pointer)->size_occupied=0;             
    (*circ_buff_pointer)->total_size=size;
    
    /*Initialise the head and tail positions to base*/
    (*circ_buff_pointer)->head=(*circ_buff_pointer)->base;                        
    (*circ_buff_pointer)->tail=(*circ_buff_pointer)->base;   
    
    /*return successfully*/
    return CIRC_BUFF_SUCCESS;                          
}	


/*								                
 * Function:     circ_buff_destroy(circ_buff_ptr circ_buff_ptr)
 * -----------------------------------------------------------------------------
 * Description:  De-allocates memory on the heap allocated to the circ_buffer_
 *               pointer.
 *               
 *              
 * Usage:        Pass a pointer to the circular buffer struc which needs to be
 *               de-allocated memory on the heap.
 * 
 * Returns:      Error codes:
 *               CIRC_BUFF_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *
 *               CIRC_BUFF_SUCCESS: The function completes execution 
 *               completely.   
 * ----------------------------------------------------------------------------
 */
circ_buff_code circ_buff_destroy(circ_buff_ptr circ_buff_pointer)
{
    /*basic pointer check*/
    if(circ_buff_pointer==NULL)
	 return CIRC_BUFF_NULL_PTR;
    
    /*free the memory of the buffer on the heap*/
    free(circ_buff_pointer->base);

    /*Reassign all the parameters to 0*/
    circ_buff_pointer->size_occupied=0;             
    circ_buff_pointer->total_size=0;
    
    /*assigning NULL to the head and tail ptrs*/
    circ_buff_pointer->head=NULL;                        
    circ_buff_pointer->tail=NULL;   
    
    /*now deallocate the structure*/
    free(circ_buff_pointer);

    /*return safely*/ 
    return CIRC_BUFF_SUCCESS; 
}

/*								                
 * Function:     if_circ_buff_full(circ_buff_ptr circ_buff_ptr)
 * -----------------------------------------------------------------------------
 * Description:  Returns code indicating whether or not the buffer is full
 *              
 * Usage:        Pass a pointer to the circular buff struct and collect status
 *               indicating whether or not the buffer is full in the return 
 *               code
 * 
 * Returns:      Error/Status codes:
 *               CIRC_BUFF_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *               
 *               CIRC_BUFF_FULL: The circular buffer is full.
 * ----------------------------------------------------------------------------
 */
circ_buff_code if_circ_buff_full(circ_buff_ptr circ_buff_pointer)
{
    /*basic pointer check*/	
    if(circ_buff_pointer==NULL)
	 return CIRC_BUFF_NULL_PTR;

    /*collect total and current size values of the buffer in a local variables*/ 
    uint32_t current_buff_size=circ_buff_pointer->size_occupied, total_buff_size= circ_buff_pointer->total_size;
    
    /*check if the buffer is full*/
    if(current_buff_size ==total_buff_size)
	 return CIRC_BUFF_FULL;
    else
	 return CIRC_BUFF_CAN_WRITE; 
}

/*								                
 * Name:         circ_buff_empty(circ_buff_ptr circ_buff_pointer)
 * -----------------------------------------------------------------------------
 * Description:  Returns status code based on whether or not the buffer is empty.
 *               Takes a pointer to the circular buffer
 *               
 * Returns:      Error/status codes:
 *               CIRC_BUFF_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *
 *               CIRC_BUFF_EMPTY: The buffer is currently empty and thus data
 *               cannot be read from it.
 *               
 *               CIRC_BUFF_CAN_READ: The buffer is not empty; data can be read
 * ----------------------------------------------------------------------------
 */
circ_buff_code if_circ_buff_empty(circ_buff_ptr circ_buff_pointer)
{
    /*basic pointer check; error handling*/	
    if(circ_buff_pointer==NULL)
	 return CIRC_BUFF_NULL_PTR;

    /*read current buffer size*/
    uint32_t current_buff_size=circ_buff_pointer->size_occupied;  
    
    /*check if the buffer is emptry*/
    if(current_buff_size ==0)
	 return CIRC_BUFF_EMPTY;
    else
	 return CIRC_BUFF_CAN_READ; 
}


/*								                
 * Name:         circ_buff_write(CIRC_BUFF* circ_buff_ptr, uint8_t data)
 * -----------------------------------------------------------------------------
 * Description:  Writes data to the circular buffer at circ_buff_ptr.
 *               
 * Working:      Writes at location tail+1 if there is space. Calculates space 
 *               first. Returns error if there is no space. Also updates tail 
 *               and the current size occupied upon a successful write.  
 * 
 * Returns:      Error codes:
 *               CIRC_BUFF_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *
 *               CIRC_BUFF_FULL: The buffer is currently full and thus new
 *               data can not be written to it.
 *
 *               CIRC_BUFF_SUCCESS: The function completes execution 
 *               successfully.   
 * ----------------------------------------------------------------------------
 */
circ_buff_code circ_buff_write(circ_buff_ptr circ_buff_pointer, uint32_t data)
{
    /*basic pointer check; error handling*/	
    if(circ_buff_pointer==NULL)
	 return CIRC_BUFF_NULL_PTR;
    
    /*call if_circ_buff_full to check if a write is feasible at all*/
    circ_buff_code if_write_ok=if_circ_buff_full(circ_buff_pointer);
    
    if(if_write_ok!=CIRC_BUFF_CAN_WRITE)
	 return CIRC_BUFF_FULL;

    /*collect total size in a variable*/
    uint32_t total_buff_size= circ_buff_pointer->total_size;
    
    /*grab the tail and write to it*/
    *(circ_buff_pointer->tail)=data;  
    
    /*update tail circularly*/
    if((circ_buff_pointer->tail-circ_buff_pointer->base)!=total_buff_size)
         circ_buff_pointer->tail++;           
    else
	 circ_buff_pointer->tail=circ_buff_pointer->base;

    /*update the size occupied by the buffer*/
    circ_buff_pointer->size_occupied++;
    
    /*return successfully*/
    return CIRC_BUFF_SUCCESS;
}

/*								                
 * Function:     circ_buff_read(circ_buff_ptr circ_buff_pointer, uint32_t* data)
 * -----------------------------------------------------------------------------
 * Description:  Returns data from the circular buffer pointed by circ_buff_ptr, 
 *               based on the current head position in the buffer in the *data
 *               pointer.
 *               
 * Usage:        Pass a pointer to the circular buffer, a pointer to uint8_t 
 *               in that order. The pointer to uint8_t will contain the data
 *               at the head of the circular buffer.
 *                
 * Returns:      Error/Status codes:
 *               CIRC_BUFF_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *               
 *               CIRC_BUFF_EMPTY: The buffer is currently empty and thus can
 *               not return any data.
 *               
 *               CIRC_BUFF_SUCCESS: The function completes execution 
 *               completely.   
 * ----------------------------------------------------------------------------
 */
circ_buff_code circ_buff_read(circ_buff_ptr circ_buff_pointer, uint32_t* data)
{
    /*basic pointer check; error handling*/	
    if(circ_buff_pointer==NULL||data==NULL)
	 return CIRC_BUFF_NULL_PTR;

    /*get buffer status- find if data can be read*/
    circ_buff_code if_read_ok=if_circ_buff_empty(circ_buff_pointer);     
    
    /*check if a read is feasible at all*/ 
    if(if_read_ok!=CIRC_BUFF_CAN_READ)
	 return CIRC_BUFF_EMPTY;                      
    
    /*collect total size in a local variable*/ 
    uint32_t total_buff_size= circ_buff_pointer->total_size;
    
    /*assign the byte located at head to data and complete the read*/
    *data= *(circ_buff_pointer->head);  

    /*update head circularly*/
    if((circ_buff_pointer->head-circ_buff_pointer->base)!=total_buff_size)
         circ_buff_pointer->head++;           
    else
	 circ_buff_pointer->head=(circ_buff_pointer->base);

    /*update the size occupied by the buffer*/
    circ_buff_pointer->size_occupied--;
    
    /*return successfully*/
    return CIRC_BUFF_SUCCESS;
}	

/*								                
 * Function:     circ_buff_dump(circ_buff_ptr cb)
 * -----------------------------------------------------------------------------
 * Description:  Dumps all data from the circular buffer pointed by circ_buff_ptr
 *               in a file in the same directory whose name is defined by FILE_NAME
 *               
 * Usage:        Pass a pointer to the circular buffer.
 * 
 * Returns:      Error/Status codes:
 *               CIRC_BUFF_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *               
 *               CIRC_BUFF_FILE_OPEN_FAILED: Call to fopen failed.
 *
 *               CIRC_BUFF_EMPTY: The buffer is currently empty and thus can
 *               not return any data.
 *               
 *               CIRC_BUFF_SUCCESS: The function completes execution 
 *               completely.
 * ----------------------------------------------------------------------------
 */
circ_buff_code dump(circ_buff_ptr cb)
{
    uint32_t total_size= cb->total_size, index; 
    uint32_t head=cb->head-cb->base, tail=cb->tail-cb->base;
    
    FILE* fp1;
    
    /*get buffer status- find if data can be read*/
    circ_buff_code if_read_ok=if_circ_buff_empty(cb);     
    
    /*check if there's data to be dumped in the first place*/ 
    if(if_read_ok!=CIRC_BUFF_CAN_READ)
	 return CIRC_BUFF_EMPTY;                      
    
    /*open a file*/ 
    fp1=fopen(FILE_NAME, "w+");
    
    if(fp1==NULL)
	 return CIRC_BUFF_FILE_OPEN_FAILED;
    
    /*heading*/ 
    fprintf(fp1, "Buffer Data:\n");
    
    /*handle case by case*/ 
    /*Case 1:*/
    /*Buffer scenario:*/
    /*  ###########************##############             
     *  ^          ^           ^            ^
     *  |          |           |            |
     *  base_ptr   tail_ptr    head_ptr     base_ptr+total_size
     *  #-Data element
     *  *-empty element
     * */
    if(head>tail)
    {
         /*using for loop to print as per the above scenario*/
	 for(index=0; index<tail; index++)
              fprintf(fp1, "%"PRIu32"\t", *(cb->base+index));
         for(index=tail; index<head; index++){
              fprintf(fp1, "*\t");
         }
         for(index=head; index<total_size; index++){
              fprintf(fp1, "%"PRIu32"\t", *(cb->base+index));
         }
    }
    /*Case 2:*/
    /*Buffer scenario:*/
    /*  ***********############**************             
     *  ^          ^           ^            ^
     *  |          |           |            |
     *  base_ptr   head_ptr    tail_ptr     base_ptr+total_size
     *  
     *  '#'-Data element
     *  '*'-empty
     *
     * */
    else{
         /*using for loop to print as per the above scenario*/
         for(index=0; index<head; index++){
              fprintf(fp1, "*\t");
         }
         
         for(index=head; index<tail; index++){
              fprintf(fp1, "%"PRIu32"\t", *(cb->base+index));
         }

         for(index=tail; index<total_size; index++){
              fprintf(fp1, "*\t");
         }
    
    }    
    /*the above scenarios encompass all the buffer states*/ 
    return CIRC_BUFF_SUCCESS;
}
