// Forward the function used to check if the player is still inside his vehicle during a job
forward Roadworker_VehicleTimer(playerid);
forward Roadworker_VehicleTimer2(playerid);
// Forward the function used to repair a camera (when the player entered a racecheckpoint)
forward Roadworker_RepairCamera(playerid);



enum TBrokenVehicleLocation
{
	BrokenName[50], // Holds the name of the location where the vehicle is located
	Float:BrokenX, // Holds the X coordinate where the vehicle spawns
	Float:BrokenY, // Holds the Y coordinate where the vehicle spawns
	Float:BrokenZ // Holds the Z coordinate where the vehicle spawns
}
new ABrokenVehicles[][TBrokenVehicleLocation] =
{
	{"Shady Creeks", -2047.5, -1882.25, 52.4},
	{"Angel Pine", -2072.5, -2407.75, 30.7},
	{"Shady Creeks", -1595.25, -2625.0, 52.6},
	{"Back O Beyond", -990.25, -2335.5, 66.8},
	{"Flint County", 46.5, -2654.25, 40.5},
	{"Los Santos Inlet", -313.5, -1959.75, 20.0},
	{"Leafy Hollow", -833.0, -1737.25, 80.8},
	{"Flint Range", -347.5, -1331.0, 17.1},
	{"Flint County", 17.25, -987.75, 28.7},
	{"Fallen Tree", -763.0, -621.25, 61.5},
	{"Foster Valley", -1885.5, -435.5, 25.2},
	{"Missionary Hill", -2451.25, -681.0, 133.6},
	{"Garcia", -2371.5, 118.25, 35.3},
	{"Downtown", -1781.5, 429.25, 16.6},
	{"Palisades", -2905.0, 656.5, 6.3},
	{"Paradiso", -2771.25, 1239.5, 22.6}
//	{"nnnnnnnnnn", xxxxxxx, yyyyyyyy, zzzzzzz},
};



