//************************************************************************************************************************************
// You may edit these values if you like
//************************************************************************************************************************************

// Default max number of players is set to 500, re-define it to 50
#undef MAX_PLAYERS
#define MAX_PLAYERS 500

// Bank system
new bool:IntrestEnabled = true; // The intrest has been enabled (or disabled when false)
new Float:BankIntrest = 0.001; // The intrest a player receives every hour is by default 0.1% (0.001 means 0.1%)
								// Setting this to 1.0 would mean 100%, that would double the player's bank account every hour)

// Set timer-delay for exiting houses (this timer freezes a player when he exits a house, this allows the game to load the environment
// before the player starts to fall, also the player's vehicles assigned to the house he exits from, are respawned by this timer)
new ExitHouseTimer = 1000;
new ExitBusinessTimer = 1000;

// This allows you to toggle the red houses on the map (bought houses appear on the map as red house icons when this is set to "true")
new bool:ShowBoughtHouses = false;

// Define maximum fuel amount (default: 5000) and maximum price for a complete refuel (default: 1000)
// Changing MaxFuel changes how fast a vehicle will run without fuel
//      (setting it to 2500 for example, let's vehicles run out of fuel twice as fast)
// RefuelMaxPrice is the price you pay for a total refuel (when the vehicle has no more fuel), the price to pay is calculated
//      by the amount of fuel to refuel (pay 50% of RefuelMaxPrice when vehicle has half a fuel-tank left)
new MaxFuel = 5000;
new RefuelMaxPrice = 1000;

// Define housing parameters
#define MAX_HOUSES					2000 // Defines the maximum number of houses that can be created
#define MAX_HOUSESPERPLAYER			5 // Defines the maximum number of houses that any player can own
#define HouseUpgradePercent         100 // Defines the percentage for upgrading a house (house of 10m can be upgraded for 5m when set to 50)
#define ParkRange                   150.0 // Defines the range for parking the vehicle around the house (default = 150m)

// Define business parameters
#define MAX_BUSINESS                1000 // Defines the maximum number of businesses that can be created
#define MAX_BUSINESSPERPLAYER		3 // Defines the maximum number of businesses that any player can own

// Defines for the toll-system
#define MAX_TOLLGATES				20

// Defines for spikestrips
#define MAX_SPIKESTRIPS             10 // Defines a maximum of 10 spikestrips

// Defines for the speedcameras
#define MAX_CAMERAS					100

// Defines for police
new bool:PoliceGetsWeapons = false;
// These are the weapons that a police player will get when "PoliceGetsWeapons = true"
// 5 = Baseball Bat
// 24 = Desert Eagle
// 25 = Shotgun
// 28 = Micro SMG
// 30 = AK-47
// 34 = Sniper Rifle
// 38 = Minigun
// 39 = Satchel Charge
// 41 = Spraycan
// 10 = Purple Dildo
// 46 = Parachute
// 40 = Detonator
new APoliceWeapons[12] = {5, 24, 25, 28, 30, 34, 38, 39, 41, 10, 46, 40};
new PoliceWeaponsAmmo = 5000;



// Jailing system variables
new DefaultJailTime = 120; // Set default jailtime to 2 minutes
new DefaultFinePerStar = 1000; // Set the fine for each wanted level (star)
new DefaultWarnTimeBeforeJail = 60; // Allow the wanted player 60 seconds to pull over (always set this value to multiples of 5: 5, 10, 15, 20, ...)



// Courier variables
new Float:CourierJobRange = 1000.0;
new PaymentPerPackage = 500;



// Unclamp price per vehicle
new UnclampPricePerVehicle = 20000;

