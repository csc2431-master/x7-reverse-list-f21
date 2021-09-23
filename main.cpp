#include <assert.h>
#include <iostream>
using std::cout;
using std::endl;

#include "FixedArrayList.h"

void ReverseList(FixedArrayList<int>& L);

int main() {
    FixedArrayList<int> L(5);
    int max;

    // Load list with numbers
    L.Insert(0,47);
    L.Insert(1,2);
    L.Insert(2,39);
    L.Insert(3, 54);
    L.Insert(4, 10);

    // Find the maximum in the list recursively
    cout << "List before calling ReserveList: " << L << endl;
    ReverseList(L);
    cout << "List after calling ReserveList: " << L << endl;
    return 0;
}

void ReverseList(FixedArrayList<int>& L) {
    cout << "Calling ReverseList on L = " << L << endl;
    if (L.Size() > 1) {
        int last;

        L.Remove(L.Size() - 1, last);
        ReverseList(L);
        L.Insert(0, last);
    }
}
