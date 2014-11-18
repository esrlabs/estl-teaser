/**
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */

#include <cstdio>

#include <algorithm>

#include <estd/vector.h>

void print(int i)
{
    fprintf(stderr, " %d", i);
}

int main()
{
    // declare a vector of 10 ints
    esrlabs::estd::declare::vector<int, 10> vec;

    // add some values to the vector
    for(int i = 9; i >= 0; --i)
    {
        vec.push_back(i);
    }

    std::sort(vec.begin(), vec.end());

    fprintf(stderr, "Vector contains:");
    std::for_each(vec.begin(), vec.end(), print);
    fprintf(stderr, "\n");

    return 0;
}
