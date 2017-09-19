/* 
 * Author:       Ashwath Gundepally, CU ECEE
 * 
 * File:         doubly_ll.c
 * 
 * Description:  Contains an implementation of a doubly linked list
 *               that supports basic operations like write an item,
 *               read an item, find size, etc.
 *
 * */

#include "doubly_ll.h"
#include<stdint.h>
#include<stdlib.h>


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
dll_code dll_add_node(dll_node_ptr* head, uint32_t position, uint32_t data)
{
    /*error handling*/
    if(head==NULL)                                                          //check if the pointer is NULL
         return DLL_NULL_PTR;   

    /* check if the head pointer is NULL; head does not exist 
     * and the position for new node is non-zero. Thus, this 
     * is an illegal request.       
     */  
    if(*head==NULL&&position!=0)
	 return DLL_NULL_PTR;                                               

    /*this case works even if the head is NULL*/
    if(position==0)
    {
         dll_node_ptr new_node=(dll_node_ptr)malloc(sizeof(dll_node));      //allocate memory
	 
	 if(new_node==NULL)
	      return DLL_MALLOC_FAIL;

	 new_node->prev_ptr=NULL;                                           //this is now the head pointer, so the previous should be NULL
	 new_node->next_ptr=*head;                                          //the older version of the head ptr is the next pointer for this linked list
	 new_node->data= data;                                              //assign data
	 if(*head!=NULL)
	      (*head)->prev_ptr=new_node;                                   //link the older head to this new node before modifying the older head
	 *head=new_node;                                                    //position zero is always the head.
         
	 return DLL_SUCCESS;
    }
    else
    {
         dll_node_ptr tmp_head=*head;
         uint32_t index;

	 /*go to index=position-1 in the dll*/
	 for(index=0; index<position-1; index++)
              tmp_head=tmp_head->next_ptr; 
         
         dll_node_ptr new_node=(dll_node_ptr)malloc(sizeof(dll_node));      //allocate memory
	 
	 /*malloc check*/
	 if(new_node==NULL)
	      return DLL_MALLOC_FAIL;
         
	 /*link the new node to the nodes before and after it in the dll*/
	 new_node->prev_ptr=tmp_head;
	 new_node->next_ptr=tmp_head->next_ptr;
        
	 /*link the nodes surrounding the new node to the new node*/ 
         tmp_head->next_ptr=new_node;
	 (new_node->next_ptr)->prev_ptr=new_node;

         return DLL_SUCCESS;                          //return successfully
    } 
}	


/*								                
 * Function:     dll_destroy(dll_node_ptr* head)
 * -----------------------------------------------------------------------------
 * Description:  De-allocates memory on the heap allocated to all the nodes in
 *               the doubly linked list.
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
dll_code dll_destroy(dll_node_ptr head)
{
    //basic pointer check; error handling	
    if(head==NULL)
	 return DLL_NULL_PTR;

    /*assign the head to a tmp pointer*/
    dll_node_ptr tmp_head=head;

    /*free the memory of all the nodes on the heap*/
    while(tmp_head!=NULL)
    {
         head=(head)->next_ptr;                                                 //go to next node
	 free(tmp_head);                                                        //delete current node
	 tmp_head=head;                                                         //assign next node value to a temporary variable
    }

    return DLL_SUCCESS; 
}




/*								                
 * Name:         dll_remove_node(dll_node_ptr* head, uint32_t position)
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
dll_code dll_remove_node(dll_node_ptr head, uint32_t position, uint32_t* data)
{
    //basic pointer check; error handling	
    if(head==NULL)
	 return DLL_NULL_PTR;

    dll_node_ptr tmp_head=head;                                                 //assign head to temp variable

    /*handle position equals zero case*/	 
    if(position==0)
    {
         *data=tmp_head->data;                                                  //get node data in the input pointer parameter

	 if(head->next_ptr!=NULL)                                               //if the next is NULL, the size is 1
	 {    
	      head=head->next_ptr;
	      head->prev_ptr=NULL;
	 }

	 free(tmp_head);
	 return DLL_SUCCESS;
    }
    
    /*check if given position is valid*/
    uint32_t size;
    dll_code size_rc=dll_size(tmp_head, &size);

    if(size_rc!=DLL_NULL_PTR)                                                   //only fail rc for dll_size
    {
         if(position>size-1)                                                    //the position cannot be 2 for a dll of size 2; position starts from 0
              return DLL_BAD_POSITION;
    }    
    else
	 return DLL_NULL_PTR;


    uint32_t index;                                                             //loop variable
    
    /*reach node of position-1*/
    for(index=0; index<position-1; index++)
         tmp_head=tmp_head->next_ptr;
    
    /*store the node to be deleted*/
    dll_node_ptr delete_node=tmp_head->next_ptr;  
    
    /*get node data in the input parameter*/
    *data=delete_node->data;

    /*link the previous and the next node of the node to be deleted appropriately*/
    tmp_head->next_ptr=delete_node->next_ptr;
    
    if(delete_node->next_ptr!=NULL)                                             //complete this only if the next node is not NULL
         (delete_node->next_ptr)->prev_ptr=tmp_head;

    free(delete_node);

    return DLL_SUCCESS;
}

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
dll_code dll_size(dll_node_ptr head, uint32_t* size)
{
    //basic pointer check; error handling	
    if(head==NULL||size==NULL)
         return DLL_NULL_PTR;
    
    dll_node_ptr tmp_head=head;                                                 //assign head to a temp variable
    uint32_t count=0;                                                           //initialise count to zero- this will track the dll's size
    
    /*increment count as long as the node is not a NULL*/
    while(tmp_head!=NULL)           
    {
         tmp_head=tmp_head->next_ptr;
    	 count++;
    }   
    *size=count;                                                                //assign count to the size pointer

    return DLL_SUCCESS;                                                         //return successfully
}	


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
dll_code dll_search(dll_node_ptr head, uint32_t data, uint32_t* position)
{
    //basic pointer check; error handling	
    if(head==NULL||position==NULL)
	 return DLL_NULL_PTR;
    

    dll_node_ptr tmp=head;                                                     //assign the head variable to a temporary variable
    
    /*this variable keeps track of the position*/
    uint32_t count=0;
    
    /*check the entire list to see if data is found*/
    while(tmp!=NULL)
    {
        if(tmp->data==data)                                                     //break out of the loop if data is found
	      break;
	count++;                                                                //increment count to track position of data
	tmp=tmp->next_ptr;                                                      //move to the next node
    }
    
    if(tmp==NULL)                                                               //basically we reached the end of the dll- the break prevents this
    {	
	position=NULL;
	return DLL_DATA_MISSING;
    }	
    else                                                                        //data is found- return position safely
    {	    
	*position=count;
	return DLL_SUCCESS;                                                     
    }
}

