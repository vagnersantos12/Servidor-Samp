// Debug messages
#define TXT_DebugInfo "Debug information"
#define TXT_HousesFixed "Houses that have been fixed: %i"
#define TXT_LastVehicleID "Last vehicle ID: %i"
#define TXT_LastObjectID "Last object ID: %i"
#define TXT_TotalHouses "Loaded %i houses"
#define TXT_TotalBusiness "Loaded %i businesses"
#define TXT_TotalSpeedCameras "Loaded %i speed-camera's"

// Define the message that's sent to all players when a player joins the server
#define TXT_PlayerJoinedServer "{0000FF}O jogador '{FFFF00}%s{0000FF}' (id: {FFFF00}%i{0000FF}) entrou no server."
#define TXT_PlayerLeftServer "{0000FF}O jogador '{FFFF00}%s{0000FF}' (id: {FFFF00}%i{0000FF}) saiu do server."

// Banned texts (also kick messages)
#define TXT_StillBanned "{FF0000}Você está banido" // Define the text that the player sees when he's still banned when trying to login
#define TXT_BannedDuration "{FF0000}Falta: Dias: %i, Horas: %i, Minutos: %i, Segundos: %i" // Define the remaining ban-time text
#define TXT_KickSpeedHack "{FF0000}Você foi kickado por usar speed-hack ou air-brake"
#define TXT_KickJetPackHack "{FF0000}Você foi kickado por usar jetpack-hack"
#define TXT_KickHealthHack "{FF0000}Você foi kickado por usar health-hack"

// Dialog buttons
#define TXT_DialogButtonCancel "Cancelar" // Define the text on the "Cancel"-button for dialogs
#define TXT_DialogButtonBuy "Comprar" // Define the text on the "Buy"-button for dialogs
#define TXT_DialogButtonSpawn "Spawn"
#define TXT_DialogButtonSelect "Selecionar"
#define TXT_DialogButtonYes "Sim"
#define TXT_DialogButtonNo "Nao"

// Dialog entries
#define TXT_DialogEntryNext "Próximo..."

// The register dialog
#define TXT_DialogRegisterTitle "Bem Vindo" // Define the title-message on top of the register-dialog
#define TXT_DialogRegisterMsg "Insira uma senha para registrar:" // Define the actual message in the register-dialog
#define TXT_DialogRegisterButton1 "Registrar" // Define the text on the "register" button for the register-dialog
#define TXT_AccountRegistered "{00FF00}Sua conta foi registrada com sucesso!"
#define TXT_RegisterEnterValidPassword "Por favor digite uma senha válida para registrar:"
#define TXT_PlayerMustRegister "{FF0000}Você deve se registrar para poder jogar, você foi kickado!"

// The login dialog
#define TXT_DialogLoginTitle "Transportando o Brasil" // Define the title-message on top of the login-dialog
#define TXT_DialogLoginMsg "Insira a senha para logar:" // Define the actual message in the login-dialog
#define TXT_DialogLoginButton1 "Logar" // Define the text on the "login" button for the login-dialog
#define TXT_LoggedIn "{00FF00}Você logou, Bem Vindo ao Transportando o Brasil novamente."
#define TXT_WrongPassword "{FF0000}Você digitou a senha errada, você foi kickado"
#define TXT_LoginEnterValidPassword "Faça o login, digitando a sua senha:"
#define TXT_PlayerMustLogin "{FF0000}Você deve entrar para jogar, você foi kickado!"
#define TXT_FailedLoginProperly "{FF0000}Você não conseguiu entrar corretamente, você foi kickado"

