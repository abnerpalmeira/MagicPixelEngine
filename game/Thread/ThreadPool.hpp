//
//  ThreadPool.hpp
//  2D Sand
//
//  Created by Abner Palmeira on 05/06/22.
//

#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <stdio.h>
#include <functional>
#include <mutex>
#include <thread>
#include <queue>
#include <vector>
#include "Job.hpp"

class ThreadPool {
public:
    void Start();
    void QueueJob(Job& job);
    void Stop();
    bool busy();

private:
    void ThreadLoop();

    bool should_terminate = false;           // Tells threads to stop looking for jobs
    std::mutex queue_mutex;                  // Prevents data races to the job queue
    std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination
    std::vector<std::thread> threads;
    std::queue<Job*> jobs;
};
#endif /* ThreadPool_hpp */
