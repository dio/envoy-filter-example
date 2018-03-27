package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
)

envoy_cc_library(
    name = "echo2",
    srcs = ["echo2.cc"],
    hdrs = ["echo2.h"],
    repository = "@envoy",
    deps = [
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_library(
    name = "config",
    srcs = ["config.cc"],
    repository = "@envoy",
    deps = [
        ":echo2",
        "@envoy//source/exe:envoy_common_lib",
    ],
)