// The license dialog
#define TXT_DialogLicenseTitle "Selecionar licenca:" // Define the title-message on top of the licenses-dialog
#define TXT_DialogLicenseList "Licenca de caminhao ($50.000, 100 points)\r\nLicenca de onibus ($25.000, 50 points)" // Define the licenses and their price
#define TXT_PickupText "Comprar licenca" // Defines the text that's shown above the pickup for buying licenses
#define TXT_TruckerLicenseBought "{00FF00}Você adquiriu a licenca de caminhao."
#define TXT_TruckerLicenseNotEnoughMoney "{FF0000}Você precisa de R$50.000 e 100 pontos de score para comprar a licenca de caminhao"
#define TXT_TruckerLicenseOwned "{FF0000}Você já comprou a licença"
#define TXT_TruckerLicenseWrongClass "{FF0000}Você deve ser um caminhoneiro para comprar uma licença de caminhao"
#define TXT_BusLicenseBought "{00FF00}Você adquiriu uma licenca de onibus"
#define TXT_BusLicenseNotEnoughMoney "{FF0000}Você precisa de R$25.000 e 50 pontos de score para comprar a licenca de onibus"
#define TXT_BusLicenseOwned "{FF0000}Você já comprou a licenca"
#define TXT_BusLicenseWrongClass "{FF0000}Você precisa ser motorista de onibus para comprar a licenca de onibus"



// Dialog related for /car, /plane, ...
#define TXT_DialogCarTitle "Escolha o carro (page %i):"
#define TXT_DialogPlaneTitle "Escolha o aviao (page %i):"
#define TXT_DialogTrailerTitle "Escolha a carga (page %i):"
#define TXT_PlayerSpawnedVehicle "{00FF00}%s spawnou o veiculo %i (modelo-id = %i) para as coordenadas: x=%4.2f, y=%4.2f, z=%4.2f"
#define TXT_ChangedWeather "{00FF00}Você alterou a agua")
#define TXT_DialogCommandTitle "Lista de comandos (page %i):"

// Trucker related
#define TXT_PlayerCompletedTruckJob "{FFFFFF}O Camnhoneiro {FF00FF}%s{FFFFFF} transportou {0000FF}%s{FFFFFF} com sucesso."
#define TXT_PlayerCompletedTruckJobInfo "de {00FF00}%s{FFFFFF} para {00FF00}%s{FFFFFF}"
#define TXT_TruckerBonusOverloaded "{00FF00}Você também ganhou um bônus por estar sobrecarregado: R$%i"
#define TXT_TruckerBonusMafiaLoad "{00FF00}Você também ganhou um bônus para a entrega de uma máfia-carga: R$%i"
#define TXT_TruckerBonusOwnVehicle "{00FF00}Você também ganhou um bônus por usar o seu próprio caminhão: R$%i"
#define TXT_TruckerMustEnterVehicle "{FF0000}Você deve entrar no seu veículo ou re-anexar o seu reboque"
#define TXT_TruckerOverloaded "{FF0000}Você está sobrecarregado! Evite a polícia!"
#define TXT_TruckerMafiaInterested "~r~A Máfia está interessada na sua carga~w~"
#define TXT_TruckerDialogSelectLoad "Selecionar carga:"
#define TXT_TruckerDialogSelectStartLoc "Selecione local de carga:"
#define TXT_TruckerDialogSelectEndLoc "Selecione local de descarga:"
#define TXT_NeedVehicleToProceed "{FF0000}Você precisa estar no seu veículo para prosseguir"
#define TXT_NeedTrailerToProceed "{FF0000}Você precisa ter o seu reboque atrelado para prosseguir"
#define TXT_NeedOnFootToProceed "{FF0000}Você precisa estar a pé para continuar"

// Busdriver related
#define TXT_PlayerCompletedBusLine "{FFFFFF}O Motorista de ônibus {FF00FF}%s{FFFFFF} completou a linha {0000FF}%i{FFFFFF} com sucesso."
#define TXT_BusDriverMissionPassed "Trabalho terminado" // Define the game-text that shows when the player passed a busdriver mission
#define TXT_BusDriverJobInfo "~w~Linha ~y~%i~w~ (~g~%s~w~): ~b~%i~w~ no onibus"
#define TXT_BusDriverBusStopInfo "~w~Linha ~y~%i~w~ (~g~%s~w~): ~b~%i~w~ no onibus, ~b~%i~w~ no ponto"
#define TXT_BusDriverReward "~g~Você ganhou R$%i~w~"
#define TXT_BusDriverMustEnterBus "{FF0000}Você deve entrar em seu ônibus"
#define TXT_SelectBusRoute "Selecione a rota:"
#define TXT_BusdriverAlreadyDoingJob "{FF0000}Você já está fazendo um trabalho."

