#include <signal.h>
#include <unistd.h>

#include <chrono>
#include <iostream>

int ask_for_pid() {
  int pid;
  std::cout << "Enter PID of the process:" << std::endl;
  std::cin >> pid;
  return pid;
}

int main() {
  pid_t proc[8];
  int status[8];
  double A, B, step;
  int precision, countProc;
  std::cout << "Please, enter A (lower bound): " << std::endl;
  std::cin >> A;
  std::cout << "Please, enter B (upper bound): " << std::endl;
  std::cin >> B;
  std::cout << "Please, enter step for tabulation for each process: "
            << std::endl;
  std::cin >> step;
  std::cout << "Please, enter iteration count for each process (precision): "
            << std::endl;
  std::cin >> precision;
  std::cout << "Please, enter the number of processes: " << std::endl;
  std::cin >> countProc;
  double rangePerProcess = (B - A) / countProc;

  // creation of processes
  for (int i = 0; i < countProc; i++) {
    proc[i] = fork();
    if (proc[i] == -1) {
      std::cout << "Error! Could not create child process" << std::endl;
    } else if (proc[i] == 0) {
      auto a = rangePerProcess * i;
      auto b = rangePerProcess * (i + 1);

      std::cout << "Launch with args:" << a << " " << b << " " << step << " "
                << precision << std::endl;
      auto cmd =
          "\"tell application \\\"Terminal\\\" to do script "
          "\\\"/Users/nickyasnogorodskyi/Documents/personal/university/labs/"
          "3_term/operating_systems/4/program_15 " +
          std::to_string(a) + " " + std::to_string(b) + " " +
          std::to_string(step) + " " + std::to_string(precision) + "\\\"\"";

      std::system(("/usr/bin/osascript -e " + cmd).c_str());
    } else {
      wait(NULL);
    }
  }

  int option;
  while (1) {
    int priority = 0;
    std::cout << std::endl << "Please, choose the action: " << std::endl;
    std::cout << "1. Change priority" << std::endl
              << "2. Suspend process" << std::endl
              << "3. Resume process" << std::endl
              << "4. Kill process" << std::endl
              << "5. Quit" << std::endl;
    std::cin >> option;

    int result;
    switch (option) {
      case 1:
        std::cout << "Enter priority" << std::endl;
        std::cin >> priority;
        result = setpriority(PRIO_PROCESS, ask_for_pid(), priority);
        std::cout << "priority change result: " << result << " errno: " << errno
                  << std::endl;
        break;
      case 2:
        kill(ask_for_pid(), SIGSTOP);
        break;
      case 3:
        kill(ask_for_pid(), SIGCONT);
        break;
      case 4:
        kill(ask_for_pid(), SIGKILL);
        break;
      default:
        return 0;
    }
  }
  return 0;
}
