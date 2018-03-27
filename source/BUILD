package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
)

envoy_cc_binary(
    name = "envoy",
    repository = "@envoy",
    deps = [
        "//source/extensions/filters/network/echo2:config",
        "//source/extensions/filters/http/sample:config",
        "//source/extensions/filters/network/echo3:config",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)