cc_library(
    name = "heap_lib",
    hdrs = ["heap.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "heap",
    srcs = ["heap.cc"],
    deps = ["heap_lib"],
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
    name = "stack",
    srcs = ["stack.cc"],
    deps = ["stack_lib"],
)

cc_binary(
    name = "binary_search_tree",
    srcs = ["binary_search_tree.cc"],
)
