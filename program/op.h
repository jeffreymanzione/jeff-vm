// op.h
//
// Created on: Jun 4, 2020
//     Author: Jeff Manzione

#ifndef PROGRAM_OP_H_
#define PROGRAM_OP_H_

typedef enum {
  // Do nothing.
  NOP,
  EXIT,
  // Loads something into resval.
  RES,
  TGET,
  TLEN,
  SET,
  // Assigns a value locally.
  LET,
  PUSH,
  PEEK,
  PSRS,  // PUSH+RES
  NOT,   // where !1 == Nil
  NOTC,  // C-like NOT, where !1 == 0
  GT,
  LT,
  EQ,
  NEQ,
  GTE,
  LTE,
  AND,
  OR,
  XOR,
  IF,
  IFN,
  JMP,
  NBLK,
  BBLK,
  RET,
  ADD,
  SUB,
  MULT,
  DIV,
  MOD,
  INC,
  DEC,
  FINC,
  FDEC,
  SINC,
  CALL,
  CLLN,
  TUPL,
  TGTE,
  TLTE,
  TEQ,
  DUP,
  GOTO,
  PRNT,
  LMDL,
  GET,
  GTSH,  // GET+PUSH
  RNIL,  // RES Nil
  PNIL,  // PUSH Nil
  FLD,
  FLDC,
  IS,
  ADR,
  RAIS,
  CTCH,
  // ARRAYS
  ANEW,
  AIDX,
  ASET,
  //
  CNST,
  SETC,
  LETC,
  SGET,
  // NOT A REAL OP
  OP_BOUND,
} Op;

const char *op_to_str(Op op);

#endif /* PROGRAM_OP_H_ */