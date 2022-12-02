#include "poly.h"

#include <iostream>
#include <chrono>
#include <optional>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

void sumNumbersVec(int starting, int ending, int idx, std::vector<long> &sum)
{
    long sum1 = 0;
    for (int i = starting; i <= ending; i++)
    {
        sum1 += i;
    }
    sum[idx] = sum1;
}

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
        //std::cout << std::endl<< CoeffAndPowerVec[i].second << ", " << CoeffAndPowerVec[i].first << std::endl;
        //dont print the last + sign, dont print coeff if it equals 1
        if(i == size - 1)
        {
            //print
            
            if(CoeffAndPowerVec[i].second == 1)
            {
                std::cout <<"x^" << CoeffAndPowerVec[i].first;
            }
            else
            {
                std::cout << CoeffAndPowerVec[i].second << "x^" << CoeffAndPowerVec[i].first;
            }
        }
        else
        {
            if(CoeffAndPowerVec[i].second == 1)
            {
                std::cout << "x^" << CoeffAndPowerVec[i].first << " + ";
            }
            else
            {
                std::cout << CoeffAndPowerVec[i].second << "x^" << CoeffAndPowerVec[i].first << " + ";
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
//
int polynomial::MultiplyThreading(const polynomial &other, int start, int end, polynomial &result)
{
    // this is the multiplication operator
    //print start and end
    //printf("start: %d, end: %d\n", start, end);
    //print this polynomial
    //printf("this polynomial: ");
    //print();
    //print other polynomial
    //printf("other polynomial: ");
    //other.print();

    int currentbiggestpower = 0;
    // we initialize the iterators at start
    auto it1 = CoeffAndPowerVec.begin() + start;
    auto it2 = other.CoeffAndPowerVec.begin() + start;
    //multi(&it1,&it2);
    //print


    // we loop through the vectors using start and end
    for (int i = start; i < end; i++)
    {
        //print i
       for(int j = start; j < end; j++)
       {
           //print i and j
          // printf("i: %d, j: %d\n", i, j);
          // printf("it1pow: %d, it2pow: %d\n", it1->first, it2->first);
          // printf("it1coeff: %d, it2coeff: %d\n", it1->second, it2->second);
           //we calculate the power
           int power = it1->first + it2->first;
           //we calculate the coefficient
           int coeff = it1->second * it2->second;
           //we check if the power is bigger than the current biggest power
           if(power > currentbiggestpower)
           {
               currentbiggestpower = power;
           }
           //print power and coeff
             // printf("power: %d, coeff: %d\n", power, coeff);
           //we push back the pair
           result.CoeffAndPowerVec.push_back(std::make_pair(power, coeff));
           //we increment it2
           it2++;
       }
         //we increment it1
        it1++;
        //we set it2 to the beginning of the vector
        it2 = other.CoeffAndPowerVec.begin()+start;

    }
    // we update the size and biggestpower
    result.size = result.CoeffAndPowerVec.size();
    
       

    //we combine the coefficients if they have the same power
    for (size_t i = 0; i < result.size; i++)
    {
        for (size_t j = i + 1; j < result.size; j++)
        {
            if (result.CoeffAndPowerVec[i].first == result.CoeffAndPowerVec[j].first)
            {
                result.CoeffAndPowerVec[i].second += result.CoeffAndPowerVec[j].second;
                result.CoeffAndPowerVec.erase(result.CoeffAndPowerVec.begin() + j);
                result.size--;
            }
        }
    }

    //sort so that the highest power is first
    std::sort(result.CoeffAndPowerVec.begin(), result.CoeffAndPowerVec.end(), std::greater<std::pair<int, int>>());

    
    // update biggestpower
    result.biggestpower = currentbiggestpower;
    // if biggest power is greater then 0, trim all 0 coefficients, else leave the 0 power coefficient
    // we trim all 0 coefficients that are not also 0 power

    if (result.biggestpower > 0)
    {
        for (size_t i = 0; i < result.size; i++)
        {
            if (result.CoeffAndPowerVec[i].second == 0)
            {
                result.CoeffAndPowerVec.erase(result.CoeffAndPowerVec.begin() + i);
                result.size--;
            }
        }
    }

    // we update the size
    result.size = result.CoeffAndPowerVec.size();

    // we print the result
    //printf("Size: %d, Biggest power: %d\n", result.size, result.biggestpower);
    return 1;
}

polynomial polynomial::operator*(const polynomial &other) const
{
    //we declare max threads to 8
    int MAX_THREADS = 8;
    //we declare the result polynomial
    polynomial result;
    //we declare the vector of threads
    vector<thread> threads;
    //set size of threads to MAX_THREADS
    //we declare the vector of results
    vector<polynomial> results;
    //set the size of the results vector to the max threads
    results.resize(MAX_THREADS);
    //thread counter
    int thread_counter = 0;
    
    //we find the size of the polynomial with the biggest size
    int biggestsize;
    if(size > other.size)
    {
        biggestsize = size;
    }
    else
    {
        biggestsize = other.size;
    }
    //print biggestsize
    printf("biggestsize: %d\n", biggestsize);
    //if size is less then 100, we solve it in one thread
    if(biggestsize < 100)
    {
        //we find start and end as ints
        int start = 0;
        int end = biggestsize;
        //print start and end
        printf("start: %d, end: %d\n", start, end);
        //we create a thread
        std::thread t1(&polynomial::MultiplyThreading, *this, other, start, end, std::ref(results[0]));
        //std::vector<long> sumVector;
        //std::thread t1(sumNumbersVec, 1, 10, 1, std::ref(sumVector));
        //and enqueue it
        threads.push_back(std::move(t1));
        //we increment the thread counter
        thread_counter++;
    }
    else
    {
        //we will evenly divide work between the 8 threads, giving the extra remainder to the last thread
        int work_per_thread = biggestsize / MAX_THREADS;
        int remainder = biggestsize % MAX_THREADS;
        printf("work_per_thread: %d, remainder: %d\n", work_per_thread, remainder);
        //we create the threads
        for(int i = 0; i < MAX_THREADS; i++)
        {
            //we store the start and end of the work for each thread as two ints
            int start = i * work_per_thread;
            int end = (i + 1) * work_per_thread;
            //if we are on the last thread, we add the remainder to the end
            if(i == MAX_THREADS - 1)
            {
                end += remainder;
            }
            //print start and end
            printf("Starting thread %d, start: %d, end: %d\n", i, start, end);

            //we create a thread
            std::thread t1(&polynomial::MultiplyThreading, *this, other, start, end, std::ref(results[i]));
            //and enqueue it
            threads.push_back(move(t1));
            //we increment the thread counter
            thread_counter++;
        }
    }


//print threads used
printf("Threads used: %d\n", thread_counter);
    //we join the threads up to the thread counter
    for (int i = 0; i < thread_counter; i++)
    {
        printf("joining thread %d which has size %d\n", i, results[i].size);
        threads[i].join();
    }
    //print threads joined
    printf("Threads joined\n");


    //we add the results
    result = results[0];
    if (results.size() > 1)
    {
        for (int i = 1; i < results.size(); i++)
        {
            result = result + results[i];
        }
    }
    printf("Size: %d, Biggest power: %d\n", result.size, result.biggestpower);

    return result;

}

    /*
    // this is the multiplication operator
    polynomial result;

    int currentbiggestpower = 0;
    // we initialize the iterators
    auto it1 = CoeffAndPowerVec.begin();
    auto it2 = other.CoeffAndPowerVec.begin();
    //multi(&it1,&it2);

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
    */
//}
/*
void multi(polynomial &p1, polynomial &p2)
{
    //multithreading
    //create 8 parts for the 8 threads
    int parts = 8;
    int partsize = p1.size / parts;
    int remainder = p1.size % parts;
    int start = 0;
    int end = partsize;
    std::vector<std::thread> threads;
    std::vector<polynomial> results;

    //create the threads
    for (int i = 0; i < parts; i++)
    {
        if (i == parts - 1)
        {
            end += remainder;
        }
        threads.push_back(std::thread(multi, std::ref(p1), std::ref(p2), start, end, std::ref(results)));
        start += partsize;
        end += partsize;
    }
    
    //join the threads
    for (auto &t : threads)
    {
        t.join();
    }
    //multiply the results
    for (auto &r : results)
    {
        p1 = p1 * r;
    }
    //print the result
    p1.print();

}*/


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