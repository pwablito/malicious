#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/random.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/proc_fs.h>

static void corrupt_memory(void) {
  // Get a random number between 0 and the number of processes
  int num_processes = 0;
  struct task_struct *task;
  for_each_process(task)
    num_processes++;

  int r;
  get_random_bytes(&r, sizeof(int));
  r = r % num_processes;

  int i = 0;
  for_each_process(task) {
    if (i == r) {
      char *p = task->mm->start_code + (task->mm->end_code - task->mm->start_code) / 2;
      get_random_bytes(p, 1);
      break;
    }
    i++;
  }
}

static int __init corruptor_init(void) {
  printk(KERN_INFO "Corruptor: Loaded\n");

  while (1) {
    msleep(5000);
    corrupt_memory();
  }

  return 0;
}

static void __exit corruptor_exit(void) {
  printk(KERN_INFO "Corruptor: Unloaded\n");
}

module_init(corruptor_init);
module_exit(corruptor_exit);

MODULE_LICENSE("GPL");

