//
// Created by tattsun on 15/07/04.
//

#ifndef DUST_BYTECHARSTEST_H
#define DUST_BYTECHARSTEST_H

#include <CppUTest/CommandLineTestRunner.h>
#include "../src/ByteChars.h"

using namespace dust;

TEST_GROUP(ByteCharsTest) {
};

TEST(ByteCharsTest, Instantiate) {
    {
        const char *t1 = "Hello";
        ByteChars b1(t1, 5);
        STRCMP_EQUAL(t1, b1.c_str());
        LONGS_EQUAL(5, b1.length());
    }

    {
        std::string str("Hello");
        ByteChars bc(str);
        STRCMP_EQUAL(str.c_str(), bc.c_str());
        LONGS_EQUAL(5, bc.length());
    }

    {
        ByteChars bc1("Hello");
        ByteChars bc2("Hello");
        STRCMP_EQUAL(bc1.c_str(), bc2.c_str());
        LONGS_EQUAL(5, bc1.length());
    }
}

TEST(ByteCharsTest, Append) {
    {
        std::string s1("hello");
        std::string s2("world");
        ByteChars bc(s1);
        bc.Append(s2);
        STRCMP_EQUAL("helloworld", bc.c_str());
        LONGS_EQUAL(10, bc.length());
    }

    {
        ByteChars bc("aaa");
        bc.Append(ByteChars("bbb"));
        bc.Append(ByteChars("ccc"));
        STRCMP_EQUAL("aaabbbccc", bc.c_str());
        LONGS_EQUAL(9, bc.length());
    }
}

TEST(ByteCharsTest, FindCharFirstPos) {
    {
        ByteChars bc("Hello,world");
        LONGS_EQUAL(5, bc.FindCharFirstPos(','));
        LONGS_EQUAL(0, bc.FindCharFirstPos('H'));
        LONGS_EQUAL(-1, bc.FindCharFirstPos('N'));
        LONGS_EQUAL(10, bc.FindCharFirstPos('d'));
    }
}

TEST(ByteCharsTest, Substr) {
    {
        ByteChars bc("Hello,world");
        STRCMP_EQUAL("Hello", bc.Substr(0, 5).c_str());
        STRCMP_EQUAL("world", bc.Substr(6, 5).c_str());

        STRCMP_EQUAL("world", bc.Substr(6).c_str());
    }
}

#endif //DUST_BYTECHARSTEST_H
