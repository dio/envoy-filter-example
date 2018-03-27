#include "extensions/filters/network/echo2/echo2.h"

#include "envoy/buffer/buffer.h"
#include "envoy/network/connection.h"

#include "common/common/assert.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Echo {

Network::FilterStatus Echo2Filter::onData(Buffer::Instance& data, bool) {
  ENVOY_CONN_LOG(trace, "echo: got {} bytes", read_callbacks_->connection(), data.length());
  read_callbacks_->connection().write(data, false);
  ASSERT(0 == data.length());
  return Network::FilterStatus::StopIteration;
}
} // namespace Echo
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
