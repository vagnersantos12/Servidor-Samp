forward Courier_VehicleTimer(playerid);


// This function gets called whenever a courier player enters "/work"
Courier_StartJob(playerid)
{
	// Setup local variables
	new HouseCounter, HousesInRange[200], DialogList[200];

	// First clear the house-list
	for (new i; i < 11; i++)
		APlayerData[playerid][CourierHouses][i] = 0;

	// Count how many owned houses are in range of the player
	for (new HouseID = 1; HouseID < MAX_HOUSES; HouseID++)
	{
		// Check if the house is owned
		if (AHouseData[HouseID][Owned] == true)
		{
			// Check if the house is in range of the player
			if (IsPlayerInRangeOfPoint(playerid, CourierJobRange, AHouseData[HouseID][HouseX], AHouseData[HouseID][HouseY], AHouseData[HouseID][HouseZ]))
			{
			    // Check if there aren't 200 in-range houses have been found yet
				if (HouseCounter < 200)
				{
					HousesInRange[HouseCounter] = HouseID; // Store the HouseID in the list of in-range houses
					HouseCounter++; // Increase the number of owned houses in range of the player (range = 1000 meters)
				}
				else
				{
					break; // Stop searching for more houses (200 is the maximum)
				}
			}
		}
	}

	// Abort the mission if there are less than 2 houses in range and inform the player
	if (HouseCounter < 2)
	{
	    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] N�o h� casas com dono para realizar as entregas das correspondencias, tente alguma outra classe.");
		return 0;
	}

	// Try to add the 3 lines to the dialog-list
	if (HouseCounter >= 2)
	{
	    format(DialogList, sizeof(DialogList), "Entregar 2 pacotes\n"); // Add the line to the dialog
		APlayerData[playerid][CourierMaxStep] = 2; // Set the number of houses for the job to 2
	}
	if (HouseCounter >= 5)
	{
	    format(DialogList, sizeof(DialogList), "%sEntregar 5 pacotes\n", DialogList); // Add the line to the dialog
		APlayerData[playerid][CourierMaxStep] = 5; // Set the number of houses for the job to 5
	}
	if (HouseCounter >= 10)
	{
	    format(DialogList, sizeof(DialogList), "%sEntregar 10 pacotes\n", DialogList); // Add the line to the dialog
		APlayerData[playerid][CourierMaxStep] = 10; // Set the number of houses for the job to 10
	}

	// Choose a random house for the first house to visit
	APlayerData[playerid][CourierHouses][1] = HousesInRange[random(HouseCounter)];
	// Now choose as many houses randomly as allowed, starting from the second
	for (new i = 2; i <= APlayerData[playerid][CourierMaxStep]; i++)
	{
		// Copy a random HouseID from the prepared list on in-range houses to the job-list
	    APlayerData[playerid][CourierHouses][i] = HousesInRange[random(HouseCounter)];

		// If the HouseID is the same as the previous HouseID (the player would visit the same house twice in a row)
		while (APlayerData[playerid][CourierHouses][i - 1] == APlayerData[playerid][CourierHouses][i])
			APlayerData[playerid][CourierHouses][i] = HousesInRange[random(HouseCounter)]; // Get a new random HouseID as long as the HouseID is the same as the previous one
	}

	// Let the player choose how many packages he wants to deliver
	ShowPlayerDialog(playerid, DialogCourierSelectQuant, DIALOG_STYLE_LIST, "[ToB] Escolha quantos pacotes voc� deseja entregar.", DialogList, TXT_DialogButtonSelect, TXT_DialogButtonCancel);

	return 1;
}

// This function is called when the player has chosen how many packages he wants to deliver
Courier_BeginJob(playerid)
{
	// Setup local variables
	new RouteText[128], Step, HouseID, Float:x, Float:y, Float:z;

	// Job has started
	APlayerData[playerid][JobStarted] = true;
	// Store the vehicleID (required to be able to check if the player left his vehicle)
	APlayerData[playerid][VehicleID] = GetPlayerVehicleID(playerid);
	// Set jobstep to 1 (going to the first house)
	Step = 1;
	APlayerData[playerid][JobStep] = Step;
	// Get the HouseID of the house where the mission starts (the first house in the list of in-range owned house)
	HouseID = APlayerData[playerid][CourierHouses][Step];
	// Set the TextDraw so the player can see it
	format(RouteText, 255, "~w~Entregar pacote ~b~%i/%i~w~ para: ~r~%s", Step, APlayerData[playerid][CourierMaxStep], AHouseData[HouseID][HouseName]);
	TextDrawSetString(APlayerData[playerid][MissionText], RouteText);
	// Grab the x, y, z positions for the first location
	x = AHouseData[HouseID][HouseX];
	y = AHouseData[HouseID][HouseY];
	z = AHouseData[HouseID][HouseZ];
	// Create a checkpoint where the player should deliver his package
	SetPlayerCheckpoint(playerid, x, y, z, 3);
	// Start a timer that ticks every second to see if the player is still inside his vehicle
	APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission;
	APlayerData[playerid][VehicleTimer] = SetTimerEx("Courier_VehicleTimer", 1000, true, "d" , playerid);
	// Send the player a message to inform him that the mission has started
	SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Entregar pacotes para as casas dos jogadores.");

	return 1;
}



