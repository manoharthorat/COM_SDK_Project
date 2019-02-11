struct Animal
{
	char Phylum[50];
	char Class[50];
	char Order[50];
	char Family[50];
	char Genus[50];
	char Species[50];
};

extern "C" Animal  ShowDetails(TCHAR * name);
