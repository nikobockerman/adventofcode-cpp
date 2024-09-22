#pragma once

#include <gtest/gtest.h>

void enableDebugLogging();

class TestFixture : public ::testing::Test {
 protected:
  void SetUp() override { enableDebugLogging(); }
};
