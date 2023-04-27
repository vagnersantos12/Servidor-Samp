/*
====================
    Timer com Callback
        By: SuB_ZeRo0_
====================
*/

#include <a_samp>
#include <Dini>

//News
new tempoNew[MAX_PLAYERS];
//Defines
#define Lugar "RPG/tempo/%s.ini" //Salva o tempo
#define Tempo 60000 //Tempo para calcular
#define MinT 3600000 //Tempo minimo [De preferência coloque multiplos do Tempo]

forward OnPlayerTimerFinish(playerid);
stock PName(playerid) {new namme[25];GetPlayerName(playerid,namme,25);return namme;}
stock FormatConta(Nome[]) {new nnn[35];format(nnn,35,Lugar,Nome);return nnn;}

stock OnPlayerConnect_SZTimer(playerid) 
{
	if(!fexist(FormatConta(PName(playerid)))) 
	{
		new File:P=fopen(FormatConta(PName(playerid)),io_write);
		fclose(P);
		dini_IntSet(FormatConta(PName(playerid)),"Tempo",0);
	}
	tempoNew[playerid]=SetTimerEx("ContT",Tempo,true,"d",playerid);
	return 1;
}
stock OnPlayerDisconnect_SZTimer(playerid) 
{
	KillTimer(tempoNew[playerid]);
	return 1;
}
stock GetTimeToFinish(playerid) 
{
	new timenow=dini_Int(FormatConta(PName(playerid)),"Tempo");
	new conta=((MinT/60000)-timenow);
	return conta;
}

forward ContT(playerid);
public ContT(playerid) 
{
	new o=dini_Int(FormatConta(PName(playerid)),"Tempo");
	dini_IntSet(FormatConta(PName(playerid)),"Tempo",o+1);
	if(((o+1)*Tempo)>=MinT) {
		CallRemoteFunction("OnPlayerTimerFinish","d",playerid);
		dini_IntSet(FormatConta(PName(playerid)),"Tempo",0);
	}
	return 1;
}