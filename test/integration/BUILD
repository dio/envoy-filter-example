licenses(["notice"])  # Apache 2

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_test",
)

envoy_cc_test(
    name = "echo2_integration_test",
    srcs = ["echo2_integration_test.cc"],
    data = [
        "//test/fixtures/configs:v2",
    ],
    repository = "@envoy",
    deps = [
        "//source/extensions/filters/network/echo2:config",
        "@envoy//test/integration:integration_lib",
    ],
)

envoy_cc_test(
    name = "sample_integration_test",
    srcs = ["sample_integration_test.cc"],
    repository = "@envoy",
    deps = [
        "//source/extensions/filters/http/sample:config",
        "@envoy//test/integration:http_integration_lib",
    ],
)