// This function is called when a roadworker wants to start a job by entering "/work"
Roadworker_StartRandomJob(playerid)
{
	// Setup local variables
	new vid, trailerid;

	// If the player is the driver of the vehicle (GetPlayerVehicleSeat returns -1 if the player is not in a vehicle)
	if (GetPlayerVehicleSeat(playerid) == 0)
	{
		// Get the vehicle-id
		vid = GetPlayerVehicleID(playerid);
		// Get the trailer-id
		trailerid = GetVehicleTrailer(vid);

		switch (GetVehicleModel(vid))
		{
		    case VehicleUtilityVan: // With a Utility Van, you're gonna do "repair speedcamera" job-type
		    {
			    // Check if the player has a utility trailer attached
			    if (trailerid != 0)
				{
					// Check if there is a utility trailer attached
			        if (GetVehicleModel(trailerid) == VehicleUtilityTrailer)
					{
					    // Setup local variables
						new Float:x, Float:y, Float:z, CamID;
						// Get a random speedcamera (no previous camera has been fixed yet, so Exception = -1 (invalid camera))
						CamID = GetRandomCamera(-1);
						// Check if there are no speedcamera's
						if (CamID == -1)
						{
							SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Não pode iniciar o trabalho, pois não ha radares criados.");
							return 1;
						}

						// Job has started
						APlayerData[playerid][JobStarted] = true;
						// Set job-type
						APlayerData[playerid][JobID] = 1; // Job-type: "repair speedcameras"
						// Store the CamID
						APlayerData[playerid][JobLoc1] = CamID;
						// Set the TextDraw so the player can see it
						TextDrawSetString(APlayerData[playerid][MissionText], TXT_RepairSpeedcamera);

						// Grab the x, y, z positions for the checkpoint
						x = ACameras[CamID][CamX];
						y = ACameras[CamID][CamY];
						z = ACameras[CamID][CamZ];
						// Create a racecheckpoint where the player should repair a speedcamera
	                    SetPlayerRaceCheckpoint(playerid, 1, x, y, z, 0.0, 0.0, 0.0, 2.5);
						// Create a checkpoint to indicate the base
						SetPlayerCheckpoint(playerid, -1870.0, -1710.0, 21.8, 7.0);

						// Store the vehicleID (required to be able to check if the player left his vehicle)
						APlayerData[playerid][VehicleID] = vid;
						APlayerData[playerid][TrailerID] = trailerid;
						// Start a timer that ticks every second to see if the player is still inside his vehicle
						APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission;
						APlayerData[playerid][VehicleTimer] = SetTimerEx("Roadworker_VehicleTimer", 1000, true, "i" , playerid);
						// Inform the player what he must do
						SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Faça a manutenção no radar indicado no mapa, ou volte para a base para finalizar o trabalho.");
					}
					else
					    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você precisa ter um 'Utility Trailer' acoplado em seu 'Ultility Van' para iniciar o trabalho.");
				}
				else
				    SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você precisa ter um 'Utility Trailer' acoplado em seu 'Ultility Van'.");
			}
			case VehicleTowTruck: // With a towtruck, you're gonna do "tow broken vehicle to shredder" job-type
			{
			    // Setup local variables
				new Float:x, Float:y, Float:z, RouteText[128];

				// Job has started
				APlayerData[playerid][JobStarted] = true;
				// Set job-type
				APlayerData[playerid][JobID] = 2; // Job-type: "tow broken vehicles to shredder"
				// Choose a random spawn-location for the vehicle
				APlayerData[playerid][JobLoc1] = random(sizeof(ABrokenVehicles));
				// Set the job-step to 1 (going to pickup the broken vehicle)
				APlayerData[playerid][JobStep] = 1;

				// Set the TextDraw so the player can see it
				format(RouteText, 128, TXT_TowBrokenVehicle, ABrokenVehicles[APlayerData[playerid][JobLoc1]][BrokenName]);
				TextDrawSetString(APlayerData[playerid][MissionText], RouteText);

				// Grab the x, y, z positions for the checkpoint where the vehicle will spawn, once the player comes into range (100m)
				x = ABrokenVehicles[APlayerData[playerid][JobLoc1]][BrokenX];
				y = ABrokenVehicles[APlayerData[playerid][JobLoc1]][BrokenY];
				z = ABrokenVehicles[APlayerData[playerid][JobLoc1]][BrokenZ];
				// Create a checkpoint to indicate the location of the vehicle
				SetPlayerCheckpoint(playerid, x, y, z, 10.0);
				// Also create the vehicle inside the checkpoint and store the vehicle's reference as the LoadID
				APlayerData[playerid][LoadID] = CreateBrokenVehicle(x, y, z);

				// Store the vehicleID (required to be able to check if the player left his vehicle)
				APlayerData[playerid][VehicleID] = vid;
				// Start a timer that ticks every second to see if the player is still inside his vehicle
				APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission;
				APlayerData[playerid][VehicleTimer] = SetTimerEx("Roadworker_VehicleTimer2", 1000, true, "i" , playerid);
				// Inform the player what he must do
				SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Reboque o carro quebrado para o triturador.");
			}
		}
	}

	return 1;
}

