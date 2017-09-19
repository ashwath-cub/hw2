
/* 
 * Author:       Ashwath Gundepally, CU ECEE
 * 
 * File:         doubly_ll.h
 * 
 * Description:  Contains all function prototypes, enums of the doubly linked list
 *               that supports basic operations like write an item,
 *               read an item, find size, etc. defined in doubly_ll.c in the same
 *               directory
 *
 * */

#ifndef _DLL_H_
#define _DLL_H_

#include<stdint.h>

/*various status codes returned by functions*/
typedef enum {DLL_SUCCESS, DLL_NULL_PTR, DLL_MALLOC_FAIL, DLL_BAD_POSITION, DLL_DATA_MISSING} dll_code;


/*								                
 * Structure:    doubly linked list(dll) node 
 * -----------------------------------------------------------------------------
 * Description:  This structure 
 *           
 * Usage:        Use regular structure syntax to access any of the members of 
 *               this structure       
 * ----------------------------------------------------------------------------
 */
typedef struct dll_node *dll_node_ptr;

typedef struct dll_node
{
    dll_node_ptr next_ptr;
    dll_node_ptr prev_ptr;
    uint32_t data;
}dll_node;



/*								                
 * Function:     dll_add_node(dll_node_ptr* head, uint32_t data, uint32_t position)
 * -----------------------------------------------------------------------------
 * Description:  Assigns memory specified by 'size' to the circular buffer 
 *               structure pointed to by the pointer argument on the heap. 
 *               Also initialises various parameters to this buffer, like the 
 *               head, tail, total size, and size_occupied, etc.  
 *              
 *           
 * Usage:        Pass a pointer to the pointer to the head node of the ll.
 *               If the linked list does not exit, pass a pointer to NULL
 *               and enter zero for the position index.
 *               If a non-null head is detected with position zero, a new node
 *               will be created at position zero.
 * 
 * Returns:      Error codes:
 *               DLL_NULL_POINTER: The pointer passed is detected to be a 
 *               null. The function halts execution and returns w/o completion.   
 *                  
 *               DLL_BAD_DATA: The size parameter is less than or equal 
 *               to zero.
 *               
 *               DLL_MALLOC_FAIL: The call to malloc fails.
 *
 *               DLL_SUCCESS: The funcion returns successfully.
 */
dll_code dll_add_node(dll_node_ptr* head, uint32_t position, uint32_t data);
/*								                
 * Function:     dll_destroy(dll_node_ptr head)
 * -----------------------------------------------------------------------------
 * Description:  De-allocates memory on the heap allocated to all the nodes in
 *               the doubly linked list.
 *               
 *              
 * Usage:        Pass a pointer the head of the dll.
 * 
 * Returns:      Error codes:
 *               DLL_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *
 *               DLL_SUCCESS: The function completes execution 
 *               completely.   
 * ----------------------------------------------------------------------------
 */
dll_code dll_destroy(dll_node_ptr head);

/*								                
 * Name:         dll_remove_node(dll_node_ptr head, uint32_t position)
 * -----------------------------------------------------------------------------
 * Description:  Removes node from the dll safely at a given index.
 *               
 * Working:      Takes a ptr to the head and traverses the dll to reach 
 *               position-1, grabs node at position and frees its memory. Links 
 *               node before and after position safely. Returns node data in
 *               the pointer passed.
 * 
 * Returns:      Error codes:
 *               DLL_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *
 *               DLL_BAD_POSITION: The dll's size is lesser than the position
 *               specified.
 *
 *               DLL_SUCCESS: The function completes execution successfully   
 * ----------------------------------------------------------------------------
 */
dll_code dll_remove_node(dll_node_ptr head, uint32_t position, uint32_t* data);


/*								                
 * Function:     dll_size(dll_node_ptr head, uint32_t* size)
 * -----------------------------------------------------------------------------
 * Description:  Returns size of the dll whose head is given by *head.
 *      
 * Usage:        Pass a pointer to the head of the dll, a pointer
 *               to a uint32_t type in that order. The pointer to uint32_t will 
 *               contain the size of the dll.
 *                
 * Returns:      Error codes:
 *               DLL_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *
 *               DLL_SUCCESS: The function completes execution successfully.   
 * ----------------------------------------------------------------------------
 */
dll_code dll_size(dll_node_ptr head, uint32_t* size);


/*								                
 * Function:     dll_search(dll_node_ptr head, uint32_t data, uint32_t* position)
 * -----------------------------------------------------------------------------
 * Description:  Returns the position of the node containing the data input via a 
 *               input pointer of the dll with the head pointer equal to head.
 *               
 * Usage:        Checks to see if the data element is there in each node starting
 *               from head. Returns the position of the first node which has the
 *               data. Sets position pointer to NULL and passes apt return code
 *               to indicate data was not found.
 *               
 *
 * Returns:      Error codes:
 *               DLL_NULL_PTR: The pointer passed to the function is a
 *               NULL and is thus invalid. The function halts execution and 
 *               returns.
 *
 *               DLL_DATA_MISSING: The data requested to be searched was not
 *               found present in any of the nodes.
 *
 *               DLL_SUCCESS: The function completes execution 
 *               successfully- the data is found.
 * ----------------------------------------------------------------------------
 */
dll_code dll_search(dll_node_ptr head, uint32_t data, uint32_t* position);
#endif
