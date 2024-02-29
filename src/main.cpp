#include <iostream>
#include "Worker.h"

int main() 
{
    auto worker = get_new_worker();
    Matrix mtx {
        .data = { 1, 2, 3,
            4, 5, 6 },
        .width = 3,
        .height = 2 };
    auto future = worker->AsyncProcess(mtx);
    auto m = future.get();
    for (std::size_t i = 0; i < m.data.size(); ++i)
        std::cout << m.data[i] << ' '; 
    return 0;
}

