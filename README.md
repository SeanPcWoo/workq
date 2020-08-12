# workq
SylixOS 下的一个工作队列工具

接口使用说明：

创建一个工作队列

```
int taskq_init (struct taskq_struct *t, void (*func)(unsigned long), unsigned long data)
```

struct taskq_struct 可以自己填充 job_q_name ，从而指定队列名称，如果不填，则使用默认的队列名称；



删除一个工作队列

```
void taskq_deinit(struct taskq_struct *t);
```



通知一个队列进行任务执行

```
int taskq_schedule (struct taskq_struct *t);
```



更新一个工作队列执行函数的参数

```
int taskq_data_update (struct taskq_struct *t, unsigned long data);
```