// Mafia related
#define TXT_PlayerCompletedMafiaJob "{FFFFFF}O Mafioso {FF00FF}%s{FFFFFF} transportou {0000FF}%s{FFFFFF} com sucesso."
#define TXT_PlayerCompletedMafiaJobInfo "de {00FF00}%s{FFFFFF} para {00FF00}%s{FFFFFF}"
#define TXT_MafiaMustEnterVehicle "{FF0000}Você precisa estar no veículo"
#define TXT_MafiaDeliverStolenLoad "~w~Leve a ~b~ carga roubada~w~ para o ~r~esconderijo~w~"
#define TXT_MafiaDeliveredStolenLoad "{00FF00}Você entregou a carga-mafia roubada, você ganhou R$5000"

// Police related
#define TXT_PoliceWarnPlayer "~r~É a policia! Encoste o veículo!~w~"
#define TXT_PoliceFinedPlayerReward "{00FF00}Voce mutou %s e ganhou R$%i"
#define TXT_PlayerGotFinedByPolice "{FF0000}Você foi pego por %s e pagou uma multa de R$%i"
#define TXT_PoliceFinedPlayer "{00FF00}O Oficial %s multou %s"
#define TXT_PoliceJailedPlayerReward "{00FF00}Você prendeu %s e ganhou R$%i"
#define TXT_PlayerGotJailedByPolice "{FF0000}Você foi preso por %s durante %i minutos"
#define TXT_PoliceJailedPlayer "{00FF00}O Oficial %s prendeu %s durante %i minutos"

// Pilot related
#define TXT_PlayerCompletedPilotJob "{FFFFFF}O Piloto {FF00FF}%s{FFFFFF} transportou {0000FF}%s{FFFFFF} com sucesso."
#define TXT_PlayerCompletedPilotJobInfo "de {00FF00}%s{FFFFFF} para {00FF00}%s{FFFFFF}"

// Courier related
#define TXT_CourierMustEnterVehicle "{FF0000}Você precisa estar no veículo."
#define TXT_PlayerCompletedCourierJob "{FFFFFF}O Agente dos Correios {FF00FF}%s{FFFFFF} entregou {0000FF}%i{FFFFFF} pacotes com sucesso."
#define TXT_PackageDeliveredGameText "Pacote entregue"
#define TXT_PackageDeliveredMessage "{00FF00}Pacote entregue"

// Roadworker related
#define TXT_RepairSpeedcamera "~w~Fazer manutencao no ~r~radar ~w~ indicado no mapa"
#define TXT_TowBrokenVehicle "~w~Rebocar o ~r~veiculo quebrado~w~ de ~b~%s~w~ para o triturador"
#define TXT_DeliverBrokenVehicle "~w~Rebocar o veiculo quebrado de ~b~%s~w~ para o ~r~triturador~w~"
#define TXT_RoadworkerMustEnterVehicle "{FF0000}Você precisa estar no veículo e recuperar o trailer"
#define TXT_RoadworkerMissionPassed "Trabalho finalizado" // Define the game-text that shows when the player passed a roadworker mission

// Job related, for all classes
#define TXT_RewardJob "{00FF00}Voce terminou o trabalho e ganhou R$%i"
#define TXT_FailedMission "~w~Voce ~r~falhou~w~ com seu trabalho. Voce perdeu ~y~R$1000~w~ para cobrir as despesas." // Define game-text when player fails a mission

// Class related
#define TXT_ClassTrucker "Caminhoneiro" // Define the game-text that shows when the player is choosing classes (this one = trucker)
#define TXT_ClassBusDriver "Motorista de onibus" // Define the game-text that shows when the player is choosing classes (this one = bus-driver)
#define TXT_ClassPilot "Piloto" // Define the game-text that shows when the player is choosing classes (this one = pilot)
#define TXT_ClassPolice "Policial" // Define the game-text that shows when the player is choosing classes (this one = police)
#define TXT_ClassMafia "Mafia" // Define the game-text that shows when the player is choosing classes (this one = mafia)
#define TXT_ClassCourier "Correios" // Define the game-text that shows when the player is choosing classes (this one = courier)
#define TXT_ClassAssistance "Mecanico" // Define the game-text that shows when the player is choosing classes (this one = assistance)
#define TXT_ClassRoadWorker "DNIT" // Define the game-text that shows when the player is choosing classes (this one = roadworker)

