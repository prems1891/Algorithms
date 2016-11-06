#include<array>

#include "gtest/gtest.h"
#include "combinations.h"

template<std::size_t t> class RecordingVisitor {
  private:
    std::vector<std::array<int, t>> solutions;

  public:
    bool visit(const std::array<int, t>& rows) {
      std::array<int, t> v(rows);
      solutions.push_back(v);
      return true;
    }

    void reset() {
      solutions.clear();
    }

    int getN() const {
      return solutions.size();
    }

    const std::array<int, t>& get(int i) {
      return solutions.at(i);
    }
};

template<std::size_t t> class CountingVisitor {
  private:
    int nsolutions;

  public:
    CountingVisitor() { nsolutions = 0; }

    bool visit(const std::array<int, t>& rows) {
      ++nsolutions;
      return true;
    }

    void reset() {
      nsolutions = 0;
    }

    int getN() const {
      return nsolutions;
    }
};

// Tests

TEST(CombinationsTest, Test_3_3) {
  RecordingVisitor<3> vis;
  combinations::combinations_lex_basic(3, vis);
  std::array<int, 3> expected = {{0, 1, 2}};
  EXPECT_EQ(vis.getN(), 1)
    << "Should have 1 visit for 3 objects taken 3 at a time";
  EXPECT_EQ(vis.get(0), expected) << "Didn't get expected indices";
}

TEST(CombinationsTest, Test_3_2) {
  // 3 objects 2 at a time
  std::vector<std::array<int, 2>> expected =
    {{0, 1}, {0, 2}, {1, 2}};

  RecordingVisitor<2> vis;
  combinations::combinations_lex_basic(3, vis);
  EXPECT_EQ(vis.getN(), 3)
    << "Should have 3 visits for 3 objects taken 2 at a time";
   for (int i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(vis.get(i), expected[i])
      << "Got unexpected combination for 3 objects 2 at a time in index " << i;
  }
}

TEST(CombinationsTest, Test_6_3) {
  // 6 objects 3 at a time
  std::vector<std::array<int, 3>> expected =
    {{0, 1, 2}, {0, 1, 3}, {0, 2, 3}, {1, 2, 3}, {0, 1, 4},
     {0, 2, 4}, {1, 2, 4}, {0, 3, 4}, {1, 3, 4}, {2, 3, 4},
     {0, 1, 5}, {0, 2, 5}, {1, 2, 5}, {0, 3, 5}, {1, 3, 5},
     {2, 3, 5}, {0, 4, 5}, {1, 4, 5}, {2, 4, 5}, {3, 4, 5}};

  RecordingVisitor<3> vis;
  combinations::combinations_lex_basic(6, vis);
  EXPECT_EQ(vis.getN(), 20)
    << "Should have 20 visits for 6 objects taken 3 at a time";
   for (int i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(vis.get(i), expected[i])
      << "Got unexpected combination for 3 objects 2 at a time in index " << i;
  }
}

TEST(CombinationsTest, TestCount1) {
  CountingVisitor<1> vis1;
  combinations::combinations_lex_basic(10, vis1);
  EXPECT_EQ(vis1.getN(), 10) << "10 chose 1 is 10";

  vis1.reset();
  combinations::combinations_lex_basic(20, vis1);
  EXPECT_EQ(vis1.getN(), 20) << "20 chose 1 is 20";
}

TEST(CombinationsTest, TestCount4) {
  CountingVisitor<4> vis4;
  combinations::combinations_lex_basic(10, vis4);
  EXPECT_EQ(vis4.getN(), 210) << "10 chose 4 is 210";

  vis4.reset();
  combinations::combinations_lex_basic(20, vis4);
  EXPECT_EQ(vis4.getN(), 4845) << "20 chose 4 is 4845";
}

TEST(CombinationsTest, TestCountBig) {
  CountingVisitor<10> vis10;
  combinations::combinations_lex_basic(20, vis10);
  EXPECT_EQ(vis10.getN(), 184756) << "20 chose 10 is 184756";
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}