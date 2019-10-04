#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <mach/processor_info.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>
#include <mach/thread_status.h>
#include <unistd.h>

void lupaso() {
  while(1)  printf("hregh");
}

void error(int res) {
   printf ("Error getting thread_create (0x%x), %s\n", res, 
                mach_error_string(res));
   exit(1);
}

#define STACK_SIZE 4096

int main () {
   int res, i;
   int * p;

   mach_port_t task_child;
   struct i386_thread_state context;
   mach_msg_type_number_t state_count = THREAD_STATE_MAX;

   res = thread_create(mach_task_self(), &task_child);
   if (res != KERN_SUCCESS) error(res);

   res = thread_get_state(task_child, i386_THREAD_STATE, (thread_state_t) &context, &state_count);
   if (res != KERN_SUCCESS) error(res);

   context.eip = (unsigned int) lupaso;
   context.uesp = (unsigned int) malloc(STACK_SIZE) + STACK_SIZE;

   res = thread_set_state(task_child, i386_THREAD_STATE, (thread_state_t) &context, state_count);
   if (res != KERN_SUCCESS) error(res);

   res = mach_setup_tls (task_child);
   if (res != KERN_SUCCESS) error(res);

   res = thread_resume(task_child);
   if (res != KERN_SUCCESS) error(res);

   sleep(10);

   res = thread_terminate(task_child);
   if (res != KERN_SUCCESS) error(res);
}

