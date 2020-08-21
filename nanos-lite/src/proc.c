#include "proc.h"

#define MAX_NR_PROC 4

static PCB pcb[MAX_NR_PROC] __attribute__((used)) = {};
static PCB pcb_boot = {};
PCB *current = NULL;

void naive_uload(PCB *pcb, const char *filename);
void context_kload(PCB *pcb, void *entry);
void context_uload(PCB *pcb, const char *filename);

void switch_boot_pcb() {
  current = &pcb_boot;
}

void hello_fun(void *arg) {
  int j = 1;
  while (1) {
    Log("Hello World from Nanos-lite for the %dth time!", j);
    j ++;
    _yield();
  }
}

void init_proc() {

  Log("Initializing processes...");
  
  //context_kload(&pcb[0], (void *)hello_fun);
  //context_uload(&pcb[0], "/bin/hello");
  context_uload(&pcb[0], "/bin/bmptest");
  //context_uload(&pcb[0], "/bin/dummy");
  //naive_uload(NULL, "/bin/dummy");
  switch_boot_pcb();
  
  // load program here
  // naive_uload(NULL, "/bin/init");
  
}

_Context* schedule(_Context *prev) {
  current->cp = prev;
  current = &pcb[0];
  //current = (current == &pcb[0] ? &pcb[1] : &pcb[0]);
  return current->cp;
}
