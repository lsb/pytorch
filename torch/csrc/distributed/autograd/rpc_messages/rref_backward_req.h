#pragma once

#include <torch/csrc/distributed/rpc/message.h>
#include <torch/csrc/distributed/rpc/rpc_command_base.h>
#include <torch/csrc/distributed/rpc/types.h>

namespace torch {
namespace distributed {
namespace autograd {

// Internal system RPC to invoke distributed backward pass on remote nodes when
// 'rref.backward()' is invoked.
class TORCH_API RRefBackwardReq : public rpc::RpcCommandBase {
 public:
  RRefBackwardReq(
      const rpc::RRefId& rrefId,
      int64_t autogradContextId,
      bool retainGraph = false);

  const rpc::RRefId& getRRefId();

  int64_t getAutogradContextId();

  bool retainGraph();

  // Serialization and deserialization methods.
  rpc::Message toMessageImpl() && override;
  static std::unique_ptr<RRefBackwardReq> fromMessage(
      const rpc::Message& message);

 private:
  rpc::RRefId rrefId_;
  int64_t autogradContextId_;
  bool retainGraph_;
};

} // namespace autograd
} // namespace distributed
} // namespace torch