// This function is called when a courier enters a checkpoint
Courier_OnPlayerEnterCheckpoint(playerid)
{
	// Setup local variables
	new RouteText[128], Step, HouseID, Float:x, Float:y, Float:z, Name[24], Msg[128], Payment;

	// Check if the player is outside his vehicle while entering a checkpoint
	if (GetPlayerVehicleSeat(playerid) == -1)
	{
		// Check if all the packages haven't been delivered
		if (APlayerData[playerid][CourierMaxStep] != APlayerData[playerid][JobStep])
		{
			// First disable the current checkpoint
			DisablePlayerCheckpoint(playerid);
			// Let the player know he delivered a package
			GameTextForPlayer(playerid, TXT_PackageDeliveredGameText, 5000, 4);
			SendClientMessage(playerid, 0xFFFFFFFF, TXT_PackageDeliveredMessage);
			// Set next JobStep (next house)
			APlayerData[playerid][JobStep]++;
			Step = APlayerData[playerid][JobStep];
			// Get the HouseID of the house where the mission starts (the first house in the list of in-range owned house)
			HouseID = APlayerData[playerid][CourierHouses][Step];
			// Set the TextDraw so the player can see it
			format(RouteText, 255, "~w~Entregar pacote ~b~%i/%i~w~ para: ~r~%s", Step, APlayerData[playerid][CourierMaxStep], AHouseData[HouseID][HouseName]);
			TextDrawSetString(APlayerData[playerid][MissionText], RouteText);
			// Grab the x, y, z positions for the first location
			x = AHouseData[HouseID][HouseX];
			y = AHouseData[HouseID][HouseY];
			z = AHouseData[HouseID][HouseZ];
			// Create a checkpoint where the player should deliver his package
			SetPlayerCheckpoint(playerid, x, y, z, 3);
		}
		else // All packages have been delivered, the player has to get paid now
		{
			// Get the player name
			GetPlayerName(playerid, Name, sizeof(Name));
			// Send a message to all players to inform them that this player completed a courier-job
			format(Msg, 128, TXT_PlayerCompletedCourierJob, Name, APlayerData[playerid][CourierMaxStep]);
			SendClientMessageToAll(0xFFFFFFFF, Msg);
			// Set a payment based on the number of packages
			Payment = APlayerData[playerid][CourierMaxStep] * PaymentPerPackage;
			// Pay the player money and give scorepoints, both based on the number of packages delivered
			RewardPlayer(playerid, Payment, APlayerData[playerid][CourierMaxStep]);
			// Send a message to let the player know he finished his mission and got paid
			format(Msg, 128, TXT_RewardJob, Payment);
			SendClientMessage(playerid, 0xFFFFFFFF, Msg);

			// Increase the stats for completing a courier job
			APlayerData[playerid][StatsCourierJobs]++;
			// End the current trucker job (clear mission-data)
			Courier_EndJob(playerid);
			// Also save the data (in case the server crashes, progress would be lost)
			PlayerFile_Save(playerid);
		}
	}
	else
	    SendClientMessage(playerid, 0xFFFFFFFF, TXT_NeedOnFootToProceed);

	return 1;
}



// A timer that runs every second to see if the player is still inside his vehicle
public Courier_VehicleTimer(playerid)
{
	new OldVehicleID = APlayerData[playerid][VehicleID];
	new NewVehicleID = GetPlayerVehicleID(playerid);

	if (APlayerData[playerid][VehicleTimerTime] != 0)
	{
		// If VehicleID and TrailerID are still the same as when the player accepted the job
		if (OldVehicleID == NewVehicleID)
			APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission; // Reset the time before the mission fails
		else // Player stepped out of his vehicle
		{
			new TimeLeft[5];
			// Reduce the time left by 1
			APlayerData[playerid][VehicleTimerTime] = APlayerData[playerid][VehicleTimerTime] - 1;
			// Convert the time left to a string for displaying
			valstr(TimeLeft, APlayerData[playerid][VehicleTimerTime]);
			// Display the time left
			GameTextForPlayer(playerid, TimeLeft, 1000, 4);
			// Send only one message to inform the player what he must do
			if (APlayerData[playerid][VehicleTimerTime] == (Job_TimeToFailMission - 1))
				SendClientMessage(playerid, 0xFFFFFFFF, TXT_CourierMustEnterVehicle);
		}
	}
	else
	{
	    // Time left has reached 0
		Courier_EndJob(playerid);
		// Inform the player that he failed the mission
		GameTextForPlayer(playerid, TXT_FailedMission, 5000, 4);
		// Reduce the player's cash by 1000
		RewardPlayer(playerid, -1000, 0);
	}
}


// This function is used to stop any Courier-mission that has been started
Courier_EndJob(playerid)
{
	if (APlayerData[playerid][JobStarted] == true)
	{
		// Clear all data about the job from the player, so he can start a new one
		APlayerData[playerid][JobStarted] = false;
		APlayerData[playerid][JobStep] = 0;
		APlayerData[playerid][VehicleTimerTime] = 0;
		APlayerData[playerid][VehicleID] = 0;
		APlayerData[playerid][CourierMaxStep] = 0;

		// Clear the list of houses-in-range
		for (new i; i < 11; i++)
			APlayerData[playerid][CourierHouses][i] = 0;

		// Delete the checkpoint
		DisablePlayerCheckpoint(playerid);
		// Reset the missiontext
		TextDrawSetString(APlayerData[playerid][MissionText], Courier_NoJobText);
		// Kill the VehicleTimer
		KillTimer(APlayerData[playerid][VehicleTimer]);
	}

	return 1;
}
















