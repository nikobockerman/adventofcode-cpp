#pragma once

#include <gtest/gtest.h>

#include "day-interface.hpp"

void enableDebugLogging();

class TestFixture : public ::testing::Test {
 protected:
  void SetUp() override { enableDebugLogging(); }
};

template <typename TResultType>
auto verifyResult(const ResultType &result, const TResultType &expected) {
  ASSERT_TRUE(std::holds_alternative<TResultType>(result));
  EXPECT_EQ(std::get<TResultType>(result), expected);
}
