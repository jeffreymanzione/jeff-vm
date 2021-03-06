// process.h
//
// Created on: Dec 28, 2020
//     Author: Jeff Manzione

#ifndef ENTITY_NATIVE_PROCESS_H_
#define ENTITY_NATIVE_PROCESS_H_

#include "entity/object.h"
#include "vm/module_manager.h"

void process_add_native(ModuleManager *mm, Module *process);

#endif /* ENTITY_NATIVE_PROCESS_H_ */