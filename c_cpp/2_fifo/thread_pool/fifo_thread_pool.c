
#include <pthread.h>
#include <stdbool.h>
#include "fifo_thread_pool.h"

// 线程入口函数指针
typedef int (*THREAD_ENTRANCE) (void* arg,sc_bool * pisRunning);

typedef struct Thread_ {
    void *arg;
    pthread_t  tid;
    bool; isRunning;
    THREAD_ENTRANCE entry;
    pthread_attr_t attr;

}Thread;

// 线程任务函数指针
typedef void (*TaskFunc) (void* arg);

// 线程池中的一个任务：数据和方法
typedef struct ThreadTask_
{
	// 执行线程的函数指针
	TaskFunc threadFunc;
	void *arg;

}ThreadTask;

// 线程池数据结构
typedef struct ThreadPool_
{
	// 伪代码
	// fifoList 中的任务要放到 pThreadPool 执行
	
	// int close; 				// 线程池是否销毁标志
	// int maxThreadCount;		// 线程池中允许活动的最大线程数目
	// int curFifoCount;		// 当前等待的任务数量
	// 
	// fifo fifoList; 			// member: ThreadTask，线程池中所有等待的任务
	// Thread **pThreadPool;	// 线程数组
	
}ThreadPool;


/**
 * 1. 线程池创建
 * 		根据线程池的大小size，提前创建size个线程，存进数组
 * 		
 * 2. 线程池销毁
 * 
 * 3. 向线程池中添加一个任务，及入队列 fifoList
 * 4. 从任务队列fifoList中读取任务，执行任务
 * 
 */