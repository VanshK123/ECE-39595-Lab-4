#include "poly.h"

#include <iostream>
#include <chrono>
#include <optional>
#include <vector>
#include <algorithm>

using namespace std;

polynomial::polynomial()
{
    // we push back the pair (0,0) to the vector
    CoeffAndPowerVec.push_back(std::make_pair(0, 0));

    // we set the size to 1
    size = 1;
    biggestpower = 0;
}

polynomial::polynomial(const polynomial &other)
{
    // this is our copy constructor, we copy the values from the other polynomial

    // copy the vector
    CoeffAndPowerVec = other.CoeffAndPowerVec;

    // we set the size to other.size
    size = other.size;
    biggestpower = other.biggestpower;
}

void polynomial::print() const
{
    // NOT GRADED - just used for debugging, prints in x^y form
    for (size_t i = 0; i < size; i++)
    {
        //dont print the last + sign, dont print coeff if it equals 1
        if(i == size - 1)
        {
            if(CoeffAndPowerVec[i].second == 1)
            {
                printf("x^%ld", CoeffAndPowerVec[i].first);
            }
            else
            {
                printf("%ldx^%ld", CoeffAndPowerVec[i].second, CoeffAndPowerVec[i].first);
            }
        }
        else
        {
            if(CoeffAndPowerVec[i].second == 1)
            {
                printf("x^%ld + ", CoeffAndPowerVec[i].first);
            }
            else
            {
                printf("%ldx^%ld + ", CoeffAndPowerVec[i].second, CoeffAndPowerVec[i].first);
            }
        }
    }
    std::cout << std::endl;

    //we print the size and biggestpower
    printf("size: %ld, biggestpower: %ld\n", size, biggestpower);
}

polynomial &polynomial::operator=(const polynomial &other)
{
    // this is the assignment operator, so we can just copy the elements from the other polynomial
    if (this == &other)
    {
        return *this;
    }

    // copy the vector
    CoeffAndPowerVec = other.CoeffAndPowerVec;

    // we set the size to other.size
    size = other.size;
    biggestpower = other.biggestpower;

    // we delete the old array
    // delete[] CoeffAndPowerarray;

    return *this;
}

polynomial polynomial::operator+(const polynomial &other) const
{
    // this is the addition operator, so we can just add the elements from the other polynomial
    polynomial result;
    
    //we set the biggestpower to the biggest power of the two polynomials
    if (biggestpower > other.biggestpower)
    {
        result.biggestpower = biggestpower;
    }
    else
    {
        result.biggestpower = other.biggestpower;
    }
    // we the append the two vectors into the result vector based on the power (highest to lowest)

    // we initialize the iterators
    auto it1 = CoeffAndPowerVec.begin();
    auto it2 = other.CoeffAndPowerVec.begin();

    // we loop through the vectors

    while (it1 != CoeffAndPowerVec.end() && it2 != other.CoeffAndPowerVec.end())
    {
        // we check if the power of the first vector is bigger than the second vector
        if (it1->first > it2->first)
        {
            // we push back the pair from the first vector
            result.CoeffAndPowerVec.push_back(*it1);
            it1++;

        }
        // we check if the power of the second vector is bigger than the first vector
        else if (it1->first < it2->first)
        {
            // we push back the pair from the second vector
            result.CoeffAndPowerVec.push_back(*it2);
            it2++;

        }
        // we check if the power of the first vector is equal to the second vector
        else if (it1->first == it2->first)
        {
            // we add the coefficients and push back the pair
            result.CoeffAndPowerVec.push_back(std::make_pair(it1->first, it1->second + it2->second));
            it1++;
            it2++;

        }
    }

    // we update the size and biggestpower
    result.size = result.CoeffAndPowerVec.size();

    //we remove 0 coefficients if they exist if size is bigger than 1
    if(result.size > 1)
    {
        for (size_t i = 0; i < result.size; i++)
        {
            if(result.CoeffAndPowerVec[i].second == 0)
            {
                result.CoeffAndPowerVec.erase(result.CoeffAndPowerVec.begin() + i);
                result.size--;
            }
        }
    }

    

    return result;
}

