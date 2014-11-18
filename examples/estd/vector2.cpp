/**
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */

#include <cstdio>

#include <estd/vector.h>


class MyClass
{
public:

    MyClass();

    void fillVec(esrlabs::estd::vector<int>& aVec, size_t count) const;
    void printVec(const esrlabs::estd::vector<int>& aVec) const;
    void scaleVec(esrlabs::estd::vector<int>& aVec, int scale) const;

};

MyClass::MyClass()
{

}

/*
 * Fill the vector
 */
void MyClass::fillVec(esrlabs::estd::vector<int>& aVec, size_t count) const
{
    for(size_t i = 0; i < count; ++i)
    {
        aVec.push_back(i);
    }
}

/*
 * Use the const_iterator methods: cbegin, cend
 */
void MyClass::printVec(const esrlabs::estd::vector<int>& aVec) const
{
    esrlabs::estd::vector<int>::const_iterator iter;

    fprintf(stderr, "Vector contains:");
    for(iter = aVec.cbegin(); iter != aVec.cend(); ++iter)
    {
        fprintf(stderr, " %d", *iter);
    }
    fprintf(stderr, "\n");
}

void MyClass::scaleVec(esrlabs::estd::vector<int>& aVec, int scale) const
{
    // use operator[] to scale the values in the vector
    for(size_t i = 0; i < aVec.size(); ++i)
    {
        aVec[i] = aVec[i] * scale;
    }
}

int main()
{
    // declare a vector of 10 ints
    esrlabs::estd::declare::vector<int, 10> vec;

    MyClass mc;

    mc.fillVec(vec, 8);
    mc.printVec(vec);
    mc.scaleVec(vec, 20);
    mc.printVec(vec);

    return 0;
}
