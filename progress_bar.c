#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
 const int BAR_len =50;
 const int Max_task=5;
 
 typedef struct 
 {
    int id;
    int progress;
    int step;
    
 }Task;
 void BAR_function(Task task);
 void screen_clear();
int main()
{
   Task  task[Max_task];
   srand(time(NULL));
for(int i=0;i<Max_task;i++ )
{
task[i].id=i+1;
task[i].progress=0;
task[i].step=rand()%5+1;
}
int Task_incomplet =1;
while(Task_incomplet)
{Task_incomplet=0;
screen_clear();
for(int i=0;i<Max_task;i++)
{
    task[i].progress += task[i].step;
if (task[i].progress>100)
{
    task[i].progress=100;
}
else if(task[i].progress<100)
    {
        Task_incomplet=1;
    }  
BAR_function(task[i]);
}
sleep(1);  //sleep for 1 sec
}
printf("All tasks completed");
return 0;
}
void BAR_function(Task task)
{
int bar_progrss = (BAR_len*task.progress)/100;
printf("Task %d: [",task.id);
for(int i=0; i<BAR_len;i++)
{
if(i<bar_progrss)
{
    printf("=");
}
else
{
    printf(" ");
}
}
printf("] %d%%\n",task.progress);
}
void screen_clear()
{


    printf("\033[2J\033[H");
    fflush(stdout);
}



    


