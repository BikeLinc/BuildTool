#include <iostream>
#include "gtest/gtest.h"
#include "Fakefile.h"

class FakeTest : public testing::Test {
    protected:
};

// ==== First ====

TEST_F(FakeTest, fakeCalledInFirst) {
    Parser parser("fake/tests/first/Fakefile");
    Compiler compiler(parser.getRules());
    testing::internal::CaptureStdout();
    compiler.executeAllRules();
    
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "echo second output 1\nsecond output 1\necho second output 2\nsecond output 2\necho first output 1\nfirst output 1\necho first output 2\nfirst output 2\n";
    
    ASSERT_EQ(output, expected);
}

// ==== Second ====

TEST_F(FakeTest, fakeCalledInSecond) {
    Parser parser("fake/tests/second/Fakefile");
    Compiler compiler(parser.getRules());
    testing::internal::CaptureStdout();
    compiler.executeAllRules();
    
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "echo second output 1\nsecond output 1\necho second output 2\nsecond output 2\necho \"first output 1\"\nfirst output 1\necho first output 2\nfirst output 2\n";
    
    ASSERT_EQ(output, expected);
}

TEST_F(FakeTest, fakeSecondCalledInSecond) {
    Parser parser("fake/tests/second/Fakefile");
    Compiler compiler(parser.getRules());
    testing::internal::CaptureStdout();
    compiler.executeRule("second");
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "echo second output 1\nsecond output 1\necho second output 2\nsecond output 2\n";
    
    ASSERT_EQ(output, expected);
}

// ==== Third ====

TEST_F(FakeTest, fakeCalledInThird) {
    Parser parser("fake/tests/third/Fakefile");
    Compiler compiler(parser.getRules());
    testing::internal::CaptureStdout();
    compiler.executeAllRules();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "fake: Circular third <- first dependency dropped.\necho third\nthird\necho second output 1\nsecond output 1\necho second output 2\nsecond output 2\necho first output 1\nfirst output 1\necho first output 2\nfirst output 2\n";
    
    ASSERT_EQ(output, expected);
}

// ==== Fourth ====

TEST_F(FakeTest, fakeCalledInFourth) {
    Parser parser("fake/tests/fourth/Fakefile");
    Compiler compiler(parser.getRules());
    testing::internal::CaptureStdout();
    compiler.executeAllRules();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected = "echo '#include <iostream>\\nint main(){std::cout <<\"hello world\" << std::endl;return 0;}' > temp.cpp\ng++ -o temp temp.cpp\n./temp\nhello world\nrm temp\nrm temp.cpp\n";
    
    ASSERT_EQ(output, expected);
}

// ==== Fifth ====\
// Does not let me get the exit value


TEST_F(FakeTest, fakeCalledInFifth) {
   
    ASSERT_DEATH( new Parser("fake/tests/fifth/Fakefile");, "");
}

// ==== Sixth ====

TEST_F(FakeTest, fakeCalledInSixth) {
    Parser parser("fake/tests/sixth/Fakefile");
    Compiler compiler(parser.getRules());
    ASSERT_DEATH(compiler.executeAllRules(), "");
}

// ==== Seventh ====

TEST_F(FakeTest, fakeCalledInSeventh) {
    Parser parser("fake/tests/seventh/Fakefile");
    Compiler compiler(parser.getRules());
    ASSERT_DEATH(compiler.executeAllRules(), "");
}

// ==== Eighth ====

TEST_F(FakeTest, fakeCalledInEighth) {
    Parser parser("fake/tests/eighth/Fakefile");
    Compiler compiler(parser.getRules());
    ASSERT_DEATH(compiler.executeAllRules(), "");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
