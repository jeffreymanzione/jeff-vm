load("@rules_cc//cc:defs.bzl", "cc_library")

package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "intern",
    srcs = ["intern.c"],
    hdrs = ["intern.h"],
    deps = [
        "@memory-wrapper//alloc/arena:intern",
    ],
)

cc_library(
    name = "virtual_machine",
    srcs = ["virtual_machine.c"],
    hdrs = ["virtual_machine.h"],
    deps = [
        ":module_manager",
        "//vm/process",
        "//vm/process:context",
        "//vm/process:processes",
        "//vm/process:task",
    ],
)

cc_library(
    name = "module_manager",
    srcs = ["module_manager.c"],
    hdrs = ["module_manager.h"],
    deps = [
        "//entity/class",
        "//entity/class:classes",
        "//entity/function",
        "//entity/module",
        "//lang/lexer:file_info",
        "//lang/parser",
        "//lang/semantics",
        "//program:tape",
        "//struct:keyed_list",
    ],
)