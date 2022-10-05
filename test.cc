#ifdef PTESTING
#define private public
#endif

#include <gtest/gtest.h>
#include "include/vector.hpp"


int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//tests for private members
#ifdef PTESTING
TEST(VectorTest, DefaultProperties){
    vector<int> vec;

    EXPECT_EQ(vec.size(), 0)<<"default size must be equal to zero";
    EXPECT_EQ(vec.capacity(),0)<<"default capacity must be eqaul to zero";
    EXPECT_EQ(vec.m_Buffer, nullptr);
}


TEST(VectorTest, ConstructorWithProvidedCapacity){
    int SIZE = 3;
    vector<int> vec(SIZE);

    EXPECT_EQ(vec.size(), 0)<<"default size must be equal to zero";
    ASSERT_EQ(vec.capacity(), SIZE)<<"capacity must be equal to provided number - "<<SIZE;
    EXPECT_NE(vec.m_Buffer+0, nullptr);
    EXPECT_NE(vec.m_Buffer+1, nullptr);
    EXPECT_NE(vec.m_Buffer+2, nullptr);
}

TEST(VectorTest, ConstructorWithProvidedCapacityAndValue){
    int SIZE = 3;
    int VALUE = 101;
    vector<int> vec(SIZE, VALUE);

    EXPECT_EQ(vec.size(), SIZE)<<"default size must be equal to zero";
    ASSERT_EQ(vec.capacity(), SIZE)<<"capacity must be equal to provided number - "<<SIZE;
    
    EXPECT_PRED1([=](int x)->bool{return x == VALUE;}, *(vec.m_Buffer+0));
    EXPECT_PRED1([=](int x)->bool{return x == VALUE;}, *(vec.m_Buffer+1));
    EXPECT_PRED1([=](int x)->bool{return x == VALUE;}, *(vec.m_Buffer+2));
}

TEST(VectorTest, ConstructByVector){
    vector<int> v1(3,1);
    vector<int>v2(v1);

    EXPECT_EQ(v2.size(), v1.size());
    ASSERT_EQ(v2.capacity(), v1.capacity());
    
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, *(v2.m_Buffer+0), *(v1.m_Buffer+0));
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, *(v2.m_Buffer+1), *(v1.m_Buffer+1));
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, *(v2.m_Buffer+2), *(v1.m_Buffer+2));
}

TEST(VectorTest, AssignVector){
    vector<int> v1(3,1);
    vector<int>v2;
    v2 = v1;

    EXPECT_EQ(v2.size(), v1.size());
    ASSERT_EQ(v2.capacity(), v1.capacity());

    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, *(v2.m_Buffer+0), *(v1.m_Buffer+0));
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, *(v2.m_Buffer+1), *(v1.m_Buffer+1));
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, *(v2.m_Buffer+2), *(v1.m_Buffer+2));
}
#endif //test for private members