// This function gets executed when the player entered a checkpoint (to tow a broken vehicle to the shredder)
Roadworker_EnterCheckpoint(playerid)
{
	// Setup local variables
	new RouteText[128];

	// Check which job-type you're doing
	if (APlayerData[playerid][JobID] == 2) // Job-type: tow broken vehicle to shredder
	{
		// Check if the player is still inside his towtruck
		if (GetPlayerVehicleID(playerid) == APlayerData[playerid][VehicleID])
		{
			// Select action based on JobStep
			switch (APlayerData[playerid][JobStep])
			{
			    case 1: // Going to pickup the broken vehicle
			    {
					// Delete the checkpoint
					DisablePlayerCheckpoint(playerid);
					// Attach the broken vehicle to your towtruck
					AttachTrailerToVehicle(APlayerData[playerid][LoadID], GetPlayerVehicleID(playerid));
					// Update the TextDraw so the player can see it
					format(RouteText, 128, TXT_DeliverBrokenVehicle, ABrokenVehicles[APlayerData[playerid][JobLoc1]][BrokenName]);
					TextDrawSetString(APlayerData[playerid][MissionText], RouteText);
					// Create a checkpoint to indicate the location of the shredder
					SetPlayerCheckpoint(playerid, -1868.5, -1684.0, 21.8, 10.0);
					// Set the next jobstep (2 = going to deliver the broken vehicle to the shredder)
					APlayerData[playerid][JobStep] = 2;

					// Stop the timer that only checks if the player is still inside his vehicle
					KillTimer(APlayerData[playerid][VehicleTimer]);
					// Store the vehicleID AND the id of the broken vehicle as trailer (required to be able to check if the player left his vehicle)
					APlayerData[playerid][VehicleID] = GetPlayerVehicleID(playerid);
					APlayerData[playerid][TrailerID] = APlayerData[playerid][LoadID];
					// Start a timer that ticks every second to see if the player is still inside his vehicle
					APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission;
					APlayerData[playerid][VehicleTimer] = SetTimerEx("Roadworker_VehicleTimer", 1000, true, "i" , playerid);

					// Inform the player what he must do
					SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Reboque o carro quebrado para o triturador.");
			    }
			    case 2: // Going to deliver the broken vehicle to the shredder
			    {
			        // Delete the broken vehicle
			        AVehicleData[APlayerData[playerid][LoadID]][Owned] = false;
			        DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
			        DestroyVehicle(APlayerData[playerid][LoadID]);
			        APlayerData[playerid][LoadID] = 0;

					// End the mission, clearing all data
					Roadworker_EndJob(playerid);
					// Pay the player for delivering the broken vehicle to the shredder
					RewardPlayer(playerid, 3500, 1);
					// Let the player know he earned money for delivering the broken vehicle to the shredder
					SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Você ganhou {FFFF00}R$3500{00FF00} por carregar a sucata para o triturador.");
					// Also increase the stats
					APlayerData[playerid][StatsRoadworkerJobs]++;
					// Save the player's account
					PlayerFile_Save(playerid);
			    }
			}
		}
		else
			SendClientMessage(playerid, 0xFFFFFFFF, "{FF0000}[ToB] Você precisa estar em um TowTruck para proceder o trabalho.");
	}

	return 1;
}

// This function gets executed when the player entered a race-checkpoint (to repair a speedcamera)
Roadworker_EnterRaceCheckpoint(playerid)
{
	// Check which job-type you're doing
	if (APlayerData[playerid][JobID] == 1) // Repairing speedcamera's
	{
		// Check if the player is on foot
		if (GetPlayerVehicleSeat(playerid) == -1)
		{
			// Inform the player that he's repairing the camera
	 		GameTextForPlayer(playerid, "Fazendo manutencao no radar...", 5000, 4);

			// Disable the player's actions (he cannot move anymore)
			TogglePlayerControllable(playerid, 0);
			// Start a timer (Public function "Roadworker_RepairCamera(playerid)" gets called when the timer runs out)
			APlayerData[playerid][LoadingTimer] = SetTimerEx("Roadworker_RepairCamera", 5000, false, "d" , playerid);
		}
		else
		    SendClientMessage(playerid, 0xFFFFFFFF, TXT_NeedOnFootToProceed);
	}

	return 1;
}

// Repair the camera, pay the player and choose a new camera to fix
public Roadworker_RepairCamera(playerid)
{
    // Setup local variables
	new Float:x, Float:y, Float:z, CamID;

	// Pay the player for fixing this camera
	RewardPlayer(playerid, 2500, 1);
	// Let the player know he earned money for fixing this camera
	SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Você ganhou {FFFF00}R$2500{00FF00} por fazer a manutenção no aparelho de radar.");
	// Also increase the stats
	APlayerData[playerid][StatsRoadworkerJobs]++;
	// Save the player's account
	PlayerFile_Save(playerid);

	// Get a random speedcamera (don't allow the function to choose the same camera that just has been fixed)
	CamID = GetRandomCamera(APlayerData[playerid][JobLoc1]);
	// Store the CamID
	APlayerData[playerid][JobLoc1] = CamID;

	// Set the mission-TextDraw so the player can see it
	TextDrawSetString(APlayerData[playerid][MissionText], TXT_RepairSpeedcamera);

	// First delete the racecheckpoint
	DisablePlayerRaceCheckpoint(playerid);
	// Grab the x, y, z positions for the checkpoint
	x = ACameras[CamID][CamX];
	y = ACameras[CamID][CamY];
	z = ACameras[CamID][CamZ];
	// Create a new racecheckpoint where the player should repair a speedcamera
	SetPlayerRaceCheckpoint(playerid, 1, x, y, z, 0.0, 0.0, 0.0, 2.5);

	// Inform the player what he must do
	SendClientMessage(playerid, 0xFFFFFFFF, "{00FF00}[ToB] Fazer manutenção no próximo radar indicado no mapa, ou retornar para a base para finalizar o serviço. ");
	// Enable the player's actions (he can move again)
	TogglePlayerControllable(playerid, 1);
}



