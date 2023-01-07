#pragma once

#include <gtest/gtest.h>

#include "log.hpp"

class TestFixture : public ::testing::Test {
 protected:
  void SetUp() override { enableDebugLogging(); }
};
