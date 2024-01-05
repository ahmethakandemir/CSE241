#include <iostream>

// class Sale{
// public:
//     Sale();
//     Sale(double thePrice);
//     virtual double bill() const;
//     double savings(const Sale& other) const;
//     double getPrice() const;
// private:
//     double price;
// };

// // Path: main.cpp
// Sale::Sale() : price(0) {}
// Sale::Sale(double thePrice) : price(thePrice) {}

// double Sale::bill() const {return price;}
// bool operator < (const Sale& first, const Sale& second){
//     return (first.bill() < second.bill());
// }
// double Sale::savings(const Sale& other) const {
//     return (bill() - other.bill());
// }

// class DiscountSale : public Sale{
// public:
//     DiscountSale();
//     DiscountSale(double thePrice, double theDiscount);
//     double getDiscount() const;
//     virtual double bill() const;
    
    
// protected:
//     double discount;
// };

// // Path: main.cpp
// DiscountSale::DiscountSale() : Sale(), discount(0) {}
// DiscountSale::DiscountSale(double thePrice, double theDiscount) : Sale(thePrice), discount(theDiscount) {}
// double DiscountSale::getDiscount() const {return discount;}
// double Sale::getPrice() const {return price;}


// double DiscountSale::bill( ) const{
//     double fraction = discount / 100;
//     return (1 - fraction) * getPrice( );
// }

// int main()
// {
//     Sale simple(10.00); //One item at $10.00.
//     DiscountSale discount(simple.bill(), 10);
//     if (discount < simple)
//     {
//     std::cout << "Discounted item is cheaper.\n";
//     std::cout << "Savings is $" << simple.savings(discount) << std::endl;   // Savings is $0.1
//     }
//     else
//     std::cout << "Discounted item is not cheaper.\n";
//     return 0;
// }

#include <iostream>
#include <vector>

// Forward declaration of the generic template
template <class T>
class MyContainer;

// Function template for the generic version
template <class T>
void print(const MyContainer<T>& container);

// Generic class template using class
template <class T>
class MyContainer {
private:
    std::vector<T> elements;

public:
    // Constructor
    MyContainer(const std::initializer_list<T>& values) : elements(values) {}

    // Function to print elements (defined outside the class)
    friend void print<T>(const MyContainer<T>& container);
};

// Definition of the function template for the generic version
template <class T>
void print(const MyContainer<T>& container) {
    std::cout << "Generic implementation: ";
    for (const auto& element : container.elements) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// Template specialization for int using class
template <>
class MyContainer<int> {
private:

public:
    std::vector<int> elements;
    // Constructor with additional functionality for int
    MyContainer(const std::initializer_list<int>& values) : elements(values) {}

    // Function to print elements for int (defined outside the class)
    friend void print<int>(const MyContainer<int>& container);
};

// Definition of the function template for the specialization of int
void print(const MyContainer<int>& container) {
    std::cout << "Specialized implementation for int: ";
    for (const auto& element : container.elements) {
        std::cout << element * 2 << " ";  // Specialized behavior for int
    }
    std::cout << std::endl;
}

int main() {
    // Instantiate generic MyContainer with double values
    MyContainer<double> doubleContainer = {1.5, 2.5, 3.5};
    print(doubleContainer);  // Output: Generic implementation: 1.5 2.5 3.5

    // Instantiate specialized MyContainer for int values
    MyContainer<int> intContainer = {1, 2, 3};
    print(intContainer);  // Output: Specialized implementation for int: 2 4 6

    return 0;
}
