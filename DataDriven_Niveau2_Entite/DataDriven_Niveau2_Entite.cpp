#include "TaxCalculator.h"

#include "Common/Ensure.h"

#include <iostream>

int main()
{
	DataManager dataManager;
	ensure(dataManager.Initialize());

	TaxCalculator taxCalculator(dataManager);

	float price;
	std::cout << "Entrer le prix du produit: ";
	std::cin >> price;

	float finalPrice = taxCalculator.ComputeFinalPrice(price);
	std::cout << "Le prix final est: " << finalPrice << std::endl;
}