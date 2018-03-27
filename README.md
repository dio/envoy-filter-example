# Envoy filter example

This project demonstrates the linking of additional filters (extensions) with the Envoy binary.
This contains two filter examples:

1.  A network filter [`echo2`](source/extensions/filters/network/echo2), identical modulo renaming to the existing
    [`echo`](https://github.com/envoyproxy/envoy/blob/master/source/extensions/filters/network/echo/echo.h)
    filter.
2.  An HTTP filter [`sample`](source/extensions/filters/http/sample), demonstrates the implementation of a simple HTTP decoder filter.

Integration tests demonstrating each filter's end-to-end behavior are also provided in [test/integration](test/integration) directory.

## Building

To build the Envoy static binary, with these filters enabled (see [`BUILD`](source/BUILD#L12-L13)):

```
$ bazel build //source:envoy
```

## Testing

```
$ bazel test //...`
```

To run the regular Envoy tests from this project:

```
$ bazel test @envoy//test/...
```

## How it works

The [Envoy repository](https://github.com/envoyproxy/envoy/) is fetched as an HTTP archive. The [`WORKSPACE`](WORKSPACE) file maps the `@envoy` as `http_archive`.

The [`BUILD`](source/BUILD) file introduces a new Envoy static binary target, `envoy`, that links together the new filters (by requiring its config lib as `deps` as depicted here [here](source/BUILD#L12-L13)) and `@envoy//source/exe:envoy_main_lib`. The `echo2` and `sample` filter registers itself during the static initialization phase of the Envoy binary as new filters.

## Add your own filter

To add your own filter, you can try by copying one of the example and then modifying it as necessary. For instance you want to build `echo3` filter.

1. Copy the `echo2` filter directory as `echo3`, hence the structure becomes:

```
|-- source
|   |-- BUILD
|   `-- extensions
|       `-- filters
|           |-- http
|           |   `-- sample
|           `-- network
|               `-- echo2
|               `-- echo3
```

2. Modify the namespace and the class name as necessary. Don't forget to change the [`name()`](source/extensions/filters/network/echo2/config.cc#L30) in the [config factory](source/extensions/filters/network/echo2/config.cc) to return your filter name, in this case: `"echo3"`.

3. Add the path of your config BUILD entry to [source/BUILD](source/BUILD) file. The diff should be something like:

```diff
--- a/source/BUILD
+++ b/source/BUILD
@@ -11,6 +11,7 @@ envoy_cc_binary(
     deps = [
         "//source/extensions/filters/network/echo2:config",
         "//source/extensions/filters/http/sample:config",
+        "//source/extensions/filters/network/echo3:config",
         "@envoy//source/exe:envoy_main_entry_lib",
     ],
 )
```

4. Build it.