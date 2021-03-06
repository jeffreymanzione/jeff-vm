// compiler.c
//
// Created on: Oct 28, 2020
//     Author: Jeff Manzione

#include "compile/compile.h"

#include <stdbool.h>
#include <stdlib.h>

#include "alloc/alloc.h"
#include "lang/parser/parser.h"
#include "lang/semantics/expression_tree.h"
#include "lang/semantics/semantics.h"
#include "program/optimization/optimize.h"
#include "program/tape.h"
#include "program/tape_binary.h"
#include "struct/map.h"
#include "struct/set.h"
#include "struct/struct_defaults.h"
#include "util/args/commandline.h"
#include "util/args/commandlines.h"
#include "util/args/lib_finder.h"
#include "util/file/file_info.h"
#include "util/file/file_util.h"
#include "util/string.h"
#include "vm/intern.h"

Tape *_read_file(const char fn[], bool opt) {
  FileInfo *fi = file_info(fn);
  SyntaxTree stree = parse_file(fi);
  ExpressionTree *etree = populate_expression(&stree);
  Tape *tape = tape_create();
  produce_instructions(etree, tape);
  delete_expression(etree);
  syntax_tree_delete(&stree);
  file_info_delete(fi);

  if (opt) {
    tape = optimize(tape);
  }

  return tape;
}

void write_tape(const char fn[], const Tape *tape, bool out_ja,
                const char machine_dir[], bool out_jb,
                const char bytecode_dir[]) {
  char *path, *file_name, *ext;
  split_path_file(fn, &path, &file_name, &ext);

  if (out_ja && ends_with(fn, ".jv")) {
    make_dir_if_does_not_exist(machine_dir);
    char *file_path = combine_path_file(machine_dir, file_name, ".ja");
    FILE *file = FILE_FN(file_path, "wb");
    tape_write(tape, file);
    fclose(file);
    DEALLOC(file_path);
  }
  if (out_jb && !ends_with(fn, ".jb")) {
    make_dir_if_does_not_exist(bytecode_dir);
    char *file_path = combine_path_file(bytecode_dir, file_name, ".jb");
    FILE *file = FILE_FN(file_path, "wb");
    tape_write_binary(tape, file);
    fclose(file);
    DEALLOC(file_path);
  }
  DEALLOC(path);
  DEALLOC(file_name);
  DEALLOC(ext);
}

Map *compile(const Set *source_files, const ArgStore *store) {
  parsers_init();
  semantics_init();
  optimize_init();

  const bool out_ja = argstore_lookup_bool(store, ArgKey__OUT_ASSEMBLY);
  const char *machine_dir =
      argstore_lookup_string(store, ArgKey__ASSEMBLY_OUT_DIR);
  const bool out_jb = argstore_lookup_bool(store, ArgKey__OUT_BINARY);
  const char *bytecode_dir = argstore_lookup_string(store, ArgKey__BIN_OUT_DIR);
  const bool opt = argstore_lookup_bool(store, ArgKey__OPTIMIZE);

  M_iter srcs = set_iter((Set *)source_files);
  Map *src_map = map_create_default();
  for (; has(&srcs); inc(&srcs)) {
    const char *src = value(&srcs);
    Tape *tape = _read_file(src, opt);
    map_insert(src_map, src, tape);
    write_tape(src, tape, out_ja, machine_dir, out_jb, bytecode_dir);
  }

  optimize_finalize();
  semantics_finalize();
  parsers_finalize();
  return src_map;
}

int jvc(int argc, const char *argv[]) {
  alloc_init();
  strings_init();

  ArgConfig *config = argconfig_create();
  argconfig_compile(config);
  ArgStore *store = commandline_parse_args(config, argc, argv);

  Map *src_map = compile(argstore_sources(store), store);
  M_iter tapes = map_iter(src_map);
  for (; has(&tapes); inc(&tapes)) {
    tape_delete(value(&tapes));
  }
  map_delete(src_map);

  argstore_delete(store);
  argconfig_delete(config);
  strings_finalize();
  token_finalize_all();
  alloc_finalize();

  return EXIT_SUCCESS;
}