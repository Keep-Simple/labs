#include <pthread.h>
#include <semaphore.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <thread>

int duration;
int sched_policy = SCHED_RR;
int sleep_time;

std::vector<double> numbers;
double resulting_sum = 0;

struct parameters {
  int from;
  int to;
  int method;
  bool with_sleep;
};

sem_t sum_semaphore;
pthread_spinlock_t sum_spinlock;
std::vector<pthread_t> thread_ids;

int thread_count = 0;

class Rand_double {
 public:
  Rand_double(double low, double high)
      : r(std::bind(std::uniform_real_distribution<>(low, high),
                    std::default_random_engine())) {}

  double operator()() { return r(); }

 private:
  std::function<double()> r;
};

void *count_array_sum(void *lparams) {
  parameters *params = (parameters *)lparams;
  // perform calculations
  int partial_sum = 0;
  for (int idx = params->from; idx < params->to; idx++) {
    partial_sum += numbers[idx];
  }

  // updated shared variable
  if (params->method == 1) {
    sem_wait(&sum_semaphore);
    resulting_sum += partial_sum;
    sem_post(&sum_semaphore);
  } else {
    pthread_spin_lock(&sum_spinlock);
    resulting_sum += partial_sum;
    pthread_spin_unlock(&sum_spinlock);
  }

  if (params->with_sleep) {
    sleep(sleep_time);
  }
}

void *_run_find_array_sum(void *) {
  const auto begin = std::chrono::high_resolution_clock::now();

  // wait for threads to complete
  for (int i = 0; i < thread_ids.size(); i++) {
    pthread_join(thread_ids[i], NULL);
  }

  const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::high_resolution_clock::now() - begin)
                            .count();
  std::cout << "\n-------------\nComputed sum: " << resulting_sum << "\n";
  std::cout << "Time taken: " << duration << "ms\n-------------\n";
  // cleanup
  resulting_sum = 0;
  numbers.clear();
  thread_ids.clear();
  thread_count = 0;
}

void option_find_array_sum(bool with_sleep) {
  parameters *params;
  int method = 0;
  int nums_size = 0;
  Rand_double rd{1, 1000};

  if (with_sleep) {
    std::cin.ignore();
    std::cout << "Enter sleep time: ";
    std::cin >> sleep_time;
  }

  std::cin.ignore();
  std::cout << "Enter array size: ";
  std::cin >> nums_size;

  numbers.reserve(nums_size);
  for (int i = 0; i < nums_size; i++) {
    numbers.push_back(rd());
  }

  std::cin.ignore();
  std::cout << "Enter thread amount: ";
  std::cin >> thread_count;

  std::cout << "Choose method:\n0. Spinlock\n1. Semaphore\n";
  std::cin >> method;
  std::cin.ignore();

  int batch_size = numbers.size() / thread_count;
  int bonus_size = numbers.size() - batch_size * thread_count;
  pthread_t thread_id;

  for (int from = 0, to = batch_size; from < numbers.size();
       from = to, to = from + batch_size) {
    if (bonus_size) {
      to++;
      bonus_size--;
    }
    params = new parameters();
    params->from = from;
    params->to = to;
    params->method = method;
    params->with_sleep = with_sleep;

    pthread_attr_t attrs;
    pthread_attr_init(&attrs);
    if (pthread_attr_setschedpolicy(&attrs, sched_policy)) {
      std::cout << "Failed setting sched_policy";
    }
    pthread_create(&thread_id, &attrs, count_array_sum, params);
    pthread_attr_destroy(&attrs);

    thread_ids.push_back(thread_id);
  }

  pthread_create(&thread_id, NULL, _run_find_array_sum, NULL);
  pthread_detach(thread_id);
}

void option_list_threads() {
  struct sched_param param;
  for (int i = 0; i < thread_ids.size(); i++) {
    pthread_getschedparam(thread_ids[i], &sched_policy, &param);
    std::cout << "idx: " << i << " | tid: " << thread_ids[i]
              << " | prio: " << param.sched_priority
              << " | max prio: " << sched_get_priority_max(sched_policy)
              << std::endl;
  }
}

pthread_t prompt_thread_id() {
  int index = 0;
  std::cout << "Enter idx: ";
  std::cin >> index;
  return thread_ids[std::min(index, thread_count - 1)];
}

void option_renice() {
  auto thread_id = prompt_thread_id();
  struct sched_param param;
  int priority = 0;

  std::cout << "Enter priority: \n";
  std::cin >> priority;

  param.sched_priority = priority;
  if (pthread_setschedparam(thread_id, sched_policy, &param)) {
    std::cout << "couldn't change prio";
  }
}

void option_detach() {
  if (pthread_detach(prompt_thread_id())) {
    std::cout << "couldn't detach thread";
  } else {
    std::cout << "thread has been detached\n";
  }
}

void option_cancel() {
  if (pthread_cancel(prompt_thread_id())) {
    std::cout << "couldn't cancel thread" << std::endl;
  } else {
    std::cout << "thread has been canceled" << std::endl;
  }
}

void option_exit() {
  pthread_spin_destroy(&sum_spinlock);
  sem_destroy(&sum_semaphore);
}

int main(int argc, char *argv[]) {
  pthread_spin_init(&sum_spinlock, PTHREAD_PROCESS_PRIVATE);
  sem_init(&sum_semaphore, 0, 1);

  char option;
  while (true) {
    std::cout << "Choose option:\n"
                 "f. Find array sum\n"
                 "F. Find array sum with sleep\n"
                 "p. Change thread prio\n"
                 "d. Detach thread\n"
                 "c. Cancel thread\n"
                 "l. List threads\n"
                 "q. Exit\n"
                 "Enter choice: ";
    std::cin >> option;
    std::cout << std::endl;

    switch (option) {
      case 'f':
        option_find_array_sum(false);
        break;
      case 'F':
        option_find_array_sum(true);
        break;
      case 'p':
        option_renice();
        break;
      case 'd':
        option_detach();
        break;
      case 'c':
        option_cancel();
        break;
      case 'l':
        option_list_threads();
        break;
      case 'q':
        option_exit();
        return 0;
    }

    std::cout << "\n\n";
  }
}
