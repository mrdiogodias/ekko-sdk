#include "bsp/inc/bsp.h"
#include "bsp/inc/timer.h"
#include "bsp/inc/i2c.h"
#include "threadx/common/inc/tx_api.h"

#define DEMO_STACK_SIZE 512
#define DEMO_QUEUE_SIZE 64

UCHAR stack_thread_0[DEMO_STACK_SIZE];
TX_THREAD thread_0;

UCHAR stack_thread_1[DEMO_STACK_SIZE];
TX_THREAD thread_1;

UCHAR stack_thread_2[DEMO_STACK_SIZE];
TX_THREAD thread_2;

UCHAR stack_thread_3[DEMO_STACK_SIZE];
TX_THREAD thread_3;

UCHAR stack_thread_4[DEMO_STACK_SIZE];
TX_THREAD thread_4;

UCHAR stack_thread_5[DEMO_STACK_SIZE];
TX_THREAD thread_5;

UCHAR stack_thread_6[DEMO_STACK_SIZE];
TX_THREAD thread_6;

UCHAR stack_thread_7[DEMO_STACK_SIZE];
TX_THREAD thread_7;

ULONG counter_t0 = 0;
ULONG counter_t1 = 0;
ULONG counter_t2 = 0;
ULONG counter_t3 = 0;
ULONG counter_t4 = 0;
ULONG counter_t5 = 0;
ULONG counter_t6 = 0;
ULONG counter_t7 = 0;

ULONG thread_2_messages_sent;
ULONG thread_3_messages_received;

TX_QUEUE queue_0;
TX_EVENT_FLAGS_GROUP event_flags_0;
TX_SEMAPHORE semaphore_0;
TX_MUTEX mutex_0;


void thread_0_entry(ULONG thread_input)
{
    UINT status;

    while(1)
    {
        /* Increment the thread counter */
        counter_t0++;

        /* Sleep for 10 ticks.  */
        tx_thread_sleep(10);

        /* Wakeup thread 1 after 5 runs */
        if(counter_t0 == 5) {
            /* Set event flag 0 to wakeup thread 1 */
            status =  tx_event_flags_set(&event_flags_0, 0x1, TX_OR);

            /* Check status */
            if (status != TX_SUCCESS)
                break;
        }
    }
}

void thread_1_entry(ULONG thread_input)
{
    UINT status;
    ULONG actual_flags;

    /* Wait forever for event flag 0 */
    status =  tx_event_flags_get(&event_flags_0, 0x1, TX_OR_CLEAR, &actual_flags, TX_WAIT_FOREVER);

    /* Check status */
    if ((status != TX_SUCCESS) || (actual_flags != 0x1))
        return;

    while(1)
    {
        /* Increment the thread counter */
        counter_t1++;

        /* Sleep for 5 ticks */
        tx_thread_sleep(5);
    }
}

void thread_2_entry(ULONG thread_input)
{
    UINT status;

    while(1)
    {
        /* Increment the thread counter */
        counter_t2++;

        /* Send message to queue 0 */
        status =  tx_queue_send(&queue_0, &thread_2_messages_sent, TX_WAIT_FOREVER);

        /* Check completion status */
        if (status != TX_SUCCESS)
            break;

        /* Increment the message sent */
        thread_2_messages_sent++;

        /* Sleep for 20 ticks */
        tx_thread_sleep(20);
    }
}

void thread_3_entry(ULONG thread_input)
{
    ULONG received_message;
    UINT status;

    while(1)
    {
        /* Increment the thread counter */
        counter_t3++;

        /* Retrieve a message from the queue */
        status = tx_queue_receive(&queue_0, &received_message, TX_WAIT_FOREVER);

        /* Check completion status and make sure the message is what we expected */
        if ((status != TX_SUCCESS) || (received_message != thread_3_messages_received))
            break;
        
        /* Otherwise, all is okay. Increment the received message count */
        thread_3_messages_received++;
    }
}

void thread_4_entry(ULONG thread_input)
{
    UINT status;

    while(1)
    {
        /* Increment the thread counter */
        counter_t4++;

        /* Get the semaphore with suspension */
        status =  tx_semaphore_get(&semaphore_0, TX_WAIT_FOREVER);

        /* Check status */
        if (status != TX_SUCCESS)
            break;

        /* Sleep for 50 ticks to hold the semaphore */
        tx_thread_sleep(50);

        /* Release the semaphore */
        status =  tx_semaphore_put(&semaphore_0);

        /* Check status */
        if (status != TX_SUCCESS)
            break;

        /* Give the semaphore for 150 ticks */
        tx_thread_sleep(150);
    }
}

