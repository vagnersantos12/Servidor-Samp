// Setup a custom type that holds all data about a load
enum TLoad
{
	LoadName[50], // The name of the load
	bool:Mafia, // Holds "true" if this load is wanted by the mafia
	Float:PayPerUnit, // Holds the price for every meter to haul this type of load (this gets multiplied by the distance to calculate the payment)
	PCV_Required, // This holds the vehicle-type the player needs to use this load (and automatically the player's class)
	FromLocations[30], // This array holds all loading-points for this load
	ToLocations[30] // This array holds all unloading-points for this load
}

new ALoads[][TLoad] =
{
	// LoadName, MafiaLoad, PayPerUnit, VehicleNeeded, From-Locations, To-Locations

	// Dummy Load (never used)
	{"Dummy", false, 0.00, 0, {0}, {0}}, // LoadID 0

	// Loads for ore trailer
	{"Cascalhos", false, 1.00, PCV_TruckerOreTrailer, {11}, {1, 2, 3}}, // LoadID 1
	{"Areia", false, 1.00, PCV_TruckerOreTrailer, {12}, {1, 2, 3, 4, 5}}, // LoadID 2
	{"Pedras", false, 1.00, PCV_TruckerOreTrailer, {11}, {1, 2, 3, 4, 5}}, // LoadID 3
	{"Carvao", false, 1.00, PCV_TruckerOreTrailer, {12}, {6, 7, 8}}, // LoadID 4
	{"Minerio", false, 1.00, PCV_TruckerOreTrailer, {12}, {6, 9}}, // LoadID 5
	{"Tora", false, 1.00, PCV_TruckerOreTrailer, {13}, {7, 10}}, // LoadID 6
	{"Lascas de madeira", false, 1.00, PCV_TruckerOreTrailer, {10}, {14}}, // LoadID 7
	{"Residuos secos", false, 1.00, PCV_TruckerOreTrailer, {6, 15, 16}, {17, 18, 19}}, // LoadID 8
	{"Detritos", false, 1.00, PCV_TruckerOreTrailer, {17, 19}, {6, 18, 20}}, // LoadID 9
	{"Trigo", false, 1.00, PCV_TruckerOreTrailer, {21, 22}, {18, 23, 24}}, // LoadID 10

	// Loads for liquids trailer
	{"Combustivel vazio", true, 1.00, PCV_TruckerFluidsTrailer, {8, 25, 26}, {27, 28, 29, 30, 31, 32, 33, 34}}, // LoadID 11
	{"Combustivel Diesel", true, 1.00, PCV_TruckerFluidsTrailer, {8, 25, 26}, {27, 28, 29, 30, 31, 32, 33, 34}}, // LoadID 12
	{"Combustivel cheio", true, 1.00, PCV_TruckerFluidsTrailer, {8, 25, 26}, {35, 36}}, // LoadID 13
	{"Oleo cru", false, 1.00, PCV_TruckerFluidsTrailer, {8, 25, 26}, {6}}, // LoadID 14
	{"Nitrogenio liquido", false, 1.00, PCV_TruckerFluidsTrailer, {37, 38}, {39, 40}}, // LoadID 15
	{"Produtos quimicos", false, 1.00, PCV_TruckerFluidsTrailer, {37}, {6, 15, 39, 40}}, // LoadID 16
	{"Agua potavel", false, 1.00, PCV_TruckerFluidsTrailer, {37}, {15, 40, 41}}, // LoadID 17
	{"Graxa", false, 1.00, PCV_TruckerFluidsTrailer, {8, 25}, {6, 10, 14, 42}}, // LoadID 18
	{"Fertilizante", false, 1.00, PCV_TruckerFluidsTrailer, {37, 38}, {21, 22}}, // LoadID 19
	{"Leite", false, 1.00, PCV_TruckerFluidsTrailer, {21, 22}, {43, 44, 45}}, // LoadID 20
	{"Cerveja", true, 1.00, PCV_TruckerFluidsTrailer, {41}, {44, 46}}, // LoadID 21
	{"Etanol", false, 1.00, PCV_TruckerFluidsTrailer, {37, 41}, {26, 39, 40}}, // LoadID 22

	// Loads for cargo trailer
	{"Comida", false, 1.00, PCV_TruckerCargoTrailer, {7, 44, 47, 48}, {49, 50, 51, 52, 53}}, // LoadID 23
	{"Bebidas", false, 1.00, PCV_TruckerCargoTrailer, {15, 54, 55}, {49, 50, 51, 52, 53}}, // LoadID 24
	{"Cerveja Engarrafada", true, 1.00, PCV_TruckerCargoTrailer, {56}, {57, 58, 59, 60, 61}}, // LoadID 25
	{"Utensilios Luxuosos", false, 1.00, PCV_TruckerCargoTrailer, {24, 55}, {47, 48, 50}}, // LoadID 26
	{"Aparelhos Eletronicos", true, 1.00, PCV_TruckerCargoTrailer, {7, 24, 48}, {50, 51, 62, 63}}, // LoadID 27
	{"Equipamento Esportivo", false, 1.00, PCV_TruckerCargoTrailer, {47, 48}, {50, 53, 57}}, // LoadID 28
	{"Placas", false, 1.00, PCV_TruckerCargoTrailer, {10}, {4, 7, 18, 22}}, // LoadID 29
	{"Materiais de Contrucao", false, 1.00, PCV_TruckerCargoTrailer, {4}, {1, 2, 3, 5}}, // LoadID 30
	{"Carga Viva", false, 1.00, PCV_TruckerCargoTrailer, {21, 22}, {23, 43, 47}}, // LoadID 31
	{"Carne", false, 1.00, PCV_TruckerCargoTrailer, {43}, {44, 49, 50, 51, 52, 53}}, // LoadID 32
	{"Papel", false, 1.00, PCV_TruckerCargoTrailer, {14}, {9, 62}}, // LoadID 33

	// Loads for cement truck
	{"Cimento", false, 1.00, PCV_TruckerCementTruck, {12}, {1, 2, 3, 4}}, // LoadID 34

	// Loads for truckers without trailer
	{"Comida", false, 0.60, PCV_TruckerNoTrailer, {7, 44, 47, 48}, {49, 50, 51, 52, 53}}, // LoadID 35
	{"Bebidas", false, 0.60, PCV_TruckerNoTrailer, {15, 54, 55}, {49, 50, 51, 52, 53}}, // LoadID 36
	{"Cerveja Engarrafada", true, 0.60, PCV_TruckerNoTrailer, {56}, {57, 58, 59, 60, 61}}, // LoadID 37
	{"Utensilios Luxuosos", false, 0.60, PCV_TruckerNoTrailer, {24, 55}, {47, 48, 50}}, // LoadID 38
	{"Aparelhos Eletronicos", true, 0.60, PCV_TruckerNoTrailer, {7, 24, 48}, {50, 51, 62, 63}}, // LoadID 39
	{"Equipamento Esportivo", false, 0.60, PCV_TruckerNoTrailer, {47, 48}, {50, 53, 57}}, // LoadID 40
	{"Placas", false, 0.60, PCV_TruckerNoTrailer, {10}, {4, 7, 18, 22}}, // LoadID 41
	{"Materiais de Construcao", false, 0.60, PCV_TruckerNoTrailer, {4}, {1, 2, 3, 5}}, // LoadID 42
	{"Carga Viva", false, 0.60, PCV_TruckerNoTrailer, {21, 22}, {23, 43, 47}}, // LoadID 43
	{"Carne", false, 0.60, PCV_TruckerNoTrailer, {43}, {44, 49, 50, 51, 52, 53}}, // LoadID 44
	{"Papel", false, 0.60, PCV_TruckerNoTrailer, {14}, {9, 62}}, // LoadID 45

	// Loads for pilots
	{"Passageiros", false, 1.00, PCV_PilotPlane, {121, 122, 125, 126, 130, 131, 134}, {121, 122, 125, 126, 130, 131, 134}}, // LoadID 46
	{"Carga", false, 1.00, PCV_PilotPlane, {123, 124, 127, 128, 129, 132, 133, 135}, {123, 124, 127, 128, 129, 132, 133, 135}}, // LoadID 47
	{"Passageiros", false, 1.00, PCV_PilotHelicopter, {121, 122, 125, 126, 130, 131, 134}, {121, 122, 125, 126, 130, 131, 134}}, // LoadID 48

	// Loads for mafia
	{"Comida", false, 1.50, PCV_MafiaVan, {7, 44, 47, 48}, {49, 50, 51, 52, 53}}, // LoadID 49
	{"Bebidas", false, 1.50, PCV_MafiaVan, {15, 54, 55}, {49, 50, 51, 52, 53}}, // LoadID 50
	{"Cerveja Engarrafada", true, 1.50, PCV_MafiaVan, {56}, {57, 58, 59, 60, 61}}, // LoadID 51
	{"Utensilios Luxuosos", false, 1.50, PCV_MafiaVan, {24, 55}, {47, 48, 50}}, // LoadID 52
	{"Aparelhos Eletronicos", true, 1.50, PCV_MafiaVan, {7, 24, 48}, {50, 51, 62, 63}}, // LoadID 53
	{"Equipamento Esportivo", false, 1.50, PCV_MafiaVan, {47, 48}, {50, 53, 57}}, // LoadID 54
	{"Placas", false, 1.50, PCV_MafiaVan, {10}, {4, 7, 18, 22}}, // LoadID 55
	{"Materiais de Contrucao", false, 1.50, PCV_MafiaVan, {4}, {1, 2, 3, 5}}, // LoadID 56
	{"Carga Viva", false, 1.50, PCV_MafiaVan, {21, 22}, {23, 43, 47}}, // LoadID 57
	{"Carne", false, 1.50, PCV_MafiaVan, {43}, {44, 49, 50, 51, 52, 53}}, // LoadID 58
	{"Papel", false, 1.50, PCV_MafiaVan, {14}, {9, 62}} // LoadID 59
};



