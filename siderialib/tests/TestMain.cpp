#include <gtest/gtest.h>

class TestEventListener : public testing::EmptyTestEventListener{
public:
    // Called after a test ends.
    void OnTestEnd(const testing::TestInfo& test_info) override {
        printf("*** %s.%s %s\n",
               test_info.test_suite_name(), test_info.name(), test_info.result()->Failed() ? "FAILURE" : "SUCCESS");
    }
};

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    // Gets hold of the event listener list.
    testing::TestEventListeners& listeners =
            testing::UnitTest::GetInstance()->listeners();
    // Adds a listener to the end.  GoogleTest takes the ownership.
    listeners.Append(new TestEventListener);
    return RUN_ALL_TESTS();
}