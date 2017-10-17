//
// Created by Arseny Tolmachev on 2017/10/13.
//

#include "feature_impl_ngram_partial.h"

namespace jumanpp {
namespace core {
namespace features {
namespace impl {

Status PartialNgramDynamicFeatureApply::addChild(const NgramFeature& nf) {
  auto& args = nf.arguments;
  auto sz = args.size();
  switch (sz) {
    case 1: {
      unigrams_.emplace_back(unigrams_.size(), nf.index, args[0]);
      break;
    }
    case 2: {
      bigrams_.emplace_back(bigrams_.size(), nf.index, args[0], args[1]);
      break;
    }
    case 3: {
      trigrams_.emplace_back(trigrams_.size(), nf.index, args[0], args[1],
                             args[2]);
      break;
    }
    default:
      return JPPS_INVALID_STATE << "invalid ngram feature #" << nf.index
                                << "of order " << nf.arguments.size()
                                << " only 1-3 are supported";
  }
  return Status::Ok();
}

void PartialNgramDynamicFeatureApply::uniStep0(
    util::ArraySlice<u64> patterns, util::MutableArraySlice<u32> result) const
    noexcept {
  for (auto& uni : unigrams_) {
    uni.step0(patterns, result);
  }
}

void PartialNgramDynamicFeatureApply::biStep0(
    util::ArraySlice<u64> patterns, util::MutableArraySlice<u64> state) const
    noexcept {
  for (auto& bi : bigrams_) {
    bi.step0(patterns, state);
  }
}

void PartialNgramDynamicFeatureApply::biStep1(
    util::ArraySlice<u64> patterns, util::ArraySlice<u64> state,
    util::MutableArraySlice<u32> result) const noexcept {
  for (auto& bi : bigrams_) {
    bi.step1(patterns, state, result);
  }
}

void PartialNgramDynamicFeatureApply::triStep0(
    util::ArraySlice<u64> patterns, util::MutableArraySlice<u64> state) const
    noexcept {
  for (auto& tri : trigrams_) {
    tri.step0(patterns, state);
  }
}

void PartialNgramDynamicFeatureApply::triStep1(
    util::ArraySlice<u64> patterns, util::ArraySlice<u64> state,
    util::MutableArraySlice<u64> result) const noexcept {
  for (auto& tri : trigrams_) {
    tri.step1(patterns, state, result);
  }
}

void PartialNgramDynamicFeatureApply::triStep2(
    util::ArraySlice<u64> patterns, util::ArraySlice<u64> state,
    util::MutableArraySlice<u32> result) const noexcept {
  for (auto& tri : trigrams_) {
    tri.step2(patterns, state, result);
  }
}

bool PartialNgramDynamicFeatureApply::outputClassBody(
    util::io::Printer& p) const {
  p << "\nvoid uniStep0(" << JPP_TEXT(jumanpp::util::ArraySlice<jumanpp::u64>)
    << " patterns, " << JPP_TEXT(jumanpp::util::MutableArraySlice<jumanpp::u32>)
    << " result"
    << ") const noexcept {";
  {
    util::io::Indent id{p, 2};
    for (int i = 0; i < unigrams_.size(); ++i) {
      auto& f = unigrams_[i];
      f.writeMember(p, i);
      p << "\nuni_" << i << ".step0(patterns, result);";
    }
  }
  p << "\n}\n";

  p << "\nvoid biStep0(" << JPP_TEXT(jumanpp::util::ArraySlice<jumanpp::u64>)
    << " patterns, " << JPP_TEXT(jumanpp::util::MutableArraySlice<jumanpp::u64>)
    << " state"
    << ") const noexcept {";
  {
    util::io::Indent id{p, 2};
    for (int i = 0; i < bigrams_.size(); ++i) {
      auto& f = bigrams_[i];
      f.writeMember(p, i);
      p << "\nbi_" << i << ".step0(patterns, state);";
    }
  }
  p << "\n}\n";

  p << "\nvoid biStep1(" << JPP_TEXT(jumanpp::util::ArraySlice<jumanpp::u64>)
    << " patterns, " << JPP_TEXT(jumanpp::util::ArraySlice<jumanpp::u64>)
    << " state, " << JPP_TEXT(jumanpp::util::MutableArraySlice<jumanpp::u32>)
    << " result"
    << ") const noexcept {";
  {
    util::io::Indent id{p, 2};
    for (int i = 0; i < bigrams_.size(); ++i) {
      auto& f = bigrams_[i];
      f.writeMember(p, i);
      p << "\nbi_" << i << ".step1(patterns, state, result);";
    }
  }
  p << "\n}\n";

  p << "\nvoid triStep0(" << JPP_TEXT(jumanpp::util::ArraySlice<jumanpp::u64>)
    << " patterns, " << JPP_TEXT(jumanpp::util::MutableArraySlice<jumanpp::u64>)
    << " state"
    << ") const noexcept {";
  {
    util::io::Indent id{p, 2};
    for (int i = 0; i < trigrams_.size(); ++i) {
      auto& f = trigrams_[i];
      f.writeMember(p, i);
      p << "\ntri_" << i << ".step0(patterns, state);";
    }
  }
  p << "\n}\n";

  p << "\nvoid triStep1(" << JPP_TEXT(jumanpp::util::ArraySlice<jumanpp::u64>)
    << " patterns, " << JPP_TEXT(jumanpp::util::ArraySlice<jumanpp::u64>)
    << " state, " << JPP_TEXT(jumanpp::util::MutableArraySlice<jumanpp::u64>)
    << " result"
    << ") const noexcept {";
  {
    util::io::Indent id{p, 2};
    for (int i = 0; i < trigrams_.size(); ++i) {
      auto& f = trigrams_[i];
      f.writeMember(p, i);
      p << "\ntri_" << i << ".step1(patterns, state, result);";
    }
  }
  p << "\n}\n";

  p << "\nvoid triStep2(" << JPP_TEXT(jumanpp::util::ArraySlice<jumanpp::u64>)
    << " patterns, " << JPP_TEXT(jumanpp::util::ArraySlice<jumanpp::u64>)
    << " state, " << JPP_TEXT(jumanpp::util::MutableArraySlice<jumanpp::u32>)
    << " result"
    << ") const noexcept {";
  {
    util::io::Indent id{p, 2};
    for (int i = 0; i < trigrams_.size(); ++i) {
      auto& f = trigrams_[i];
      f.writeMember(p, i);
      p << "\ntri_" << i << ".step2(patterns, state, result);";
    }
  }
  p << "\n}\n";

  return true;
}

void UnigramFeature::writeMember(util::io::Printer& p, i32 count) const {
  p << "\nconstexpr const "
    << "::jumanpp::core::features::impl::" << JPP_TEXT(UnigramFeature)
    << " uni_" << count << " { " << target_ << ", " << index_ << ", " << t0idx_
    << " };";
}

void BigramFeature::writeMember(util::io::Printer& p, i32 count) const {
  p << "\nconstexpr const "
    << "::jumanpp::core::features::impl::" << JPP_TEXT(BigramFeature) << " bi_"
    << count << " { " << target_ << ", " << index_ << ", " << t0idx_ << ", "
    << t1idx_ << " };";
}

void TrigramFeature::writeMember(util::io::Printer& p, i32 count) const {
  p << "\nconstexpr const "
    << "::jumanpp::core::features::impl::" << JPP_TEXT(TrigramFeature)
    << " tri_" << count << " { " << target_ << ", " << index_ << ", " << t0idx_
    << ", " << t1idx_ << ", " << t2idx_ << " };";
}
}  // namespace impl
}  // namespace features
}  // namespace core
}  // namespace jumanpp