// No-job texts for all classes
#define Trucker_NoJobText "Sem servico no momento. Use \"~y~/trabalhar~w~\" para iniciar o trabalho"
#define BusDriver_NoJobText "Sem servico no momento. Use \"~y~/trabalhar~w~\" para iniciar o trabalho"
#define Pilot_NoJobText "Sem servico no momento. Use \"~y~/trabalhar~w~\" para iniciar o trabalho"
#define Police_NoJobText "~r~'RMB'~w~ multas em um jogador (a pe), ~r~'LCTRL'~w~ advertencias de um jogador (no veiculo)"
#define Mafia_NoJobText "Veiculo de sequestro ~r~marcado~w~ entre no carro e use \"~y~/trabalhar~w~\" para iniciar o trabalho"
#define Courier_NoJobText "Sem servico no momento. Use \"~y~/trabalhar~w~\" para iniciar o trabalho"
#define Assistance_NoJobText "~r~'RMB'~w~ reparos e abastecimentos de veiculo (a pé), ~r~'LCTRL'~w~ Correcoes de seu próprio veiculo"
#define RoadWorker_NoJobText "Sem servico no momento. Use \"~y~/trabalhar~w~\" para iniciar o trabalho"

// Command related
#define TXT_PlayerRescued "{0000FF}Você foi reduzido. O valor foi R$200"

// Fuel related
#define TXT_Refuelling "~g~Abastecendo..." // Define the game-text that shows when you're refuelling your vehicle
#define TXT_PickupRefuel "Buzine para chamar o frentista"
#define TXT_RefuelledVehicle "{00FF00}Você reabasteceu seu veículo por R$%i"
#define TXT_CannotRefuelVehicle "{FF0000}Você não tem dinheiro para abastecer seu veículo."

// Gametexts for loading/unloading
#define TXT_LoadingGoods "~r~Carregando %s... ~w~Espere"
#define TXT_UnloadingGoods "~r~Descarregando %s... ~w~Espere"
#define TXT_TruckerLoadingGoods "~r~Carregando seu caminhao... ~w~Espere"
#define TXT_TruckerUnloadingGoods "~r~Descarregando seu caminhao... ~w~Espere"
#define TXT_TransportingFromToPickup "~w~Transportando ~b~%s~w~ de ~r~%s~w~ para %s"
#define TXT_TransportingFromToDeliver "~w~Transportando ~b~%s~w~ de %s para ~r~%s~w~"
#define TXT_HaulingCargoFromToPickup "~w~Tansportando ~b~%s~w~ de ~r~%s~w~ para %s"
#define TXT_HaulingCargoFromToDeliver "~w~Transportando ~b~%s~w~ de %s para ~r~%s~w~"
#define TXT_PickupCargoAt "{00FF00}Colete o %s em %s"
#define TXT_DeliverCargoTo "{00FF00}Entregue %s em %s"

