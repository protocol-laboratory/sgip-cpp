#ifndef BOUNDATOMIC_H
#define BOUNDATOMIC_H

#include <atomic>
#include <cassert>

class BoundAtomic {
public:
    BoundAtomic(int min, int max);
    int next_val();

private:
    int min_;
    int max_;
    std::atomic<int> integer_;
};

#endif //BOUNDATOMIC_H
