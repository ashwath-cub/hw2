#include<stdio.h>
#include<stdlib.h>
#include "doubly_ll.h"
#include "Unity/src/unity.h"

#define FILE_NAME "stdout"



void collect_return(dll_code dll_rc)
{
    
    FILE *fp1=fopen(FILE_NAME, "a+");
    
    if(fp1==NULL)
	 printf("call to fopen returned NULL.\n");
    
    switch(dll_rc)
    {
         case DLL_SUCCESS:
              fprintf(fp1, "status: DLL_BUFF_SUCCESS\n\n");
	      break;
         case DLL_NULL_PTR:
	      fprintf(fp1, "status: DLL_NULL_PTR\n\n");
	      break;
         case DLL_MALLOC_FAIL:
	      fprintf(fp1, "status: DLL_MALLOC_FAIL\n\n");
	      break;
         case DLL_BAD_POSITION:
	      fprintf(fp1, "status: DLL_BAD_POSITION\n\n");
	      break;
         case DLL_DATA_MISSING:
	      fprintf(fp1, "status: DLL_DATA_MISSING\n\n");
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
    uint32_t position=0, data=13;
    dll_code add_node_rc=dll_add_node(&head, position, data);
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to create new dll when it does not exist");
    
    printf("After calling dll_add_node to create the dll\n");
    
    /*dump all the nodes that were allocated to this guy*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head), "Dump fails for some random reason");
    uint32_t size;
    int index;
    
    /*build on this dll-add more nodes*/
    for(index=0; index<5; index++)
    {
         position=index+1;
	 data=index;
	 add_node_rc=dll_add_node(&head, position, data);
	 TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to add nodes at the end");
         
         printf("\nAfter inserting the data element:%u, at position:%u \n", data, position); 
         /*dump all the nodes that were allocated to this guy*/
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head), "Dump fails for some random reason");
    }
    
    /*add more nodes in the middle*/
    for(index=0; index<5; index++)
    {
         TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_size(head, &size), "Something's wrong with the size function");
         
	 position=random()%size;
	 data=random()%25;
	 add_node_rc=dll_add_node(&head, position, data);
	 
	 if(position<=size) 
	 {
	      TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, add_node_rc, "Fails to add nodes in the middle");
              printf("\nAfter inserting the data element:%u, at position:%u \n", data, position); 
              /*dump all the nodes that were allocated to this guy*/
              TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head), "Dump fails for some random reason");
         } 
    }
    printf("\n\nAttempting to add node at location much greater than size\n"); 
    /*lets start slightly complicating things*/
    /*lets call size and pass index greater than size to watch this guy return DLL_BAD_POSITION*/ 
    dll_code size_rc=dll_size(head, &size);
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, size_rc, "Something's wrong with the size function");
    
    position=size+5;
    add_node_rc=dll_add_node(&head, position, data);                                                //data value is irrelevant
    
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_BAD_POSITION, add_node_rc, "Adds nodes even when the position is much greater than the size- stupid.");
    /*dump all the nodes that were allocated to this guy*/
    TEST_ASSERT_EQUAL_INT_MESSAGE(DLL_SUCCESS, dll_dump(head), "Dump fails for some random reason");

    printf("Clearly everything is fine- the dll has not been modified\n");
    
}


int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_add_node);

    return UNITY_END();
}
