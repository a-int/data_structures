#include <cassert>
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
#endif //test for private members

TEST(VectorTest, ConstructorWithProvidedCapacityAndValue){
    int SIZE = 3;
    int VALUE = 101;
    vector<int> vec(SIZE, VALUE);

    EXPECT_EQ(vec.size(), SIZE)<<"default size must be equal to zero";
    ASSERT_EQ(vec.capacity(), SIZE)<<"capacity must be equal to provided number - "<<SIZE;
    
    EXPECT_PRED1([=](int x)->bool{return x == VALUE;}, vec[0]);
    EXPECT_PRED1([=](int x)->bool{return x == VALUE;}, vec[1]);
    EXPECT_PRED1([=](int x)->bool{return x == VALUE;}, vec[2]);
}
TEST(VectorTest, ConstructByVector){
    vector<int> v1(3,1);
    vector<int>v2(v1);

    EXPECT_EQ(v2.size(), v1.size());
    ASSERT_EQ(v2.capacity(), v1.capacity());
    
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, v2[0], v1[0]);
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, v2[1], v1[1]);
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, v2[2], v1[2]);
}
TEST(VectorTest, AssignVector){
    vector<int> v1(3,1);
    vector<int>v2;
    v2 = v1;

    EXPECT_EQ(v2.size(), v1.size());
    ASSERT_EQ(v2.capacity(), v1.capacity());

    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, v2[0], v1[0]);
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, v2[1], v1[1]);
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, v2[2], v1[2]);
}

TEST(VectorTest, BeginMethod){
    vector<int> vec(1,2);
    ASSERT_EQ(*vec.begin(), vec[0]);
}
TEST(VectorTest, EndMethod){
    vector<int> vec(1,2);

    ASSERT_EQ(*vec.end(), vec[vec.size()]);
}
TEST(VectorTest, FrontMethod){
    vector<int> vec(10,5);

    EXPECT_EQ(vec.front(), *vec.begin());
    EXPECT_EQ(&vec.front(), &(*(vec.begin())));
}
TEST(VectorTest, BackMethod){
    vector<int> vec(10,5);

    EXPECT_EQ(vec.back(), *(vec.end()-1));
    EXPECT_EQ(&vec.back(), &(*(vec.end()-1)));
}
TEST(VectorTest, SubscriptOperator){
    vector<int> vec(10, 5);

    EXPECT_EQ(vec[0], vec.front());
    EXPECT_EQ(vec[vec.size()-1], vec.back());
}

TEST(VectorTest, ResizeToSmaller){
    int SIZE = 10, NEWSIZE = 3;
    int VAL = 5;
    vector<int> vec(SIZE,VAL);

    vec.resize(NEWSIZE);

    EXPECT_EQ(vec.size(), NEWSIZE)<<"the vector was shrank, size must be updated to "<<NEWSIZE;
    EXPECT_EQ(vec.capacity(), NEWSIZE)<<"capacity must be equal to "<<NEWSIZE;

    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, vec[0], VAL);
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, vec[1], VAL);
    EXPECT_PRED2([=](int x, int y)->bool{return x == y;}, vec[2], VAL);
}
TEST(VectorTest, ResizeToBigger){
    int SIZE = 10, NEWSIZE = 13;
    int VAL = 5;
    vector<int> vec(SIZE,VAL);

    vec.resize(NEWSIZE);

    EXPECT_EQ(vec.size(), SIZE)<<"the vector was extented, size must be equal to origin size -"<<SIZE;
    EXPECT_EQ(vec.capacity(), NEWSIZE)<<"capacity must be equal to "<<NEWSIZE;
}
TEST(VectorTest, ResizeToSame){
    int SIZE = 10, NEWSIZE = 10;
    int VAL = 5;
    vector<int> vec(SIZE,VAL);

    vec.resize(NEWSIZE);

    EXPECT_EQ(vec.size(), SIZE)<<"size must be equal to origin size -"<<SIZE;
    EXPECT_EQ(vec.capacity(), NEWSIZE)<<"capacity must be equal to "<<NEWSIZE;
}
