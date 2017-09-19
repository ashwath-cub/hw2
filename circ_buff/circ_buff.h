/*Declaring all functions which are defined in data.c*/

#ifndef _CIRC_BUFF_H
#define _CIRC_BUFF_H  
#include<stdint.h>
#define FILE_NAME "stdout"

typedef enum {CIRC_BUFF_SUCCESS, CIRC_BUFF_NULL_PTR, CIRC_BUFF_MALLOC_FAIL, CIRC_BUFF_BAD_DATA, CIRC_BUFF_EMPTY, CIRC_BUFF_FULL, CIRC_BUFF_CAN_WRITE, CIRC_BUFF_CAN_READ, CIRC_BUFF_FILE_OPEN_FAILED} circ_buff_code;


/*								                
 * Structure:    circ_buff 
 * -----------------------------------------------------------------------------
 * Description:  A circular buffer structure that tracks the head, the tail, 
 *               the total size and the current size of the circular buffer.
 *           
 * Usage:        Use regular structure syntax to access any of the members of 
 *               this structure       
 * ----------------------------------------------------------------------------
 */

/*typedef a circ_buff ptr type so that "*" does not have to be used always*/
typedef struct circ_buff *circ_buff_ptr;


typedef struct circ_buff
{
    uint32_t *base;
    uint32_t *head;
    uint32_t *tail;
    uint32_t  total_size;
    uint32_t  size_occupied;
}circ_buff;


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
circ_buff_code circ_buff_init(circ_buff_ptr* circ_buff_pointer, int32_t size);
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
circ_buff_code circ_buff_destroy(circ_buff_ptr circ_buff_pointer);
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
circ_buff_code if_circ_buff_full(circ_buff_ptr circ_buff_pointer);

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
circ_buff_code if_circ_buff_empty(circ_buff_ptr circ_buff_pointer);


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
circ_buff_code circ_buff_write(circ_buff_ptr circ_buff_pointer, uint32_t data);

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
circ_buff_code circ_buff_read(circ_buff_ptr circ_buff_pointer, uint32_t* data);


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
circ_buff_code dump(circ_buff_ptr cb);

#endif    
