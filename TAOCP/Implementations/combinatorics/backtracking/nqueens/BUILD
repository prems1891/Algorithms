cc_library(
  name = "nqueens_lib",
  hdrs = [
    "nqueens_visitors.h",
    "nqueens_array.h",
    "nqueens_basic.h",
    "nqueens_bitwise.h",
    "nqueens_iterative.h",
    "nqueens_walker.h",
  ]
)

cc_test(
  name = "nqueens_test",
  srcs = [
    "nqueens_array_test.cc",
    "nqueens_basic_test.cc",
    "nqueens_bitwise_test.cc",
    "nqueens_iterative_test.cc",
    "nqueens_walker_test.cc"
  ],
  deps = [
    ":nqueens_lib",
    "@googletest//:gtest_main",
  ],
  size = "small",
)

cc_binary(
  name = "nqueens_bench",
  srcs = ["nqueens_benchmarks.cc"],
  deps = [
    ":nqueens_lib",
    "@googlebench//:gbench",
  ]
)