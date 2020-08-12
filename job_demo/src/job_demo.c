#include <stdio.h>
#include "workq.h"

struct taskq_struct  job;

void  job_func(unsigned long  argv)
{
    printf("this is job function, argv:%s\n", (char *)argv);
}


int main (int argc, char **argv)
{
    int   ret;
    int   change = 1;
    int   times  = 10;
    char  buff1[] = "hello_1";
    char  buff2[] = "hello_2";

    ret = taskq_init(&job, job_func, (unsigned long)buff1);

    if (ret) {
        printf("job_task_init failed!\n");
        return 0;
    }

    while (times--) {
        taskq_schedule(&job);

        taskq_data_update(&job, (unsigned long)(change ? buff2 : buff1));
        change = !change;

        sleep(1);
    }

    taskq_deinit(&job);

    return  (0);
}