// Cardealer related
#define TXT_PickupCarDealer "Use \"/alugarcarro\"\para alugar um carro"
#define TXT_BuyRentCarEmptyList "{FF0000}Esta é uma lista vazia, o administrador pode ter desabilitado todos os veículos desta classe"
#define TXT_RentBike "Alugar Bike:"
#define TXT_RentBoat "Alugar Barco:"
#define TXT_RentConvertible "Alugar converssivel:"
#define TXT_RentHelicopter "Alugar helicoptero:"
#define TXT_RentIndustrial "Alugar um veículo industrial:"
#define TXT_RentLowRider "Alugar um low-rider:"
#define TXT_RentOffRoad "Alugar um off-road:"
#define TXT_RentPlane "Alugar um aviao:"
#define TXT_RentPublicService "Alugar um veiculo de servico publico:"
#define TXT_RentRC "Alugar RC:"
#define TXT_RentSaloon "Alugar Carros Saloon:"
#define TXT_RentSport "Alugar Carros Sport:"
#define TXT_RentStationWagon "Alugar vagao de trilho:"
#define TXT_RentTrailer "Alugar Carga:"
#define TXT_RentUnique "Alugar Carros Unicos:"
#define TXT_AlreadyRentedVehicle "{FF0000}Você já tinha um veículo alugado, mas foi substituído por um novo"
#define TXT_PlayerRentsVehicle "{00FF00}Você alugou um {FFFF00}%s{00FF00} por R${FFFF00}%i{00FF00}"
#define TXT_RentingTooExpensive "{FF0000}Você não pode dar ao luxo de alugar este veículo"
#define TXT_BuyBike "Comprar Bike:"
#define TXT_BuyBoat "Comprar Barco:"
#define TXT_BuyConvertible "Comprar um converssivel:"
#define TXT_BuyHelicopter "Comprar um helicoptero:"
#define TXT_BuyIndustrial "Comprar um veiculo industrial:"
#define TXT_BuyLowRider "Comprar um low-rider:"
#define TXT_BuyOffRoad "Comprar um off-road:"
#define TXT_BuyPlane "Comprar um aviao:"
#define TXT_BuyPublicService "Comprar um carro de servico publico:"
#define TXT_BuyRC "Comprar um RC:"
#define TXT_BuySaloon "Comprar um Saloon:"
#define TXT_BuySport "Comprar um carro Sport:"
#define TXT_BuyStationWagon "Comprar um vagao e trilho:"
#define TXT_BuyTrailer "Comprar uma carga:"
#define TXT_BuyUnique "Comrpar um carro unico:"



// Jail related
#define TXT_JailTimer "~w~Preso: ~r~%i~w~"

// Speedometer related
#define TXT_SpeedometerSpeed "~w~Velocidade: ~b~%i~w~ KM/h"
#define TXT_SpeedometerFuel "~w~Combsutivel: %s"
#define TXT_SpeedometerCannotUseVehicle "{FF0000}Você não pode usar este veículo, é de propriedade de \"{FFFF00}%s{FF0000}\""
#define TXT_SpeedometerClampedVehicle "{FF0000}Este veículo está apreendido, você não pode usá-lo"
#define TXT_SpeedometerClampedVehicle2 "{FF0000}Você precisa liberá-lo para usar {FFFF00}/liberar"
#define TXT_PlayerCaughtSpeeding "{FF0000}Você foi capturado por um radar, ande com mais cautela!"

// Toll-gate related
#define TXT_PlayerPaysToll "Você pagou R$%i para o pedágio"

