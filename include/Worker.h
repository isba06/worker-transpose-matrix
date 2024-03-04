#pragma once

#include "WorkerInterface.h"

class Worker : public WorkerInterface {
public:
    Worker() = default;
    ~Worker() override { };
    
    Matrix transpose(Matrix matrix);

    std::future<Matrix> AsyncProcess(Matrix m) override;
};