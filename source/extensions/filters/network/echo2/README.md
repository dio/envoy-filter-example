# Envoy network filter example

This project demonstrates the linking of an additional network filter with the Envoy binary. A new filter `echo2`.

## Building

To build the Envoy static binary, with this filter enabled (see [`BUILD`](../../../../BUILD#L12)):

```
$ bazel build //source:envoy
```

## Testing

To run the `echo2` integration test:

```
$ bazel test //test/integration:echo2_integration_test
```
