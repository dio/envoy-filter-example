#include <string>

#include "extensions/filters/http/sample/sample.h"

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Decoder {

HttpSampleDecoderFilterConfig::HttpSampleDecoderFilterConfig(const sample::Decoder& proto_config)
    : key_(proto_config.key()), val_(proto_config.val()) {}

HttpSampleDecoderFilter::HttpSampleDecoderFilter(HttpSampleDecoderFilterConfigSharedPtr config)
    : config_(config) {}

HttpSampleDecoderFilter::~HttpSampleDecoderFilter() {}

void HttpSampleDecoderFilter::onDestroy() {}

const Http::LowerCaseString HttpSampleDecoderFilter::headerKey() const {
  return Http::LowerCaseString(config_->key());
}

const std::string HttpSampleDecoderFilter::headerValue() const { return config_->val(); }

Http::FilterHeadersStatus HttpSampleDecoderFilter::decodeHeaders(Http::HeaderMap& headers, bool) {
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return Http::FilterHeadersStatus::Continue;
}

Http::FilterDataStatus HttpSampleDecoderFilter::decodeData(Buffer::Instance&, bool) {
  return Http::FilterDataStatus::Continue;
}

Http::FilterTrailersStatus HttpSampleDecoderFilter::decodeTrailers(Http::HeaderMap&) {
  return Http::FilterTrailersStatus::Continue;
}

void HttpSampleDecoderFilter::setDecoderFilterCallbacks(Http::StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

} // namespace Decoder
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
