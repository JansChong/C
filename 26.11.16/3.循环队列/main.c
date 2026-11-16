#include "circular_queue.h"

int main(int argc, char const *argv[])
{

    circular_queue_type_p manager = init_queue(5);

    enQueue(manager, 10);
    enQueue(manager, 20);
    enQueue(manager, 30);
    enQueue(manager, 40);
    enQueue(manager, 50); // 队列已满 无法入队
    forEach(manager); // 10 20 30 40 

    outQueue(manager); 
    outQueue(manager);
    forEach(manager); // 30 40

    enQueue(manager, 60);
    enQueue(manager, 70);
    enQueue(manager, 80); // 队列已满,无法入队
    forEach(manager); // 30 40 60 70

}