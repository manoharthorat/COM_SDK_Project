
#define ID_CB		102
#define ID_ETPHYLUM	103
#define ID_ETCLASS	104 
#define ID_ETORDER	105
#define ID_ETFAMILY	106
#define ID_ETGENUS	107
#define ID_ETSPECIES 108 
#define ID_ALLCLEAR	109
#define ID_ANIMALCOMBO 110
#define ID_ETRESULT 111
#define ID_PBDATASTORE 112
#define ID_ETVELOCITY 113
#define ID_ETACCELERATION 114
#define ID_PBVCAL 115
#define ID_PBACAL 116
#define ID_ETDISTANCE 117
#define ID_ETTIME 118
#define ID_OK 119
#define ID_CANCEL 120
#define ID_ETINITIALVELOCITY 121
#define ID_ETFINALVELOCITY 122
#define ID_ETDELTATIME 123

#define ID_CBTRIGONOMETRIC 201
#define ID_CBDEGREE	202
#define ID_CBANIMAL 203
#define ID_TRIGO 204
#define ID_DEGREE 205



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

class ISin : public IUnknown
{
public:
	virtual HRESULT __stdcall MySin(double, double *) = 0;
};

class ICos : public IUnknown
{
public:
	virtual HRESULT __stdcall MyCos(double, double *) = 0;
};

class ITan : public IUnknown
{
public:
	virtual HRESULT __stdcall MyTan(double, double *) = 0;
};

class ICot : public IUnknown
{
public:
	virtual HRESULT __stdcall MyCot(double, double *) = 0;
};

class ISec : public IUnknown
{
public:
	virtual HRESULT __stdcall MySec(double, double *) = 0;
};

class ICosec : public IUnknown
{
public:
	virtual HRESULT __stdcall MyCosec(double, double *) = 0;
};

// {C760C77F-5638-4AA6-9D2F-9D9D8A8124D5}
const CLSID CLSID_Trigonometric = { 0xc760c77f, 0x5638, 0x4aa6, 0x9d, 0x2f, 0x9d, 0x9d, 0x8a, 0x81, 0x24, 0xd5 };

// {18222194-25AD-4985-8266-FD6EBFA7FF36}
const IID IID_ISin = { 0x18222194, 0x25ad, 0x4985, 0x82, 0x66, 0xfd, 0x6e, 0xbf, 0xa7, 0xff, 0x36 };

// {B06D02C7-3C70-4481-8EFB-1A4CD10547C0}
const IID IID_ICos = { 0xb06d02c7, 0x3c70, 0x4481, 0x8e, 0xfb, 0x1a, 0x4c, 0xd1, 0x5, 0x47, 0xc0 };

// {7F33FC1C-D9C1-4FC6-A22B-E45EBC966FA6}
const IID IID_ITan = { 0x7f33fc1c, 0xd9c1, 0x4fc6, 0xa2, 0x2b, 0xe4, 0x5e, 0xbc, 0x96, 0x6f, 0xa6 };

// {B2BE5D17-B398-4DB6-B660-1CE3046A2DD8}
const IID IID_ICot = { 0xb2be5d17, 0xb398, 0x4db6, 0xb6, 0x60, 0x1c, 0xe3, 0x4, 0x6a, 0x2d, 0xd8 };

// {1D2A5E99-7D20-4C57-B1C1-263FF683FCFF}
const IID IID_ISec = { 0x1d2a5e99, 0x7d20, 0x4c57, 0xb1, 0xc1, 0x26, 0x3f, 0xf6, 0x83, 0xfc, 0xff };

// {5070302B-853B-4B78-897B-057A57D04A59}
const IID IID_ICosec = { 0x5070302b, 0x853b, 0x4b78, 0x89, 0x7b, 0x5, 0x7a, 0x57, 0xd0, 0x4a, 0x59 };
