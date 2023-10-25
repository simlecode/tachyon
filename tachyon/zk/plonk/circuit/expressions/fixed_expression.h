// Copyright 2020-2022 The Electric Coin Company
// Copyright 2022 The Halo2 developers
// Use of this source code is governed by a MIT/Apache-2.0 style license that
// can be found in the LICENSE-MIT.halo2 and the LICENCE-APACHE.halo2
// file.

#ifndef TACHYON_ZK_PLONK_CIRCUIT_EXPRESSIONS_FIXED_EXPRESSION_H_
#define TACHYON_ZK_PLONK_CIRCUIT_EXPRESSIONS_FIXED_EXPRESSION_H_

#include <memory>
#include <string>

#include "absl/memory/memory.h"

#include "tachyon/zk/plonk/circuit/expressions/expression.h"
#include "tachyon/zk/plonk/circuit/query.h"

namespace tachyon::zk {

template <typename F>
class FixedExpression : public Expression<F> {
 public:
  static std::unique_ptr<FixedExpression> CreateForTesting(
      const FixedQuery& query) {
    return absl::WrapUnique(new FixedExpression(query));
  }

  const FixedQuery& query() const { return query_; }

  std::string ToString() const override {
    return absl::Substitute("{type: $0, column: $1}",
                            ExpressionTypeToString(this->type_),
                            query_.ToString());
  }

  // Expression methods
  size_t Degree() const override { return 1; }

  uint64_t Complexity() const override { return 1; }

 private:
  friend class ExpressionFactory<F>;

  explicit FixedExpression(const FixedQuery& query)
      : Expression<F>(ExpressionType::kFixed), query_(query) {}

  FixedQuery query_;
};

}  // namespace tachyon::zk

#endif  // TACHYON_ZK_PLONK_CIRCUIT_EXPRESSIONS_FIXED_EXPRESSION_H_