#include "link_queue.h"

int main(int argc, char const *argv[])
{
    // 初始化
    link_queue_type_p manager = init_link_queue();

    enQueue(manager, 10);
    enQueue(manager, 20);
    enQueue(manager, 30);
    enQueue(manager, 40);
    enQueue(manager, 50); 
    
    forEach(manager); // 10 20 30 40 50

    outQueue(manager);
    outQueue(manager);
    forEach(manager); // 30 40 50

    enQueue(manager, 60);
    enQueue(manager, 70);
    enQueue(manager, 80); 

    forEach(manager); // 30 40 50 60 70 80

    // 销毁
    destroy(manager); 
}