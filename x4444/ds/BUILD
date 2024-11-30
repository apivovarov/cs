cc_library(
    name = "heap_lib",
    hdrs = ["heap.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "heap_main",
    srcs = ["heap_main.cc"],
    deps = ["heap_lib"],
)

cc_binary(
    name = "hashmap_example",
    srcs = ["hashmap_example.cc"],
)

cc_binary(
    name = "hello",
    srcs = ["hello.cc"],
)

cc_library(
    name = "stack_lib",
    hdrs = ["stack.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "stack_main",
    srcs = ["stack_main.cc"],
    deps = ["stack_lib"],
)

cc_library(
    name = "binary_search_tree_lib",
    hdrs = ["binary_search_tree.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "binary_search_tree_main",
    srcs = ["binary_search_tree_main.cc"],
    deps = ["binary_search_tree_lib"],
)

cc_library(
    name = "hashset_lib",
    hdrs = ["hashset.h"],
    deps = ["forward_list_lib"],
)

cc_binary(
    name = "hashset_main",
    srcs = ["hashset_main.cc"],
    deps = ["hashset_lib"],
)

cc_library(
    name = "forward_list_lib",
    hdrs = ["forward_list.h"],
)

cc_binary(
    name = "forward_list_main",
    srcs = ["forward_list_main.cc"],
    deps = ["forward_list_lib"],
)

cc_library(
    name = "graph",
    hdrs = ["graph.h"],
)

cc_binary(
    name = "graph_main",
    srcs = ["graph_main.cc"],
    deps = ["graph"]
)

cc_library(
    name = "tree",
    hdrs = ["tree.h"],
)

cc_binary(
    name = "tree_main",
    srcs = ["tree_main.cc"],
    deps = ["tree"]
)
