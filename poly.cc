#include "poly.h"

#include <iostream>
#include <chrono>
#include <optional>
#include <vector>
#include <algorithm>

using namespace std;

polynomial::polynomial()
{
    //we push back the pair (0,0) to the vector
    CoeffAndPowerVec.push_back(std::make_pair(0,0));

    //we set the size to 1
    size = 1;
    biggestpower = 0;
}


polynomial::polynomial(const polynomial &other)
{
    //this is our copy constructor, we copy the values from the other polynomial

    //copy the vector
    CoeffAndPowerVec = other.CoeffAndPowerVec;

    //we set the size to other.size
    size = other.size;
    biggestpower = other.biggestpower;
}
void polynomial::print() const
{
    //NOT GRADED - just used for debugging, prints in x^y form
    for (size_t i = 0; i < size; i++)
    {
        std::cout << CoeffAndPowerVec[i].second << "x^" << CoeffAndPowerVec[i].first << " + ";
    }
    std::cout << std::endl;

}

polynomial &polynomial::operator=(const polynomial &other)
{
    //this is the assignment operator, so we can just copy the elements from the other polynomial
    if(this == &other)
    {
        return *this;
    }

    //copy the vector
    CoeffAndPowerVec = other.CoeffAndPowerVec;

    //we set the size to other.size
    size = other.size;
    biggestpower = other.biggestpower;

    
    //we delete the old array
    //delete[] CoeffAndPowerarray;

    return *this;
}

polynomial polynomial::operator+(const polynomial &other) const
{
    //this is the addition operator, so we can just add the elements from the other polynomial
    polynomial result;
    int currentbiggestpower = INT32_MAX;
    //we the append the two vectors into the result vector based on the power (highest to lowest)
    
    //we initialize the iterators
    auto it1 = CoeffAndPowerVec.begin();
    auto it2 = other.CoeffAndPowerVec.begin();

    //we loop through the vectors

    while (it1 != CoeffAndPowerVec.end() && it2 != other.CoeffAndPowerVec.end())
    {
        //we check if the power of the first vector is bigger than the second vector
        if (it1->first > it2->first)
        {
            //we push back the pair from the first vector
            result.CoeffAndPowerVec.push_back(*it1);
            it1++;
        }
        //we check if the power of the second vector is bigger than the first vector
        else if (it1->first < it2->first)
        {
            //we push back the pair from the second vector
            result.CoeffAndPowerVec.push_back(*it2);
            it2++;
        }
        //we check if the power of the first vector is equal to the second vector
        else if (it1->first == it2->first)
        {
            //we add the coefficients and push back the pair
            result.CoeffAndPowerVec.push_back(std::make_pair(it1->first, it1->second + it2->second));
            it1++;
            it2++;
        }
    }

    //we update the size and biggestpower
    result.size = result.CoeffAndPowerVec.size();
    result.biggestpower = result.CoeffAndPowerVec[0].first;

    return result;

}


polynomial polynomial::operator*(const polynomial &other) const
{
    //this is the multiplication operator
    polynomial result;
    
    int currentbiggestpower = INT32_MAX;
    //we initialize the iterators
    auto it1 = CoeffAndPowerVec.begin();
    auto it2 = other.CoeffAndPowerVec.begin();
    /*
    for(auto i = it1; i < other.CoeffAndPowerVec.end(); i++)
    {
        
    }*/
    
    //we loop through the vectors
    for(auto i = it2; i < other.CoeffAndPowerVec.end(); i++)
    {
        for(auto j = it1; j != CoeffAndPowerVec.end(); j++)
        {
            //we push back the pair from the first vector
            result.CoeffAndPowerVec.push_back(std::make_pair(it1->first + it2->first, it1->second * it2->second));
        }
    }

    //we update the size and biggestpower
    result.size = result.CoeffAndPowerVec.size();
    result.biggestpower = result.CoeffAndPowerVec[0].first;
    
    return result;
}

