// This timer is created every time a player changes his class to assistance
forward Assistance_CheckPlayers(playerid);
public Assistance_CheckPlayers(playerid)
{
	// Scan through all players
	for (new PlayerToCheck; PlayerToCheck < MAX_PLAYERS; PlayerToCheck++)
	{
		// check if this player is connected
		if (IsPlayerConnected(PlayerToCheck))
		{
			//Check if that player needs assistance
			if (APlayerData[PlayerToCheck][AssistanceNeeded] == true)
			    SetPlayerMarkerForPlayer(playerid, PlayerToCheck, 0xFF0000FF); // Make that player red to the assistance-player
			else
			{
				// Reset the playercolor based on the player's class
			    switch (APlayerData[PlayerToCheck][PlayerClass])
			    {
			        case ClassTruckDriver: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassTruckDriver);
			        case ClassBusDriver: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassBusDriver);
			        case ClassPilot: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassPilot);
			        case ClassPolice: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassPolice);
			        case ClassMafia: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassMafia);
			        case ClassCourier: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassCourier);
			        case ClassAssistance: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassAssistance);
			    }
			}
		}
	}
}

// This function lets the assistance player repair and refuel another player's vehicle if he called for assistance
Assistance_FixVehicle(playerid)
{
	// Setup local variables
	new vid, Float:vhealth, Float:FPayment, Payment, Float:x, Float:y, Float:z, Name[24], AssistName[24], Msg[128];
	new vFuel;

	// Get the assistance player's name
	GetPlayerName(playerid, AssistName, sizeof(AssistName));

	// Loop through all players
	for (new OtherPlayer; OtherPlayer < MAX_PLAYERS; OtherPlayer++)
	{
		// Check if this player is online
		if (IsPlayerConnected(OtherPlayer))
		{
			// Check if this player isn't the assistance player
			if (OtherPlayer != playerid)
			{
				// Check if this player needs assistance
				if (APlayerData[OtherPlayer][AssistanceNeeded] == true)
				{
					// Check if this player is the driver of a vehicle
					if (GetPlayerVehicleSeat(OtherPlayer) == 0)
					{
					    // Get the location of the player
					    GetPlayerPos(OtherPlayer, x, y, z);
						// Check if this player is closeby the assistance player
						if (IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z))
						{
							// Clear the other player's need for assistance
							APlayerData[OtherPlayer][AssistanceNeeded] = false;
							// Get the name of the other player
							GetPlayerName(OtherPlayer, Name, sizeof(Name));
							// Get the vehicle-id of that player's vehicle
							vid = GetPlayerVehicleID(OtherPlayer);

							// Get the current health of that vehicle
							GetVehicleHealth(vid, vhealth);
							// Calculate the price to repair the vehicle (calculate as a float, then convert to integer)
							FPayment = (1000.0 - vhealth) * 1.0;
							Payment = floatround(FPayment, floatround_round);
							// Repair the other player's vehicle
							RepairVehicle(vid);
							// Pay the assistance player and give 1 scorepoint
							RewardPlayer(playerid, Payment * 2, 1);
							// Let the other player pay for the repairs
							RewardPlayer(OtherPlayer, -Payment, 0);
							// Let the other player know that his vehicle has been repaired
							format(Msg, 128, "{00FF00}[ToB] Seu ve�culo foi reparado por {FFFF00}R$%i{00FF00} pelo \"{FFFF00}%s{00FF00}\"", Payment, AssistName);
							SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);
							// Let the assistance player know who's vehicle has been repaired
							format(Msg, 128, "{00FF00}[ToB] Voc� reparou {FFFF00}%s{00FF00} ve�culos e ganhou {FFFF00}R$%i.", Name, Payment);
							SendClientMessage(playerid, 0xFFFFFFFF, Msg);

							// Calculate the amount of fuel that needs to be refuelled
							vFuel = MaxFuel - AVehicleData[vid][Fuel];
							// Calculate the price to refuel
							Payment = (vFuel * RefuelMaxPrice) / MaxFuel;
							// Pay the assistance player and give 1 scorepoint
							RewardPlayer(playerid, Payment * 2, 1);
							// Let the other player pay for the refuel
							RewardPlayer(OtherPlayer, -Payment, 0);
							// Refuel the other player's vehicle
							AVehicleData[vid][Fuel] = MaxFuel;
							// Increase the stats
							APlayerData[playerid][StatsAssistance]++;
							// Let the other player know that his vehicle has been refuelled
							format(Msg, 128, "{00FF00}[ToB] Seu ve�culo foi abastecido por {FFFF00}R$%i{00FF00} pelo \"{FFFF00}%s{00FF00}\"", Payment, AssistName);
							SendClientMessage(OtherPlayer, 0xFFFFFFFF, Msg);
							// Let the assistance player know who's vehicle has been refuelled
							format(Msg, 128, "{00FF00}[ToB] Voc� abasteceu {FFFF00}%s{00FF00} ve�culos e ganhou {FFFF00}R$%i.", Name, Payment);
							SendClientMessage(playerid, 0xFFFFFFFF, Msg);

							// Save the player's account
							PlayerFile_Save(playerid);
						}
					}
				}
			}
		}
	}

	return 1;
}

// This function allows the assistance player to repair and refuel his own vehicle
Assistance_FixOwnVehicle(playerid)
{
	// Get the vehicle-id of the player's vehicle
	new vid = GetPlayerVehicleID(playerid);
	// Repair the player's vehicle
	RepairVehicle(vid);
	// Refuel the other player's vehicle
	AVehicleData[vid][Fuel] = MaxFuel;
	// Let the player know that he has repaired and refuelled his own vehicle
	SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Voc� tem reparado e abastecido o seu pr�prio ve�culo.");
}

// This function gets called when the assistance player dies (or changes class)
Assistance_EndJob(playerid)
{
	// Kill the PlayerCheckTimer
	KillTimer(APlayerData[playerid][PlayerCheckTimer]);

	// Scan through all players (to reset them to their default colors for the assistance-player)
	for (new PlayerToCheck; PlayerToCheck < MAX_PLAYERS; PlayerToCheck++)
	{
		// Check if this player is connected
		if (IsPlayerConnected(PlayerToCheck))
		{
			// Reset the playercolor based on the player's class
		    switch (APlayerData[PlayerToCheck][PlayerClass])
		    {
		        case ClassTruckDriver: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassTruckDriver);
		        case ClassBusDriver: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassBusDriver);
		        case ClassPilot: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassPilot);
		        case ClassPolice: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassPolice);
		        case ClassMafia: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassMafia);
		        case ClassCourier: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassCourier);
		        case ClassAssistance: SetPlayerMarkerForPlayer(playerid, PlayerToCheck, ColorClassAssistance);
		    }
		}
	}

	return 1;
}