void thread_5_entry(ULONG thread_input)
{
    UINT status;

    while(1)
    {
        /* Increment the thread counter */
        counter_t5++;

        /* Get the semaphore with suspension */
        status =  tx_semaphore_get(&semaphore_0, TX_WAIT_FOREVER);

        /* Check status */
        if (status != TX_SUCCESS)
            break;

        /* Sleep for 50 ticks to hold the semaphore */
        tx_thread_sleep(50);

        /* Release the semaphore */
        status =  tx_semaphore_put(&semaphore_0);

        /* Check status */
        if (status != TX_SUCCESS)
            break;
    }
}

void thread_6_entry(ULONG thread_input)
{
    UINT status;

    while(1)
    {
        /* Increment the thread counter */
        counter_t6++;

        /* Get the mutex with suspension */
        status =  tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

        /* Check status */
        if (status != TX_SUCCESS)
            break;

        /* Sleep for 50 ticks to hold the mutex */
        tx_thread_sleep(50);

        /* Release the mutex */
        status =  tx_mutex_put(&mutex_0);

        /* Check status */
        if (status != TX_SUCCESS)
            break;

        /* Give the mutex for 50 ticks */
        tx_thread_sleep(50);
    }
}

void thread_7_entry(ULONG thread_input)
{
    UINT status;

    while(1)
    {
        /* Increment the thread counter */
        counter_t7++;

        /* Get the mutex with suspension */
        status =  tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

        /* Check status */
        if (status != TX_SUCCESS)
            break;

        /* Sleep for 50 ticks to hold the semaphore */
        tx_thread_sleep(50);

        /* Release the semaphore */
        status =  tx_mutex_put(&mutex_0);

        /* Check status */
        if (status != TX_SUCCESS)
            break;
    }
}

void tx_application_define(void *first_unused_memory) {
    ULONG queue[DEMO_QUEUE_SIZE];

    tx_thread_create(&thread_0, "thread 0", thread_0_entry, 0,  
                    stack_thread_0, DEMO_STACK_SIZE, 
                    4, 4, TX_NO_TIME_SLICE, TX_AUTO_START);

    tx_thread_create(&thread_1, "thread 1", thread_1_entry, 1,  
                    stack_thread_1, DEMO_STACK_SIZE, 
                    4, 4, TX_NO_TIME_SLICE, TX_AUTO_START);

    tx_thread_create(&thread_2, "thread 2", thread_2_entry, 2,  
                    stack_thread_2, DEMO_STACK_SIZE, 
                    8, 8, 4, TX_AUTO_START);

    tx_thread_create(&thread_3, "thread 3", thread_3_entry, 3,  
                    stack_thread_3, DEMO_STACK_SIZE, 
                    8, 8, 4, TX_AUTO_START);

    tx_thread_create(&thread_4, "thread 4", thread_4_entry, 4,  
                    stack_thread_4, DEMO_STACK_SIZE, 
                    16, 16, TX_NO_TIME_SLICE, TX_AUTO_START);

    tx_thread_create(&thread_5, "thread 5", thread_5_entry, 5,  
                    stack_thread_5, DEMO_STACK_SIZE, 
                    16, 16, TX_NO_TIME_SLICE, TX_AUTO_START);

    tx_thread_create(&thread_6, "thread 6", thread_6_entry, 6,  
                    stack_thread_6, DEMO_STACK_SIZE, 
                    24, 24, TX_NO_TIME_SLICE, TX_AUTO_START);

    tx_thread_create(&thread_7, "thread 7", thread_7_entry, 7,  
                    stack_thread_7, DEMO_STACK_SIZE, 
                    24, 24, TX_NO_TIME_SLICE, TX_AUTO_START);

    /* Create the event flags group used by threads 0 and 1 */
    tx_event_flags_create(&event_flags_0, "event flags 0");

    /* Create the message queue shared by threads 2 and 3 */
    tx_queue_create(&queue_0, "queue 0", TX_1_ULONG, &queue, DEMO_QUEUE_SIZE * sizeof(ULONG));

    /* Create the semaphore used by threads 4 and 5 */
    tx_semaphore_create(&semaphore_0, "semaphore 0", 1);

    /* Create the mutex used by threads 6 and 7 */
    tx_mutex_create(&mutex_0, "mutex 0", 0);
}

int main(int argc, char **argv) {
    /* Configure timer 0 as a 10ms systick */
    TIMER_InitType timer0_values;
    timer0_values.compare_value = SYS_CLK_FREQ / 100;
    timer0_values.auto_reload = 1;
    timer0_values.interrupt_enable = 1;
    TIMER_Initialize(timer0, timer0_values);
	TIMER_Start(timer0);          

	/* ThreadX scheduler */
    tx_kernel_enter();

    /* Unreachable code */
    while (1) {}

    return 0;
}
