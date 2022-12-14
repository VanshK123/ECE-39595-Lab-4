#ifndef POLY_H
#define POLY_H
#include <cstddef>
#include <vector>

using power = size_t;
using coeff = int;

class polynomial
{

public:
    /**
     * @brief Construct a new polynomial object that is the number 0 (ie. 0x^0)
     * 
     */
    polynomial();

    /**
     * @brief Construct a new polynomial object from an iterator to pairs of <power,coeff>
     *
     * @tparam Iter 
     *  An iterator that points to a std::pair<power, coeff>
     * @param begin
     *  The start of the container to copy elements from
     * @param end
     *  The end of the container to copy elements from
     */
    template <typename Iter>
    polynomial(Iter begin, Iter end);

    /**
     * @brief Construct a new polynomial object from an existing polynomial object
     * 
     * @param other
     *  The polynomial to copy
     */
    polynomial(const polynomial &other);

    /**
     * @brief Prints the polynomial. 
     * 
     * Only used for debugging, isn't graded.
     *
     */
    void print() const;

    /**
     * Each of these has the standard math definition
     */
    polynomial &operator=(const polynomial &other);
    polynomial operator+(const polynomial &other) const;
    polynomial operator*(const polynomial &other) const;
    bool operator<(const polynomial &other) const;
    bool operator>(const polynomial &other) const;
    bool operator==(const polynomial &other) const;

    //takes two polynomials(this polynomial and another polynomial) and returns one polynomial by reference
    int MultiplyThreading(const polynomial &other, int start, int end, polynomial &result);
    /**
     * @brief Returns the degree of the polynomial
     *
     * @return size_t
     *  The degree of the polynomial
     */
    size_t find_degree_of();

    /**
     * @brief Returns a vector that contains the polynomial is canonical form. This
     *        means that the power at index 0 is the largest power in the polynomial,
     *        the power at index 1 is the second largest power, etc.
     *
     *        ie. x^2 + 7x^4 + 1 would be returned as [(4,7),(2,1),(0,1)]
     * 
     *        Note: any terms that have a coefficient of zero aren't returned in 
     *        in the canonical form, with one exception. 
     *        See the above example (there's no x^3 term, so
     *        there's no entry in the vector for x^3)
     * 
     *        The only exception to this is the polynomial 0. If your polynomial is 
     *        just the constant 0 then you would return a single entry of [(0,0)]
     * 
     *        ie. y = 0 would be returned as [(0,0)]    
     *
     * @return std::vector<std::pair<power, coeff>>
     *  A vector of pairs representing the canonical form of the polynomial
     */
    std::vector<std::pair<power, coeff>> canonical_form() const;

    //ADDED PART
    std::vector<std::pair<power, coeff>> CoeffAndPowerVec; //this is the vector of pairs
    long size; //this is used to keep track of size of the array
    long biggestpower; //this is used to keep track of the biggest power in the array

};

//#include "poly.hpp"
template <typename Iter>
polynomial::polynomial(Iter begin, Iter end)
{
    //we are using an iterator to go through the vector
    int big = 0;
    //we first find size of the iterator
    size_t itersize = 0;
    for (Iter i = begin; i != end; i++)
    {
        itersize++;
    }

    //we push back the pairs from the iterator to the vector
    for (Iter i = begin; i != end; i++)
    {
        CoeffAndPowerVec.push_back(*i);

        //we also find the biggest power
        if (i->first > big)
        {
           big = i->first;
        }
    }

    //we set the size to itersize
    size = itersize;
    //biggestpower
    biggestpower = big;

}


#endif
