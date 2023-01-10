#include "can-driver.h"


void initialize_CAN();
{

}

void read_CAN_signal();
{

}

int8_t write_CAN_signal(int msg)
{
    //can send  = Perform data transfer to CAN bus.
    //can write = Write a set amount of data to the can bus.
    
    //make sure message is less <= 64 bits
    //timeout = Waiting for empty tx mailbox timeout in ms or K_FOREVER.
    
    ret = can_send(*dev, *msg, timeout, can_tx_callback_tcallback_isr)
    return ret
}