// This function returns a string (array) that holds all ProductID's that are linked to a certain vehicletype (and player class)
stock Product_GetList(PCV_Needed, &NumProducts)
{
	// Setup local variables
	new ProductList[50];

	// Loop through all products
	for (new i; i < sizeof(ALoads); i++)
	{
		// Check if there aren't 50 products found (and added to the ProductList) yet
		if (NumProducts < 50)
		{
			// Check if the current product has the same PCV_Needed
			if (ALoads[i][PCV_Required] == PCV_Needed)
			{
				// Add the ProductID to the ProductList
				ProductList[NumProducts] = i;
				// Increase the counter NumProducts
				NumProducts++;
			}
		}
	}

	// Return the ProductList
	return ProductList;
}

// This function returns a random products for the given vehicletype (and player class)
stock Product_GetRandom(PCV_Needed)
{
	// Setup local variables
	new ProductList[50], NumProducts;

	// Get the entire product-list for this vehicle and class, and also the amount of products
	ProductList = Product_GetList(PCV_Needed, NumProducts);

	// Get a random product from this list and return it
	return ProductList[random(NumProducts)];
}

// This function returns a random startlocation from the given product (load)
stock Product_GetRandomStartLoc(ProductID)
{
	// Setup local variables
	new NumProducts;

	// First find out how many valid start-locations there are in this product
	for (new i; i < 30; i++)
	{
		// If the product has a valid location in this index
		if (ALoads[ProductID][FromLocations][i] != 0)
		    NumProducts++; // Count the number of valid start-locations
		else // A start-location with ID 0 has been found (dummy-location)
		    break; // Stop counting
	}

	// Return the LocationID that's stored at a random index
	return ALoads[ProductID][FromLocations][random(NumProducts)];
}

// This function returns a random endlocation from the given product (load)
stock Product_GetRandomEndLoc(ProductID)
{
	// Setup local variables
	new NumProducts;

	// First find out how many valid end-locations there are in this product
	for (new i; i < 30; i++)
	{
		// If the product has a valid location in this index
		if (ALoads[ProductID][ToLocations][i] != 0)
		    NumProducts++; // Count the number of valid end-locations
		else // An end-location with ID 0 has been found (dummy-location)
		    break; // Stop counting
	}

	// Return the LocationID that's stored at a random index
	return ALoads[ProductID][ToLocations][random(NumProducts)];
}