// Convoy related
#define TXT_PlayerStartsConvoy "O jogador {00FF00}%s{FFFFFF} quer comecar um {00FF00}comboio{FFFFFF}, para entrar use\"/comboio\""
#define TXT_PlayerJoinedConvoy "O jogador {00FF00}%s{FFFFFF} entrou no comboio"
#define TXT_YouJoinedConvoy "{00FF00}Você se juntou ao comboio"
#define TXT_WaitingLeaderJob "Espera o líder para iniciar um trabalho"
#define TXT_WaitingMembersToLoadCargo "À espera de todos os membros para carregar sua carga"
#define TXT_WaitingMembersToUnLoadCargo "À espera de todos os membros para descarregar sua carga"
#define TXT_ConvoyFull "{FF0000}O comboio está cheio"
#define TXT_ConvoyEnRoute "Este comboio é rota para seu destino, você não pode entrar nele"
#define TXT_LeaderCancelledConvoy "{FF0000}O lider cancelou o comboio"
#define TXT_MeetOtherConvoyMembers "{00FF00}Conheça os outros membros do comboio no ponto de carregamento"
#define TXT_ConvoyDistanceForLeader "{00FF00}Todo mundo precisa ficar 500 metros perto e você"
#define TXT_ConvoyDistanceForMember "{00FF00}Permanecer dentro de 500m do líder do comboio"
#define TXT_MemberNeedsCargoTrailer "Você precisa de um trailer"
#define TXT_MemberNeedsOreTrailer "Você precisa de um reboque de minério"
#define TXT_MemberNeedsFluidsTrailer "Você precisa de um reboque de fluidos"
#define TXT_AllMembersSameTrailer "{00FF00}Todos os membros têm o mesmo trailer, comboio está pronto para ir"
#define TXT_AllMembersNotSameTrailer "{FF0000}Nem todos os membros têm o mesmo trailer, comboio não pode iniciar ainda"
#define TXT_AllMembersLoadedCargo "{00FF00}Todos os membros têm carregado a sua carga, o comboio está pronto para prosseguir para o ponto de descarga"
#define TXT_MemberKickedByDistance "{FF0000}Você não ficou perto do líder, você foi expulso do comboio"
#define TXT_MemberFellBehind "Ojogador {00FF00}%s{FFFFFF} ficou para trás e foi expulso do comboio "
#define TXT_FinishedConvoy "{00FF00}Você finalizou o comboio e ganhou R$%i"
#define TXT_LeaderInfoBar "Membros: ~g~%i~w~, Membro mais distante: ~g~%s~w~, Distancia: ~r~%3.1f~w~"
#define TXT_MemberInfoBar "Líder: ~r~%s~w~, distancia: ~r~%3.1f~w~, membros: ~r~%i~w~"
#define TXT_CannotJoinJobStarted "{FF0000}Você já começou um trabalho, você não pode criar ou participar de um comboio"
#define TXT_ConvoyAllreadyJoined "{FF0000}Você já está em um comboio."
#define TXT_ConvoyNeedsTruckerClass "{FF0000}Você precis ser caminhoneiro para entrar ou criar um/no comboio"

// Timed messages
#define TXT_TimedRefuel "{808080}Você quer para reabastecer o seu veículo? Pare em uma PickUP reabastecer e buzine"
#define TXT_TimedConvoy "{808080}Você quer entrar num comboio? Use \"/comboio\" para iniciar ou entrar em um"
#define TXT_TimedGohome "{808080}Quer teleportar-se a sua casa? Use \"/irparacasa\" para ir"
#define TXT_TimedRentCar "{808080}Quer alugar um veículo? Visite a Wang Cars em Doherty, San Fierro"
#define TXT_TimedLicense "{808080}Você está cansado de cargas aleatórias de caminhoneiro / Motorisa de Onibus? Visite a alto-Escola em Doherty e compre a licenca"
#define TXT_TimedSpeedTraps "{808080}Cuidado com os radares(60kph na cidade, 90kph nas estradas, nas rodovias 120kph)"
#define TXT_TimedGoBusiness "{808080}Quer teleportar-se a sua empresa? Use \"/irempresa\" para ir"