polynomial polynomial::operator*(const polynomial &other) const
{
    // this is the multiplication operator
    polynomial result;

    int currentbiggestpower = 0;
    // we initialize the iterators
    auto it1 = CoeffAndPowerVec.begin();
    auto it2 = other.CoeffAndPowerVec.begin();

    // we loop through the vectors
    for (auto i = it2; i < other.CoeffAndPowerVec.end(); i++)
    {
        for (auto j = it1; j != CoeffAndPowerVec.end(); j++)
        {
            // we push back the pair from the first vector
            //if power is already in the vector, we add the coefficient
            if(result.CoeffAndPowerVec.size() > 0 && result.CoeffAndPowerVec.back().first == i->first + j->first){
                result.CoeffAndPowerVec.back().second += i->second * j->second;
            }
            else{
                result.CoeffAndPowerVec.push_back(std::make_pair(i->first + j->first, i->second * j->second));
            }
            //result.CoeffAndPowerVec.push_back(std::make_pair(i->first + j->first, i->second * j->second));
            if (i->first + j->first > currentbiggestpower)
            {
                currentbiggestpower = i->first + j->first;
            }
        }
    }

    //we combine the coefficients if they have the same power
    for (size_t i = 0; i < result.CoeffAndPowerVec.size(); i++)
    {
        for (size_t j = i + 1; j < result.CoeffAndPowerVec.size(); j++)
        {
            if (result.CoeffAndPowerVec[i].first == result.CoeffAndPowerVec[j].first)
            {
                result.CoeffAndPowerVec[i].second += result.CoeffAndPowerVec[j].second;
                result.CoeffAndPowerVec.erase(result.CoeffAndPowerVec.begin() + j);
                j--;
            }
        }
    }

    //sort so that the highest power is first
    std::sort(result.CoeffAndPowerVec.begin(), result.CoeffAndPowerVec.end(), std::greater<std::pair<int, int>>());

    
    // update biggestpower
    result.biggestpower = currentbiggestpower;
    // if biggest power is greater then 0, trim all 0 coefficients, else leave the 0 power coefficient
    // we trim all 0 coefficients that are not also 0 power

    if (result.CoeffAndPowerVec.size() > 1)
    {
        printf("size is greater than 1\n");
        for (auto i = result.CoeffAndPowerVec.begin(); i != result.CoeffAndPowerVec.end(); i++)
        {
            if (i->second == 0)
            {
                result.CoeffAndPowerVec.erase(i);
            }
        }
    }

    // we update the size
    result.size = result.CoeffAndPowerVec.size();

    // we print the result
    printf("Size: %d, Biggest power: %d\n", result.size, result.biggestpower);
    return result;
}