// This function checks if there are camera's defined and returns a random CamID
GetRandomCamera(Exception)
{
	// Setup local variables
	new CameraList[100], CamCount = -1, CamID;

	// Build the list of camera's
	for (CamID = 0; CamID < 100; CamID++)
	{
	    // Check if there is a camera defined at this location
		if (ACameras[CamID][CamSpeed] > 0)
		{
			// Increase the camera-counter to select the next index in the list
			CamCount++;
			// Store the CamID in the list
			CameraList[CamCount] = CamID;
		}
	}

	// If there are no camera's, return -1
	if (CamCount == -1)
	    return -1;

	// Get a random CameraID
	CamID = CameraList[random(CamCount + 1)];

	// Prevent the same camera being chosen as before
	while (CamID == Exception)
		CamID = CameraList[random(CamCount + 1)];

	// Choose a random camera from the list
	return CamID;
}



// A timer that runs every second to see if the player is still inside his vehicle
public Roadworker_VehicleTimer(playerid)
{
	new OldVehicleID = APlayerData[playerid][VehicleID];
	new NewVehicleID = GetPlayerVehicleID(playerid);
	new OldTrailerID = APlayerData[playerid][TrailerID];
	new NewTrailerID = GetVehicleTrailer(GetPlayerVehicleID(playerid));

	if (APlayerData[playerid][VehicleTimerTime] != 0)
	{
		// If VehicleID and TrailerID are still the same as when the player accepted the job
		if ((OldVehicleID == NewVehicleID) && (OldTrailerID == NewTrailerID))
			APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission; // Reset the time before the mission fails
		else // VehicleID isn't still the same (player lost his vehicle or trailer)
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
				SendClientMessage(playerid, 0xFFFFFFFF, TXT_RoadworkerMustEnterVehicle);
		}
	}
	else
	{
	    // Time left has reached 0
		Roadworker_EndJob(playerid);
		// Inform the player that he failed the mission
		GameTextForPlayer(playerid, TXT_FailedMission, 5000, 4);
		// Reduce the player's cash by 1000
		RewardPlayer(playerid, -1000, 0);
	}
}

// A timer that runs every second to see if the player is still inside his vehicle (but trailer isn't checked here)
public Roadworker_VehicleTimer2(playerid)
{
	new OldVehicleID = APlayerData[playerid][VehicleID];
	new NewVehicleID = GetPlayerVehicleID(playerid);

	if (APlayerData[playerid][VehicleTimerTime] != 0)
	{
		// If VehicleID is still the same as when the player accepted the job
		if (OldVehicleID == NewVehicleID)
			APlayerData[playerid][VehicleTimerTime] = Job_TimeToFailMission; // Reset the time before the mission fails
		else // VehicleID isn't still the same (player lost his vehicle)
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
				SendClientMessage(playerid, 0xFFFFFFFF, TXT_RoadworkerMustEnterVehicle);
		}
	}
	else
	{
	    // Time left has reached 0
		Roadworker_EndJob(playerid);
		// Inform the player that he failed the mission
		GameTextForPlayer(playerid, TXT_FailedMission, 5000, 4);
		// Reduce the player's cash by 1000
		RewardPlayer(playerid, -1000, 0);
	}
}



