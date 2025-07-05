#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

typedef struct {
    int id;
    char name[25];
    char gender;
} Student;

// 子线程的执行流程
void* start_routine(void* args){
    // 不能返回指向该线程栈上数据的指针，因为当线程退出时，该线程的栈会销毁
    //Student* p = (Student*) args;
    Student* p = (Student*) malloc(sizeof(Student));
    // 在子线程中访问主线程栈里面的数据
    p->id = 1;
    strcpy(p->name, "yugin");
    p->gender = 'm';
    pthread_exit((void**) p);
    return NULL;
}

int main(int argc, char* argv[])
{
    // 主线程
    pthread_t tid;
    int err = pthread_create(&tid, NULL, start_routine, NULL);
    if(err){
        error(1, err, "pthread_create");
    }
    Student* result;
    pthread_join(tid, (void**) &result);
    printf("%d %s %c\n",
        result->id,
        result->name,
        result->gender);
    printf("main: child_thread = %lu\n", tid);

    // 注意事项：当主线程终止时，整个进程就终止了
    return 0;
}