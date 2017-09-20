#include<stdio.h>
#include<stdlib.h>
#include "doubly_ll.h"
#include "Unity/src/unity.h"

#define FILE_NAME "test_results.txt"
#define NON_ZERO_VALUE 12


FILE *fp;


void collect_return(dll_code dll_rc)
{
    
//    FILE *fp1=fopen(FILE_NAME, "a+");
    
    if(fp==NULL)
	 fprintf(fp, "call to fopen returned NULL.\n");
    
    switch(dll_rc)
    {
         case DLL_SUCCESS:
              fprintf(fp, "status: DLL_BUFF_SUCCESS\n\n");
	      break;
         case DLL_NULL_PTR:
	      fprintf(fp, "status: DLL_NULL_PTR\n\n");
	      break;
         case DLL_MALLOC_FAIL:
	      fprintf(fp, "status: DLL_MALLOC_FAIL\n\n");
	      break;
         case DLL_BAD_POSITION:
	      fprintf(fp, "status: DLL_BAD_POSITION\n\n");
	      break;
         case DLL_DATA_MISSING:
	      fprintf(fp, "status: DLL_DATA_MISSING\n\n");
	      break;
	 default:
	      break;
    }	    
    return;

}



void test_add_node(void)
{
    /*check creation of the dll first*/
    dll_node_ptr head=NULL;
    uint32_t position, data=13;
    position=NON_ZERO_VALUE;
    
    /*try to create node at non-zero position when the dll does not exist*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_NULL_PTR, dll_add_node(&head, position, data), "Doesn't return apt code when illegal position is provided");
   
    /*create the dll*/ 
    position=0;
    dll_code add_node_rc=dll_add_node(&head, position, data);
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to create new dll when it does not exist");
    
    fprintf(fp, "After calling dll_add_node to create the dll\n");
    
    /*dump all the nodes that were allocated to this guy*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
    uint32_t size;
    int index;
    fprintf(fp, "Adding more nodes to the end:\n"); 
    /*build on this dll-add more nodes*/
    for(index=0; index<5; index++)
    {
         position=index+1;
	 data=index;
	 add_node_rc=dll_add_node(&head, position, data);
	 TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to add nodes at the end");
         fprintf(fp, "\nAfter inserting the data element:%u, at position:%u \n", data, position); 
         /*dump all the nodes that were allocated to this guy*/
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
    }
    fprintf(fp, "\n Adding more nodes to the middle\n");
    /*add more nodes in the middle*/
    for(index=0; index<5; index++)
    {
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_size(head, &size), "Something's wrong with the size function");
         
	 position=random()%size;
	 data=random()%25;
	 add_node_rc=dll_add_node(&head, position, data);
	 
	 if(position<=size &&position!=0) 
	 {
	      TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to add nodes in the middle");
              fprintf(fp, "\nAfter inserting the data element:%u, at position:%u \n", data, position); 
              /*dump all the nodes that were allocated to this guy*/
              TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
         } 
    }
    fprintf(fp, "\nAdding nodes to the start: \n");
    /*adding nodes at the start */
    position=0;
    for(index=0; index<5; index++)
    {
         data=random()%2500;
	 add_node_rc=dll_add_node(&head, position, data);
	 TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to add nodes in the middle");
         fprintf(fp, "\nAfter inserting the data element:%u, at position:%u \n", data, position); 
         /*dump all the nodes that were allocated to this guy*/
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
    }
    
    
    fprintf(fp, "\n\nAttempting to add node at location much greater than size\n"); 
    
    /*lets start slightly complicating things*/
    /*lets call size and pass index greater than size to watch this guy return DLL_BAD_POSITION*/ 
    dll_code size_rc=dll_size(head, &size);
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, size_rc, "Something's wrong with the size function");
    
    position=size+5;
    add_node_rc=dll_add_node(&head, position, data);                                                //data value is irrelevant
    
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_BAD_POSITION, add_node_rc, "Adds nodes even when the position is much greater than the size- stupid.");
    /*dump all the nodes that were allocated to this guy*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");

    fprintf(fp, "Clearly everything is fine- the dll has not been modified\n");


    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_destroy(head), "Destroy dll func does not return properly");
}

void test_remove_node()
{
    /*check creation of the dll first*/
    dll_node_ptr head=NULL;
    uint32_t position=0, data=13;
    
   
    /*create the dll*/ 
    dll_code add_node_rc=dll_add_node(&head, position, data);
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to create new dll when it does not exist");
    
    fprintf(fp, "After calling dll_add_node to create the dll\n");
    
    /*dump all the nodes that were allocated to this guy*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
    uint32_t size;
    int index;
    
    /*build on this dll-add more nodes*/
    for(index=0; index<15; index++)
    {
         position=index+1;
	 data=random()%300;
	 add_node_rc=dll_add_node(&head, position, data);
	 TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to add nodes at the end"); 
    }
    
    fprintf(fp, "\nAfter creating a dll of size 16: \n"); 
    /*dump all the nodes that were allocated to this guy*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
    
    fprintf(fp, "\nInitiating a series of removes from middle\n"); 
    
    /*remove nodes from the middle*/
    for(index=0; index<10; index++)
    {
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_size(head, &size), "Something's wrong with the size function");
	 
	 position=random()%size;	 
	 if(position<=size && position!=0) 
	 {
	      TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_remove_node(&head, position, &data), "Fails to remove nodes in the middle");
              fprintf(fp, "\nAfter removing the data element:%u, at position:%u \n", data, position); 
              /*dump all the nodes that were allocated to this guy*/
              TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
         } 
    }

    /*replenish the dll again*/
    for(index=0; index<15; index++)
    {
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_size(head, &size), "Something's wrong with the size function");
         position=size;
	 data=random()%300;
	 add_node_rc=dll_add_node(&head, position, data);
	 TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to add nodes at the end"); 
    }
    fprintf(fp, "\n\nAfter repleneshing the DLL again\n");
    /*dump all the nodes that were allocated to this guy*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
    position=0;	 

    fprintf(fp, "\nInitiating a series of removes from start\n"); 
    /*remove nodes from the start*/
    for(index=0; index<10; index++)
    {
	 TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_remove_node(&head, position, &data), "Fails to remove nodes in the middle");
         fprintf(fp, "\nAfter removing the data element:%u, at position:%u \n", data, position); 
         /*dump all the nodes that were allocated to this guy*/
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason"); 
    }


    /*replenish the dll again*/
    for(index=0; index<15; index++)
    {
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_size(head, &size), "Something's wrong with the size function");
         position=size;     //that data gets inserted right at the end
	 data=random()%30;
	 add_node_rc=dll_add_node(&head, position, data);
	 TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to add nodes at the end"); 
    }

    fprintf(fp, "\n\nAfter repleneshing the DLL again\n");
    /*dump all the nodes that were allocated to this guy*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
    
    fprintf(fp, "\nInitiating a series of removes from the end\n"); 
    /*remove nodes from the end*/
    for(index=0; index<10; index++)
    {
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_size(head, &size), "Something's wrong with the size function");
	 
	 position=size-1;	     //this way the last node is referenced always 
	 if(position<=size && position!=0) 
	 {
	      TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_remove_node(&head, position, &data), "Fails to remove nodes in the middle");
              fprintf(fp,"\nAfter removing the data element:%u, at position:%u \n", data, position); 
              /*dump all the nodes that were allocated to this guy*/
              TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
         } 
    }

    fprintf(fp, "\nInitiating a series of removes that are out of bounds\n"); 
    /*updating the size variable again*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_size(head, &size), "Something's wrong with the size function");
    /*attempt removing nodes at positions which are beyond the dll*/
    for(index=0; index<10; index++)
    {
	 position=size+index;	     //this way the position is always out of bounds
	 TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_BAD_POSITION, dll_remove_node(&head, position, &data), "rc!=bad position when position>size remove is requested");
         fprintf(fp,"\nAfter trying to removing the element at position:%u when the size is a max: %u\n", position, size); 
         /*dump all the nodes that were allocated to this guy*/
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason"); 
    }
    /*try to remove nodes from a dll that does not exist*/
    head=NULL;
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_NULL_PTR, dll_remove_node(&head, position, &data), "rc!=DLL_NULL_PTR when remove from a non existant dll is requested");
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_NULL_PTR, dll_remove_node(NULL, position, &data), "rc!=DLL_NULL_PTR when remove from a non existant dll is requested");
    
}

