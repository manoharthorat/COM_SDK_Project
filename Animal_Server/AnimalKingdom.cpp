#include<Windows.h>
#include "AnimalKingdom.h"
BOOL WINAPI DllMain(HANDLE handle, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		//MessageBox(NULL, TEXT("Inside the PROCESS_ATTACH"), TEXT("AnimalKingdom Dll"), MB_OK);
		break;
	case DLL_PROCESS_DETACH:
		//MessageBox(NULL, TEXT("Inside the PROCESS_ATTACH_DETACH"), TEXT("AnimalKingdom Dll"), MB_OK);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return(TRUE);
}

extern "C" Animal  ShowDetails(TCHAR * name)
{
	Animal obj;
	TCHAR str[4096];
	int num = 10;
	//MessageBox(NULL, str, name, MB_OK);
	//MessageBox(NULL, name, TEXT("AnimalKingdom Dll"), MB_OK);
	if (strcmp(name,"COW")==0)
	{
		//MessageBox(NULL, str, TEXT("COW"), MB_OK);
		obj = { "Chordata", "Mammalia", "Artidactyla", "Bovidae", "Bos", "Taurus" };

		//wsprintf(str,TEXT("Phylum = Chordat \n Class = Mammalia \n Order = Artiodactyla \n Family = Bovidae \n Genus = Bos \n Species = Taurus"));
		
		return obj;
	}
	
	else if (strcmp(name, "Grizzly Bear") == 0)
	{
		//MessageBox(NULL, str, TEXT("Grizzly Bear"), MB_OK);
		obj = { "Chordata", "Mammalia", "Carnivora", "Ursidae", "Ursus", "Arctos Horribilis" };
		//wsprintf(str, TEXT("Phylum = Chordat \n Class = Mammalia \n Order = Carniora \n Family = Ursidae \n Genus = Ursus \n Species = Arctos horribilies"));
		
		return obj;
	}
	else if (strcmp(name,"Clown Fish")==0)
	{
		//MessageBox(NULL, str, TEXT("Clown Fish"), MB_OK);
		obj = { "Chordata", "Actinopterygii", "Perciformes", "Pomacentridaie", "Amphiprion", "Chilenis" };
		//wsprintf(str, TEXT("Phylum = Chordat \n Class = Actinopterygii \n Order = Perciformes \n Family = Pomacentridaie \n Genus = Amphiprion \n Species = Ocellaris"));
		
		return obj;
	}
	else if (strcmp(name,"Chilean flamingo")==0)
	{
			//MessageBox(NULL, str, TEXT("Chilean flamingo"), MB_OK);
		obj = { "Chordata", "Aves", "Ciconiiformes", "Phoenicopteridae", "Phoenicopterus", "Chilenis" };
	//	wsprintf(str, TEXT("Phylum = Chordat \n Class = Aves \n Order = Ciconiiformes \n Family = Phoenicopteridae \n Genus = Phoenicopterus \n Species = Chilenis"));
	
		return obj;
	}
	else if (strcmp(name,"Blue whale")==0)
	{
		//MessageBox(NULL, str, TEXT("Blue whale"), MB_OK);
		obj = { "Chordata", "Mammalia", "Cetacea", "Balaenopteridae", "Balaenoptera", "Musculus" };
		//wsprintf(str, TEXT("Phylum = Chordat \n Class = Mammalia \n Order = Cetacea \n Family = Balaenopteridae \n Genus = Balaenoptera\n Species = Musculus"));
		
		return obj;
	}
	else if (strcmp(name,"Horse")==0)
	{

		//MessageBox(NULL, str, TEXT("Horse"), MB_OK);
		obj = { "Chordata", "Mammalia", "Perissodactyla", "Equidae", "Equus", "Caballus" };
		//wsprintf(str, TEXT("Phylum = Chordat \n Class = Mammalia \n Order = Perissodactyla \n Family = Equidae\n Genus = Equus\n Species = Cabllus"));
		
		return obj;
	}
	else {
		MessageBox(NULL, TEXT("new dll Something wrong"), TEXT("AnimalKingdom Dll"), MB_OK);
	}
}
