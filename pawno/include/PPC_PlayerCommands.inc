// This is just a joke command
COMMAND:eu(playerid,params[])
{
	// Setup local variables
	new Msg[128], Message[128], Name[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/eu", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		if (sscanf(params, "s[128]", Message)) SendClientMessage(playerid, 0xFF0000AA, "Use: /eu [ação]");
		else
		{
		    // Check if the player isn't muted
		    if (APlayerData[playerid][Muted] == false)
		    {
				GetPlayerName(playerid, Name, sizeof(Name));
				format(Msg, sizeof(Msg), "* %s: %s", Name, Message);
				SendClientMessageToAll(0xFFFF00AA, Msg);
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você ainda está mudo.");
		}
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This commands allows the player to send a private message to another player
COMMAND:pm(playerid, params[])
{
	// Setup local variables
	new OtherPlayer, Message[128], Msg1[128], Msg2[128], YourName[24], OtherPlayerName[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/pm", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		if (sscanf(params, "us[128]", OtherPlayer, Message)) SendClientMessage(playerid, 0xFF0000AA, "Use: /pm [id] [menssagem]");
		else
		{
			// Check if that other player is online
			if (IsPlayerConnected(OtherPlayer))
			{
			    // Check if the player isn't muted
			    if (APlayerData[playerid][Muted] == false)
			    {
				    // Get both names
					GetPlayerName(playerid, YourName, sizeof(YourName));
					GetPlayerName(OtherPlayer, OtherPlayerName, sizeof(OtherPlayerName));
				    // Construct the message that is sent to yourself
					format(Msg1, 128, "{808080}Menssagem privada para %s{FFFFFF}: %s", OtherPlayerName, Message);
					// Construct the message that is sent to the other player
					format(Msg2, 128, "{A0A0A0}Menssagem privada de %s{FFFFFF}: %s", YourName, Message);
					// Send the messages
					SendClientMessage(playerid, 0xFFFFFFFF, Msg1);
					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg2);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você ainda está mudo.");
			}
			else
			    SendClientMessage(playerid, 0xFF0000FF, "[ToB] O jogador não está online.");
		}
	}
	else
	 return 0;

	// Let the server know that this was a valid command
	return 1;
}


// Lets the player add new houses
COMMAND:criarcasa(playerid, params[])
{
	// Setup local variables
	new HPrice, MaxLevel, HouseID;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/criarcasa", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			// Check if the player isn't inside a vehicle
			if (GetPlayerVehicleSeat(playerid) == -1)
			{
				if (sscanf(params, "ii", HPrice, MaxLevel)) SendClientMessage(playerid, 0xFF0000AA, "Use: /criarcasa [preço] [level]");
				else
				{
					// Check if the player entered a proper maxlevel
					if ((MaxLevel >= 1) && (MaxLevel <= 10))
					{
						// Find the first free HouseID
						for (HouseID = 1; HouseID < MAX_HOUSES; HouseID++)
							if (AHouseData[HouseID][PickupID] == 0) // Check if an empty house-index has been found (PickupID is 0)
							    break; // Stop searching, the first free HouseID has been found now

					    // Check if the house-limit hasn't been reached yet
						if (HouseID < MAX_HOUSES)
						{
						    // Setup some local variables
							new Float:x, Float:y, Float:z, Msg[128];
							// Get the player's position
							GetPlayerPos(playerid, x, y, z);
							// Set some default data
							AHouseData[HouseID][HouseX] = x;
							AHouseData[HouseID][HouseY] = y;
							AHouseData[HouseID][HouseZ] = z;
							AHouseData[HouseID][HouseLevel] = 1;
							AHouseData[HouseID][HouseMaxLevel] = MaxLevel;
							AHouseData[HouseID][HousePrice] = HPrice;
							AHouseData[HouseID][Owned] = false;

							// Add the pickup and 3DText at the location of the house-entrance (where the player is standing when he creates the house)
							House_CreateEntrance(HouseID);

							// Save the house
							HouseFile_Save(HouseID);

							// Inform the player that he created a new house
							format(Msg, 128, "{00FF00}[ToB] Você criou a casa de ID {FF00FF}%i{00FF00} com sucesso!", HouseID);
							SendClientMessage(playerid, 0xFFFFFFFF, Msg);
						}
						else
						    SendClientMessage(playerid, 0xFF0000FF, "[ToB] A quantidade máxima de casas criadas, foi atingido!");
					}
					else
					    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você deve escolher o Level entre 0 e 10.");
				}
			}
			else
			    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode estar dentro de um veículo para criar uma casa!");
		}
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command lets the player delete a house
COMMAND:deletarcasa(playerid, params[])
{
	// Setup local variables
	new file[100], Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/deletarcasa", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			// Make sure the player isn't inside a vehicle
			if (GetPlayerVehicleID(playerid) == 0)
			{
				// Loop through all player-owned houses
				for (new HouseID = 1; HouseID < MAX_HOUSES; HouseID++)
				{
					// Check if the house exists
					if (AHouseData[HouseID][PickupID] != 0)
					{
						// Check if the house has no owner
						if (AHouseData[HouseID][Owned] == false)
						{
							// Check if the player is in range of the house-pickup
							if (IsPlayerInRangeOfPoint(playerid, 2.5, AHouseData[HouseID][HouseX], AHouseData[HouseID][HouseY], AHouseData[HouseID][HouseZ]))
							{
								// Clear all data of the house
	                            AHouseData[HouseID][HouseName] = 0;
	                            AHouseData[HouseID][Insurance] = 0;
	                            AHouseData[HouseID][HouseX] = 0.0;
	                            AHouseData[HouseID][HouseY] = 0.0;
	                            AHouseData[HouseID][HouseZ] = 0.0;
	                            AHouseData[HouseID][HouseLevel] = 0;
	                            AHouseData[HouseID][HouseMaxLevel] = 0;
	                            AHouseData[HouseID][HousePrice] = 0;
	                            AHouseData[HouseID][Owned] = false;
	                            AHouseData[HouseID][Owner] = 0;
	                            AHouseData[HouseID][HouseName] = 0;
	                            AHouseData[HouseID][HouseName] = 0;
	                            AHouseData[HouseID][HouseName] = 0;
								// Destroy the mapicon, 3DText and pickup for the house
								DestroyDynamicPickup(AHouseData[HouseID][PickupID]);
								DestroyDynamicMapIcon(AHouseData[HouseID][MapIconID]);
								DestroyDynamic3DTextLabel(AHouseData[HouseID][DoorText]);
	                            AHouseData[HouseID][PickupID] = 0;
	                            AHouseData[HouseID][MapIconID] = 0;

								// Delete the House-file
								format(file, sizeof(file), HouseFile, HouseID); // Construct the complete filename for this house-file
								if (fexist(file)) // Make sure the file exists
									fremove(file); // Delete the file

								// Also let the player know he deleted the house
								format(Msg, 128, "{00FF00}[ToB] Você deletou a casa de ID {FFFF00}%i{00FF00} com sucesso!", HouseID);
								SendClientMessage(playerid, 0xFFFFFFFF, Msg);

								// Exit the function
								return 1;
							}
						}
					}
				}

				// There was no house in range, so let the player know about it
				SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não está na porta de uma casa para apagá-la!");
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode deletar uma casa de dentro de um veículo!");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command lets the player buy a house when he's standing in range of a house that isn't owned yet
COMMAND:comprarcasa(playerid, params[])
{
	// Setup local variables
	new Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/comprarcasa", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Make sure the player isn't inside a vehicle
		if (GetPlayerVehicleID(playerid) == 0)
		{
			// Check if the player is near a house-pickup
			for (new i = 1; i < sizeof(AHouseData); i++)
			{
				// Check if this house is created (it would have a valid pickup in front of the door)
				if (AHouseData[i][PickupID] != 0)
				{
					// Check if the player is in range of the house-pickup
					if (IsPlayerInRangeOfPoint(playerid, 2.5, AHouseData[i][HouseX], AHouseData[i][HouseY], AHouseData[i][HouseZ]))
					{
					    // Check if the house isn't owned yet
					    if (AHouseData[i][Owned] == false)
					    {
					        // Check if the player can afford this house
					        if (APlayerData[playerid][PlayerMoney] >= AHouseData[i][HousePrice])
					            House_SetOwner(playerid, i); // Give ownership of the house to the player
					        else
					            SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode pagar por esta casa."); // The player cannot afford this house
					    }
					    else
					    {
					        // Let the player know that this house is already owned by a player
							format(Msg, 128, "{FF0000}[ToB] Essa casa tem dono!  Dono:{00FF00}%s{FFFFFF}", AHouseData[i][Owner]);
							SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					    }

						// The player was in range of a house-pickup, so stop searching for the other house pickups
					    return 1;
					}
				}
			}

			// All houses have been processed, but the player wasn't in range of any house-pickup, let him know about it
			SendClientMessage(playerid, 0xFF0000FF, "[ToB] Para comprar a casa esteja na porta da casa desejada(pickup)");
		}
		else
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode comprar uma casa de dentro de um veículo!");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command lets the player enter the house/business if he's the owner
COMMAND:entrar(playerid, params[])
{
	// Setup local variables
	new HouseID, hLevel, BusID, BusType;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/entrar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Make sure the player isn't inside a vehicle
		if (GetPlayerVehicleID(playerid) == 0)
		{
			// Loop through all houses
			for (HouseID = 1; HouseID < MAX_HOUSES; HouseID++)
			{
				// Check if this house exists
				if (AHouseData[HouseID][PickupID] != 0)
				{
					// Check if the player is in range of the house-pickup
					if (IsPlayerInRangeOfPoint(playerid, 2.5, AHouseData[HouseID][HouseX], AHouseData[HouseID][HouseY], AHouseData[HouseID][HouseZ]))
					{
						// Check if the house is closed to the public
						if (AHouseData[HouseID][HouseOpened] == false)
						{
							// The house isn't open to the public, so keep anyone out who isn't the owner of the house
							if (House_PlayerIsOwner(playerid, HouseID) == 0)
							{
							    // Let the player know that this house isn't open to the public and he can't enter it
								SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Esta casa não é aberta ao público, você não pode entrar!");
							    return 1;
							}
						}

						// The house is open to the public, or the player trying to enter is the owner, so let the player inside the house

					    // Get the level of the house
						hLevel = AHouseData[HouseID][HouseLevel];
						// Set the worldid so other players cannot see him anymore
						SetPlayerVirtualWorld(playerid, 5000 + HouseID);
						// Set the player inside the interior of the house
						SetPlayerInterior(playerid, AHouseInteriors[hLevel][InteriorID]);
						// Set the position of the player at the spawn-location of the house's interior
						SetPlayerPos(playerid, AHouseInteriors[hLevel][IntX], AHouseInteriors[hLevel][IntY], AHouseInteriors[hLevel][IntZ]);
						// Also set a tracking-variable to enable /housemenu to track in which house the player is
						APlayerData[playerid][CurrentHouse] = HouseID;
						// Also let the player know he can use /housemenu to upgrade/exit his house
						SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Use {FFFF00}/menucasa{00FF00} para selecionar as opções da casa.");

						// Exit the function
						return 1;
					}
				}
			}

			// Loop through all player-owned businesses
			for (new i; i < MAX_BUSINESSPERPLAYER; i++)
			{
			    // Get the business-id at the selected slot from the player
			    BusID = APlayerData[playerid][Business][i];

				// Check if the player has owned a business in this slot
				if (BusID != 0)
				{
					// Check if the player is in range of the business-pickup
					if (IsPlayerInRangeOfPoint(playerid, 2.5, ABusinessData[BusID][BusinessX], ABusinessData[BusID][BusinessY], ABusinessData[BusID][BusinessZ]))
					{
					    // Get the business-type
					    BusType = ABusinessData[BusID][BusinessType];
						// Set the worldid so other players cannot see him anymore
						SetPlayerVirtualWorld(playerid, 1000 + playerid);
						// Set the player inside the interior of the business
						SetPlayerInterior(playerid, ABusinessInteriors[BusType][InteriorID]);

						// Set the position of the player at the spawn-location of the business's interior
						SetPlayerPos(playerid, ABusinessInteriors[BusType][IntX], ABusinessInteriors[BusType][IntY], ABusinessInteriors[BusType][IntZ]);
						// Also set a tracking-variable to enable /busmenu to track in which business the player is
						APlayerData[playerid][CurrentBusiness] = BusID;
						// Also let the player know he can use /busmenu to upgrade/exit his business
						SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Use {FFFF00}/menuempresa{00FF00} para selecionar as opções da empresa.");

						// Exit the function
						return 1;
					}
				}
			}
		}
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command opens a menu when you're inside your house to allow to access the options of your house
COMMAND:menucasa(playerid, params[])
{
	// Setup local variables
	new OptionsList[200], DialogTitle[200];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/menucasa", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player is inside a house
		if (APlayerData[playerid][CurrentHouse] != 0)
		{
			format(DialogTitle, sizeof(DialogTitle), "Selecione a opção para: %s", AHouseData[APlayerData[playerid][CurrentHouse]][HouseName]);

			format(OptionsList, sizeof(OptionsList), "%sMudar nome da casa\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sAtualizar casa\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sComprar carro da casa\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sComprar carro da casa seguro\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sVender carro da casa\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sVender casa\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sAbrir casa para o público\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sFechar casa para o público\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sSair da casa\n", OptionsList);
			// Show the housemenu
			ShowPlayerDialog(playerid, DialogHouseMenu, DIALOG_STYLE_LIST, DialogTitle, OptionsList, "Selecionar", "Cancelar");
		}
		else
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não possui uma casa.");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// This command allows you to port a vehicle from your house to your location
COMMAND:usarcarro(playerid, params[])
{
	// Setup local variables
	new HouseList[1000];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/usarcarro", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player is not jailed
		if (APlayerData[playerid][PlayerJailed] == 0)
		{
			// Check if the player is not inside a vehicle
			if (GetPlayerVehicleID(playerid) == 0)
			{
				// Ask to which house the player wants to add his vehicle
				for (new i; i < MAX_HOUSESPERPLAYER; i++)
				{
					// Check if this houseindex is occupied
					if (APlayerData[playerid][Houses][i] != 0)
						format(HouseList, 1000, "%s{00FF00}%s{FFFFFF}\n", HouseList, AHouseData[APlayerData[playerid][Houses][i]][HouseName]);
					else
						format(HouseList, 1000, "%s{FFFFFF}%s{FFFFFF}\n", HouseList, "Slot Vazio");
				}
				ShowPlayerDialog(playerid, DialogGetCarSelectHouse, DIALOG_STYLE_LIST, "Escolha a casa que terá o carro:", HouseList, "Selecionar", "Cancelar");
			}
			else
				SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar a pé, à porta de um veículo para a sua localização!");
		}
		else
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode usar o comando /usarcarro quando está preso!");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command checks if the player is inside a vehicle that he owns and if he's in range of the house where the vehicle is assigned to
COMMAND:estacionar(playerid, params[])
{
	// Setup local variables
	new Float:x, Float:y, Float:z, Float:rot, vid, HouseID, Msg[128];
	new engine,lights,alarm,doors,bonnet,boot,objective;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/estacionar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player is inside a vehicle (he must be the driver)
		if (GetPlayerVehicleSeat(playerid) == 0)
		{
			// Get the vehicle-id
			vid = GetPlayerVehicleID(playerid);
			// Get the HouseID to which this vehicle belongs
			HouseID = AVehicleData[vid][BelongsToHouse];

			// Check if the vehicle is owned (owner-check is not really required, as another player would get kicked out very fast)
			// AND it must belong to a house that the player owns
			if ((AVehicleData[vid][Owned] == true) && (HouseID != 0))
			{
				// Check if the vehicle is in range of the house-entrance (you cannot park a vehicle further away from your house than 150m)
				if (IsPlayerInRangeOfPoint(playerid, ParkRange, AHouseData[HouseID][HouseX], AHouseData[HouseID][HouseY], AHouseData[HouseID][HouseZ]))
				{
					// Get the player's position and angle
					GetVehiclePos(vid, x, y, z);
					GetVehicleZAngle(vid, rot);
					// Save those values for the vehicle
					AVehicleData[vid][SpawnX] = x;
					AVehicleData[vid][SpawnY] = y;
					AVehicleData[vid][SpawnZ] = z;
					AVehicleData[vid][SpawnRot] = rot;

					// Find the vehicle in the player's houses
					for (new i; i < MAX_HOUSESPERPLAYER; i++)
					{
						// Get the HouseID of the current house
					    HouseID = APlayerData[playerid][Houses][i];

						// Loop through all carslots of this house to find the vehicle-id
						for (new CarSlot; CarSlot < 10; CarSlot++)
						{
							// Check if this carslot holds the same vehicle-id
						    if (AHouseData[HouseID][VehicleIDs][CarSlot] == vid)
						    {
			                    House_ReplaceVehicle(HouseID, CarSlot); // Re-create the vehicle at the same spot the player wants to park his vehicle
			                    PutPlayerInVehicle(playerid, AHouseData[HouseID][VehicleIDs][CarSlot], 0);
								// Turn on the engine
								GetVehicleParamsEx(AHouseData[HouseID][VehicleIDs][CarSlot], engine, lights, alarm, doors, bonnet, boot, objective);
								SetVehicleParamsEx(AHouseData[HouseID][VehicleIDs][CarSlot], 1, lights, alarm, doors, bonnet, boot, objective);
			                    break; // Stop the for-loop
							}
						}
					}

					// Let the player know he parked his vehicle
					SendClientMessage(playerid, 0x00FF00FF, "[ToB] Você estacionou o seu veículo.");

					// Save the player-file (and his houses)
					PlayerFile_Save(playerid);
				}
				else
				{
				    format(Msg, 128, "{FF0000}[ToB] Você precisa estar dentro do veículo da sua casa para estacioná-lo!", ParkRange);
				    SendClientMessage(playerid, 0xFFFFFFFF, Msg);
				}
			}
			else
			    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode estacionar um veículo que não é da sua propriedade!");
		}
		else
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você deve estar dentro do veículo para estacioná-lo!");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// Lets the player rent a vehicle
COMMAND:alugarcarro(playerid, params[])
{
	// Setup local variables
	new VehicleClassList[1000];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/alugarcarro", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Make sure the player isn't inside a vehicle
		if (GetPlayerVehicleID(playerid) == 0)
		{
			// Check if the player is near a cardealerpickup
			for (new i; i < sizeof(ACarDealerPickups); i++)
			{
				// Check if a valid cardealerpickup is found
				if (ACarDealerPickups[i][PickupID] != 0)
				{
					// Check if the player is in range of the cardealerpickup
					if(IsPlayerInRangeOfPoint(playerid, 2.5, ACarDealerPickups[i][pux], ACarDealerPickups[i][puy], ACarDealerPickups[i][puz]))
					{
					    // Let the player choose a vehicle-class
						format(VehicleClassList, 1000, "%s{00FF00}%s{FFFFFF}\n", VehicleClassList, "Bicicletas e Motos");
						format(VehicleClassList, 1000, "%s{40FF00}%s{FFFFFF}\n", VehicleClassList, "Barcos");
						format(VehicleClassList, 1000, "%s{80FF00}%s{FFFFFF}\n", VehicleClassList, "Converssíveis");
						format(VehicleClassList, 1000, "%s{B0FF00}%s{FFFFFF}\n", VehicleClassList, "Helicópteros");
						format(VehicleClassList, 1000, "%s{FFFF00}%s{FFFFFF}\n", VehicleClassList, "Veículos Industriais");
						format(VehicleClassList, 1000, "%s{B0FF40}%s{FFFFFF}\n", VehicleClassList, "Low-riders");
						format(VehicleClassList, 1000, "%s{80FF80}%s{FFFFFF}\n", VehicleClassList, "Veículos OFF-Road");
						format(VehicleClassList, 1000, "%s{40FFB0}%s{FFFFFF}\n", VehicleClassList, "Aviões");
						format(VehicleClassList, 1000, "%s{00FFFF}%s{FFFFFF}\n", VehicleClassList, "Veículos de Serviço Público");
						format(VehicleClassList, 1000, "%s{00B0FF}%s{FFFFFF}\n", VehicleClassList, "RC");
						format(VehicleClassList, 1000, "%s{0080FF}%s{FFFFFF}\n", VehicleClassList, "Veículos Saloon");
						format(VehicleClassList, 1000, "%s{0040FF}%s{FFFFFF}\n", VehicleClassList, "Veículos Sport");
						format(VehicleClassList, 1000, "%s{0000FF}%s{FFFFFF}\n", VehicleClassList, "Vagões de Estação");
						format(VehicleClassList, 1000, "%s{4000FF}%s{FFFFFF}\n", VehicleClassList, "Reboques");
						format(VehicleClassList, 1000, "%s{8000FF}%s{FFFFFF}\n", VehicleClassList, "Veículos Únicos");
						// Ask which vehicle class the player wants to see to buy a vehicle
						ShowPlayerDialog(playerid, DialogRentCarClass, DIALOG_STYLE_LIST, "Select vehicle class:", VehicleClassList, "Select", "Cancel");
						// Exit the function
						return 1;
					}
				}
			}

			// The player wasn't in range of a cardealer
			SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode alugar um veículo quando não está perto de um comerciante.");
		}
		else
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode alugar um veículo quando estiver dentro de um veículo");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// This command teleports you to your selected house
COMMAND:irparacasa(playerid, params[])
{
	// Setup local variables
	new HouseList[1000];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/irparacasa", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player has a wanted level of less than 3
		if (GetPlayerWantedLevel(playerid) < 3)
		{
			// Check if the player is not jailed
			if (APlayerData[playerid][PlayerJailed] == 0)
			{
				// Check if the player is not inside a vehicle
				if (GetPlayerVehicleID(playerid) == 0)
				{
					// Ask to which house the player wants to add his vehicle
					for (new i; i < MAX_HOUSESPERPLAYER; i++)
					{
						// Check if this houseindex is occupied
						if (APlayerData[playerid][Houses][i] != 0)
							format(HouseList, 1000, "%s{00FF00}%s{FFFFFF}\n", HouseList, AHouseData[APlayerData[playerid][Houses][i]][HouseName]);
						else
							format(HouseList, 1000, "%s{FFFFFF}%s{FFFFFF}\n", HouseList, "Slot Vazio");
					}
					ShowPlayerDialog(playerid, DialogGoHome, DIALOG_STYLE_LIST, "Selecione a casa que deseja ir:", HouseList, "Selecionar", "Cancelar");
				}
				else
					SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar a pé na porta da sua casa.");
			}
			else
			    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode usar o comando /irparacasa quando está preso!");
		}
		else
			SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode usar o comando /irparacasa quando preso!");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// Gives the player the cash he requests
COMMAND:dinheiro(playerid, params[])
{
	new Amount, Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/dinheiro", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 4
		if (APlayerData[playerid][PlayerLevel] >= 4)
		{
			if (sscanf(params, "i", Amount)) SendClientMessage(playerid, 0xFF0000AA, "Use: /dinheiro [quantia]");
			else
			{
				// Reward the player (give cash and points)
				RewardPlayer(playerid, Amount, 0);
				format(Msg, 128, "[ToB] Você ganhou R$%i", Amount);
				SendClientMessage(playerid, 0x00FF00AA, Msg);
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	return 1;
}

// Gives the player the cash he requests
COMMAND:score(playerid, params[])
{
	new Amount, Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/score", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 4
		if (APlayerData[playerid][PlayerLevel] >= 4)
		{
			if (sscanf(params, "i", Amount)) SendClientMessage(playerid, 0xFF0000AA, "Usage: /score [quantia]");
			else
			{
				// Reward the player (give cash and points)
				RewardPlayer(playerid, 0, Amount);
				format(Msg, 128, "[ToB] Você ganhou %i pontos de score", Amount);
				SendClientMessage(playerid, 0x00FF00AA, Msg);
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	return 1;
}

// Detaches the trailer from the vehicle
COMMAND:desatrelar(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/desatrelar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Detach the trailer from the vehicle
		DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
		// Send the player a message that the trailer has been detached
		SendClientMessage(playerid, 0x0000FFFF, "[ToB] Você desatrelou a carroceria.");
	}
	else
		return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Puts the player's vehicle back onto his wheels
COMMAND:virar(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/virar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Setup some local variables
		new Float:x = 0.0, Float:y = 0.0, Float:z = 0.0;
		// Check if the player is inside a vehicle
		if(IsPlayerInAnyVehicle(playerid))
			SetCameraBehindPlayer(playerid);
		// Get the player's position
		GetPlayerPos(playerid, x, y, z);
		// Set the vehicle on the player's coordinates
		SetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
		// Let the vehicle point north
		SetVehicleZAngle(GetPlayerVehicleID(playerid), 0.0);
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Repairs the player's vehicle
COMMAND:reparar(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/reparar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
		    // Check if the player is inside a vehicle
			if(!IsPlayerInAnyVehicle(playerid))
				return SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não está em um veículo!"); // Let the player know he's not inside a vehicle and let the server know that this was a valid command
			// Fully repair the vehicle (damage value and bodywork)
			RepairVehicle(GetPlayerVehicleID(playerid));
			// Send the player a message to inform him that his vehicle has been repaired
			SendClientMessage(playerid, 0x00FF00FF, "[ToB] Veículo reparado!");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Repairs all vehicles
COMMAND:reparartodos(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/reparartodos", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
			// Loop through all vehicles
			for (new i; i < 2000; i++)
				RepairVehicle(i); // Fully repair the vehicle (damage value and bodywork)

			// Send all players a message to inform them that all vehicles have been repaired
			SendClientMessageToAll(0x00FF00FF, "[ToB] Todos os Veículos foram reparados pelo admin!");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Heals all players
COMMAND:darvidatodos(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/darvidatodos", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
			// Loop through all players
			for (new i; i < MAX_PLAYERS; i++)
				if (IsPlayerConnected(i)) // Check if the player is connected
				    if (IsPlayerInAnyVehicle(i) == 0) // Check if the player isn't inside a vehicle
				        SetPlayerHealth(i, 100.0); // Heal the player

			// Send all players a message to inform them that all players have been healed
			SendClientMessageToAll(0x00FF00FF, "[ToB] Todos os jogadores receberam vida máxima!");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// Kills the player
COMMAND:morrer(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/morrer", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player has a wanted level of less than 3
		if (GetPlayerWantedLevel(playerid) < 3)
		{
			// Check if the player isn't in jail
			if (APlayerData[playerid][PlayerJailed] == 0)
			{
			    // Force the player back into class-selection
				ForceClassSelection(playerid);
				// Kill the player (required after ForceClassSelection)
				SetPlayerHealth(playerid, 0.0);
			}
			else
			    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode usar o comando /morrer quando preso!");
		}
		else
		    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode usar o comando /morrer quando procurado!");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Lets the player choose another class
COMMAND:reescolher(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/reescolher", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player has a wanted level of less than 3
		if (GetPlayerWantedLevel(playerid) < 3)
		{
			// Check if the player isn't in jail
			if (APlayerData[playerid][PlayerJailed] == 0)
			{
			    // Force the player back into class-selection
				ForceClassSelection(playerid);
				// Kill the player (required after ForceClassSelection)
				SetPlayerHealth(playerid, 0.0);
			}
			else
			    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode usar o comando /reescolher quando preso!");
		}
		else
		    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode usar o comando /reescolher quando procurado!");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Starts a job
COMMAND:trabalhar(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/trabalhar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// First check if the player already has a job
		if (APlayerData[playerid][JobStarted] == false)
		{
		    // Check the player's class
			switch (APlayerData[playerid][PlayerClass])
			{
				case ClassTruckDriver:
				{
					// Get the id of the convoy (if the player is in a convoy)
					new Convoy = APlayerData[playerid][ConvoyID];

					// Check if the player is part of a convoy AND is not the leader
					if ((APlayerData[playerid][InConvoy] == true) && (AConvoys[Convoy][Members][0] != playerid))
					{
						// Let the player know he's not the leader of his convoy and cannot start a job
						SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não é o líder do comboio, por tanto não pode iniciar uma missão.");
						// Exit the function
						return 1;
					}

					// A convoy-leader proceeds here, and also a normal player (no convoy-member)

					// Check if the player is the driver of a vehicle
					if (GetPlayerVehicleSeat(playerid) == 0)
					{
						// Check if the player is inside a valid trucking vehicle
						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))
						{
							case VehicleFlatbed, VehicleDFT30, VehicleCementTruck: // Flatbed, DFT-30, CementTruck
								if (APlayerData[playerid][TruckerLicense] == 1) // Check if the player has acquired a truckers license
									ShowPlayerDialog(playerid, DialogTruckerJobMethod, DIALOG_STYLE_LIST, "Selecione o método:", "Configurar sua própria carga e rota\r\nAtribuir auto-carga", "Selecionar", "Cancelar");
								else
								    Trucker_StartRandomJob(playerid); // Start a random job

							case VehicleLineRunner, VehicleTanker, VehicleRoadTrain: // Player is driving a truck which needs a trailer
								if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid))) // Check if there is a trailer attached
									if (APlayerData[playerid][TruckerLicense] == 1) // Check if the player has acquired a truckers license
										ShowPlayerDialog(playerid, DialogTruckerJobMethod, DIALOG_STYLE_LIST, "Selecione o método:", "Configurar sua própria carga e rota\r\nAtribuir auto-carga", "Selecionar", "Cancelar");
									else
									    Trucker_StartRandomJob(playerid); // Start a random job
								else
								    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa de um trailer para iniciar o trabalho.");

							default: SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar conduzindo um caminhão para iniciar o trabalho.");
						}
					}
					else
		                SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar conduzindo um caminhão para iniciar o trabalho.");
				}
				case ClassBusDriver:
				{
					// Check if the player is the driver of a vehicle
					if (GetPlayerVehicleSeat(playerid) == 0)
						if (GetVehicleModel(GetPlayerVehicleID(playerid)) == VehicleCoach) // Check if the player is inside a valid busdriver vehicle
							if (APlayerData[playerid][BusLicense] == 1) // Check if the player has acquired a busdriver license
								ShowPlayerDialog(playerid, DialogBusJobMethod, DIALOG_STYLE_LIST, "Selecione o método :", "Escolha sua própria rota de ônibus\r\nAtribuir auto-rota", "Selecionar", "Cancelar");
							else
								BusDriver_StartJob(playerid, random(sizeof(ABusRoutes))); // Start a random job
						else
			                SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar dirigindo um ônibus para iniciar o trabalho!");
					else
		                SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar dirigindo um ônibus para iniciar o trabalho!");
				}
				case ClassPilot:
				{
					// Check if the player is the driver of a vehicle
					if (GetPlayerVehicleSeat(playerid) == 0)
					{
						// Check if the player is inside a valid piloting vehicle
						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))
						{
							case VehicleShamal, VehicleNevada, VehicleMaverick, VehicleCargobob: // Plane (Shamal), Plane (Nevada), helicopter (Maverick)
								Pilot_StartRandomJob(playerid); // Start a random piloting job
							default: SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar conduzindo um veículo de voo para iniciar o trabalho.");
						}
					}
					else
		                SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar conduzindo um veículo de voo para iniciar o trabalho.");
				}
				case ClassMafia:
				{
					// Check if the player is the driver of a vehicle
					if (GetPlayerVehicleSeat(playerid) == 0)
					{
						// Check if the player is inside a valid piloting vehicle
						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))
						{
							case VehicleSandKing, VehicleMoonbeam: // Sangking, Moonbeam
								Mafia_StartRandomJob(playerid); // Start a random mafia job
							default: SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar conduzindo um veículo da máfia para iniciar o trabalho.");
						}
					}
					else
		                SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar conduzindo um veículo da máfia para iniciar o trabalho.");
				}
				case ClassCourier:
				{
					// Check if the player is the driver of a vehicle
					if (GetPlayerVehicleSeat(playerid) == 0)
					{
						// Check if the player is inside a valid courier vehicle
						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))
						{
							case VehicleBurrito, VehicleFaggio, VehicleBenson: // Van (Burrito), bike (Faggio)
								Courier_StartJob(playerid); // Start a random courier job
							default: SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar conduzindo um veículo dos Correios para iniciar o trabalho.");
						}
					}
					else
		                SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar conduzindo um veículo dos Correios para iniciar o trabalho.");
				}
				case ClassRoadWorker:
				{
					// Check if the player is the driver of a vehicle
					if (GetPlayerVehicleSeat(playerid) == 0)
					{
						// Check if the player is inside a valid courier vehicle
						switch (GetVehicleModel(GetPlayerVehicleID(playerid)))
						{
							case VehicleUtilityVan, VehicleTowTruck: // Utility Van, Towtruck
								Roadworker_StartRandomJob(playerid); // Start a random roadworker job
							default: SendClientMessage(playerid, 0xFF0000FF, "Você precisa estar conduzindo um veículo do DNIT para iniciar o trabalho.");
						}
					}
					else
		                SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar conduzindo um veículo do DNIT para iniciar o trabalho.");
				}
				default: SendClientMessage(playerid, 0xFF0000FF, "[ToB] A sua classe não pode fazer todos os trabalhos.");
			}
		}
		else // Send a message to let the player know he already has a job
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você já está realizando um trabalho!");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Stops the current job
COMMAND:parartrabalho(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/parartrabalho", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
	    // Check if the player has a job started
		if (APlayerData[playerid][JobStarted] == true)
		{
		    // Check the class of the player
			switch (APlayerData[playerid][PlayerClass])
			{
				case ClassTruckDriver: Trucker_EndJob(playerid); // Stop any trucker job
				case ClassBusDriver: BusDriver_EndJob(playerid); // Stop any busdriver job
				case ClassPilot: Pilot_EndJob(playerid); // Stop any pilot job
				case ClassMafia: Mafia_EndJob(playerid); // Stop any mafia job
				case ClassCourier: Courier_EndJob(playerid);
				case ClassRoadWorker: Roadworker_EndJob(playerid);
				default: SendClientMessage(playerid, 0xFF0000FF, "[ToB] A sua classe não tem trabalho para terminar.");
			}

			// Inform the player that he failed the mission
			GameTextForPlayer(playerid, "~w~Voce ~r~falhou~w~ com seu trabalho. Você perdeu ~y~R$1000~w~ para cobrir as despesas.", 5000, 4);
			// Reduce the player's cash by 1000
			RewardPlayer(playerid, -1000, 0);
		}
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Displays the player's coordinates on the map
COMMAND:local(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/local", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
		    // Setup some local variables
			new Message[200], Float:x, Float:y, Float:z, Float:rot, Interior, World;
			// Get the player's position
			GetPlayerPos(playerid, x, y, z);
			// Check if the player is on foot or in a vehicle
			if (GetPlayerVehicleSeat(playerid) == -1)
				GetPlayerFacingAngle(playerid, rot); // Get the player's angle
			else
			    GetVehicleZAngle(GetPlayerVehicleID(playerid), rot);

			// Get the interior where the player is located
			Interior = GetPlayerInterior(playerid);
			// Get the virtual world of the player
			World = GetPlayerVirtualWorld(playerid);
			// combine the position and angle into a proper message
		    format(Message, sizeof(Message), "Localizacao: X=%4.2f, Y=%4.2f, Z=%4.2f, rotacao=%4.2f, interior=%i, world=%i", x, y, z, rot, Interior, World);
		    // Send the message with the coordinates and the angle of the player
			SendClientMessage(playerid, 0xFF0000AA, Message);
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Saves the location into a file
COMMAND:savelocal(playerid, params[])
{
	new File:LocFile, LineForFile[255], LineMsg[255];
	new Float:x, Float:y, Float:z, LocName[255], ID;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/savelocal", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			if (sscanf(params, "is[255]", ID, LocName)) SendClientMessage(playerid, 0xFF0000AA, "Use: /savelocal [id] [descrição]");
			else
			{
				if (!fexist("ServerData/Locations.txt"))
				{
				    LocFile = fopen("ServerData/Locations.txt", io_write); // Create the file
					fclose(LocFile); // Close the file
				}

				// Get the player's position
				GetPlayerPos(playerid, x, y, z);
				// Combine all the data in a proper structure, so it can be used directly for setting up the ALocations array
			    format(LineForFile, sizeof(LineForFile), "\t{\"%s\", %4.2f, %4.2f, %4.2f}, // ID = %i", LocName, x, y, z, ID);

				LocFile = fopen("ServerData/Locations.txt", io_append); // Open the locationfile for appending data to it
				fwrite(LocFile, LineForFile); // Append the data to the end of the file
				fwrite(LocFile, "\r\n"); // Start a new line, or all the data is saved in one line
				fclose(LocFile); // Close the file

				// Let the player know what data has been saved
				format(LineMsg, 255, "[ToB] Localização salva: %s", LineForFile);
				SendClientMessage(playerid, 0x808080FF, LineMsg);
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Lets the player choose where he wants to respawn (costs $200)
COMMAND:resgate(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/resgate", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player has a wanted level of less than 3
		if (GetPlayerWantedLevel(playerid) < 3)
		{
			// Check if the player isn't in jail
			if (APlayerData[playerid][PlayerJailed] == 0)
			{
				if (APlayerData[playerid][JobStarted] == false)
				{
					// Make sure you can't use "/rescue" when you're inside a vehicle (doesn't respawn you at the requested coords
					// and puts a random item (bottle, sigarette, ...) in the player's hands
					if (GetPlayerVehicleID(playerid) == 0)
					{
					    // Create a dialog based on the player's class
						switch (APlayerData[playerid][PlayerClass])
						{
							case ClassTruckDriver: // Ask where the trucker player wants to respawn
								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Caminhoneiro nascer em:", "Fallen Tree Depot\r\nFlint Trucking Depot\r\nLVA Freight Depot\r\nDoherty Depot\r\nEl Corona Depot\r\nLas Payasdas Depot\r\nQuarry Top\r\nShady Creek Depot", "Spawn", "Cancel");
							case ClassBusDriver: // Ask where the busdriver wants to respawn
								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Motorista de Ônibus nascer em:", "Los Santos\r\nSan Fierro\r\nLas Venturas", "Spawn", "Cancel");
							case ClassPilot: // Ask where the pilot wants to respawn
								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Piloto nascer em:", "Los Santos\r\nSan Fierro\r\nLas Venturas", "Spawn", "Cancel");
							case ClassPolice: // Ask where the police player wants to respawn
								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Policial nascer em:", "Los Santos\r\nSan Fierro\r\nLas Venturas", "Spawn", "Cancel");
							case ClassCourier: // Ask where the courier player wants to respawn
								ShowPlayerDialog(playerid, DialogRescue, DIALOG_STYLE_LIST, "Correios nascer em:", "Los Santos\r\nSan Fierro\r\nLas Venturas", "Spawn", "Cancel");
						}
					}
					else
						SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode usar o comando /resgate dentro de um veículo."); // "/rescue" doesn't work inside a vehicle
				}
				else
				    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode ser resgatado realizando um trabalho!"); // "/rescue" doesn't work during a job
			}
			else
			    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você nao pode usar o comando /resgate quando preso.");
		}
		else
		    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode usar o comando /resgate quando procurado.");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Increases the player's wanted level by 1
COMMAND:procurado(playerid, params[])
{
	new OtherPlayer, Stars;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/procurado", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 2
		if (APlayerData[playerid][PlayerLevel] >= 2)
		{
			if (sscanf(params, "ui", OtherPlayer, Stars)) SendClientMessage(playerid, 0xFF0000AA, "Use: /procurado [id] [nivel]");
			else
				if (IsPlayerConnected(OtherPlayer)) // If the player is a valid playerid (he's connected)
					SetPlayerWantedLevel(OtherPlayer, Stars);
				else
				    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Esse jogador não está online.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// Lets the player choose a motorcycle to spawn
COMMAND:motos(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/motos", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Make sure the player isn't inside a vehicle
			if (GetPlayerVehicleID(playerid) == 0)
			{
				// Ask which motorcycle the player wants to have
				ShowPlayerDialog(playerid, DialogBike, DIALOG_STYLE_LIST, "Escolha a Bike:", "Bike\r\nBMX\r\nMountain Bike\r\nFaggio\r\nPizzaboy\r\nBF-400\r\nNRG-500\r\nPCJ-600\r\nFCR-900\r\nFreeway\r\nWayfarer\r\nSanchez\r\nQuad", "Criar", "Cancelar");
				// Let the server know that this was a valid command
				return 1;
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// Lets the player choose a car to spawn (in a split list which shows only 10 cars at a time)
COMMAND:carros(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/carros", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Make sure the player isn't inside a vehicle
			if (GetPlayerVehicleID(playerid) == 0)
				CarList_Create(playerid); // Create a list of cars (only the first 10 cars) and show the dialog so the player can choose a car
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// Lets the player choose a plane to spawn (in a split list which shows only 10 planes at a time)
COMMAND:avioes(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/avioes", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Make sure the player isn't inside a vehicle
			if (GetPlayerVehicleID(playerid) == 0)
				PlaneList_Create(playerid); // Create a list of planes (only the first 10 planes) and show the dialog so the player can choose a plane
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// Lets the player choose a trailer to spawn (in a split list which shows only 10 trailers at a time)
COMMAND:carrocerias(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/carrocerias", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Make sure the player isn't inside a vehicle
			if (GetPlayerVehicleID(playerid) == 0)
				TrailerList_Create(playerid); // Create a list of trailers (only the first 10 trailers) and show the dialog so the player can choose a trailer
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Lets the player choose a boat to spawn
COMMAND:barcos(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/barcos", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Make sure the player isn't inside a vehicle
			if (GetPlayerVehicleID(playerid) == 0)
			{
				// Ask which motorcycle the player wants to have
				ShowPlayerDialog(playerid, DialogBoat, DIALOG_STYLE_LIST, "Escolha o barco:", "Coastguard\nDinghy\nJetmax\nLaunch\nMarquis\nPredator\nReefer\nSpeeder\nSquallo\nTropic", "Criar", "Cancelar");
				// Let the server know that this was a valid command
				return 1;
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// Jail a player
COMMAND:prender(playerid, params[])
{
	new PlayerToJail, JailTime, Reason[128], Msg[128], Name[24], AdminName[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/prender", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			if (sscanf(params, "uis[128]", PlayerToJail, JailTime, Reason)) SendClientMessage(playerid, 0xFF0000AA, "Use: /prender [id] [tempo] [motivo]");
			else
				if (IsPlayerConnected(PlayerToJail)) // If the player is a valid playerid (he's connected)
				{
				    // Jail the player
					Police_JailPlayer(PlayerToJail, JailTime);
					// Get the name of the player who jailed the player
					GetPlayerName(playerid, AdminName, sizeof(AdminName));
					// Get the name of the player who's being sent to jail
					GetPlayerName(PlayerToJail, Name, sizeof(Name));
					// Send the jailed player a message who jailed him, why he's been jailed and how long
					format(Msg, 128, "[ToB] Você foi preso por %s %s por %i segundos.", AdminLevelName[APlayerData[playerid][PlayerLevel]], AdminName, JailTime);
					SendClientMessage(PlayerToJail, 0xFF0000FF, Msg);
					format(Msg, 128, "Motivo: %s", Reason);
					SendClientMessage(PlayerToJail, 0xFF0000FF, Msg);
					format(Msg, 128, "{00FF00}Você prendeu {FFFF00}%s{00FF00} por {FFFF00}%i{00FF00} segundos.", Name, JailTime);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
				}
				else
				    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Esse jogador não está online.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Warn a player
COMMAND:aviso(playerid, params[])
{
	new PlayerToWarn, Reason[128], ReasonMsg[128], Name[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/aviso", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			if (sscanf(params, "us[128]", PlayerToWarn, Reason)) SendClientMessage(playerid, 0xFF0000AA, "Use: /aviso [id] [motivo]");
			else
				if (IsPlayerConnected(PlayerToWarn)) // If the player is a valid playerid (he's connected)
				{
					// Increase the number of warnings
					APlayerData[PlayerToWarn][Warnings]++;

					// Get the name of the player who warned the player
					GetPlayerName(playerid, Name, sizeof(Name));
					// Send the warned player a message who warned him and why he's been warned
					format(ReasonMsg, 128, "[ToB] Você foi avisado por %s %s", AdminLevelName[APlayerData[playerid][PlayerLevel]], Name);
					SendClientMessage(PlayerToWarn, 0xFF0000FF, ReasonMsg);
					format(ReasonMsg, 128, "Motivo: %s", Reason);
					SendClientMessage(PlayerToWarn, 0xFF0000FF, ReasonMsg);
					format(ReasonMsg, 128, "~w~Aviso %i/%i: ~r~%s~w~", APlayerData[PlayerToWarn][Warnings], AutoKickWarnings, Reason);
					GameTextForPlayer(PlayerToWarn, ReasonMsg, 5000, 4);

					// Get the name of the warned player
					GetPlayerName(PlayerToWarn, Name, sizeof(Name));
					// Let the admin know who has been warned and why
					format(ReasonMsg, 128, "[ToB] Você recebeu um aviso %s (avisos: %i/%i)", Name, APlayerData[PlayerToWarn][Warnings], AutoKickWarnings);
					SendClientMessage(playerid, 0x00FF00FF, ReasonMsg);
					format(ReasonMsg, 128, "Motivo: %s", Reason);
					SendClientMessage(playerid, 0xFF0000FF, ReasonMsg);

					// Automatically kick the player if he got 3 warnings (if autokick is enabled)
					if ((APlayerData[PlayerToWarn][Warnings] == AutoKickWarnings) && (AutoKickAfterWarn == 1))
						Kick(PlayerToWarn);
				}
				else
				    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Esse jogador não está online.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Kicks a player with a reason
COMMAND:kick(playerid, params[])
{
	new PlayerToKick, Reason[128], ReasonMsg[128], Name[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/kick", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			if (sscanf(params, "us[128]", PlayerToKick, Reason)) SendClientMessage(playerid, 0xFF0000AA, "Use: /kick [id] [motivo]");
			else
				if (IsPlayerConnected(PlayerToKick)) // If the player is a valid playerid (he's connected)
				{
					// Get the name of the player who warned the player
					GetPlayerName(playerid, Name, sizeof(Name));
					// Send the warned player a message who kicked him and why he's been kicked
					format(ReasonMsg, 128, "[ToB] Você foi kickado por %s %s", AdminLevelName[APlayerData[playerid][PlayerLevel]], Name);
					SendClientMessage(PlayerToKick, 0xFF0000FF, ReasonMsg);
					format(ReasonMsg, 128, "Motivo: %s", Reason);
					SendClientMessage(PlayerToKick, 0xFF0000FF, ReasonMsg);
					// Kick the player
					Kick(PlayerToKick);
				}
				else
				    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Esse jogador não está online.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Bans a player for (days, hours, minutes, seconds)
COMMAND:ban(playerid, params[])
{
	// Setup local variables
	new PlayerToBan, Days, Hours, Reason[128], TotalBanTime, Msg[128], Name[24], AdminName[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/ban", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
			if (sscanf(params, "uiis[128]", PlayerToBan, Days, Hours, Reason))
				SendClientMessage(playerid, 0xFF0000AA, "Use: /ban [id] [dias] [horas] [motivo]");
			else
			{
				if (IsPlayerConnected(PlayerToBan))
				{
					// Get the names of the player and the admin who executed the ban
					GetPlayerName(playerid, AdminName, sizeof(AdminName));
					GetPlayerName(PlayerToBan, Name, sizeof(Name));

					// Increase the number of bans
					APlayerData[PlayerToBan][Bans]++;
					// Calculate the total bantime (when the player can login again)
					TotalBanTime = (Days * 86400) + (Hours * 3600) + gettime();
					// Check if this is the player's 5th ban
					if (APlayerData[PlayerToBan][Bans] == 5)
						APlayerData[PlayerToBan][BanTime] = 2147483640; // Make the ban permanent (as high as it can go)
					else
						APlayerData[PlayerToBan][BanTime] = TotalBanTime; // Store this value for the player

					// Inform the player about his ban
					// Check if this is the player's 5th ban
					if (APlayerData[PlayerToBan][Bans] == 5)
					{
						format(Msg, 128, "[ToB] Você foi banido permanentemente por %s, pois ja é o seu 5° banimento.", AdminName);
						SendClientMessage(PlayerToBan, 0x808080FF, Msg);
					}
					else
					{
						format(Msg, 128, "[ToB] Você foi banido por %s por %i dias e %i horas.", AdminName, Days, Hours);
						SendClientMessage(PlayerToBan, 0x808080FF, Msg);
						format(Msg, 128, "Reason: %s", Reason);
						SendClientMessage(PlayerToBan, 0x808080FF, Msg);
						format(Msg, 128, "[ToB] Você já foi banido %i vezes, a 5° será permanente.", APlayerData[PlayerToBan][Bans]);
						SendClientMessage(PlayerToBan, 0x808080FF, Msg);
					}

					// Kick the player (his data will be saved)
					Kick(PlayerToBan);

					// Inform everybody else which player was banned and for how long
					format(Msg, 128, "[ToB] %s %s baniu %s por %i dias e %i horas.", AdminLevelName[APlayerData[playerid][PlayerLevel]], AdminName, Name, Days, Hours);
					SendClientMessageToAll(0x808080FF, Msg);
				}
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	return 1;
}

// Unbans a player (cleares the ban-time)
COMMAND:desban(playerid, params[])
{
	// Setup local variables
	new PlayerToUnban[24], Msg[128], Name[24];
	new file[100], File:PFile, LineForFile[100];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/desban", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
			if (sscanf(params, "s[128]", PlayerToUnban))
				SendClientMessage(playerid, 0xFF0000AA, "Use: /desban [nick]");
			else
			{
			    // Get the name of the admin
				GetPlayerName(playerid, Name, sizeof(Name));

				// Construct the complete filename for this player's account
				format(file, sizeof(file), PlayerFile, PlayerToUnban);

				// Check if the file exists
				if (fexist(file))
				{
					PFile = fopen(file, io_append); // Open the playerfile for appending (this command only appends a new line to overwrite the bantime)

					format(LineForFile, 100, "BanTime 0\r\n"); // Construct the line: "BanTime <0>"
					fwrite(PFile, LineForFile); // And save it to the file

					fclose(PFile); // Close the file

					// Inform everybody else which player was unbanned
					format(Msg, 128, "[ToB] %s %s desbaniu %s", AdminLevelName[APlayerData[playerid][PlayerLevel]], Name, PlayerToUnban);
					SendClientMessageToAll(0x808080FF, Msg);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Não existe nenhuma conta com esse nome.");
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	return 1;
}

// Spawns the object at the location given by the player
COMMAND:objeto(playerid, params[])
{
    // Setup local variables
	new ObjectModel, ObjID, Msg[128], Float:x, Float:y, Float:z, Float:Angle;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/objeto", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			if (sscanf(params, "iffff", ObjectModel, x, y, z, Angle)) SendClientMessage(playerid, 0xFF0000AA, "Use: /objeto [id-obj] [x] [y] [z] [angulo]");
			else
			{
				// Spawn the object 5 units north of the player
				ObjID = CreateObject(ObjectModel, x, y, z, 0.0, 0.0, Angle, 250.0);
				// Inform the player about it
				format(Msg, 128, "[ToB] Você criou o objeto id %i (modelo-id = %i) nas coordenadas: x=%4.2f, y=%4.2f, z=%4.2f", ObjID, ObjectModel, x, y, z);
				SendClientMessage(playerid, 0x00FF00FF, Msg);
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Spawns the pickup at the location given by the player
COMMAND:pickup(playerid, params[])
{
    // Setup local variables
	new PickupModel, PickID, Msg[128], Float:x, Float:y, Float:z, PickupType;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/pickup", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			if (sscanf(params, "ifffi", PickupModel, x, y, z, PickupType)) SendClientMessage(playerid, 0xFF0000AA, "Use: /pickup [id-pick] [x] [y] [z] [tipo]");
			else
			{
				// Spawn the pickup
				PickID = CreatePickup(PickupModel, PickupType, x, y, z, -1);
				// Inform the player about it
				format(Msg, 128, "[ToB] Você criou o pickup id %i (modelo-id = %i) nas coordenadas: x=%4.2f, y=%4.2f, z=%4.2f", PickID, PickupModel, x, y, z);
				SendClientMessage(playerid, 0x00FF00FF, Msg);
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Spawns the vehicle at the location given by the player
COMMAND:setcar(playerid, params[])
{
    // Setup local variables
	new VehicleModel, vID, Msg[128], Float:x, Float:y, Float:z, Float:Angle, SpawnDelay;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/setcar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			if (sscanf(params, "iffffi", VehicleModel, x, y, z, Angle, SpawnDelay)) SendClientMessage(playerid, 0xFF0000AA, "Use:/setcar [id] [x] [y] [z] [angulo] [SpawnDelay]");
			else
			{
				// Spawn the vehicle at the location specified by the player (also set max-fuel and save the model for the vehicle)
				vID = Vehicle_Create(VehicleModel, x, y, z, Angle, random(126), random(126), SpawnDelay);
				// Inform the player about it
				format(Msg, 128, "[ToB] Você criou o veiculo id %i (modelo-id = %i) nas coordenadas: x=%4.2f, y=%4.2f, z=%4.2f", vID, VehicleModel, x, y, z);
				SendClientMessage(playerid, 0x00FF00FF, Msg);
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Deletes the given vehicle from the game
COMMAND:delveh(playerid, params[])
{
    // Setup local variables
	new vID, Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/delveh", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			if (sscanf(params, "i", vID)) SendClientMessage(playerid, 0xFF0000AA, "Use: \"/delveh [id]");
			else
			{
				// Destroy the given vehicle
				DestroyVehicle(vID);
				// Inform the player about it
				format(Msg, 128, "[ToB] Você deletou o veículo id %i", vID);
				SendClientMessage(playerid, 0x00FF00FF, Msg);
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Deletes the given vehicle from the game
COMMAND:deletarobjeto(playerid, params[])
{
    // Setup local variables
	new oID, Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/deletarobjeto", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			if (sscanf(params, "i", oID)) SendClientMessage(playerid, 0xFF0000AA, "Use: /deletarobjeto [id]");
			else
			{
				// Destroy the given vehicle
				DestroyObject(oID);
				// Inform the player about it
				format(Msg, 128, "[ToB] Você deletou o objeto id %i", oID);
				SendClientMessage(playerid, 0x00FF00FF, Msg);
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Ports the player to the given coordinates
COMMAND:irpara(playerid, params[])
{
	// Setup local variables
	new Float:x, Float:y, Float:z, PortMsg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/irpara", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Check if the player has a wanted level of less than 3
			if (GetPlayerWantedLevel(playerid) < 3)
			{
				// Check if the player is not jailed
				if (APlayerData[playerid][PlayerJailed] == 0)
				{
					if (sscanf(params, "fff", x, y, z)) SendClientMessage(playerid, 0xFF0000AA, "Use: /irpara [x] [y] [z]");
					else
					{
						// Port the player to the given location
						SetPlayerPos(playerid, x, y, z);
						// Let the player know about it
						format(PortMsg, 128, "[ToB] Você foi teleportado para a posição: %4.2f, %4.2f, %4.2f", x, y, z);
						SendClientMessage(playerid, 0x00FF00FF, PortMsg);
					}
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode usar o comando /irpara quando preso.");
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode usar o comando /irpara quando procurado.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Ports the player to the given player
COMMAND:ir(playerid, params[])
{
	// Setup local variables
	new OtherPlayer, Float:x, Float:y, Float:z, PortMsg[128], IntID, WorldID;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/ir", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Check if the player has a wanted level of less than 3
			if (GetPlayerWantedLevel(playerid) < 3)
			{
				// Check if the player is not jailed
				if (APlayerData[playerid][PlayerJailed] == 0)
				{
					if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "Use: /ir [id]");
					else
					{
						// Check if that other player is online
						if (IsPlayerConnected(OtherPlayer))
						{
							// Get the location of the other player
							GetPlayerPos(OtherPlayer, x, y, z);
							IntID = GetPlayerInterior(OtherPlayer);
							WorldID = GetPlayerVirtualWorld(OtherPlayer);
							// Port the player to the given location
							SetPlayerVirtualWorld(playerid, WorldID);
							SetPlayerInterior(playerid, IntID);
							SetPlayerPos(playerid, x, y, z + 3.0);
							// Let the player know about it
							format(PortMsg, 128, "[ToB] A posição do jogador é: %4.2f, %4.2f, %4.2f", x, y, z + 3.0);
							SendClientMessage(playerid, 0x00FF00FF, PortMsg);
						}
						else
						    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Esse jogador não está online.");
					}
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode usar o comando /ir quando preso.");
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você nao pode usar o comando /ir quando procurado.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Ports one player to another player
COMMAND:levar(playerid, params[])
{
	// Setup local variables
	new Player1, Player2, Float:x, Float:y, Float:z, PortMsg[128], IntID, WorldID, Name[24], AdminName[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/levar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			if (sscanf(params, "uu", Player1, Player2)) SendClientMessage(playerid, 0xFF0000AA, "Use: /levar [para] [id]");
			else
			{
				// Check if player1 is online
				if (APlayerData[Player1][LoggedIn] == true)
				{
					// Check if player2 is online
					if (APlayerData[Player2][LoggedIn] == true)
					{
					    // Get the name of the admin and the second player
					    GetPlayerName(playerid, AdminName, sizeof(AdminName));
					    GetPlayerName(Player2, Name, sizeof(Name));
						// Get the location of the second player
						GetPlayerPos(Player2, x, y, z);
						IntID = GetPlayerInterior(Player2);
						WorldID = GetPlayerVirtualWorld(Player2);
						// Port the first player to player2's location
						SetPlayerVirtualWorld(Player1, WorldID);
						SetPlayerInterior(Player1, IntID);
						SetPlayerPos(Player1, x, y, z + 3.0);
						// Let the first player know he's been ported
						format(PortMsg, 128, "{00FF00}[ToB] Você foi levado até {FFFF00}%s{00FF00} por {FFFF00}%s", Name, AdminName);
						SendClientMessage(Player1, 0xFFFFFFFF, PortMsg);
					}
					else
					    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Jogador 2 não está online.");
				}
				else
				    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Jogador 1 não está online.");
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Ports the player to the given vehicle
COMMAND:ircarro(playerid, params[])
{
	// Setup local variables
	new Car, Float:x, Float:y, Float:z, PortMsg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/ircarro", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Check if the player has a wanted level of less than 3
			if (GetPlayerWantedLevel(playerid) < 3)
			{
				// Check if the player is not jailed
				if (APlayerData[playerid][PlayerJailed] == 0)
				{
					if (sscanf(params, "i", Car)) SendClientMessage(playerid, 0xFF0000AA, "Use: /ircarro [id]");
					else
					{
						// Get the location of the car
						GetVehiclePos(Car, x, y, z);
						// Port the player to the given location
						SetPlayerPos(playerid, x, y, z + 3.0);
						// Let the player know about it
						format(PortMsg, 128, "A localização do carro é: %4.2f, %4.2f, %4.2f", x, y, z + 3.0);
						SendClientMessage(playerid, 0x00FF00FF, PortMsg);
					}
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode usar o comando /ircarro quando preso.");
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode usar o comando /ircarro quando procurado.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Sets the admin-level of another player
COMMAND:cdradmin(playerid, params[])
{
	// Setup local variables
	new OtherPlayer, Level, Msg[128], Name[24], AdminName[24], OldLevel;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/cdradmin", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			if (sscanf(params, "ui", OtherPlayer, Level)) SendClientMessage(playerid, 0xFF0000AA, "Use: /cdradmin [id] [nivel]");
			else
			{
				// Check if that other player is online
				if (IsPlayerConnected(OtherPlayer))
				{
				    // Get the old level of the other player
				    OldLevel = APlayerData[OtherPlayer][PlayerLevel];
					// Get the playername of the admin
					GetPlayerName(playerid, AdminName, sizeof(AdminName));
					// Also get the name of the player that has been promoted
					GetPlayerName(OtherPlayer, Name, sizeof(Name));
					// Store the level of the player
					APlayerData[OtherPlayer][PlayerLevel] = Level;
					// Let all players know about it
					if (OldLevel != Level)
					{
						// Check if the player has been promoted or demoted
						if (OldLevel < Level)
							format(Msg, 128, "[ToB] O jogador %s foi promovido a %s por %s", Name, AdminLevelName[Level], AdminName);
						if (OldLevel > Level)
							format(Msg, 128, "[ToB] O jogador %s foi rebaixado a %s por %s", Name, AdminLevelName[Level], AdminName);
						SendClientMessageToAll(0x00FF00FF, Msg);
					}
					else
						SendClientMessage(playerid, 0xFF0000FF, "[ToB] Nivel dos outros jogadores não foram alterados,");
				}
				else
				    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Esse jogador não está online.");
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Refuel the player's vehicle
COMMAND:combustivel(playerid, params[])
{
	// Setup local variables
	new vID;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/combustivel", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Check if the player is inside a vehicle
			if (IsPlayerInAnyVehicle(playerid))
			{
			    // Get the vehicleid
			    vID = GetPlayerVehicleID(playerid);
			    // Refuel the vehicle
			    AVehicleData[vID][Fuel] = MaxFuel;
				// Let the player know about it
				SendClientMessage(playerid, 0x00FF00FF, "[ToB] Seu veículo foi abastecido.");
			}
			else
				SendClientMessage(playerid, 0x00FF00FF, "[ToB] Você não está dirigindo um veículo");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Let the player use a jetpack
COMMAND:jetpack(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/jetpack", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
			// Equip the player with a jetpack
			SetPlayerSpecialAction(playerid, 2);
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Paints a car with a paintjob
COMMAND:pintura(playerid, params[])
{
    // Setup local variables
	new paintjobid, vid;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/pintura", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player is the driver of the vehicle
		if (GetPlayerVehicleSeat(playerid) == 0)
		{
			if (sscanf(params, "i", paintjobid)) SendClientMessage(playerid, 0xFF0000AA, "Use: pintura [paintjob 0-2]");
			else
			{
			    // Check if the player entered a correct paintjob-id
			    if ((paintjobid >= 0) && (paintjobid <= 2))
				{
					// Get the vehicle-id
					vid = GetPlayerVehicleID(playerid);
					// Check if the player is the owner of the vehicle
					if (AVehicleData[vid][Owned] == true)
					{
						// Change the paintjob of the player's vehicle
						ChangeVehiclePaintjob(vid, paintjobid);
						// Also save the paintjob for the vehicle
						AVehicleData[vid][PaintJob] = paintjobid + 1;

						// Also set the vehiclecolor to 1 (white), so the paintjob has it's full color
						ChangeVehicleColor(vid, 1, 1);
						// Also save the colors for the vehicle
						AVehicleData[vid][Color1] = 1;
						AVehicleData[vid][Color2] = 1;

						// Let the player pay for the paintjob
						RewardPlayer(playerid, -500, 0);
						// Inform the player about it
						SendClientMessage(playerid, 0x00FF00FF, "[ToB] Você repintou seu veiculo por R$500");
						// Save the player-file (along with the houses and businesses)
						PlayerFile_Save(playerid);
					}
					else
					    SendClientMessage(playerid, 0xFFFFFFFF, "[ToB] Você não é proprietário do veículo.");
				}
				else
				    SendClientMessage(playerid, 0xFF0000AA, "[ToB] Você precisa digitar um paintjob [0-2].");
			}
		}
		else
			SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você deve estar dentro de um veículo que você possui para aplicar um paintjob.");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Re-colors the given vehicle (lets you choose the first color)
COMMAND:cor1(playerid, params[])
{
	// Setup local variables
	new ColorList[1000];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/cor1", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player is the driver of the vehicle
		if (GetPlayerVehicleSeat(playerid) == 0)
		{
			// Check if the player is the owner of the vehicle
			if (AVehicleData[GetPlayerVehicleID(playerid)][Owned] == true)
			{
				// Construct the colorlist
				format(ColorList, sizeof(ColorList), "%s{FFFFFF}%s\n", ColorList, "Preto (remove a paintjob)"); // Color 0
				format(ColorList, sizeof(ColorList), "%s{FFFFFF}%s\n", ColorList, "Branco"); // Color 1

				for (new i = 2; i < sizeof(AVehicleColors); i++)
					format(ColorList, sizeof(ColorList), "%s%s%s\n", ColorList, AVehicleColors[i], "CarColor");

				// Show the dialog with all the colors
				ShowPlayerDialog(playerid, DialogPrimaryCarColor, DIALOG_STYLE_LIST, "Escolha a cor primária:", ColorList, "Selecionar", "Cancelar");
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não é proprietário desse veículo.");
		}
		else
			SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você deve estar dentro de um ve´culo para aplicar uma cor.");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Re-colors the given vehicle (lets you choose the first color)
COMMAND:cor2(playerid, params[])
{
	// Setup local variables
	new ColorList[1000];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/cor2", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player is the driver of the vehicle
		if (GetPlayerVehicleSeat(playerid) == 0)
		{
			// Check if the player is the owner of the vehicle
			if (AVehicleData[GetPlayerVehicleID(playerid)][Owned] == true)
			{
				// Construct the colorlist
				format(ColorList, sizeof(ColorList), "%s{FFFFFF}%s\n", ColorList, "Preto"); // Color 0
				format(ColorList, sizeof(ColorList), "%s{FFFFFF}%s\n", ColorList, "Branco"); // Color 1

				for (new i = 2; i < sizeof(AVehicleColors); i++)
					format(ColorList, sizeof(ColorList), "%s%s%s\n", ColorList, AVehicleColors[i], "CarColor");

				// Show the dialog with all the colors
				ShowPlayerDialog(playerid, DialogSedundaryCarColor, DIALOG_STYLE_LIST, "Escolha a cor secundária:", ColorList, "Selecionar", "Cancelar");
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não é o proprietário desse veículo.");
		}
		else
			SendClientMessage(playerid, 0x00FF00FF, "[ToB] Você deve estar dentro de um ve´culo para aplicar uma cor.");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Starts or stops the engine of your vehicle
COMMAND:motor(playerid, params[])
{
    // Setup local variables
	new vehicleid, engine,lights,alarm,doors,bonnet,boot,objective;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/motor", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Get the player's vehicle
			vehicleid = GetPlayerVehicleID(playerid);

			// Get the current status of the vehicle
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

			// Check if the player is inside a vehicle
			if (vehicleid != 0)
			{
				if (sscanf(params, "i", engine)) SendClientMessage(playerid, 0xFF0000AA, "Use: /motor [0-1]");
				else
				{
					// Set the engine to the value that was passed by the player and leave all other parameters alone
					SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
				}
			}
			else
				SendClientMessage(playerid, 0x00FF00FF, "[ToB] Você precisa estar dentro de um veículo para desligá-lo/ligá-lo.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Sets your numberplate
COMMAND:editarplaca(playerid, params[])
{
    // Setup local variables
	new vehicleid, engine, lights, alarm, doors, bonnet, boot, objective, Plate[32];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/editarplaca", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
			// Get the player's vehicle
			vehicleid = GetPlayerVehicleID(playerid);

			if (vehicleid != 0)
			{
				if (sscanf(params, "s[32]", Plate)) SendClientMessage(playerid, 0xFF0000AA, "Use: /editarplaca [conteúdo]");
				else
				{
					// Set the numberplate
					SetVehicleNumberPlate(vehicleid, Plate);
					// Remove the player from the vehicle
					RemovePlayerFromVehicle(playerid);
					// Respawn the vehicle
					SetVehicleToRespawn(vehicleid);
					// Put the player back in the vehicle
					PutPlayerInVehicle(playerid, vehicleid, 0);
					// Turn on the engine and lights the current status of the vehicle
					GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vehicleid, 1, 1, alarm, doors, bonnet, boot, objective);
				}
			}
			else
				SendClientMessage(playerid, 0x00FF00FF, "[ToB] Você precisa estar em um veículo para alterar a placa.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Asks which vehicle parameter you wanna toggle
COMMAND:painel(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/painel", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
			// Let the player select a weather-type
			ShowPlayerDialog(playerid, DialogCarOption, DIALOG_STYLE_LIST, "Selecione a opção:", "Motor\nFaróis\nAlarme\nPortas\nCapo\nPorta Malas\nObjetivo", "OK", "Cancelar");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Sets the global weather
COMMAND:agua(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/agua", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 4
		if (APlayerData[playerid][PlayerLevel] >= 4)
		{
			// Let the player select a weather-type
			ShowPlayerDialog(playerid, DialogWeather, DIALOG_STYLE_LIST, "Selecione o tipo de água:", "Normal\nTempestade\nFoggy\nEscaldante\nDull, nublado, chuvoso\nSandstorm\nVerde Fog\nEscuro, nublado, marrom\nExtremamente brilhante\nTrevas tóxicos céu nuvens\nPreto e branco", "Selecionar", "Cancelar");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// This command lists all online admins
COMMAND:admins(playerid, params[])
{
	// Setup local variables
	new AdminList[500], Name[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/admins", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Scan through all players
		for (new i; i < MAX_PLAYERS; i++)
		{
			// Check if this player is connected
			if (IsPlayerConnected(i))
			{
				// Get the name of the player
				GetPlayerName(i, Name, sizeof(Name));

				// Check if this player is an RCON admin
				if (IsPlayerAdmin(i))
				{
					// Add all admin players to the list
					format(AdminList, 500, "[ToB] %s%s: %s (id: %i), Level de admin: %i (RCON admin)\n", AdminList, AdminLevelName[APlayerData[i][PlayerLevel]], Name, i, APlayerData[i][PlayerLevel]); // Add the name of the admin-player to the list
					// Re-start the for loop (skipping the remaining code for this iteration)
					continue;
				}

				//Check if that player is an admin (using the PlayerLevel)
				if (APlayerData[i][PlayerLevel] > 0)
				{
					// Add all admin players to the list
					format(AdminList, 500, "%s%s: %s (id: %i), Level de admin: %i\n", AdminList, AdminLevelName[APlayerData[i][PlayerLevel]], Name, i, APlayerData[i][PlayerLevel]); // Add the name of the admin-player to the list
				}
			}
		}

		// Check if there were admin-names added to the list
		if (strlen(AdminList) > 0)
		    ShowPlayerDialog(playerid, DialogNoResponse, DIALOG_STYLE_LIST, "Admins Online:", AdminList, "OK", "Cancelar");
		else
			SendClientMessage(playerid, 0xFF0000FF, "[ToB] Não tem admins online!"); // No admins are online
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command lists all commands for normal players (admin-level 0)
COMMAND:comandos(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/comandos", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		CommandList_Create(playerid); // Create a list of commands (only the first 4 commands) and show the dialog
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

COMMAND:comboio(playerid, params[])
{
	// Setup local variables
	new ConvoyList[750], Name[24], NumMembers, ConvoyStatus[10];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/comboio", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Create the list of convoys with all their data
		for (new i; i < MAX_CONVOYS; i++)
		{
		    // Check if this is an empty convoy (not created yet by a player)
			if (AConvoys[i][Status] == CONVOY_EMPTY)
			{
				// Setup data for an empty convoy (one which hasn't been chosen yet)
				NumMembers = 0;
				format(Name, 24, "nenhum");
				format(ConvoyStatus, 10, "vazio");
			}
			else
			{
				// Get the name of the convoy-leader
				GetPlayerName(AConvoys[i][Members][0], Name, sizeof(Name));
				// Calculate the members in the convoy
				NumMembers = Convoy_CountMembers(i);
				// Set the status of the convoy
				switch (AConvoys[i][Status])
				{
					case CONVOY_OPEN: format(ConvoyStatus, 10, "Aberto");
					case CONVOY_FULL: format(ConvoyStatus, 10, "Cheio");
					case CONVOY_CLOSED: format(ConvoyStatus, 10, "Fechado");
				}
			}

			// Put all data together to form the content of the entire dialog
			format(ConvoyList, sizeof(ConvoyList), "%sLíder: {00FF00}%s{FFFFFF}, membros: {FF0000}%i{FFFFFF}, Status: {00FF00}%s{FFFFFF}\n", ConvoyList, Name, NumMembers, ConvoyStatus);
		}

		// Show the dialog
		ShowPlayerDialog(playerid, DialogSelectConvoy, DIALOG_STYLE_LIST, "Selecione o comboio:", ConvoyList, "Selecionar", "Cancelar");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Allows the leader to kick a member from the convoy
COMMAND:comboiokick(playerid, params[])
{
	// Setup local variables
	new Convoy, LeaderID, OtherPlayer, LeaderName[24], MemberName[24], Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/comboiokick", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		Convoy = APlayerData[playerid][ConvoyID]; // Get the convoy of the player
		LeaderID = AConvoys[Convoy][Members][0]; // Get the leader of his convoy

		// Check if this player is part of a convoy
		if (APlayerData[playerid][InConvoy] == true)
		{
			// Check if this player is the leader of the convoy
			if (LeaderID == playerid)
			{
				if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "Use: /comboiokick [id]");
				else
				{
					// Check if that other player is part of the convoy
					if ((APlayerData[OtherPlayer][InConvoy] == true) && (APlayerData[OtherPlayer][ConvoyID] == Convoy))
					{
					    // Kick the other player from the convoy
						Convoy_Leave(OtherPlayer);
						// Get the names of the leader and member
						GetPlayerName(playerid, LeaderName, sizeof(LeaderName));
						GetPlayerName(OtherPlayer, MemberName, sizeof(MemberName));
						// Inform the leader that he has kicked the other player
						format(Msg, 128, "[ToB] Você kickou {0000FF}%s{00FF00} do comboio.", MemberName);
						SendClientMessage(playerid, 0x00FF00FF, Msg);
						// Inform the leader that he has kicked the other player
						format(Msg, 128, "[ToB] O líder {0000FF}%s{00FF00} te kickou do comboio.", LeaderName);
						SendClientMessage(OtherPlayer, 0x00FF00FF, Msg);
					}
					else
					    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode kickar um jogador que não faz parte do seu comboio.");
				}
			}
			else
			    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa ser líder para kickar um membro de um comboio.");
		}
		else
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa ser líder para kickar um membro de um comboio.");
	}
	else
		return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Allows a convoy-member to leave the convoy
COMMAND:comboiosair(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/comboiosair", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if this player is part of a convoy
		if (APlayerData[playerid][InConvoy] == true)
		{
		    // Kick the other player from the convoy
			Convoy_Leave(playerid);
			// Inform the player that he left the convoy
			SendClientMessage(playerid, 0x00FF00FF, "[ToB] Você saiu do comboio.");
		}
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Allows the leader to cancel a convoy
COMMAND:comboiocancelar(playerid, params[])
{
	// Setup local variables
	new Convoy, LeaderID;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/comboiocancelar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		Convoy = APlayerData[playerid][ConvoyID]; // Get the convoy of the player
		LeaderID = AConvoys[Convoy][Members][0]; // Get the leader of his convoy

		// Check if this player is part of a convoy
		if (APlayerData[playerid][InConvoy] == true)
		{
			// Check if this player is the leader of the convoy
			if (LeaderID == playerid)
				Convoy_Cancel(Convoy); // Cancel the convoy, kicking every other member from it
			else
			    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa ser líder do comboio para cancelá-lo.");
		}
		else
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa ser líder do comboio para cancelá-lo.");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Displays all members in the convoy
COMMAND:comboiomembros(playerid, params[])
{
	// Setup local variables
	new Name[24], MemberList[1000], Convoy;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/comboiomembros", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the member is in a convoy
		if (APlayerData[playerid][InConvoy] == true)
		{
			// Get the convoyID of the member
			Convoy = APlayerData[playerid][ConvoyID];

			// Loop through all members
			for (new i; i < CONVOY_MAX_MEMBERS; i++)
			{
			    if (AConvoys[Convoy][Members][i] != -1) // Check if this member-spot is occupied
				{
					// Get the name of the member
					GetPlayerName(AConvoys[Convoy][Members][i], Name, sizeof(Name));
					// Add the membernames to the list
					format(MemberList, 1000, "%s%s\n", MemberList, Name);
				}
			}

			// Show the dialog
			ShowPlayerDialog(playerid, DialogConvoyMembers, DIALOG_STYLE_LIST, "Membros do comboio", MemberList, "OK", "Cancelar");
		}
		else
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não é um mmembro de um comboio.");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Displays the statictics of the player
COMMAND:status(playerid, params[])
{
	// Setup local variables
	new StatsMsg[1000], Name[24], TitleMsg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/status", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Construct the stats
		format(StatsMsg, 1000, "KM rodados: {00FF00}%f{FFFFFF}\n", (APlayerData[playerid][StatsMetersDriven] / 1000));
		format(StatsMsg, 1000, "%sTrabalhos de Caminhoneiro concluídos: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsTruckerJobs]);
		format(StatsMsg, 1000, "%sTrabalhos em Comboio concluídos: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsConvoyJobs]);
		format(StatsMsg, 1000, "%sRotas de Ônibus concluídas: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsBusDriverJobs]);
		format(StatsMsg, 1000, "%sTrabalhos de Voo concluídos: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsPilotJobs]);
		format(StatsMsg, 1000, "%sTrabalhos nos Correios concluídos: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsCourierJobs]);
		format(StatsMsg, 1000, "%sTrabalhos no DNIT concluídos: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsRoadworkerJobs]);
		format(StatsMsg, 1000, "%sTrabalhos de Mecânico concluídos: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsAssistance]);
		format(StatsMsg, 1000, "%sTrabalhos na Máfia concluídos: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsMafiaJobs]);
		format(StatsMsg, 1000, "%sCargas-Máfia roubadas e entregadas: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsMafiaStolen]);
		format(StatsMsg, 1000, "%sJogadores multados: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsPoliceFined]);
		format(StatsMsg, 1000, "%sJogadores presos: {00FF00}%i{FFFFFF}\n", StatsMsg, APlayerData[playerid][StatsPoliceJailed]);
		// Get the player's name
		GetPlayerName(playerid, Name, sizeof(Name));
		// Construct the title for the dialog
		format(TitleMsg, 128, "Estatisticas para %s:", Name);

		// Show the dialog
		ShowPlayerDialog(playerid, DialogStats, DIALOG_STYLE_LIST, TitleMsg, StatsMsg, "OK", "Cancelar");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Restarts the server
COMMAND:gmx(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/gmx", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			// Let everyone know that the server will be restarted in 2 minutes
			GameTextForAll("Reiniciando o servidor em 2 minutos!", 5000, 3);
			SendClientMessageToAll(0xA0A0A0, "[ToB] GMX em 2 minutos!");
			// Start the next timer which warns the players again that server will be restarted in 1 minute
			SetTimer("Timer_Restart_WarnPlayers", 1000 * 60, false);
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

forward Timer_Restart_WarnPlayers();
public Timer_Restart_WarnPlayers()
{
	// Let everyone know that the server will be restarted in 1 minutes
	GameTextForAll("Reiniciando servidor em 1 minuto!", 5000, 3);
	SendClientMessageToAll(0xA0A0A0, "[ToB] GMX em 1 minuto!");
	// Start the next timer
	SetTimer("Timer_Restart_Kick", 1000 * 60, false);
	// Change the hostname of the server and it's password
	SendRconCommand("hostname Pending Restart");
	SendRconCommand("password loafkagakggoagka");

	return 1;
}

forward Timer_Restart_Kick();
public Timer_Restart_Kick()
{
	// Let everyone know that the server is kicking all players before restarting
	GameTextForAll("Servidor reiniciando: Todos os players kickados!", 5000, 3);
	// Kick all players
	for(new i; i < MAX_PLAYERS; i++)
		Kick(i);

	// Start the next timer that will restart the server
	SetTimer("Timer_Restart_Reboot", 1000 * 5, false);

	return 1;
}

forward Timer_Restart_Reboot();
public Timer_Restart_Reboot()
{
	new HostCommand[128];

	// Restart the server
	SendRconCommand("gmx");
	// Change the hostname and password again
	format(HostCommand, 128, "hostname %s", GameModeName);
	SendRconCommand(HostCommand);
	SendRconCommand("password 0");

	return 1;
}



// This command allows you to create a speedcamera
COMMAND:criarradar(playerid, params[])
{
	// Setup local variables
	new Float:x, Float:y, Float:z, Float:Angle, MaxSpeed, file[100], File:PFile, LineForFile[100], Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/criarradar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			if (sscanf(params, "i", MaxSpeed)) SendClientMessage(playerid, 0xFF0000AA, "Use: /criarradar [Vel.Max]");
			else
			{
				// Get player's position and facing angle
				GetPlayerPos(playerid, x, y, z);
				GetPlayerFacingAngle(playerid, Angle);
				z = z - 1.0; // Adjust camera Z-coordinate 1m lower than normal (otherwise the camera floats in the air)

				// Move the player a bit, otherwise he could get stuck inside the camera-object
				SetPlayerPos(playerid, x, y + 1.0, z + 1.0);

				// Save the camera to a file
				for (new CamID; CamID < MAX_CAMERAS; CamID++)
				{
					// Check if this index is free
					if (ACameras[CamID][CamSpeed] == 0)
					{
					    // Setup this camera (create the objects and store the data)
                        SetupSpeedCamera(CamID, x, y, z, Angle, MaxSpeed);

					    // Save the file
						format(file, sizeof(file), CameraFile, CamID); // Construct the complete filename for this camera-file

						PFile = fopen(file, io_write); // Open the camera-file for writing

						format(LineForFile, 100, "CamX %f\r\n", x);
						fwrite(PFile, LineForFile); // And save it to the file
						format(LineForFile, 100, "CamY %f\r\n", y);
						fwrite(PFile, LineForFile); // And save it to the file
						format(LineForFile, 100, "CamZ %f\r\n", z);
						fwrite(PFile, LineForFile); // And save it to the file
						format(LineForFile, 100, "CamAngle %f\r\n", Angle);
						fwrite(PFile, LineForFile); // And save it to the file
						format(LineForFile, 100, "CamSpeed %i\r\n", MaxSpeed);
						fwrite(PFile, LineForFile); // And save it to the file

						fclose(PFile); // Close the file

						// Let the player know he created a new camera
						format(Msg, 128, "Você criou o radar ID: %i", CamID);
						SendClientMessage(playerid, 0x00FF00FF, Msg);

						// Exit the function
						return 1;
					}
				}

				// In case all camera-slots are occupied (100 camera's have been created already), let the player know about it
				format(Msg, 128, "{FF0000}[ToB] Você não pode criar mais de %i radares.", MAX_CAMERAS);
				SendClientMessage(playerid, 0xFFFFFFFF, Msg);
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command allows you to delete a speedcamera
COMMAND:deletarradar(playerid, params[])
{
	// Setup local variables
	new file[100], Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/deletarradar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
				// Loop through all camera's
			for (new CamID; CamID < MAX_CAMERAS; CamID++)
			{
				// Check if this index is used
				if (ACameras[CamID][CamSpeed] != 0)
				{
					// Check if the player is in range of the camera
					if (IsPlayerInRangeOfPoint(playerid, 5.0, ACameras[CamID][CamX], ACameras[CamID][CamY], ACameras[CamID][CamZ]))
					{
					    // Delete the file
						format(file, sizeof(file), CameraFile, CamID); // Construct the complete filename for this camera-file
						if (fexist(file)) // Make sure the file exists
							fremove(file); // Delete the file

						// Delete both camera objects
					    DestroyObject(ACameras[CamID][CamObj1]);
					    DestroyObject(ACameras[CamID][CamObj2]);
						// Also clear the data from memory
					    ACameras[CamID][CamX] = 0.0;
					    ACameras[CamID][CamY] = 0.0;
					    ACameras[CamID][CamZ] = 0.0;
					    ACameras[CamID][CamAngle] = 0.0;
					    ACameras[CamID][CamSpeed] = 0;
                        ACameras[CamID][CamObj1] = 0;
                        ACameras[CamID][CamObj2] = 0;

						// Let the player know he deleted a camera
						format(Msg, 128, "[ToB] Você deletou o radar %i", CamID);
						SendClientMessage(playerid, 0x00FF00FF, Msg);

						// Exit the function
						return 1;
					}
				}
			}

			// In case the player wasn't near a speedcamera, inform him about it
			SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Esteja em um radar para deletá-lo");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// This command ports a player to the player who executed the command
COMMAND:trazer(playerid, params[])
{
	// Setup local variables
	new OtherPlayer, Float:x, Float:y, Float:z, PortMsg[128], IntID, WorldID, Name[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/trazer", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "Use: /trazer [id]");
			else
			{
				// Check if that other player is online
				if (IsPlayerConnected(OtherPlayer))
				{
					// Get the name of the other player
					GetPlayerName(OtherPlayer, Name, sizeof(Name));
					// Get the location of the player
					GetPlayerPos(playerid, x, y, z);
					IntID = GetPlayerInterior(playerid);
					WorldID = GetPlayerVirtualWorld(playerid);
					// Port the other player to this player
					SetPlayerVirtualWorld(OtherPlayer, WorldID);
					SetPlayerInterior(OtherPlayer, IntID);
					SetPlayerPos(OtherPlayer, x, y, z + 3.0);
					// Let the player know about it
					format(PortMsg, 128, "{00FF00}[ToB] Você trouxe {FFFF00}%s{00FF00} até você.", Name);
					SendClientMessage(playerid, 0xFFFFFFFF, PortMsg);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Esse jogador não está online.");
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command deleted all vehicles that are spawned using /car, /plane, /bike, /trailer
COMMAND:limparcarros(playerid, params[])
{
	// Setup local variables
	new CarsDeleted, Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/limparcarros", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
		    // Loop through all vehicles
		    for (new vid; vid < 2000; vid++)
		    {
				// Check if this vehicle exists (check the model), otherwise all empty slots are processed as well
				if (AVehicleData[vid][Model] != 0)
				{
					// Check if the vehicle is NOT a static vehicle
					if (AVehicleData[vid][StaticVehicle] == false)
					{
						// Check if the vehicle is NOT owned by anybody (this leaves all vehicles spawned with /car, /trailer, /plane)
						if (AVehicleData[vid][Owned] == false)
						{
							// Count the cars that have been deleted
							CarsDeleted++;
							// Delete the vehicle and clear the data
							DestroyVehicle(vid);
							AVehicleData[vid][Owned] = false;
							AVehicleData[vid][Owner] = 0;
							AVehicleData[vid][Model] = 0;
							AVehicleData[vid][PaintJob] = 0;
							for (new i; i < 14; i++)
							    AVehicleData[vid][Components][i] = 0;
							AVehicleData[vid][SpawnX] = 0.0;
							AVehicleData[vid][SpawnY] = 0.0;
							AVehicleData[vid][SpawnZ] = 0.0;
							AVehicleData[vid][SpawnRot] = 0.0;
							AVehicleData[vid][BelongsToHouse] = 0;
						}
					}
				}
		    }

			// Let the player know how many vehicles have been cleaned up
			format(Msg, 128, "{00FF00}[ToB] Total de carros limpos da cidade: {FFFF00}%i", CarsDeleted);
			SendClientMessage(playerid, 0xFFFFFFFF, Msg);
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command allows the player to call for assistance
COMMAND:assistencia(playerid, params[])
{
	// Setup local variables
	new bool:AssistOnline = false, Msg[128], Name[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/assistencia", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Get the player's name
		GetPlayerName(playerid, Name, sizeof(Name));
		// Preset the message that needs to be sent to assistance players
		format(Msg, 128, "{00FF00}O jogador {FFFF00}%s{00FF00} precisa de assistência mecânica.", Name);

		// Check if there is at least one assistance player online
		for (new i; i < MAX_PLAYERS; i++)
		{
			// Check if this player is connected
			if (IsPlayerConnected(i))
			{
				// Check if this player is assistance class
				if (APlayerData[i][PlayerClass] == ClassAssistance)
				{
					// Set the flag to indicate that at least one assistance player is online
				    AssistOnline = true;
				    // Send the assistance player a message to inform him who needs assistance
				    SendClientMessage(i, 0xFFFFFFFF, Msg);
				}
			}
		}

		// Check if there is at least one assistance player online
		if (AssistOnline == true)
		{
			// Set yourself as "AssistanceNeeded"
			APlayerData[playerid][AssistanceNeeded] = true;
			// Let the player know he called for assistance
			SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Você ja pediu ajuda.");
		}
		else // No assistance is online
		{
			// Check if the player is the driver of a vehicle
			if (GetPlayerVehicleSeat(playerid) == 0)
			{
				// Fully repair the vehicle (damage value and bodywork)
				RepairVehicle(GetPlayerVehicleID(playerid));
				// Also re-fuel the vehicle
				AVehicleData[GetPlayerVehicleID(playerid)][Fuel] = MaxFuel;
				// Let the player pay for the repairs and refuel (default $2000)
				RewardPlayer(playerid, -2000, 0);
				// Let the player know he spent $2000 for auto-repair because there were no assistance players online
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Seu veículo foi reparado e abastecido por R$2000.");
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Não hà mecânico online.");
			}
		}
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command adds nitro to the player's vehicle
COMMAND:nos(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/nos", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Check if the player is the driver of a vehicle
			if (GetPlayerVehicleSeat(playerid) == 0)
			{
				// Check if the vehicle isn't owned (owned vehicle's need to buy nitro at mod garages)
				if (AVehicleData[GetPlayerVehicleID(playerid)][Owned] == false)
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1010); // Add nitro to the player's vehicle
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command let's an admin spectate another player
COMMAND:espiar(playerid, params[])
{
	// Setup local variables
	new OtherPlayer, Name[24], Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/espiar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "Use: /espiar [id]");
			else
			{
				// Check if that other player is online
				if (IsPlayerConnected(OtherPlayer))
				{
					// Get the player's name
					GetPlayerName(OtherPlayer, Name, sizeof(Name));

				    // Turn spectating on
				    TogglePlayerSpectating(playerid, 1);

					// Check if the other player is driving a vehicle
					if (GetPlayerVehicleSeat(OtherPlayer) == -1)
					{
						// The other player is on foot, so spectate him
						PlayerSpectatePlayer(playerid, OtherPlayer);
						SetPlayerInterior(playerid, GetPlayerInterior(OtherPlayer));
						APlayerData[playerid][SpectateID] = OtherPlayer;
						APlayerData[playerid][SpectateType] = ADMIN_SPEC_TYPE_PLAYER;
					}
					else
					{
						// The other player is in a vehicle, so spectate the vehicle
						PlayerSpectateVehicle(playerid, GetPlayerVehicleID(OtherPlayer));
						APlayerData[playerid][SpectateID] = OtherPlayer;
						APlayerData[playerid][SpectateVehicle] = GetPlayerVehicleID(OtherPlayer);
						APlayerData[playerid][SpectateType] = ADMIN_SPEC_TYPE_VEHICLE;
					}

					format(Msg, 128, "{00FF00}[ToB] Você está espiando {FFFF00}%s.", Name);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Esse jogador não está online.");
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command ends the spectate mode
COMMAND:pararespiar(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/pararespiar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Check if the player is spectating
			if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
			{
			    TogglePlayerSpectating(playerid, 0);
				APlayerData[playerid][SpectateID] = -1;
				APlayerData[playerid][SpectateVehicle] = -1;
				APlayerData[playerid][SpectateType] = ADMIN_SPEC_TYPE_NONE;
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não está espiando.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}



// Lets the player add new businesses
COMMAND:criarempresa(playerid, params[])
{
	// Setup local variables
	new BusinessList[2000];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/criarempresa", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			// Check if the player isn't inside a vehicle
			if (GetPlayerVehicleSeat(playerid) == -1)
			{
				// Construct the list of businesses
				for (new BusType = 1; BusType < sizeof(ABusinessInteriors); BusType++)
				{
				    format(BusinessList, sizeof(BusinessList), "%s%s\n", BusinessList, ABusinessInteriors[BusType][InteriorName]);
				}

				// Let the player choose a business-type via a dialog
				ShowPlayerDialog(playerid, DialogCreateBusSelType, DIALOG_STYLE_LIST, "Escolha o tipo de empresa:", BusinessList, "Selecionar", "Cancelar");
			}
			else
			    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode criar uma empresa e dentro de um veículo.");
		}
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command lets the player delete a business
COMMAND:deletarempresa(playerid, params[])
{
	// Setup local variables
	new file[100], Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/deletarempresa", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			// Make sure the player isn't inside a vehicle
			if (GetPlayerVehicleID(playerid) == 0)
			{
				// Loop through all player-owned businesses
				for (new BusID = 1; BusID < MAX_BUSINESS; BusID++)
				{
					// Check if the business exists
					if (ABusinessData[BusID][PickupID] != 0)
					{
						// Check if the business has no owner
						if (ABusinessData[BusID][Owned] == false)
						{
							// Check if the player is in range of the business-pickup
							if (IsPlayerInRangeOfPoint(playerid, 2.5, ABusinessData[BusID][BusinessX], ABusinessData[BusID][BusinessY], ABusinessData[BusID][BusinessZ]))
							{
								// Clear all data of the business
	                            ABusinessData[BusID][BusinessName] = 0;
	                            ABusinessData[BusID][BusinessX] = 0.0;
	                            ABusinessData[BusID][BusinessY] = 0.0;
	                            ABusinessData[BusID][BusinessZ] = 0.0;
	                            ABusinessData[BusID][BusinessType] = 0;
	                            ABusinessData[BusID][BusinessLevel] = 0;
	                            ABusinessData[BusID][LastTransaction] = 0;
	                            ABusinessData[BusID][Owned] = false;
	                            ABusinessData[BusID][Owner] = 0;
								// Destroy the mapicon, 3DText and pickup for the house
								DestroyDynamicPickup(ABusinessData[BusID][PickupID]);
								DestroyDynamicMapIcon(ABusinessData[BusID][MapIconID]);
								DestroyDynamic3DTextLabel(ABusinessData[BusID][DoorText]);
	                            ABusinessData[BusID][PickupID] = 0;
	                            ABusinessData[BusID][MapIconID] = 0;

								// Delete the business-file
								format(file, sizeof(file), BusinessFile, BusID); // Construct the complete filename for this business-file
								if (fexist(file)) // Make sure the file exists
									fremove(file); // Delete the file

								// Also let the player know he deleted the business
								format(Msg, 128, "{00FF00}[ToB] Você deletou a empresa ID: {FFFF00}%i", BusID);
								SendClientMessage(playerid, 0xFFFFFFFF, Msg);

								// Exit the function
								return 1;
							}
						}
					}
				}

				// There was no house in range, so let the player know about it
				SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Esteja na porta da empresa que deseja deletar.");
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode deletar uma empresa de dentro de um veículo.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command lets the player buy a business when he's standing in range of a business that isn't owned yet
COMMAND:comprarempresa(playerid, params[])
{
	// Setup local variables
	new Msg[128], BusType;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/comprarempresa", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Make sure the player isn't inside a vehicle
		if (GetPlayerVehicleID(playerid) == 0)
		{
			// Check if the player is near a business-pickup
			for (new i = 1; i < sizeof(ABusinessData); i++)
			{
				// Check if this business is created (it would have a valid pickup in front of the door)
				if (ABusinessData[i][PickupID] != 0)
				{
					// Check if the player is in range of the business-pickup
					if (IsPlayerInRangeOfPoint(playerid, 2.5, ABusinessData[i][BusinessX], ABusinessData[i][BusinessY], ABusinessData[i][BusinessZ]))
					{
					    // Check if the business isn't owned yet
					    if (ABusinessData[i][Owned] == false)
					    {
							// Get the type of business
							BusType = ABusinessData[i][BusinessType];
					        // Check if the player can afford this type of business business
					        if (APlayerData[playerid][PlayerMoney] >= ABusinessInteriors[BusType][BusPrice])
					            Business_SetOwner(playerid, i); // Give ownership of the business to the player
					        else
					            SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode pagar pela empresa."); // The player cannot afford this business
					    }
					    else
					    {
					        // Let the player know that this business is already owned by a player
							format(Msg, 128, "{FF0000}[ToB] Este negócio ja pertence à {00FF00}%s{FFFFFF}.", ABusinessData[i][Owner]);
							SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					    }

						// The player was in range of a business-pickup, so stop searching for the other business pickups
					    return 1;
					}
				}
				else
				    return 1; // If there are no more houses (no more pickup-id's found), stop searching
			}

			// All businesses have been processed, but the player wasn't in range of any business-pickup, let him know about it
			SendClientMessage(playerid, 0xFF0000FF, "[ToB] Para comprar uma empresa você precisa estar no pickup da mesma.");
		}
		else
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode comprar uma empresa de dentro de um veículo.");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command opens a menu when you're inside your business to allow to access the options of your business
COMMAND:menuempresa(playerid, params[])
{
	// Setup local variables
	new OptionsList[200], DialogTitle[200];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/menuempresa", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player is inside a business
		if (APlayerData[playerid][CurrentBusiness] != 0)
		{
			format(DialogTitle, sizeof(DialogTitle), "Selecione a opção para: %s", ABusinessData[APlayerData[playerid][CurrentBusiness]][BusinessName]);

			format(OptionsList, sizeof(OptionsList), "%sMudar nome da empresa\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sAtualizar empresa\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sRetirar ganhos da empresa\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sVender empresa\n", OptionsList);
			format(OptionsList, sizeof(OptionsList), "%sSair da empresa\n", OptionsList);
			// Show the businessmenu
			ShowPlayerDialog(playerid, DialogBusinessMenu, DIALOG_STYLE_LIST, DialogTitle, OptionsList, "Selecionar", "Cancelar");
		}
		else
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não está na empresa.");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command teleports you to your selected business
COMMAND:irempresa(playerid, params[])
{
	// Setup local variables
	new BusinessList[1000], BusID, BusType, Earnings;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/irempresa", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player is not jailed
		if (APlayerData[playerid][PlayerJailed] == 0)
		{
			// Check if the player has a wanted level of less than 3
			if (GetPlayerWantedLevel(playerid) < 3)
			{
				// Check if the player is not inside a vehicle
				if (GetPlayerVehicleID(playerid) == 0)
				{
					// Ask to which business the player wants to port
					for (new i; i < MAX_BUSINESSPERPLAYER; i++)
					{
						// Get the business-id
					    BusID = APlayerData[playerid][Business][i];

						// Check if this businessindex is occupied
						if (BusID != 0)
						{
							// Get the business-type
							BusType = ABusinessData[BusID][BusinessType];
							Earnings = (BusinessTransactionTime - ABusinessData[BusID][LastTransaction]) * ABusinessInteriors[BusType][BusEarnings] * ABusinessData[BusID][BusinessLevel];
							format(BusinessList, 1000, "%s{00FF00}%s{FFFFFF} (ganhos: $%i)\n", BusinessList, ABusinessData[BusID][BusinessName], Earnings);
						}
						else
							format(BusinessList, 1000, "%s{FFFFFF}%s{FFFFFF}\n", BusinessList, "Slot vazio");
					}
					ShowPlayerDialog(playerid, DialogGoBusiness, DIALOG_STYLE_LIST, "Escolha a empresa para ir:", BusinessList, "Selecionar", "Cancelar");
				}
				else
					SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você precisa estar a pé na porta da empresa.");
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não pode usar o comando /irempresa quando procurado");
		}
		else
		    SendClientMessage(playerid, 0xFF0000FF, "[ToB] Você não pode usar o comando /irempresa quando preso.");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Mutes a player (he cannot talk anymore)
COMMAND:calar(playerid, params[])
{
	// Setup local variables
	new Msg[128], Name[24], AdminName[24], Reason[128], OtherPlayer;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/calar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			if (sscanf(params, "us[128]", OtherPlayer, Reason)) SendClientMessage(playerid, 0xFF0000AA, "Use: /calar [id] [motivo]");
			else
			{
				// Check if the otherplayer is online
				if (IsPlayerConnected(OtherPlayer))
				{
					// Get the player-names
					GetPlayerName(playerid, AdminName, sizeof(AdminName));
					GetPlayerName(OtherPlayer, Name, sizeof(Name));
					// Mute the other player
					APlayerData[OtherPlayer][Muted] = true;
					// Let the other player know that he has been muted
					format(Msg, 128, "{FF0000}[ToB] Você foi calado por {FFFF00}%s {FF0000}. Motivo: {FFFF00}%s", AdminName, Reason);
					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);
					// Let the admin know who he has muted
					format(Msg, 128, "{00FF00}[ToB] Você calou {FFFF00}%s.", Name);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					// Save the player-stats
					PlayerFile_Save(OtherPlayer);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] O jogador não está online.");
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Un-mutes a player (he cannot talk anymore)
COMMAND:descalar(playerid, params[])
{
	// Setup local variables
	new Msg[128], Name[24], AdminName[24], OtherPlayer;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/descalar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "Use: /descalar [id]");
			else
			{
				// Check if the otherplayer is online
				if (IsPlayerConnected(OtherPlayer))
				{
					// Get the player-names
					GetPlayerName(playerid, AdminName, sizeof(AdminName));
					GetPlayerName(OtherPlayer, Name, sizeof(Name));
					// Un-mute the other player
					APlayerData[OtherPlayer][Muted] = false;
					// Let the other player know that he has been un-muted
					format(Msg, 128, "{FF0000}[ToB] Você foi descalado por {FFFF00}%s.", AdminName);
					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);
					// Let the admin know who he has un-muted
					format(Msg, 128, "{00FF00}[ToB] Você descalou {FFFF00}%s.", Name);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					// Save the player-stats
					PlayerFile_Save(OtherPlayer);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}That player isn't online");
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Let's the admins see which players are still muted
COMMAND:mudos(playerid, params[])
{
	// Setup local variables
	new PlayerList[1000], Name[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/mudos", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Loop through all players
			for (new i; i < MAX_PLAYERS; i++)
			{
				// Check if that player is online
				if (IsPlayerConnected(i))
				{
				    if (APlayerData[i][Muted] == true)
					{
						// Get the player's name
						GetPlayerName(i, Name, sizeof(Name));
						// Add his name and ID to the list
						format(PlayerList, sizeof(PlayerList), "%s%s (ID: %i)\n", PlayerList, Name, i);
					}
				}
			}

			// Show the list of muted players to the admin
			if (strlen(PlayerList) != 0)
				ShowPlayerDialog(playerid, DialogNoResponse, DIALOG_STYLE_LIST, "Jogadores calados:", PlayerList, "OK", "Cancelar");
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}Não ha jogadores calados.");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Freeze a player (he cannot move anymore)
COMMAND:congelar(playerid, params[])
{
	// Setup local variables
	new Msg[128], Name[24], AdminName[24], Reason[128], OtherPlayer, Duration;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/congelar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			if (sscanf(params, "uis[128]", OtherPlayer, Duration, Reason)) SendClientMessage(playerid, 0xFF0000AA, "Use: /congelar [id] [tempo] [motivo]");
			else
			{
				// Check if the otherplayer is online
				if (IsPlayerConnected(OtherPlayer))
				{
					// Get the player-names
					GetPlayerName(playerid, AdminName, sizeof(AdminName));
					GetPlayerName(OtherPlayer, Name, sizeof(Name));
					// Store the duration for the freeze, freeze him and start the frozentimer
					APlayerData[OtherPlayer][PlayerFrozen] = Duration;
					TogglePlayerControllable(OtherPlayer, 0);
					SetTimerEx("Player_FreezeTimer", 1000, true, "i", OtherPlayer);
					// Let the other player know that he has been muted
					format(Msg, 128, "{FF0000}[ToB] Você foi congelado por {FFFF00}%s {FF0000}. Motivo: {FFFF00}%s.", AdminName, Reason);
					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);
					// Let the admin know who he has muted
					format(Msg, 128, "{00FF00}[ToB] Você congelou {FFFF00}%s.", Name);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					// Save the player-stats
					PlayerFile_Save(OtherPlayer);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Esse jogador não está online.");
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Transfer money to another player
COMMAND:dardinheiro(playerid, params[])
{
	// Setup local variables
	new Msg[128], Name[24], OtherName[24], OtherPlayer, Money;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/dardinheiro", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		if (sscanf(params, "ui", OtherPlayer, Money)) SendClientMessage(playerid, 0xFF0000AA, "Use: /dardinheiro [id] [quantia]");
		else
		{
			// Check if the otherplayer is online
			if (IsPlayerConnected(OtherPlayer))
			{
				// Get the player-names
				GetPlayerName(playerid, Name, sizeof(Name));
				GetPlayerName(OtherPlayer, OtherName, sizeof(OtherName));

				// Check if the money has a positive value (to prevent stealing money using negative values)
				if (Money > 0)
				{
					// Check if the player has enough money
					if (APlayerData[playerid][PlayerMoney] >= Money)
					{
						// Transfer the money
						RewardPlayer(playerid, -Money, 0);
						RewardPlayer(OtherPlayer, Money, 0);
						// Let the other player know that he has received money
						format(Msg, 128, "{00FF00}[ToB] Você recebeu {FFFF00}R$%i{00FF00} de {FFFF00}%s.", Money, Name);
						SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);
						// Let the player know he gave money to somebody else
						format(Msg, 128, "{00FF00}[ToB] Você deu {FFFF00}R$%i{00FF00} para {FFFF00}%s.", Money, OtherName);
						SendClientMessage(playerid, 0xFFFFFFFF, Msg);
						// Save the player-stats
						PlayerFile_Save(playerid);
						PlayerFile_Save(OtherPlayer);
					}
					else
					    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você não tem dinheiro suficiente.");
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você deve usar valores maiores que 0.");
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Esse jogador não está online.");
		}
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Respawns the given vehicle
COMMAND:resetarcarro(playerid, params[])
{
	// Setup local variables
	new vid, Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/resetarcarro", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			if (sscanf(params, "i", vid)) SendClientMessage(playerid, 0xFF0000AA, "Use: /resetarcarro [id]");
			else
			{
				// Check if the vehicle-id is valid
				if ((vid > 0) && (vid < 2000))
				{
					// Check if the vehicle exists
					if (AVehicleData[vid][Model] != 0)
					{
					    // Force the vehicle to respawn
						SetVehicleToRespawn(vid);
						// Let the player know he respawned the vehicle
						format(Msg, 128, "{00FF00}[ToB] Você respawnou o veiculo {FFFF00}%i", vid);
						SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					}
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] O ID do veiculo deve ser entre 1 e 1999.");
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Creates a spikestrip (can only be used by police players)
COMMAND:tapete(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/tapete", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player if a police player
		if (APlayerData[playerid][PlayerClass] == ClassPolice)
		{
			// Check if the player is on foot
			if (GetPlayerVehicleSeat(playerid) == -1)
			{
				// Try to create a spikestrip
				SpikeStrip_Create(playerid);
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}Você deve estar apé para usar os pregos.");
		}
		else
			return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command ejects a player from his vehicle
COMMAND:ejetar(playerid, params[])
{
	// Setup local variables
	new Name[24], AdminName[24], Msg[128], OtherPlayer;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/ejetar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 2
		if (APlayerData[playerid][PlayerLevel] >= 2)
		{
			if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "Use: /ejetar [id]");
			else
			{
			    // Check if the player is logged in
				if (APlayerData[OtherPlayer][LoggedIn] == true)
				{
					// Check if the other player is driving a vehicle
					if (GetPlayerVehicleSeat(OtherPlayer) != -1)
					{
						// Get the names of the players
						GetPlayerName(playerid, AdminName, sizeof(AdminName));
						GetPlayerName(OtherPlayer, Name, sizeof(Name));
						// Eject the player from the vehicle
						RemovePlayerFromVehicle(OtherPlayer);
						// Let the player know he's been ejected from his vehicle
						format(Msg, 128, "{FF0000}[ToB] Você foi ejetado do veículo de {FFFF00}%s", AdminName);
						SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);
						// Inform the admin that he ejected the player
						format(Msg, 128, "{00FF00}[ToB] Você ejetou {FFFF00}%s{00FF00} do veículo.", Name);
						SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					}
					else
					    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] O jogador não está dentro de um veículo.");
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Esse jogador não está conectado.");
			}
		}
		else
			return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command lets you talk only to players of the same class
COMMAND:cv(playerid, params[])
{
	// Setup local variables
	new Name[24], Msg[128], Message[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/cv", params);

	// Get the player's name
	GetPlayerName(playerid, Name, sizeof(Name));

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		if (sscanf(params, "s[128]", Message)) SendClientMessage(playerid, 0xFF0000AA, "Use: /cv [texto]");
		else
		{
			// Loop through all players
			for (new i; i < MAX_PLAYERS; i++)
			{
			    // Check if the player is logged in
				if (APlayerData[i][LoggedIn] == true)
				{
				    // Check if the other player has the same class
				    if (APlayerData[i][PlayerClass] == APlayerData[playerid][PlayerClass])
				    {
						format(Msg, 128, "{B0B0B0}%s: {FFFFFF}%s", Name, Message);
						SendClientMessage(i, 0xFFFFFFFF, Msg);
				    }
				}
			}
		}
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command lets you talk only to admin players
COMMAND:asay(playerid, params[])
{
	// Setup local variables
	new Name[24], Msg[128], Message[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/acv", params);

	// Get the player's name
	GetPlayerName(playerid, Name, sizeof(Name));

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player is an admin
		if (APlayerData[playerid][PlayerLevel] > 0)
		{
			if (sscanf(params, "s[128]", Message)) SendClientMessage(playerid, 0xFF0000AA, "Use: /acv [texto]");
			else
			{
				// Loop through all players
				for (new i; i < MAX_PLAYERS; i++)
				{
				    // Check if the player is logged in
					if (APlayerData[i][LoggedIn] == true)
					{
					    // Check if the other player is also an admin
					    if (APlayerData[i][PlayerLevel] > 0)
					    {
							format(Msg, 128, "{B0B0B0}%s: {FFFFFF}%s", Name, Message);
							SendClientMessage(i, 0xFFFFFFFF, Msg);
					    }
					}
				}
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Clamp an owned vehicle (remove it completely)
COMMAND:apreender(playerid, params[])
{
	// Setup local variables
	new vid, Reason[128], HouseID, HouseOwner, Name[24], AdminName[24], Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/apreender", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			if (sscanf(params, "is[128]", vid, Reason)) SendClientMessage(playerid, 0xFF0000AA, "Use: /apreender [id-car] [motivo]");
			else
			{
			    // Get the HouseID to which this vehicle belongs
				HouseID = AVehicleData[vid][BelongsToHouse];

				// Check if the vehicle belongs to a house
				if (HouseID != 0)
				{
					//Also set the new location of the vehicle inside the KACC Military fuels hangar
					AVehicleData[vid][SpawnX] = 2585.0;
					AVehicleData[vid][SpawnY] = 2829.0;
					AVehicleData[vid][SpawnZ] = 10.9;
					AVehicleData[vid][SpawnRot] = 0.0;

					// Search all the players to see who owns the house
					for (new i; i < MAX_PLAYERS; i++)
					{
						// Loop through all the houses this player owns
						for(new j; j < MAX_HOUSESPERPLAYER; j++)
						{
						    // Check if the player owns this house
							if (APlayerData[i][Houses][j] == HouseID)
							{
							    // Store the houseowner
							    HouseOwner = i;

								// Find the CarSlot where this vehicle exists
								for (new CarSlot; CarSlot < 10; CarSlot++)
								{
									// Check if the vehicle is stored in this carslot
									if (AHouseData[HouseID][VehicleIDs][CarSlot] == vid)
									{
										vid = House_ReplaceVehicle(HouseID, CarSlot); // Re-create the vehicle at the KACC Military fuels hangar
										// Set the vehicle as clamped (clamping needs to be done after re-creating the vehice, otherwise the wrong id can be clamped)
										AVehicleData[vid][Clamped] = true;
									}
								}

								break;
							}
						}
					}

					// Get the name of the admin and owner of the house
					GetPlayerName(playerid, AdminName, sizeof(AdminName));
					GetPlayerName(HouseOwner, Name, sizeof(Name));

					// Let the admin know who's vehicle he deleted
					format(Msg, 128, "{00FF00}[ToB] Você apreendeu o veiculo de propriedade: {FFFF00}%s", Name);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					// Let the player know who deleted his vehicle
					format(Msg, 128, "{FF0000}[ToB] O veículo de sua propriedade foi apreendido pelo Admin {FFFF00}%s", AdminName);
					SendClientMessage(HouseOwner, 0xFFFFFFFF, Msg);
					format(Msg, 128, "{FF0000}[ToB] Ele pertence a casa: {FFFF00}%s", AHouseData[HouseID][HouseName]);
					SendClientMessage(HouseOwner, 0xFFFFFFFF, Msg);
					format(Msg, 128, "{FF0000}Motivo: {FFFF00}%s", Reason);
					SendClientMessage(HouseOwner, 0xFFFFFFFF, Msg);
					// Save the player's datafile (and his houses/businesses/vehicles)
					PlayerFile_Save(HouseOwner);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Esse veiculo nao pertence a um jogador, você não pode apreende-lo");
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command can be used to unclamp all your vehicles at once
COMMAND:liberar(playerid, params[])
{
	// Setup local variables
	new HouseID, vid, ClampedVehicles, UnclampPrice, Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/liberar", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Loop through all vehicles owned by this player
		for (new HouseSlot; HouseSlot < MAX_HOUSESPERPLAYER; HouseSlot++)
		{
			// Get the HouseID that exists on this index
			HouseID = APlayerData[playerid][Houses][HouseSlot];

			// check if this house-slot is used
			if (HouseID != 0)
			{
				// Loop through all vehicles assigned to this house
				for (new CarSlot; CarSlot < 10; CarSlot++)
				{
					// Get the vehicle-id of the vehicle in this carslot
					vid = AHouseData[HouseID][VehicleIDs][CarSlot];

					// Check if this carslot is used
					if (vid != 0)
					{
						// Check if this vehicle is clamped
						if (AVehicleData[vid][Clamped] == true)
						    ClampedVehicles++; // Count the clamped vehicles
					}
				}
			}
		}

		// Check if there were any clamped vehicles
		if (ClampedVehicles > 0)
		{
			// Calculate the price to unclamp all the player's vehicles
			UnclampPrice = ClampedVehicles * UnclampPricePerVehicle;

			// Construct the message to inform the player how many vehicles have been clamped and how much it costs to un-clamp them
			format(Msg, 128, "[ToB] Voce tem %i veículos apreendidos, isso vai te custar R$%i para liberá-los.", ClampedVehicles, UnclampPrice);
		    // Show a dialog that informs the player how many vehicles have been clamped and how much it costs to un-clamp them
			ShowPlayerDialog(playerid, DialogUnclampVehicles, DIALOG_STYLE_MSGBOX, TXT_AreYouSure, Msg, "Unclamp", TXT_DialogButtonCancel);
		}
		else
		    SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Você não possui veiculos apreendidos.");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command displays the rules of the server
COMMAND:regras(playerid, params[])
{
	// Setup local variables
	new Msg[2000];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/regras", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Construct the rules
		format(Msg, 2000, "%s1. Sempre dirigir do lado direito nas estradas para evitar acidentes.\n", Msg);
		format(Msg, 2000, "%s2. Não chingar ou desrespeitar os outros jogadores, eles são seus companheiros.\n", Msg);
		format(Msg, 2000, "%s3. Usar a linguagem padrão 'Portugues'.\n", Msg);
		format(Msg, 2000, "%s4. Não usar hackers ou será banido permanentemente.\n", Msg);
		format(Msg, 2000, "%s5. Não floodar no chat, pode ser calado por um admin.\n", Msg);
		format(Msg, 2000, "%s6. Não roubar carros, sujeito a prisão caso haja denuncia.\n", Msg);
	    // Show a dialog that shows the rules
		ShowPlayerDialog(playerid, DialogRules, DIALOG_STYLE_MSGBOX, "Regras do server:", Msg, "Aceitar", TXT_DialogButtonCancel);
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}


// Report a player for breaking the rules
COMMAND:relato(playerid, params[])
{
	// Setup local variables
	new OtherPlayer, Name[24], Reason[128], Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/relato", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		if (sscanf(params, "us[128]", OtherPlayer, Reason)) SendClientMessage(playerid, 0xFF0000AA, "Usage: \"/relato [id] [causa]");
		else
		{
		    // Check if that other player is logged in
		    if (APlayerData[OtherPlayer][LoggedIn] == true)
		    {
				// Send the report to all admins and add the report to the report-list so admins can review it
				SendReportToAdmins(OtherPlayer, Reason);

				// Get the name of the offender
				GetPlayerName(OtherPlayer, Name, sizeof(Name));
				// Let the player know he reported the other player
				format(Msg, 128, "{00FF00}[ToB] Você relatou {FFFF00}%s", Name);
				SendClientMessage(playerid, 0xFFFFFFFF, Msg);
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] O jogador nao está conectado.");
		}
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Lets the admins see the list of reports
COMMAND:relatorio(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/relatorio", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 1
		if (APlayerData[playerid][PlayerLevel] >= 1)
		{
			// Add the first report to the list (if it exists)
			if (AReports[0][ReportUsed] == true)
			    format(ReportList, 5000, "%s: %s\n", AReports[0][ReportName], AReports[0][ReportReason]);

			// Construct the report-dialog
			for (new i = 1; i < 50; i++)
			{
				// Check if the ReportID has been used already
				if (AReports[i][ReportUsed] == true)
				{
				    format(ReportList, 5000, "%s%s: %s\n", ReportList, AReports[i][ReportName], AReports[i][ReportReason]);
				}
			}

			// Show all the reports
			ShowPlayerDialog(playerid, DialogReports, DIALOG_STYLE_LIST, "Relatório:", ReportList, "OK", "Cancelar");
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Enables the trucker to overload himself
COMMAND:sobrecarga(playerid, params[])
{
	// Setup local variables
	new vModel, bool:ValidOverLoad = false, Float:x, Float:y, Float:z, Name[24], Msg[128];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/sobrecarga", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the playeris a trucker
		if (APlayerData[playerid][PlayerClass] == ClassTruckDriver)
		{
			// Check if he has already started a job
			if (APlayerData[playerid][JobStarted] == true)
			{
				// Check if the player has already loaded his load
				if (APlayerData[playerid][JobStep] == 2)
				{
					// Check if the player isn't overloaded already
					if (APlayerData[playerid][Overloaded] == false)
					{
						// Get the coordinates of the loading point
						x = ALocations[APlayerData[playerid][JobLoc1]][LocX];
						y = ALocations[APlayerData[playerid][JobLoc1]][LocY];
						z = ALocations[APlayerData[playerid][JobLoc1]][LocZ];

					    // Check if the player is still near the loading point
					    if (IsPlayerInRangeOfPoint(playerid, 25.0, x, y, z))
					    {
							// Get the vehicle-model of the player's vehicle
							vModel = GetVehicleModel(APlayerData[playerid][VehicleID]);

							// Check if the trucker is driving a trucking vehicle that can be overloaded
							switch (vModel)
							{
								case VehicleFlatbed, VehicleDFT30: ValidOverLoad = true; // Flatbed and DFT-30 can be overloaded
								case VehicleLineRunner, VehicleTanker, VehicleRoadTrain:
								{
									switch (GetVehicleModel(APlayerData[playerid][TrailerID]))
									{
										case VehicleTrailerCargo, VehicleTrailerCargo2, VehicleTrailerOre: ValidOverLoad = true; // Cargo and ore trailer can be overloaded
									}
								}
							}

							// Check if the vehicle is valid for overloading
							if (ValidOverLoad == true)
							{
								// Set overloaded for this player to True
							    APlayerData[playerid][Overloaded] = true;
							    // Add 2 to the player's wanted level
							    SetPlayerWantedLevel(playerid, GetPlayerWantedLevel(playerid) + 2);
							    // Let the player know he has been overloaded now
							    SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Você sobrecarregou o seu caminhão, fique atento à policia.");
								// Inform the police this trucker is overloaded
								GetPlayerName(playerid, Name, sizeof(Name));
								format(Msg, 128, "{00FF00}[ToB] Caminhão {FFFF00}%s{00FF00} está sobrecarregado. 'perseguir e multar'", Name);
								Police_SendMessage(Msg);
							}
							else
							    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Seu veículo nao suporta ser sobrecarregado.");
						}
						else
						    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você precisa estar no ponto de carregamento para sobrecarregar seu caminhão.");
					}
					else
					    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você já está sobrecarregado.");
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você deve carregar o seu caminhao primeiro.");
			}
			else
			    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Inicie o trabalho primeiro.");
		}
		else
			return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command resets a player's money, score and stats to 0 (if chosen)
COMMAND:resetarconta(playerid, params[])
{
	// Setup local variables
	new Name[24], AdminName[24], Reason[128], Msg[128], OtherPlayer, ClearMoney, ClearScore, ClearStats;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/resetarconta", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			if (sscanf(params, "uiiis[128]", OtherPlayer, ClearMoney, ClearScore, ClearStats, Reason)) SendClientMessage(playerid, 0xFF0000AA, "Use: /resetarconta [id] [dinheiro(0/1)] [score(0/1)] [Status(0/1)] [Motivo]");
			else
			{
			    // Check if the other player is logged in
				if (APlayerData[OtherPlayer][LoggedIn] == true)
				{
					// Check if there is at least one parameter given to be cleared, otherwise exit the command
					if ((ClearMoney + ClearScore + ClearStats) == 0)
						return 1;

					// Get the names of both players
					GetPlayerName(playerid, AdminName, sizeof(AdminName));
					GetPlayerName(OtherPlayer, Name, sizeof(Name));

					// Reset the other player's money to 0
					if (ClearMoney == 1)
					{
						APlayerData[OtherPlayer][PlayerMoney] = 0;
						format(Msg, 128, "{FF0000}[ToB] Seu dinheiro foi resetado por {FFFF00}%s", AdminName);
						SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);
						format(Msg, 128, "{00FF00}[ToB] Você resetou o dinheiro do jogador {FFFF00}%s", Name);
						SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					}

					// Reset the other player's score to 0
					if (ClearScore == 1)
					{
						APlayerData[OtherPlayer][PlayerScore] = 0;
						format(Msg, 128, "{FF0000}[ToB] Seu score foi resetado por {FFFF00}%s", AdminName);
						SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);
						format(Msg, 128, "{00FF00}[ToB] Você resetou o score do jogador {FFFF00}%s", Name);
						SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					}

					// Reset the other player's stats to 0
					if (ClearStats == 1)
					{
						APlayerData[OtherPlayer][StatsTruckerJobs] = 0;
						APlayerData[OtherPlayer][StatsConvoyJobs] = 0;
						APlayerData[OtherPlayer][StatsBusDriverJobs] = 0;
						APlayerData[OtherPlayer][StatsPilotJobs] = 0;
						APlayerData[OtherPlayer][StatsMafiaJobs] = 0;
						APlayerData[OtherPlayer][StatsMafiaStolen] = 0;
						APlayerData[OtherPlayer][StatsPoliceFined] = 0;
						APlayerData[OtherPlayer][StatsPoliceJailed] = 0;
						APlayerData[OtherPlayer][StatsCourierJobs] = 0;
						APlayerData[OtherPlayer][StatsAssistance] = 0;
						APlayerData[OtherPlayer][StatsRoadworkerJobs] = 0;
						APlayerData[OtherPlayer][StatsMetersDriven] = 0.0;
						format(Msg, 128, "{FF0000}[ToB] Seu status foi resetado por {FFFF00}%s", AdminName);
						SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);
						format(Msg, 128, "{00FF00}[ToB] Você resetou o status do jogador {FFFF00}%s", Name);
						SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					}

					// Let the other player know the reason too
					format(Msg, 128, "{FF0000}Motivo: {FFFF00}%s", Reason);
					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);

					// Save the other player's account
					PlayerFile_Save(OtherPlayer);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Esse jogador não está online.");
			}
		}
		else
			return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command searches every house and business that the player owns and restores the data for it in the player's account
COMMAND:corrigirjogador(playerid, params[])
{
	// Setup local variables
	new Name[24], AdminName[24], Msg[128], OtherPlayer;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/corrigirjogador", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 5
		if (APlayerData[playerid][PlayerLevel] >= 5)
		{
			if (sscanf(params, "u", OtherPlayer)) SendClientMessage(playerid, 0xFF0000AA, "Use: /corrigirjogador [id]");
			else
			{
			    // Check if the other player is logged in
				if (APlayerData[OtherPlayer][LoggedIn] == true)
				{
					// Get the names of both players
					GetPlayerName(playerid, AdminName, sizeof(AdminName));
					GetPlayerName(OtherPlayer, Name, sizeof(Name));

					// Clear the houses and businesses that the player owns right now
					for (new i; i < MAX_HOUSESPERPLAYER; i++)
					    APlayerData[OtherPlayer][Houses][i] = 0;

					for (new i; i < MAX_BUSINESSPERPLAYER; i++)
					    APlayerData[OtherPlayer][Business][i] = 0;

					// Now search through all houses and re-add them to the player
					for (new HouseID = 1; HouseID < MAX_HOUSES; HouseID++)
						if (AHouseData[HouseID][Owned] == true) // Check if the house is owned by somebody
							if (strcmp(AHouseData[HouseID][Owner], Name, false) == 0) // Check if the player is the owner of the house
							{
								for (new i; i < MAX_HOUSESPERPLAYER; i++) // Loop through all houses the player owns
								    if (APlayerData[OtherPlayer][Houses][i] == 0) // Check if the houseslot is free
								    {
										APlayerData[OtherPlayer][Houses][i] = HouseID; // Store the HouseID
										break; // Stop searching for more free slots
								    }
							}

					// Now search through all businesses and re-add them to the player
					for (new BusID = 1; BusID < MAX_BUSINESS; BusID++)
						if (ABusinessData[BusID][Owned] == true) // Check if the business is owner by someone
							if (strcmp(ABusinessData[BusID][Owner], Name, false) == 0) // Check if the player is the owner of the business
							{
								for (new i; i < MAX_BUSINESSPERPLAYER; i++) // Loop through all businesses the player owns
								    if (APlayerData[OtherPlayer][Business][i] == 0) // Check if the businessslot is free
								    {
										APlayerData[OtherPlayer][Business][i] = BusID; // Store the BusID
										break; // Stop searching for more free slots
								    }
							}

					// Let the other player know his property has been restored
					format(Msg, 128, "{00FF00}[ToB] Sua propriedade foi restaurada por: {FFFF00}%s", AdminName);
					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);

					// Save the other player's account
					PlayerFile_Save(OtherPlayer);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Esse jogador não está online.");
			}
		}
		else
			return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command sets a skin for the player
COMMAND:setskin(playerid, params[])
{
	// Setup local variables
	new Msg[128], Skin;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/setskin", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 4
		if (APlayerData[playerid][PlayerLevel] >= 4)
		{
			if (sscanf(params, "i", Skin)) SendClientMessage(playerid, 0xFF0000AA, "Use: /setskin [id(0-299)]");
			else
			{
				// Check if the player entered a valid skin-id
				if ((Skin >= 0) && (Skin <= 299))
				{
				    // Set the skin for the player
				    SetPlayerSkin(playerid, Skin);
					// Let the other player know the reason too
					format(Msg, 128, "{00FF00}[ToB] Você mudou o skin: {FFFF00}%i.", Skin);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
				}
				else
					SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Skin inválido use valores entre 0 e 299.");
			}
		}
		else
			return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Bans a player by his ip
COMMAND:banip(playerid, params[])
{
	// Setup local variables
	new PlayerToBan, Reason[128], Msg[128], Name[24], AdminName[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/banip", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
			if (sscanf(params, "us[128]", PlayerToBan, Reason))
				SendClientMessage(playerid, 0xFF0000AA, "Use: /ipban [id] [motivo]");
			else
			{
				if (IsPlayerConnected(PlayerToBan))
				{
					// Get the names of the player and the admin who executed the ban
					GetPlayerName(playerid, AdminName, sizeof(AdminName));
					GetPlayerName(PlayerToBan, Name, sizeof(Name));

					// Inform the player about his ban
					format(Msg, 128, "{FF0000}[ToB] Você teve o IP banido permanentemente por {FFFF00}%s", AdminName);
					SendClientMessage(PlayerToBan, 0xFFFFFFFF, Msg);
					format(Msg, 128, "{FF0000}Motivo: {FFFF00}%s", Reason);
					SendClientMessage(PlayerToBan, 0xFFFFFFFF, Msg);

					// Ban the player with a reason
					BanEx(PlayerToBan, Reason);

					// Inform everybody else which player was ip-banned
					format(Msg, 128, "{808080}[ToB] %s %s Baniu o ip de {FFFF00}%s", AdminLevelName[APlayerData[playerid][PlayerLevel]], AdminName, Name);
					SendClientMessageToAll(0xFFFFFFFF, Msg);
				}
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	return 1;
}

// Bans a player's entire range of IP addresses (the last part of the IP-address will be from 0 to 255)
COMMAND:rangeban(playerid, params[])
{
	// Setup local variables
	new PlayerToBan, PlayerIP[16], FirstPartsOfIP[16], BanCmd[24], Reason[128], Msg[128], Name[24], AdminName[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/banclasse", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
			if (sscanf(params, "us[128]", PlayerToBan, Reason))
				SendClientMessage(playerid, 0xFF0000AA, "Use: /banclasse [id] [motivo]");
			else
			{
				if (IsPlayerConnected(PlayerToBan))
				{
					// Get the names of the player and the admin who executed the ban
					GetPlayerName(playerid, AdminName, sizeof(AdminName));
					GetPlayerName(PlayerToBan, Name, sizeof(Name));

					// Get the player's IP-address
					GetPlayerIp(PlayerToBan, PlayerIP, 16);

					// Inform the player about his ban
					format(Msg, 128, "{FF0000}[ToB] Você teve a faixa de ip banida permanentemente por {FFFF00}%s", AdminName);
					SendClientMessage(PlayerToBan, 0xFFFFFFFF, Msg);
					format(Msg, 128, "{FF0000}Motivo: {FFFF00}%s", Reason);
					SendClientMessage(PlayerToBan, 0xFFFFFFFF, Msg);

					// Get the first three digits from the player's ip, so the fourth part can be added from 0 to 255
					FirstPartsOfIP = GetFirstThreeDigitsFromIP(PlayerIP);
					// Ban the entire range of IP-addresses of the player
					for (new i; i < 256; i++)
					{
					    format(BanCmd, 24, "banip %s%i", FirstPartsOfIP, i); // Construct the RCon command to ban every IP
                        SendRconCommand(BanCmd); // Execute the command
					}
					// Finally kick the player (the RCon command doesn't kick you out automatically)
					Kick(PlayerToBan);

					// Inform everybody else which player was ip-range-banned
					format(Msg, 128, "{808080}[ToB] %s %s teve a faixa de ip banida permanentemente por {FFFF00}%s", AdminLevelName[APlayerData[playerid][PlayerLevel]], AdminName, Name);
					SendClientMessageToAll(0xFFFFFFFF, Msg);
				}
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	return 1;
}

// Sets the score of another player
COMMAND:darscore(playerid, params[])
{
	// Setup local variables
	new Msg[128], Name[24], OtherName[24], OtherPlayer, pScore;

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/darscore", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player's admin-level is at least 3
		if (APlayerData[playerid][PlayerLevel] >= 3)
		{
			if (sscanf(params, "ui", OtherPlayer, pScore)) SendClientMessage(playerid, 0xFF0000AA, "Use: /darscore [id] [score]");
			else
			{
				// Check if the otherplayer is online
				if (IsPlayerConnected(OtherPlayer))
				{
					// Get the player-names
					GetPlayerName(playerid, Name, sizeof(Name));
					GetPlayerName(OtherPlayer, OtherName, sizeof(OtherName));

					// Set the other player's score
					APlayerData[OtherPlayer][PlayerScore] = pScore;
					// Let the other player know that his score has been changed
					format(Msg, 128, "{00FF00}[ToB] Seu score foi setado para {FFFF00}%i{00FF00} por {FFFF00}%s.", pScore, Name);
					SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);
					// Let the player know he has set the score of the other player
					format(Msg, 128, "{00FF00}[ToB] Você setou o score de {FFFF00}%s{00FF00} para {FFFF00}%i.", OtherName, pScore);
					SendClientMessage(playerid, 0xFFFFFFFF, Msg);
					// Save the other player's account
					PlayerFile_Save(OtherPlayer);
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] O jogador não está online.");
			}
		}
		else
		    return 0;
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// Allows the player to setup a bank account, login to his bank account, or use his bank account after he logged in to his bank account
COMMAND:banco(playerid, params[])
{
	// Setup local variables
	new file[100], Name[24];

	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/banco", params);

    // Get the playername
	format(Name, sizeof(Name), APlayerData[playerid][PlayerName]);
	// Construct the complete filename for this player's bank-account
	format(file, sizeof(file), BankFile, Name);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Check if the player doesn't have a bank account
		if (!fexist(file))
		{
			// Ask for a password to setup his bank account
			ShowPlayerDialog(playerid, DialogBankPasswordRegister, DIALOG_STYLE_INPUT, "Senha", "Insira a senha para registrar sua conta bancária 'não esqueça!':", TXT_DialogButtonSelect, TXT_DialogButtonCancel);
		}
		else // The player has a bank account
		{
			// If the player hasn't logged in to his bank account yet
			if (APlayerData[playerid][BankLoggedIn] == false)
			{
				// Ask for the password to login to his bank account
				ShowPlayerDialog(playerid, DialogBankPasswordLogin, DIALOG_STYLE_INPUT, "Senha", "Insira sua senha para logar na sua conta bancária:", TXT_DialogButtonSelect, TXT_DialogButtonCancel);
			}
			else // The player has logged in to his bank account already
			{
			    // Show the main bank menu dialog
				ShowBankMenu(playerid);
			}
		}
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command lists all help-items for which the player can get information about it
COMMAND:ajuda(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/ajuda", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Create the dialog that lists all help-items
        HelpList_Create(playerid);
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

// This command allows you to change your password for logging in
COMMAND:mudarsenha(playerid, params[])
{
	// Send the command to all admins so they can see it
	SendAdminText(playerid, "/mudarsenha", params);

	// Check if the player has logged in
	if (APlayerData[playerid][LoggedIn] == true)
	{
		// Show the dialog where the player must enter his old password
		ShowPlayerDialog(playerid, DialogOldPassword, DIALOG_STYLE_INPUT, "Insra a senha atual:", "Insira a senha que está ativada:", "OK", "Cancelar");
	}
	else
	    return 0;

	// Let the server know that this was a valid command
	return 1;
}

