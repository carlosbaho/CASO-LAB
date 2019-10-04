#include <mach.h>
#include <mach_error.h>
#include <mach/mig_errors.h>
#include <mach/thread_status.h>
#include <mach/processor_info.h>
#include <mach/message.h>
#include <stdio.h>
#include <stdlib.h>
#include <hurd.h>


#define PAG_SIZE 16384
#define MAXDATA 3
#define SLEEP_TIME 20

struct{
   mach_msg_header_t header;
}msg;

struct {
       mach_msg_header_t header;
} message;

int main(){
   mach_port_t port;
   mach_port_t parent = mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &port);
   int pid = fork();
   int err;
   
   if(pid < 0) {
      printf("Error forking");
   }
   if(pid == 0){     
      msg.header.msgh_remote_port = port;
      msg.header.msgh_local_port = MACH_PORT_NULL;
      msg.header.msgh_bits = MACH_MSGH_BITS (MACH_MSG_TYPE_MAKE_SEND, MACH_MSG_TYPE_MAKE_SEND_ONCE);
      msg.header.msgh_size = sizeof msg;
      mach_msg_return_t err = mach_msg_send(&msg.header); 
      if (err != MACH_MSG_SUCCESS){
            fprintf(stderr, "Couldn't send uint: 0x%x\n", err); 
      }
      exit(0);
   }
   else if(pid > 0){
       
      mach_msg_return_t err = mach_msg_receive(&message.header, MACH_RCV_MSG | MACH_RCV_INTERRUPT,0, sizeof message, parent,MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL); 
      if(err == MACH_MSG_SUCCESS){
         printf("Message recived");
      }
      int status;
      waitpid(-1, &status, 0);
   
   }
}
