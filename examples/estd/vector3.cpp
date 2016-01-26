/**
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */

#include <cstdio>

#include <estd/vector.h>
#include <estd/uncopyable.h>

/*
 * An example of using the vector with uncopyable objects.
 * This is quite common when writing embedded C++ code.
 */

/*
 * A simple class that cannot be copied.
 *
 * Classes that are stored in a vector must have a default
 * constructor.
 */
class MyClass
{
    UNCOPYABLE(MyClass);

public:

    MyClass(int value) : fValue(value) { fprintf(stderr, "Creating class\n"); }
    ~MyClass() { fprintf(stderr, "Deleting MyClass\n"); }

    void setValue(int value) { fValue = value; }

    int getValue() const { return fValue; }

private:

    int fValue;
};

/*
 * A simple method that initializes the elements in a vector
 */
void fillVec(esrlabs::estd::vector<MyClass>& aVec, size_t count)
{
    for(size_t i = 0; i < count; ++i)
    {
        // This is not possible because MyClass is not copyable.
//        MyClass tmp;
//        tmp.setValue(i);
//        aVec.push_back(tmp);

        // make sure that the vector is not full. Otherwise
        // the vector will assert!
        if(!aVec.full()) {
            // Use the emplace method to create an object in place

            aVec.emplace_back().construct(i);
        }
    }
}

/*
 * Use the const_iterator methods: cbegin, cend to print out the vector
 */
void printVec(const esrlabs::estd::vector<MyClass>& aVec)
{
    esrlabs::estd::vector<MyClass>::const_iterator iter;

    fprintf(stderr, "Vector contains:");
    for(iter = aVec.cbegin(); iter != aVec.cend(); ++iter)
    {
        fprintf(stderr, " %d", iter->getValue());
    }
    fprintf(stderr, "\n");
}

void scaleVec(esrlabs::estd::vector<MyClass>& aVec, int scale)
{
    // use operator[] to scale the values in the vector
    for(size_t i = 0; i < aVec.size(); ++i)
    {
        aVec[i].setValue(aVec[i].getValue() * scale);
    }
}

int main()
{
    // declare a vector of 10 MyClass objects
    esrlabs::estd::declare::vector<MyClass, 10> vec;

    // fill the vector with 20 items. It will only add
    // 10 because that is the size of our vector
    fillVec(vec, 20);
    vec.erase(vec.begin());
#if 0
    printVec(vec);
    scaleVec(vec, 10);
    printVec(vec);
#endif
    return 0;
}
