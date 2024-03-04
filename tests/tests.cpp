#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Worker.h"

TEST(MatrixTests, simple) {
  Matrix mtx {
    .data = {1, 2, 3, 4, 5, 6},
    .width = 3,
    .height = 2 
  };

  Matrix expected_mtx = {
    .data = {1, 4, 2, 5, 3, 6}, 
    .width = 2,
    .height = 3};

  Worker worker;
  Matrix result = worker.transpose(mtx);

  EXPECT_EQ(result.width, expected_mtx.width);
  EXPECT_EQ(result.height, expected_mtx.height);
  EXPECT_EQ(result.data, expected_mtx.data);
}

TEST(MatrixTests, 10x10) {
    Matrix mtx {
    .data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
              11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
              21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
              31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
              41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
              51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
              61, 62, 63, 64, 65, 66, 67, 68, 69, 70,
              71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
              81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
              91, 92, 93, 94, 95, 96, 97, 98, 99, 100 },
    .width = 10,
    .height = 10 
  };

  Matrix expected_mtx = { 
    .data = { 1, 11, 21, 31, 41, 51, 61, 71, 81, 91,
              2, 12, 22, 32, 42, 52, 62, 72, 82, 92,
              3, 13, 23, 33, 43, 53, 63, 73, 83, 93,
              4, 14, 24, 34, 44, 54, 64, 74, 84, 94,
              5, 15, 25, 35, 45, 55, 65, 75, 85, 95,
              6, 16, 26, 36, 46, 56, 66, 76, 86, 96,
              7, 17, 27, 37, 47, 57, 67, 77, 87, 97,
              8, 18, 28, 38, 48, 58, 68, 78, 88, 98,
              9, 19, 29, 39, 49, 59, 69, 79, 89, 99,
              10, 20, 30, 40, 50, 60, 70, 80, 90, 100 }, 
    .width = 10 ,
    .height = 10  
  };

  Worker worker;
  auto result = worker.transpose(mtx);

  EXPECT_EQ(result.width, expected_mtx.width);
  EXPECT_EQ(result.height, expected_mtx.height);
  EXPECT_EQ(result.data, expected_mtx.data);
}

TEST(MatrixTests, 1x1) {
  Matrix mtx = {
    .data = {1},
    .width = 1,
    .height = 1
  };

  Worker worker;
  EXPECT_EQ(worker.transpose(mtx).data, mtx.data);
}

TEST(MatrixTests, 0x0) {
  Matrix mtx = {
    .data = {},
    .width = 0,
    .height = 0
  };
  
  Worker worker;
  EXPECT_EQ(worker.transpose(mtx).data, mtx.data);
}

TEST(WorkerTest, GetNewWorkerTest) {
    auto worker = get_new_worker();
    ASSERT_TRUE(worker != nullptr);

    auto derived_worker = std::dynamic_pointer_cast<Worker>(worker);
    ASSERT_TRUE(derived_worker != nullptr);
}

TEST(WorkerTest, AsyncProcessTest) {
    auto worker = get_new_worker();
    Matrix mtx {
        .data = { 1, 2, 3,
                  4, 5, 6 },
        .width = 3,
        .height = 2 };
        
    Matrix expected_mtx {
        .data = { 1, 4,
                  2, 5,
                  3, 6 },
        .width = 2,
        .height = 3
    };
    auto future = worker->AsyncProcess(mtx);
    auto m = future.get();

    EXPECT_EQ(m.data, expected_mtx.data);
    EXPECT_EQ(m.width, expected_mtx.width);
    EXPECT_EQ(m.height, expected_mtx.height);
}


TEST(WorkerTest, SeveralAsyncProcess) {
    auto worker = get_new_worker();
    Matrix mtx1 {
        .data = { 1, 2, 3,
                  4, 5, 6 },
        .width = 3,
        .height = 2 };

    Matrix mtx2 {
        .data = { 1, 2, 3,
                  4, 5, 6,
                  7, 8, 9 },
        .width = 3,
        .height = 3 };    

    Matrix expected_mtx1 {
        .data = { 1, 4,
                  2, 5,
                  3, 6 },
        .width = 2,
        .height = 3
    };

    Matrix expected_mtx2 {
        .data = { 1, 4, 7,
                  2, 5, 8,
                  3, 6, 9 },
        .width = 3,
        .height = 3
    };

    auto future1 = worker->AsyncProcess(mtx1);
    auto future2 = worker->AsyncProcess(mtx2);
    auto m1 = future1.get();
    auto m2 = future2.get();

    EXPECT_EQ(m1.data, expected_mtx1.data);
    EXPECT_EQ(m2.width, expected_mtx2.width);
}

class MockWorker : public Worker {
public:
    MOCK_METHOD(std::future<Matrix>, AsyncProcess, (Matrix), (override));
};

TEST(WorkerTest, MockAsyncProcess) {
    MockWorker mock_worker;
    Matrix input_matrix{ {1, 2, 3, 4}, 2, 2 };
    Matrix expected_matrix{ {1, 3, 2, 4}, 2, 2 };

    EXPECT_CALL(mock_worker, AsyncProcess(input_matrix))
        .WillOnce(testing::Return(std::async(std::launch::deferred, [&expected_matrix]() {
            return expected_matrix;
        })));
        
    auto future_result = mock_worker.AsyncProcess(input_matrix);
    
    auto result = future_result.get();
    EXPECT_EQ(result.width, expected_matrix.width);
    EXPECT_EQ(result.height, expected_matrix.height);
    EXPECT_EQ(result.data, expected_matrix.data);
}