void test_search(void)
{

    /*check creation of the dll first*/
    dll_node_ptr head=NULL;
    uint32_t position=0, data=0;
    
   
    /*create the dll*/ 
    dll_code add_node_rc=dll_add_node(&head, position, data);
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to create new dll when it does not exist");
    
    fprintf(fp, "After calling dll_add_node to create the dll\n");
    
    /*dump all the nodes that were allocated to this guy*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
    int index;
    
    /*use this guy to store all the data values that will be in the dll*/
    uint32_t data_arr[16]; 
    *data_arr=0;
    /*build on this dll-add more nodes*/
    for(index=0; index<15; index++)
    {
         position=index+1;
	 *(data_arr + index+1)=(index+1)*5;
	 add_node_rc=dll_add_node(&head, position, *(data_arr+ index+1));
	 TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to add nodes at the end"); 
    }
    
    fprintf(fp, "\nAfter creating a dll of size 16: \n"); 
    /*dump all the nodes that were allocated to this guy*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason");
    
    fprintf(fp, "\nDemonstrating that the search function returns position accurately:\n");

    /*attempt searching the dll for data that exists- this is why it made sense to store the data in an array before adding it to the dll*/
    for(index=0; index<16; index++)
    {
	 TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_search(head, *(data_arr+index), &position), "rc!=DLL_SUCCESS when arguments are valid");
	 TEST_ASSERT_EQUAL_INT_MESSAGE(index, position, "position found is not valid");
	 
	 fprintf(fp,"\nFound data element %u, at position: %u\n", *(data_arr+index), position); 

         /*dump all the nodes that were allocated to this guy*/
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head, fp), "Dump fails for some random reason"); 
    }

    /*attempt searching the dll for data that DNE*/
    for(index=0; index<16; index++)
	 TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_DATA_MISSING, dll_search(head, *(data_arr+index)+1, &position), "rc!=DLL_DATA_MISSING when arguments are valid");
    
    /*attempt searching for data in a dll that DNE*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_NULL_PTR, dll_search(NULL, *(data_arr+index), &position), "rc!=DLL_NULL_PTR when arguments are invalid");

    /*attempt searching for data when the pointer to the position is NULL*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_NULL_PTR, dll_search(head, *(data_arr+index), NULL), "rc!=DLL_NULL_PTR when arguments are invalid");
       
}

int main()
{
    fp=fopen(FILE_NAME, "a");

    UNITY_BEGIN();
    fprintf(fp, "\n\nUnit test for the dll_add_node function:\n\n");
    RUN_TEST(test_add_node);

    fprintf(fp, "\n\nUnit test for the dll_remove_node function:\n\n");
    RUN_TEST(test_remove_node);
     
    fprintf(fp, "\n\nUnit test for the search function:\n\n");
    RUN_TEST(test_search);
    
    
    
    fclose(fp);
    return UNITY_END();
}
