/*
Problem: Round Robin Algorithms implementation in CPU scheduling using Queue?

In the below section, there is explanation about Preemptive Round Robin Scheduling algorithm. You need to use queue to solve this problem. Consider your program more comprehensive, and it should work for new inserted tasks on the queue without interrupt.

Preemptive Round Robin Scheduling implementation using queue with time-slice. 3 Marks
Implementation of Preemptive RR with different arrival time using queue with time-slice. 3 Marks
Note: Your program should calculate and show Arrival-Time, Burst-Time, Completion-Time, Turn-Around-Time, Waiting-Time. Show the Gantt chart as well. Implement the queue using circular linked list.

Round Robin Scheduling:

In the round robin scheduling, processes are dispatched in a FIFO manner but are given a limited amount of CPU time called a time-slice or a quantum. If a process does not complete before its CPU-time expires, the CPU is preempted and given to the next process waiting in a queue. The preempted process is then placed at the back of the ready list. Round Robin Scheduling is preemptive (at the end of time-slice) therefore it is effective in time-sharing environments in which the system needs to guarantee reasonable response times for interactive users.

Example:

  Consider the set of 5 processes whose arrival time and burst time are given below.

 

Process Id

Arrival time

Burst time

P1

0

5

P2

1

3

P3

2

1

P4

3

2

P5

4

3

 

If the CPU scheduling policy is Round Robin with time quantum = 2 unit, calculate the average waiting time and average turn around time. 

Ready Queue-

P5, P1, P2, P5, P4, P1, P3, P2, P1

Now, we know-

Turn Around time = Exit time – Arrival time
Waiting time = Turn Around time – Burst time
  

Process Id

Exit time

Turn Around time

Waiting time

P1

13

13 – 0 = 13

13 – 5 = 8

P2

12

12 – 1 = 11

11 – 3 = 8

P3

5

5 – 2 = 3

3 – 1 = 2

P4

9

9 – 3 = 6

6 – 2 = 4

P5

14

14 – 4 = 10

10 – 3 = 7

Now,

Average Turn Around time = (13 + 11 + 3 + 6 + 10) / 5 = 43 / 5 = 8.6 unit
Average waiting time = (8 + 8 + 2 + 4 + 7) / 5 = 29 / 5 = 5.8 unit
*/
#include <iostream>
#include <optional>
#include <iomanip>
using namespace std;

// written by group 11: Odd-Harald Lillestø Myhren, Andreas Stiansen, Suleyman 
Selcuk and Shaheen Thayalan
template <typename T>
class Node {
public:
  T value;
  Node* next;
  explicit Node(T value) {
    this->value = value;
  }
};
template <typename T>
class Queue {
  Node<T>* head;
  Node<T>* tail;
public:
  void enqueue(T value) {
    auto node = new Node<T>(value);
    if (this->head) {
      this->tail->next = node;
    } else
      this->head = node;
    this->tail = node;
    this->tail->next = this->head;
  }
  optional<T> dequeue() {
    if (this->head == nullptr)
      return nullopt;
    else if (this->head == this->tail) {
      T value = this->head->value;
      this->head = nullptr;
      this->tail = nullptr;
      return value;
    } else {
      T value = this->head->value;
      this->head = this->head->next;
      this->tail->next = this->head;
      return value;
    }
  }
  Node<T>* getHead() {
      return this->head;
  }
};
class Process {
public:
  int arrival_time;
  int burst_time;
  int exit_time;
  int turn_around_time;
  int waiting_time;
  int remaining_time;
  Process(int arrival_time, int burst_time) {
    this->arrival_time = arrival_time;
    this->burst_time = burst_time;
    this->exit_time = 0;
    this->turn_around_time = 0;
    this->waiting_time = 0;
    this->remaining_time = burst_time;
  }
  void print() const {
    printf("%2d |%2d  | %2d | %2d |%2d\n", arrival_time, burst_time, exit_time, 
turn_around_time, waiting_time);
  }
};
void round_robin(Queue<Process*> queue, int time_quantum) {
  int elapsed_time = 0;
  Node<Process*>* current_process = queue.getHead();
  cout << "Gantt Chart: " << endl;
  while (current_process != nullptr) {
      cout << elapsed_time << " -> P" << current_process->value->arrival_time + 1 
<< " -> ";
      if (current_process->value->remaining_time == time_quantum) {
          elapsed_time += time_quantum;
          current_process->value->exit_time = elapsed_time;
          current_process->value->turn_around_time = elapsed_time - 
current_process->value->arrival_time;
          current_process->value->waiting_time = current_process->value-
>turn_around_time - current_process->value->burst_time;
      }
      else if (current_process->value->remaining_time < time_quantum) {
          elapsed_time += current_process->value->remaining_time;
          current_process->value->exit_time = elapsed_time;
          current_process->value->turn_around_time = elapsed_time - 
current_process->value->arrival_time;
          current_process->value->waiting_time = current_process->value-
>turn_around_time - current_process->value->burst_time;
      }
      else {
          elapsed_time += time_quantum;
          current_process->value->remaining_time -= time_quantum;
      }
      queue.dequeue();
      current_process = queue.getHead();
  }
  cout << "finish" << endl << endl;
}
int main() {
  // | Process Id | Arrival time | Burst time |
  // |------------+--------------+------------|
  // | P1         |            0 |          5 |
  // | P2         |            1 |          3 |
  // | P3         |            2 |          1 |
  // | P4         |            3 |          2 |
  // | P5         |            4 |          3 |
  Process processes[5] = {
    Process(0, 5),
    Process(1, 3),
    Process(2, 1),
    Process(3, 2),
    Process(4, 3),
  };
  // Ready Queue-
  // P5, P1, P2, P5, P4, P1, P3, P2, P1
  Queue<Process*> queue = Queue<Process*>();
  queue.enqueue(&processes[0]);
  queue.enqueue(&processes[1]);
  queue.enqueue(&processes[2]);
  queue.enqueue(&processes[0]);
  queue.enqueue(&processes[3]);
  queue.enqueue(&processes[4]);
  queue.enqueue(&processes[1]);
  queue.enqueue(&processes[0]);
  queue.enqueue(&processes[4]);
  // If the CPU scheduling policy is Round Robin with time quantum = 2 unit,
  // calculate the average waiting time and average turn around time.
  round_robin(queue, 2);
  // Your program should calculate and show Arrival-Time, Burst-Time, Completion-
Time,
  // Turn-Around-Time, Waiting-Time. Show the Gantt chart as well.
  float turn_around_avg = 0;
  float waiting_time_avg = 0;
  cout << "Process chart:" << endl;
  cout << "ID | BT | ET | TT | WT " << endl;
  for (Process process : processes) {
      process.print();
      turn_around_avg += float(process.turn_around_time);
      waiting_time_avg += float(process.waiting_time);
  }
  turn_around_avg /= float(*(&processes + 1) - processes);
  waiting_time_avg /= float(*(&processes + 1) - processes);
  cout << endl;
  cout << "Average Turn Around time: " << turn_around_avg << endl;
  cout << "Average Waiting time: " << waiting_time_avg << endl;
}
    std::cout << "Expression: ";
    std::string input;
    std::getline(std::cin, input);
    std::string prefix = convert(input);
    std::regex whitespace_regex("\\s+");
    std::cout << "Prefix: " << std::regex_replace(prefix, whitespace_regex, " ") <<
std::endl;
    float result = evaluatePrefix(prefix);
    std::cout << "Result: " << result << std::endl;
    return 0;
}