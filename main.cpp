#include <iostream>
#include <chrono>
#include <optional>
#include <vector>
#include <iomanip>
#include <sstream>

#include "poly.h"

std::optional<double> poly_test(polynomial &p1,
                                polynomial &p2,
                                std::vector<std::pair<power, coeff>> solution)

{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    polynomial p3 = p1 * p2;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    p1.print();
    p2.print();
    p3.print();

    if (p3.canonical_form() != solution)
    {
        return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

std::optional<double> poly_test_less(polynomial &p1,
                                     polynomial &p2,
                                     bool solution)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    bool sol = p1 < p2;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "p1: ";
    p1.print();
    std::cout << "p2: ";
    p2.print();
    std::cout << "p1 < p2: " << sol << std::endl;

    if (sol != solution)
    {
        return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

std::optional<double> poly_test_greater(polynomial &p1,
                                        polynomial &p2,
                                        bool solution)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    bool sol = p1 > p2;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "p1: ";
    p1.print();
    std::cout << "p2: ";
    p2.print();
    std::cout << "p1 > p2: " << sol << std::endl;

    if (sol != solution)
    {
        return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

std::optional<double> poly_test_equal(polynomial &p1,
                                      polynomial &p2,
                                      bool solution)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    bool sol = p1 == p2;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "p1: ";
    p1.print();
    std::cout << "p2: ";
    p2.print();
    std::cout << "p1 == p2: " << sol << std::endl;

    if (sol != solution)
    {
        return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

std::optional<double> poly_test_add(polynomial &p1,
                                    polynomial &p2,
                                    std::vector<std::pair<power, coeff>> solution)

{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    polynomial p3 = p1 + p2;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "p1: ";
    p1.print();
    std::cout << "p2: ";
    p2.print();
    std::cout << "p3: ";
    p3.print();

    if (p3.canonical_form() != solution)
    {
        return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

std::optional<double> poly_test_assign(polynomial &p1,
                                       polynomial &p2,
                                       bool solution)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    polynomial p3 = p1;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "p1: ";
    p1.print();
    std::cout << "p2: ";
    p2.print();
    std::cout << "p3 = p1: ";
    p3.print();

    if (p3.canonical_form() != p1.canonical_form())
    {
        return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

std::optional<double> poly_test_copy(polynomial &p1,
                                     polynomial &p2,
                                     bool solution)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    polynomial p3(p1);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "p1: ";
    p1.print();
    std::cout << "p2: ";
    p2.print();
    std::cout << "p3(p1): ";
    p3.print();

    if (p3.canonical_form() != p1.canonical_form())
    {
        return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

void printResult(std::optional<double> result)
{
    if (result)
    {
        // print in green
        std::cout << "\033[1;32m" << result.value() << "ms to pass test\033[0m" << std::endl;
    }
    else
    {
        // print in red
        std::cout << "\033[1;31m"
                  << "Test failed"
                  << "\033[0m" << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
}

void testpolys()
{
    // create two polynomials from the polys.txt file for data
    // there is a coefficient term and a power term on each line. 1st polynomial is from line 1 to 5000 2nd polynomial is from line 5002 to 10001
    // format of each line is ex  487x^8443
    std::vector<std::pair<power, coeff>> poly1;
    std::vector<std::pair<power, coeff>> poly2;
    // read in the data from the file
    FILE *file = fopen("polys.txt", "r");
    if (file == NULL)
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    // read in the first polynomial
    for (int i = 0; i < 5000; i++)
    {
        power p;
        coeff c;
        fscanf(file, "%d", &c);
        fscanf(file, "%*c");
        fscanf(file, "%*c");
        fscanf(file, "%zu", &p);
        printf("%d %d, \n", c, p);
        poly1.push_back(std::make_pair(p, c));
    }
    // seek to the start of the second polynomial by adding 3 to the current position
    fseek(file, 3, SEEK_CUR);
    // read in the second polynomial
    for (int i = 0; i < 5000; i++)
    {
        power p;
        coeff c;
        fscanf(file, "%d", &c);
        fscanf(file, "%*c");
        fscanf(file, "%*c");
        fscanf(file, "%zu", &p);
        // printf("%d %d, \n", c, p);
        poly2.push_back(std::make_pair(p, c));
    }

    fclose(file);
    // print length of the polynomials
    std::cout << "Length of polynomial 1: " << poly1.size() << std::endl;
    std::cout << "Length of polynomial 2: " << poly2.size() << std::endl;
    // create two polynomials from the data
    polynomial p1(poly1.begin(), poly1.end());
    polynomial p2(poly2.begin(), poly2.end());
    // print some info about the polynomials
    // poly1
    std::cout << "Polynomial 1: ";
     for (int i = 0; i < poly1.size(); i++)
    {
        std::cout << poly1[i].second << ", " << poly1[i].first << std::endl;
    }
    std::cout << "p1: ";
    p1.print();
    std::cout << "p2: ";
    // p2.print();
    std::cout << "p1 == p2: " << (p1 == p2) << std::endl;
}

int main()
{
    /** We're doing (x+1)^2, so solution is x^2 + 2x + 1*/
    std::vector<std::pair<power, coeff>> solution = {{2, 1}, {1, 2}, {0, 1}};

    /** This holds (x+1), which we'll pass to each polynomial */
    std::vector<std::pair<power, coeff>> poly_input = {{1, 1}, {0, 1}};

    polynomial p1(poly_input.begin(), poly_input.end());
    polynomial p2(poly_input.begin(), poly_input.end());

    std::optional<double> result = poly_test(p1, p2, solution);

    if (result.has_value())
    {
        std::cout << "Passed test, took " << result.value() / 1000 << " seconds" << std::endl;
    }
    else
    {
        std::cout << "Failed test" << std::endl;
    }

    std::optional<double> result2 = poly_test_less(p1, p2, false);
    printResult(result2);

    // we create a new polynomial p3 with the value 2x^2 + 2x + 1
    std::vector<std::pair<power, coeff>> poly_input2 = {{2, 2}, {1, 2}, {0, 1}};
    polynomial p3(poly_input2.begin(), poly_input2.end());

    std::optional<double> result3 = poly_test_less(p1, p3, true);
    printResult(result3);

    std::optional<double> result4 = poly_test_less(p3, p1, false);
    printResult(result4);
    // we create a new polynomial p4 with the value 2x^2 + 2x + 2
    std::vector<std::pair<power, coeff>> poly_input3 = {{2, 2}, {1, 2}, {0, 2}};
    polynomial p4(poly_input3.begin(), poly_input3.end());

    std::optional<double> result5 = poly_test_less(p3, p4, true);
    printResult(result5);

    // test for the case where the polynomials are equal
    std::optional<double> result6 = poly_test_less(p3, p3, false);
    printResult(result6);

    // test greater than operator for the case where the polynomials are equal
    std::optional<double> result7 = poly_test_greater(p3, p3, false);
    printResult(result7);

    // test greater than operator for the case where the first polynomial is greater than the second
    std::optional<double> result8 = poly_test_greater(p4, p3, true);
    printResult(result8);

    // test greater than operator for the case where the first polynomial is less than the second
    std::optional<double> result9 = poly_test_greater(p3, p4, false);
    printResult(result9);

    // test equal operator for the case where the polynomials are equal
    std::optional<double> result10 = poly_test_equal(p3, p3, true);
    printResult(result10);

    // test equal operator for the case where the polynomials are not equal
    std::optional<double> result11 = poly_test_equal(p3, p4, false);
    printResult(result11);

    // solve for the case where the polynomials are equal is 4x^2 + 4x + 2
    // test addition operator for the case where the polynomials are equal
    std::vector<std::pair<power, coeff>> sol2 = {{2, 4}, {1, 4}, {0, 2}};
    std::optional<double> result12 = poly_test_add(p3, p3, sol2);
    printResult(result12);

    // solve for the case where the polynomials are not equal is 4x^2 + 4x + 3
    // test addition operator for the case where the polynomials are not equal
    std::vector<std::pair<power, coeff>> sol3 = {{2, 4}, {1, 4}, {0, 3}};
    std::optional<double> result13 = poly_test_add(p3, p4, sol3);
    printResult(result13);

    // test multiplication operator for the case where the polynomials are equal
    std::vector<std::pair<power, coeff>> sol4 = {{4, 4}, {3, 8}, {2, 8}, {1, 4}, {0, 1}};
    std::optional<double> result14 = poly_test(p3, p3, sol4);
    printResult(result14);

    // test multiplication operator for the case where the polynomials are not equal
    std::vector<std::pair<power, coeff>> sol5 = {{4, 4}, {3, 8}, {2, 10}, {1, 6}, {0, 2}};
    std::optional<double> result15 = poly_test(p3, p4, sol5);
    printResult(result15);

    // test assignment operator for the case where the polynomials are equal
    std::optional<double> result16 = poly_test_assign(p3, p3, true);
    printResult(result16);

    // test assignment operator for the case where the polynomials are not equal
    std::optional<double> result17 = poly_test_assign(p3, p4, false);
    printResult(result17);

    // test copy constructor for the case where the polynomials are equal
    std::optional<double> result18 = poly_test_copy(p3, p3, true);
    printResult(result18);

    // test copy constructor for the case where the polynomials are not equal
    std::optional<double> result19 = poly_test_copy(p3, p4, false);
    printResult(result19);

    testpolys();
}