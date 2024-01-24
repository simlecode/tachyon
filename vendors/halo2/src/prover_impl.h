#ifndef VENDORS_HALO2_SRC_PROVER_IMPL_H_
#define VENDORS_HALO2_SRC_PROVER_IMPL_H_

#include <stddef.h>
#include <stdint.h>

#include <array>
#include <memory>
#include <utility>

#include "rust/cxx.h"

#include "tachyon/base/functional/callback.h"
#include "tachyon/zk/plonk/halo2/prover.h"

namespace tachyon::halo2_api {

template <typename PCS>
class ProverImpl {
 public:
  using Field = typename PCS::Field;
  using Commitment = typename PCS::Commitment;
  using ExtendedDomain = typename PCS::ExtendedDomain;

  explicit ProverImpl(base::OnceCallback<zk::halo2::Prover<PCS>()> callback)
      : prover_(std::move(callback).Run()) {}

  const zk::halo2::Prover<PCS>& prover() const { return prover_; }

  size_t K() const { return prover_.pcs().K(); }

  size_t N() const { return prover_.pcs().N(); }

  void SetRng(std::unique_ptr<crypto::XORShiftRNG> rng) {
    prover_.SetRng(std::move(rng));
  }

  void SetTranscript(
      std::unique_ptr<crypto::TranscriptWriter<Commitment>> writer) {
    prover_.transcript_ = std::move(writer);
  }

  void SetExtendedDomain(const zk::ConstraintSystem<Field>& constraint_system) {
    size_t extended_k =
        constraint_system.ComputeExtendedDegree(prover_.pcs().K());
    prover_.set_extended_domain(
        ExtendedDomain::Create(size_t{1} << extended_k));
  }

 private:
  zk::halo2::Prover<PCS> prover_;
};

}  // namespace tachyon::halo2_api

#endif  // VENDORS_HALO2_SRC_PROVER_IMPL_H_