bool polynomial::operator<(const polynomial &other) const
{
    // this is the less than operator, so we can just compare the elements from the other polynomial
    // first check biggest power
    printf("biggestpower: %d, other.biggestpower: %d\n", biggestpower, other.biggestpower);
    if (biggestpower < other.biggestpower)
    {
        return true;
    }
    else if (biggestpower > other.biggestpower)
    {
        return false;
    }
    else
    {
        // if the biggest powers are equal, we check the coeff of the biggest power
        if (CoeffAndPowerVec[0].second < other.CoeffAndPowerVec[0].second)
        {
            return true;
        }
        else if (CoeffAndPowerVec[0].second > other.CoeffAndPowerVec[0].second)
        {
            return false;
        }
        else
        {
            // if the biggest powers, coeffs and size are equal, we check the coeff and power of the other elements
            for (size_t i = 1; i < size; i++)
            {
                if (CoeffAndPowerVec[i].second < other.CoeffAndPowerVec[i].second)
                {
                    return true;
                }
                else if (CoeffAndPowerVec[i].second > other.CoeffAndPowerVec[i].second)
                {
                    return false;
                }
                else
                {
                    if (CoeffAndPowerVec[i].first < other.CoeffAndPowerVec[i].first)
                    {
                        return true;
                    }
                    else if (CoeffAndPowerVec[i].first > other.CoeffAndPowerVec[i].first)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return false;
}

bool polynomial::operator>(const polynomial &other) const
{
    // this is the greater than operator, so we can just compare the elements from the other polynomial
    // first check biggest power
    printf("biggestpower: %d, other.biggestpower: %d\n", biggestpower, other.biggestpower);
    if (biggestpower > other.biggestpower)
    {
        return true;
    }
    else if (biggestpower < other.biggestpower)
    {
        return false;
    }
    else
    {
        // if the biggest powers are equal, we check the coeff of the biggest power
        if (CoeffAndPowerVec[0].second > other.CoeffAndPowerVec[0].second)
        {
            return true;
        }
        else if (CoeffAndPowerVec[0].second < other.CoeffAndPowerVec[0].second)
        {
            return false;
        }
        else
        {
            // if the biggest powers, coeffs and size are equal, we check the coeff and power of the other elements
            for (size_t i = 1; i < size; i++)
            {
                if (CoeffAndPowerVec[i].second > other.CoeffAndPowerVec[i].second)
                {
                    return true;
                }
                else if (CoeffAndPowerVec[i].second < other.CoeffAndPowerVec[i].second)
                {
                    return false;
                }
                else
                {
                    if (CoeffAndPowerVec[i].first > other.CoeffAndPowerVec[i].first)
                    {
                        return true;
                    }
                    else if (CoeffAndPowerVec[i].first < other.CoeffAndPowerVec[i].first)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return false;
}

bool polynomial::operator==(const polynomial &other) const
{
    // this is the equal to operator, so we can just compare the elements from the other polynomial
    // first check biggest power
    if (biggestpower != other.biggestpower)
    {
        // if the biggest powers are not equal, we return false
        return false;
    }

    // check coeff of biggest power
    if (CoeffAndPowerVec[0].second != other.CoeffAndPowerVec[0].second)
    {
        // if the coeffs of the biggest power are not equal, we return false
        return false;
    }

    // check size
    if (size != other.size)
    {
        // if the sizes are not equal, we return false
        return false;
    }

    // check the coeff and power of the other elements
    for (size_t i = 1; i < size; i++)
    {
        if (CoeffAndPowerVec[i].second != other.CoeffAndPowerVec[i].second)
        {
            // if the coeffs are not equal, we return false
            return false;
        }
        else
        {
            if (CoeffAndPowerVec[i].first != other.CoeffAndPowerVec[i].first)
            {
                // if the powers are not equal, we return false
                return false;
            }
        }
    }
    return true;
}

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const
{
    // this is the main function that we need to implement
    std::vector<std::pair<power, coeff>> result;

    //print the polynomial
    printf("Polynomial: ");
    this->print();

    //we copy the polynomial to the result in format x^2 + 7x^4 + 1 would be returned as [(4,7),(2,1),(0,1)]
    for (auto i = CoeffAndPowerVec.begin(); i != CoeffAndPowerVec.end(); i++)
    {
        power p = i->first;
        coeff c = i->second;
        result.push_back(std::make_pair(p, c));
    }

    //print the result
    printf("Canonical form: ");
    for (auto i = result.begin(); i != result.end(); i++)
    {
        printf("(%d,%d) ", i->second, i->first);
    }





    /*

    // we first initialize three arrays, one for the powers, one for the coeffs and one for the result
    int powers[size];
    int coeffs[size];
    int result_coeffs[size];

    // we initialize the result_coeffs array with 0
    for (size_t i = 0; i < size; i++)
    {
        result_coeffs[i] = 0;
    }

    // we initialize the powers and coeffs arrays with the values from the vector
    for (size_t i = 0; i < size; i++)
    {
        powers[i] = CoeffAndPowerVec[i].second;
        coeffs[i] = CoeffAndPowerVec[i].first;
    }

    // we sort the powers array
    std::sort(powers, powers + size);

    // we sort the coeffs array
    std::sort(coeffs, coeffs + size);

    // print the powers array
    std::cout << "powers: ";
    for (size_t i = 0; i < size; i++)
    {
        std::cout << powers[i] << " ";
    }
    std::cout << std::endl;
    // print the coeffs array
    std::cout << "coeffs: ";
    for (size_t i = 0; i < size; i++)
    {
        std::cout << coeffs[i] << " ";
    }
    std::cout << std::endl;

    // we initialize the result_coeffs array with the values from the coeffs array
    for (size_t i = 0; i < size; i++)
    {
        result_coeffs[i] = coeffs[i];
    }

    // we initialize the result vector with the values from the result_coeffs array
    for (size_t i = 0; i < size; i++)
    {
        result.push_back(std::make_pair(powers[i], result_coeffs[i]));
    }
    */

    return result;
}

size_t polynomial::find_degree_of()
{
    // this is the find degree function, so we can just return the power
    return biggestpower;
}
