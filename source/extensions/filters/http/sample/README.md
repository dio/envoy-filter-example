# Envoy HTTP filter example

This project demonstrates the linking of an additional HTTP filter with the Envoy binary. A new filter `sample` which adds a HTTP header is introduced.

## Building

To build the Envoy static binary, with this filter enabled (see [`BUILD`](../../../../BUILD#L13)):

```
$ bazel build //source:envoy
```

## Testing

To run the `sample` integration test:

```
$ bazel test //test/integration:sample_integration_test
```

## How to write and use an HTTP filter

* The main task is to write a class that implements the interface [`Envoy::Http::StreamDecoderFilter`][streamdecoderfilter] as in [`sample.h`](sample.h) and [`sample.cc`](sample.cc), which contains functions that handle http headers, data, and trailers. Note that this is an example of decoder filters, and to write encoder filters or decoder/encoder filters you need to implement [`Envoy::Http::StreamEncoderFilter`][streamencoderfilter] or [`Envoy::Http::StreamFilter`][streamfilter] instead.
* You also need a class that implements `Envoy::Server::Configuration::NamedHttpFilterConfigFactory` to enable the Envoy binary to find your filter, as in [`config.cc`](config.cc). It should be linked to the Envoy binary by adding the config to the [`BUILD`](../../../../BUILD#L13) file as a dependency in the `deps` list.
* Finally, you need to modify the Envoy config file to add your filter to the filter chain for a particular HTTP route configuration. For instance, if you wanted to change [the front-proxy example][front-envoy.yaml] to chain our `sample` filter, you'd need to modify its config to look like

```yaml
http_filters:
- name: sample          # before envoy.router because order matters!
  config:
    key: via
    val: sample-filter
- name: envoy.router
  config: {}
```

[streamdecoderfilter]: https://github.com/envoyproxy/envoy/blob/master/include/envoy/http/filter.h#L300
[streamencoderfilter]: https://github.com/envoyproxy/envoy/blob/master/include/envoy/http/filter.h#L413
[streamfilter]: https://github.com/envoyproxy/envoy/blob/master/include/envoy/http/filter.h#L462
[front-envoy.yaml]: https://github.com/envoyproxy/envoy/blob/master/examples/front-proxy/front-envoy.yaml#L28
