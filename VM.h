#ifndef VM_H
#define VM_H

#include "main.h"
#define MAX 1000

class VM
{
public: 
  VM(){}
  bool running = true;
  string mem[1000], temp[1000];
  string content;
  void run(string filename);
  void add_code_memory(string content);
  void execute_register (int i);
  template<typename T>
  struct reg {
    int num_ip,ip = 0;
    T registers[15] = {"R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15"};
    string kind = "";
    T operand_1, operand_2 = "";
  };
  reg<string> *checker = new reg<string> ();
  template<typename T>
  struct static_memory {
    string id[15] = {}; //address A
    T labels [15] = {"R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15"};
    T value [15] = {"R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15"};
    bool compare_check[15] {};
    int size_mem ;
  };
  static_memory<string> *addr = new static_memory<string> ();

struct stack
{
  int top = -1;
  int a[MAX];
}; 
stack *stacker = new stack();
  bool push (int x) {
    bool ok = false;
    
    if (stacker->top > 1000) {

        throw(StackFull(checker->ip));
    }
    else {
        stacker->a[++stacker->top] = x;
        ok = true;
    }
    return ok;
  }
  int pop() {
     if (stacker->top < 0) {
        cout << "Stack Underflow";
        return 0;
    }
    else {
        int x = stacker->a[stacker->top--];
        return x;
    }
  }
  int peek() {
    if (stacker->top < 0) {
        cout << "Stack is Empty";
        return 0;
    }
    else {
        int x = stacker->a[stacker->top];
        return x;
    }
  }
  bool isEmpty() {
    return (stacker->top < 0);
  }
  void action_move(string input);
  void action_store(string input);
  void action_load(string input);
  void action_output(string input);
  void action_add(string input);
  void action_minus(string input);
  void action_mul(string input);
  void action_div(string input);
  void action_CmpEQ(string input);
  void action_CmpNE(string input);
  void action_CmpLT(string input);
  void action_CmpLE(string input);
  void action_CmpGT(string input);
  void action_CmpGE(string input);
  void action_jumpif(string input);
  void action_jump(string input);
  void action_and(string input);
  void action_or(string input);
  void action_not(string input);
  void action_call (string input, int ip);
  void action_input(string input);
  void action_return ();
  void action_halt();
  ~VM(){};
  void destroy_all(){
    delete checker;
    delete stacker;
    delete addr;
  }
};
#endif

