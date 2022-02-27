#include "TaxCalculator.h"

#include <iostream>

int main()
{
	TaxCalculator taxCalculator;

	float price;
	std::cout << "Prix du produit?";
	std::cin >> price;
	
	float finalPrice = taxCalculator.ComputeFinalPrice(price);
	std::cout << "Le prix final est: $" << finalPrice << std::endl;
}