bool polynomial::operator<(const polynomial &other) const
{
    //this is the less than operator, so we can just compare the elements from the other polynomial
    //first check biggest power
    if(biggestpower < other.biggestpower)
    {
        return true;
    }
    else if(biggestpower > other.biggestpower)
    {
        return false;
    }
    else
    {
        //if the biggest powers are equal, we check the coeff of the biggest power
        if(CoeffAndPowerVec[0].second < other.CoeffAndPowerVec[0].second)
        {
            return true;
        }
        else if(CoeffAndPowerVec[0].second > other.CoeffAndPowerVec[0].second)
        {
            return false;
        }
        else
        {
                //if the biggest powers, coeffs and size are equal, we check the coeff and power of the other elements
                for (size_t i = 1; i < size; i++)
                {
                    if(CoeffAndPowerVec[i].second < other.CoeffAndPowerVec[i].second)
                    {
                        return true;
                    }
                    else if(CoeffAndPowerVec[i].second > other.CoeffAndPowerVec[i].second)
                    {
                        return false;
                    }
                    else
                    {
                        if(CoeffAndPowerVec[i].first < other.CoeffAndPowerVec[i].first)
                        {
                            return true;
                        }
                        else if(CoeffAndPowerVec[i].first > other.CoeffAndPowerVec[i].first)
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
    //this is the greater than operator, so we can just compare the elements from the other polynomial
    //first check biggest power
    if(biggestpower > other.biggestpower)
    {
        return true;
    }
    else if(biggestpower < other.biggestpower)
    {
        return false;
    }
    else
    {
        //if the biggest powers are equal, we check the coeff of the biggest power
        if(CoeffAndPowerVec[0].second > other.CoeffAndPowerVec[0].second)
        {
            return true;
        }
        else if(CoeffAndPowerVec[0].second < other.CoeffAndPowerVec[0].second)
        {
            return false;
        }
        else
        {
                //if the biggest powers, coeffs and size are equal, we check the coeff and power of the other elements
                for (size_t i = 1; i < size; i++)
                {
                    if(CoeffAndPowerVec[i].second > other.CoeffAndPowerVec[i].second)
                    {
                        return true;
                    }
                    else if(CoeffAndPowerVec[i].second < other.CoeffAndPowerVec[i].second)
                    {
                        return false;
                    }
                    else
                    {
                        if(CoeffAndPowerVec[i].first > other.CoeffAndPowerVec[i].first)
                        {
                            return true;
                        }
                        else if(CoeffAndPowerVec[i].first < other.CoeffAndPowerVec[i].first)
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
    //this is the equal to operator, so we can just compare the elements from the other polynomial
    //first check biggest power
    if(biggestpower != other.biggestpower)
    {
        //if the biggest powers are not equal, we return false
        return false;
    }

    //check coeff of biggest power
    if(CoeffAndPowerVec[0].second != other.CoeffAndPowerVec[0].second)
    {
        //if the coeffs of the biggest power are not equal, we return false
        return false;
    }

    //check size
    if(size != other.size)
    {
        //if the sizes are not equal, we return false
        return false;
    }

    //check the coeff and power of the other elements
    for (size_t i = 1; i < size; i++)
    {
        if(CoeffAndPowerVec[i].second != other.CoeffAndPowerVec[i].second)
        {
            //if the coeffs are not equal, we return false
            return false;
        }
        else
        {
            if(CoeffAndPowerVec[i].first != other.CoeffAndPowerVec[i].first)
            {
                //if the powers are not equal, we return false
                return false;
            }
        }
    }
    return true;


}

std::vector<std::pair<power, coeff>> polynomial::canonical_form() const
{
    //this is the main function that we need to implement
    std::vector<std::pair<power, coeff>> result;

    //we first initialize three arrays, one for the powers, one for the coeffs and one for the result
    int powers[size];
    int coeffs[size];
    int result_coeffs[size];

    //we initialize the result_coeffs array with 0
    for (size_t i = 0; i < size; i++)
    {
        result_coeffs[i] = 0;
    }

    //we initialize the powers and coeffs arrays with the values from the vector
    for (size_t i = 0; i < size; i++)
    {
        powers[i] = CoeffAndPowerVec[i].second;
        coeffs[i] = CoeffAndPowerVec[i].first;
    }

    //we sort the powers array
    std::sort(powers, powers + size);

    //we sort the coeffs array
    std::sort(coeffs, coeffs + size);

    //we initialize the result_coeffs array with the values from the coeffs array
    for (size_t i = 0; i < size; i++)
    {
        result_coeffs[i] = coeffs[i];
    }

    //we initialize the result vector with the values from the result_coeffs array
    for (size_t i = 0; i < size; i++)
    {
        result.push_back(std::make_pair(powers[i], result_coeffs[i]));
    }


    return result;
}

size_t polynomial::find_degree_of()
{
    //this is the find degree function, so we can just return the power
    return biggestpower;

}

