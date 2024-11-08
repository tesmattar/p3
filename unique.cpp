#include <iostream>
#include <iterator>
#include <algorithm>

namespace graal {

    template <typename Itr, typename Equal>
    Itr unique(Itr first, Itr last, Equal eq) {
        if (first == last) return last;

        Itr result = first;  // Result iterator to store unique elements.
        ++first;  // Advance first to start comparison.

        while (first != last) {
            bool is_unique = true;
            for (Itr it = result; it != first; ++it) {
                if (eq(*it, *first)) {  // Check if current element matches any previous unique element.
                    is_unique = false;
                    break;
                }
            }
            if (is_unique) {
                ++result;  // Move result forward.
                *result = std::move(*first);  // Place the unique element at the result position.
            }
            ++first;  // Move to the next element in the original range.
        }
        return ++result;  // Return the iterator past the last unique element.
    }
}


