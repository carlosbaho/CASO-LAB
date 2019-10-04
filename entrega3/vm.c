#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <mach/processor_info.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>
#include <mach/vm_prot.h>
#include <unistd.h>

#define pag_size 16384

int error(int res) {
   printf ("Error getting task created (0x%x), %s\n", res, 
                mach_error_string(res));
   exit(1);
}


int main () {
   int res, i;
   vm_address_t address;
   char data[pag_size] __attribute__((aligned(pag_size)));
   task_t task_child;


   res = task_create(mach_task_self(), FALSE,  &task_child);
   if (res != KERN_SUCCESS) error(res);

   res = vm_allocate(task_child, &address, pag_size, FALSE);
   if (res != KERN_SUCCESS) error(res);
   
   res = vm_write(task_child, address, (pointer_t) data, (mach_msg_type_number_t) pag_size); 
   if (res != KERN_SUCCESS) error(res);

   sleep(30);

   res = task_terminate(task_child);
   if (res != KERN_SUCCESS) error(res);

}   
