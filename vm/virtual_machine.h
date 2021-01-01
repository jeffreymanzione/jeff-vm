// virtual_machine.h
//
// Created on: Jun 13, 2020
//     Author: Jeff Manzione

#ifndef VM_VIRTUAL_MACHINE_H_
#define VM_VIRTUAL_MACHINE_H_

#include "util/sync/thread.h"
#include "vm/module_manager.h"
#include "vm/process/processes.h"
#include "vm/vm.h"

VM *vm_create();
void vm_delete(VM *vm);

Process *vm_main_process(VM *vm);

void process_run(Process *process);
ThreadHandle process_run_in_new_thread(Process *process);

TaskState vm_execute_task(VM *vm, Task *task);

Process *vm_create_process(VM *vm);

#endif /* VM_VIRTUAL_MACHINE_H_ */