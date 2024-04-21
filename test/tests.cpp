// Copyright 2024 StatsenkoArs
#include "googletest/googletest/include/gtest/gtest.h"
#include "textgen.h"

TEST(gen_prefix, test1) {
    std::string in = "The difference between stupidity and genius is that genius has its limits.";
    std::vector<std::string> words = mySplit(in, ' ');
    int len = 3;
    int pos = 4;
    prefix pre = gen_pre(words, pos, len);
    for (int i = 0 ; i < len; i++)
        EXPECT_EQ(words[pos - len + i], pre.at(i));
}

TEST(gen_prefix_suffix, test2) {
    std::string in = "The difference between stupidity and genius is that genius has its limits.";
    prefix pre = gen_tab(in, 11);
    prefix key({"The", "difference", "between", "stupidity", "and", "genius", "is", "that", "genius", "has", "its"});
    std::vector<std::string> value {"limits."};
    for (const auto& el : statetab) {
        EXPECT_EQ(key, el.first);
        EXPECT_EQ(value, el.second);
    }
}

TEST(pick_suffix, test3) {
    std::string in = "The difference between";
    prefix pre = gen_tab(in, 2);
    prefix key({"The", "difference"});
    EXPECT_EQ({"between"}, statetab[key]);
}

TEST(pick_single_suffix, test4) {
    
}

TEST(gen_text, test5) {
    
}