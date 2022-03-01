#include "TaxCalculator.h"

#include <iostream>

int main()
{
	TaxCalculator taxCalculator;

	float price;
	std::cout << "Entrer le prix du produit: ";
	std::cin >> price;

	float finalPrice = taxCalculator.ComputeFinalPrice(price);
	std::cout << "Le prix final est: " << finalPrice << std::endl;
}