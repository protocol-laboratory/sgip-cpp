#include "sgipcpp/BoundAtomic.h"

BoundAtomic::BoundAtomic(int min, int max) : min_(min), max_(max), integer_(min) {
    assert(min <= max);
}

int BoundAtomic::next_val() {
    int current = integer_.load();
    int next;
    do {
        next = current >= max_ ? min_ : current + 1;
    } while (!integer_.compare_exchange_strong(current, next));

    return next;
}
