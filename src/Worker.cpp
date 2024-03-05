#include "Worker.h"

Matrix Worker::transpose(Matrix matrix) {
        unsigned width = matrix.height;
        unsigned height = matrix.width;
        
        Matrix transposed {
            .data = matrix.data,
            .width = width,
            .height = height
        };

        transposed.data.reserve(width * height);
        for(std::size_t i = 0; i < width; ++i)
            for(std::size_t j = 0; j < height; ++j) {
                transposed.data[j*width+i] = matrix.data[i*height+j];
            }
        return transposed;
}

std::future<Matrix> Worker::AsyncProcess(Matrix m) {
    return std::async(std::launch::async, &Worker::transpose, this, m);
}

std::shared_ptr<WorkerInterface> get_new_worker() {
    return std::make_shared<Worker>();
}