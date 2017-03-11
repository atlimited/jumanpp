//
// Created by Arseny Tolmachev on 2017/03/03.
//

#ifndef JUMANPP_ANALYZER_IMPL_H
#define JUMANPP_ANALYZER_IMPL_H

#include "core/analysis/analysis_input.h"
#include "core/analysis/analyzer.h"
#include "core/analysis/extra_nodes.h"
#include "core/analysis/lattice_builder.h"
#include "core/analysis/lattice_types.h"
#include "core/analysis/score_processor.h"

namespace jumanpp {
namespace core {
namespace analysis {

class AnalyzerImpl {
 protected:
  AnalyzerConfig cfg_;
  const CoreHolder* core_;
  util::memory::Manager memMgr_;
  std::unique_ptr<util::memory::ManagedAllocatorCore> alloc_;
  AnalysisInput input_;
  Lattice lattice_;
  LatticeBuilder latticeBldr_;
  ExtraNodesContext xtra_;
  OutputManager outputManager_;
  ScoreProcessor* sproc_;
  std::vector<std::unique_ptr<ScoreComputer>> scorers_;

 public:
  AnalyzerImpl(const AnalyzerImpl&) = delete;
  AnalyzerImpl(AnalyzerImpl&&) = delete;
  AnalyzerImpl(const CoreHolder* core, const AnalyzerConfig& cfg);

  const OutputManager& output() const { return outputManager_; }

  Status initScorers(const ScoreConfig& cfg) {
    scorers_.reserve(cfg.others.size());
    for (auto& sf : cfg.others) {
      std::unique_ptr<ScoreComputer> comp;
      JPP_RETURN_IF_ERROR(sf->makeInstance(&comp));
      scorers_.emplace_back(std::move(comp));
    }
    return Status::Ok();
  }

  void reset() {
    lattice_.reset();
    xtra_.reset();
    memMgr_.reset();
    alloc_->reset();
    sproc_ = nullptr;
  }

  Status resetForInput(StringPiece input);
  Status makeNodeSeedsFromDic();
  Status makeUnkNodes1();
  bool checkLatticeConnectivity();
  Status makeUnkNodes2();
  Status buildLattice();
  void fixupLattice();
  Status computeScores(ScoreConfig* sconf);

  Lattice* lattice() { return &lattice_; }

  Status preprocess(StringPiece input) {
    JPP_RETURN_IF_ERROR(resetForInput(input));
    JPP_RETURN_IF_ERROR(makeNodeSeedsFromDic());
    return Status::Ok();
  }
};

}  // analysis
}  // core
}  // jumanpp

#endif  // JUMANPP_ANALYZER_IMPL_H
