cc_library(
    name="linked_list_lib",
    srcs=[],  # Source defined in the headers bc classes are templated and C++ is awesome!
    hdrs=["src/linked_list.h", "src/node.h"],
    visibility=["//visibility:public"],
)

cc_test(
    name="linked_list_test",
    srcs=["test/linked_list_test.cc"],
    deps=[
        ":linked_list_lib",
        "@googletest//:gtest_main",
    ],
)