// House-related
#define TXT_DefaultHouseName "%s Casa"
#define TXT_PlayerBoughtHouse "{33FF33}Você comprou a casa por R${FFCC33}%i"
#define TXT_PlayerOwnsMaxHouses "{FF0000}Você atingiu a quantidade máxima de casas por jogador"
#define TXT_ExitHouseReloadEnv "Espere ambiente de carga"
#define TXT_PickupHouseOwned "%s\nProprietário: %s\nLevel da casa: %i\n/entrar"
#define TXT_PickupHouseForSale "Casa avaliada em\nR$%i\nLevel Máximo: %i\n/comprarcasa"
#define TXT_DialogOldHouseName "Nome da casa antiga: %s"
#define TXT_DialogEnterNewHouseName "Ponha um novo nome na sua casa"
#define TXT_DialogSelectHouseUpgrade "Selecione a atualizaçao:"
#define TXT_HouseReachedMaxLevel "{FF0000}Sua casa chegou ao nível máximo, você não pode atualizá-la mais"
#define TXT_DialogBuyCarSelectClass "Selecione a classe do veiculo:"
#define TXT_HouseHasMaxVehicles "{FF0000}Essa casa atingiu o llimite máximo de carros por casa"
#define TXT_AlreadyBoughtRecentVehicle "{FF0000}Você já comprou um veículo recentemente, use \"/usarcarro\" e \"/estacionar\" para estacioná-lo antes de comprar um novo"
#define TXT_EmptyCarSlot "%s{FFFFFF}Slot vazio{FFFFFF}\n"
#define TXT_SelectVehicleToSell "Selecione o veiculo a vender:"
#define TXT_SelectVehicleToGet "Selecione veiculo que quer trazer a sua posição:"
#define TXT_NoHouseVehicles "{FF0000}Esta casa não tem veículos que lhe foram atribuídos"
#define TXT_SureSellHouse "Você tem certeza que quer vender sua casa por R$%i?"
#define TXT_AreYouSure "Tem certeza?"
#define TXT_CannotSellHouseWithCars "{FF0000}Você não pode vender uma casa que ainda tem carros atribuídos a ela"
#define TXT_PlayerUpgradedHouse "{00FF00}Você atualizou sua casa do level %i para $%i"
#define TXT_CannotAffordUpgrade "{FF0000}Você não pode pagar pela atualização"
#define TXT_NoHouseInSlot "{FF0000}Você não tem uma casa nesse slot"
#define TXT_ChangedHouseName "{00FF00}Você mudou o nome de sua casa"
#define TXT_PlayerBoughtVehicle "{00FF00}Você comprou um {FFFF00}%s{00FF00} por R${FFFF00}%i{00FF00}"
#define TXT_PlayerMustUseGetcarAndPark "{00FF00}Agora saia fora e ultilize\"{FFFF00}/usarcarro{00FF00}\" para usalo, depois use \"{FFFF00}/estacionar{00FF00}\" para estaciona-lo na sua casa"
#define TXT_PlayerMustUsePark "{00FF00}Você gerou o seu veículo, agora use \"{FFFF00}/estacionar{00FF00}\" para estacioná-lo na sua casa"
#define TXT_CannotAffordVehicle "{FF0000}Você não pode pagar por este carro"
#define TXT_PlayerSoldHouse "{00FF00}Você vendeu sua casa"
#define TXT_PlayerSoldVehicle "{00FF00}Você vendeu seu {FFFF00}%s{00FF00} por ${FFFF00}%i{00FF00}"
#define TXT_NoVehicleInSlot "{FF0000}Não ha carro nesse slot"
#define TXT_DialogTitleBuyInsurance "Comprar segurança?"
#define TXT_DialogBuyInsurance "Tem certeza de que quer comprar um seguro para os veículos de sua casa por R$%i?"
#define TXT_HouseAlreadyHasInsurance "{FF0000}Esta casa já tem um seguro para veículos"
#define TXT_PlayerBoughtInsurance "{00FF00}Você comprou seguro para todos os carros desta casa por R$%i"
#define TXT_CannotAffordInsurance "{FF0000}Você não pode pagar pelo seguro"

// Business related
#define TXT_PickupBusinessOwned "%s\nProprietário: %s\nLevel da empresa: %i\n/entrar"
#define TXT_PickupBusinessForSale "%s\nAvaliada em\nR$%i\nGanhos: R$%i\n/comprarempresa"
#define TXT_DefaultBusinessName "%s' Empresa"
#define TXT_PlayerBoughtBusiness "{33FF33}Você abriu um negócio por R${FFCC33}%i"
#define TXT_PlayerOwnsMaxBusinesses "{FF0000}Você já possui a quantidade máxima de empresas permitido por jogador"
#define TXT_NoBusinessInSlot "{FF0000}Você não possui empresa nesse slot"
#define TXT_DialogOldBusinessName "Nome antigo da empresa: %s"
#define TXT_DialogEnterNewBusinessName "Coloque novo nome na sua empresa"
#define TXT_ChangedBusinessName "{00FF00}Você mudou o nome da sua empresa"
#define TXT_BusinessReachedMaxLevel "{FF0000}Sua empresa atingiu o nível máximo, você não pode atualizá-la mais"
#define TXT_SureSellBusiness "Você tem certeza que quer vender seu negócio por R$%i?"
#define TXT_PlayerSoldBusiness "{00FF00}Você vendeu o seu negócio"

