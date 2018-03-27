#include <string>

#include "extensions/filters/http/sample/sample.h"

#include "envoy/registry/registry.h"

#include "source/extensions/filters/http/sample/sample.pb.h"
#include "source/extensions/filters/http/sample/sample.pb.validate.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Decoder {

class HttpSampleDecoderFilterConfigFactory
    : public Server::Configuration::NamedHttpFilterConfigFactory {
public:
  Server::Configuration::HttpFilterFactoryCb
  createFilterFactoryFromProto(const Protobuf::Message& proto_config, const std::string&,
                               Server::Configuration::FactoryContext& context) override {

    return createFilter(
        Envoy::MessageUtil::downcastAndValidate<const sample::Decoder&>(proto_config), context);
  }

  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new sample::Decoder()};
  }

  std::string name() override { return "sample"; }

  Server::Configuration::HttpFilterFactoryCb
  createFilterFactory(const Json::Object&, const std::string&,
                      Server::Configuration::FactoryContext&) override {

    NOT_IMPLEMENTED;
  }

private:
  Server::Configuration::HttpFilterFactoryCb
  createFilter(const sample::Decoder& proto_config,
               Server::Configuration::FactoryContext& context) {

    HttpSampleDecoderFilterConfigSharedPtr config = std::make_shared<HttpSampleDecoderFilterConfig>(
        HttpSampleDecoderFilterConfig(proto_config));

    return [&context, config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
      auto filter = new HttpSampleDecoderFilter(config);
      callbacks.addStreamDecoderFilter(Http::StreamDecoderFilterSharedPtr{filter});
    };
  }
};

/**
 * Static registration for this sample filter. @see RegisterFactory.
 */
static Registry::RegisterFactory<HttpSampleDecoderFilterConfigFactory,
                                 Server::Configuration::NamedHttpFilterConfigFactory>
    register_;

} // namespace Decoder
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy