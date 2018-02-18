#include <string>
#include <regex>

#include "http_filter.h"

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

static const std::regex kRegexSessionId{"(<sessionId>)(.*)(</sessionId>)"};

HttpSampleDecoderFilterConfig::HttpSampleDecoderFilterConfig(const sample::Decoder& proto_config)
    : key_(proto_config.key()), val_(proto_config.val()) {}

HttpSampleDecoderFilter::HttpSampleDecoderFilter(HttpSampleDecoderFilterConfigSharedPtr config)
    : config_(config) {}

HttpSampleDecoderFilter::~HttpSampleDecoderFilter() {}

void HttpSampleDecoderFilter::onDestroy() { decoder_headers_ = nullptr; }

const LowerCaseString HttpSampleDecoderFilter::headerKey() const {
  return LowerCaseString(config_->key());
}

const std::string HttpSampleDecoderFilter::headerValue() const { return config_->val(); }

FilterHeadersStatus HttpSampleDecoderFilter::decodeHeaders(HeaderMap& headers, bool) {
  decoder_headers_ = &headers;
  return FilterHeadersStatus::StopIteration;
}

FilterDataStatus HttpSampleDecoderFilter::decodeData(Buffer::Instance& data, bool) {
  uint64_t num_slices = data.getRawSlices(nullptr, 0);
  Buffer::RawSlice slices[num_slices];
  data.getRawSlices(slices, num_slices);

  for (const Buffer::RawSlice& slice : slices) {
    auto raw = std::string(static_cast<const char*>(slice.mem_), slice.len_);
    std::smatch matched;
    if (std::regex_search(raw, matched, kRegexSessionId)) {
      // TODO(dio): check if session-id is not set and provide a better matcher
      if (matched.size() >= 3) {
        decoder_headers_->addCopy(headerKey(), matched[2]);
      }
      break;
    }
  }

  return FilterDataStatus::Continue;
}

FilterTrailersStatus HttpSampleDecoderFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void HttpSampleDecoderFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

} // namespace Http
} // namespace Envoy