// This function is used to cleanup the current job
Roadworker_EndJob(playerid)
{
	if (APlayerData[playerid][JobStarted] == true)
	{
		// Clear all data about the job from the player, so he can start a new one
		APlayerData[playerid][JobStarted] = false;
		APlayerData[playerid][JobStep] = 0;
		APlayerData[playerid][JobID] = 0;
		APlayerData[playerid][VehicleTimerTime] = 0;
		APlayerData[playerid][VehicleID] = 0;
		APlayerData[playerid][TrailerID] = 0;
		APlayerData[playerid][JobLoc1] = 0;
		APlayerData[playerid][JobLoc2] = 0;
		// If the player was doing the "tow broken vehicle" job-type, check if there was a vehicle created
		if (APlayerData[playerid][LoadID] != 0)
		{
			DestroyVehicle(APlayerData[playerid][LoadID]); // Destroy the vehicle
			APlayerData[playerid][LoadID] = 0; // Clear the LoadID
		}

		// Delete the checkpoints
		DisablePlayerCheckpoint(playerid);
		DisablePlayerRaceCheckpoint(playerid);
		// Reset the missiontext
		TextDrawSetString(APlayerData[playerid][MissionText], RoadWorker_NoJobText);
		// Kill the VehicleTimer and LoadingTimer (mission-timer)
		KillTimer(APlayerData[playerid][VehicleTimer]);
		KillTimer(APlayerData[playerid][LoadingTimer]);
	}

	return 1;
}



// This function creates a random vehicle, spawns it and damages it and protects it from the /cleanupcars command, so admins cannot
// bug missions by cleaning up the world from spawned cars
CreateBrokenVehicle(Float:x, Float:y, Float:z)
{
	// Setup local variables
	new vid, panels, doors, lights, tires;
	new paramsengine, paramslights, paramsalarm, paramsdoors, paramsbonnet, paramsboot, paramsobjective;
	new BrokenVids[] = {400, 401, 402, 404, 405, 409, 410, 411, 412, 415, 419, 420, 421, 424, 426, 429, 434, 436, 438, 439, 442, 445, 451, 458, 466, 467, 474, 475, 477, 479, 480, 489, 490, 491, 492, 494, 495, 496, 500, 502, 503, 504, 505, 506, 507, 516, 517, 518, 526, 527, 528, 529, 533, 534, 535, 536, 540, 541, 542, 543, 545, 546, 547, 549, 550, 551, 552, 554, 555, 558, 559, 560, 561, 562, 565, 566, 567, 568, 575, 576, 579, 580, 582, 585, 587, 588, 589, 596, 597, 598, 599, 600, 602, 603};

	// Create the vehicle (choose a random vehicle from the array BrokenVids)
    vid = CreateVehicle(BrokenVids[random(sizeof(BrokenVids))], x, y, z, random(360), random(126), random(126), 3600);
	// Also set the data to prevent /cleanupcars deleting this vehicle
	AVehicleData[vid][Owned] = true;
	// Create an arrow above the vehicle to point to it (objective) and lock the doors so nobody can steal it
	GetVehicleParamsEx(vid, paramsengine, paramslights, paramsalarm, paramsdoors, paramsbonnet, paramsboot, paramsobjective);
	SetVehicleParamsEx(vid, paramsengine, paramslights, paramsalarm, true, paramsbonnet, paramsboot, true);

	// Damage all components of the vehicle
	tires = encode_tires(1, 1, 1, 1); // All tires popped
	panels = encode_panels(3, 3, 3, 3, 3, 3, 3); // All panels broken off
	doors = encode_doors(4, 4, 4, 4, 4, 4); // All doors broken
	lights = encode_lights(1, 1, 1, 1); // All lights damaged
	// Update the damage status of the vehicle
	UpdateVehicleDamageStatus(vid, panels, doors, lights, tires);
	// Set the vehicle damage quite low (this will make the vehicle smoke)
	SetVehicleHealth(vid, 300.0);

	return vid;
}



encode_tires(tire1, tire2, tire3, tire4)
{
	return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);
}
encode_panels(flp, frp, rlp, rrp, windshield, front_bumper, rear_bumper)
{
    return flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}
encode_doors(bonnet, boot, driver_door, passenger_door, behind_driver_door, behind_passenger_door)
{
    #pragma unused behind_driver_door
    #pragma unused behind_passenger_door
    return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}
encode_lights(light1, light2, light3, light4)
{
    return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
}

