#pragma once

#include "WorkerInterface.h"

class Worker : public WorkerInterface {
public:
    Worker() = default;
    ~Worker() override  { };
    
    Matrix transpose(Matrix matrix);

    std::future<Matrix> AsyncProcess(Matrix m) override {
        return std::async(std::launch::deferred, &Worker::transpose, this, m);
    }
};