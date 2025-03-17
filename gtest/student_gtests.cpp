#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

TEST(WordLadderTest, EditDistanceWithin) {
    EXPECT_TRUE(edit_distance_within("cat", "cot", 1));
    EXPECT_TRUE(edit_distance_within("chat", "cheat", 1));
    EXPECT_TRUE(edit_distance_within("date", "data", 1));
    EXPECT_FALSE(edit_distance_within("cats", "cot", 1));
    EXPECT_FALSE(edit_distance_within("cat", "dog", 1));
    EXPECT_TRUE(edit_distance_within("cat", "ca", 1));
    EXPECT_TRUE(edit_distance_within("ca", "cat", 1));
}

TEST(WordLadderTest, IsAdjacent) {
    EXPECT_TRUE(is_adjacent("cat", "cot"));
    EXPECT_TRUE(is_adjacent("chat", "cheat"));
    EXPECT_TRUE(is_adjacent("date", "data"));
    EXPECT_FALSE(is_adjacent("cats", "cot"));
    EXPECT_FALSE(is_adjacent("cat", "dog"));
    EXPECT_TRUE(is_adjacent("cat", "ca"));
    EXPECT_TRUE(is_adjacent("ca", "cat"));
}

TEST(WordLadderTest, verify) {
    verify_word_ladder();
}
