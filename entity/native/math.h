// math.h
//
// Created on: Nov 29, 2020
//     Author: Jeff Manzione

#ifndef ENTITY_NATIVE_MATH_H_
#define ENTITY_NATIVE_MATH_H_

#include "entity/object.h"
#include "vm/module_manager.h"

void math_add_native(ModuleManager *mm, Module *math);

#endif /* ENTITY_NATIVE_MATH_H_ */