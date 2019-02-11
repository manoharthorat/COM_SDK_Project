
#define PI 3.14159265
#include<Windows.h>
#include<math.h>
#include "TrigonometricClassFactoryServer.h"

double radian;
class CTrigonometric : public ISin, ICos, ITan, ICot, ISec, ICosec
{
private:
	long m_cRef;
public:
	CTrigonometric();
	~CTrigonometric();

	HRESULT __stdcall QueryInterface(REFIID, void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release();

	HRESULT __stdcall MySin(double, double *);
	HRESULT __stdcall MyCos(double, double *);
	HRESULT __stdcall MyTan(double, double *);
	HRESULT __stdcall MyCot(double, double *);
	HRESULT __stdcall MySec(double, double *);
	HRESULT __stdcall MyCosec(double, double*);
};

class CTrigonometricClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	CTrigonometricClassFactory();
	~CTrigonometricClassFactory();

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release();

	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void **);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfServevrLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return(TRUE);
}


CTrigonometric::CTrigonometric()
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CTrigonometric::~CTrigonometric()
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}


HRESULT CTrigonometric::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<ISin *>(this);
	}
	else if (riid == IID_ISin)
	{
		*ppv = static_cast<ISin *>(this);
	}
	else if (riid == IID_ICos)
	{
		*ppv = static_cast<ICos *>(this);
	}
	else if (riid == IID_ITan)
	{
		*ppv = static_cast<ITan *>(this);
	}
	else if (riid == IID_ICot)
	{
		*ppv = static_cast<ICot *>(this);
	}
	else if (riid == IID_ISec)
	{
		*ppv = static_cast<ISec *>(this);
	}
	else if (riid == IID_ICosec)
	{
		*ppv = static_cast<ICosec *>(this);
	}
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CTrigonometric::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CTrigonometric::Release()
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}
	return (m_cRef);
}
HRESULT CTrigonometric::MySin(double radian, double * result)
{
	*result = sin(radian);
	return(S_OK);
}

HRESULT CTrigonometric::MyCos(double radian, double * result)
{
	
	*result = cos(radian);
	return(S_OK);
}

HRESULT CTrigonometric::MyTan(double radian, double * result)
{
	*result = tan(radian);
	return(S_OK);
}

HRESULT CTrigonometric::MyCot(double radian, double * result)
{


	*result = 1/tan(radian);
	return(S_OK);
}
HRESULT CTrigonometric::MySec(double radian, double * result)
{
	*result = 1 / cos(radian);
	return(S_OK);
}
HRESULT CTrigonometric::MyCosec(double radian, double * result)
{
	*result = 1 / sin(radian);
	return(S_OK);
}
CTrigonometricClassFactory::CTrigonometricClassFactory()
{
	m_cRef = 1;
}

CTrigonometricClassFactory::~CTrigonometricClassFactory()
{

}

HRESULT CTrigonometricClassFactory::QueryInterface(REFIID riid, void ** ppv)
{
	if (riid == IID_IUnknown)
	{
		*ppv = static_cast<IClassFactory *>(this);
	}
	else if (riid == IID_IClassFactory)
	{
		*ppv = static_cast<IClassFactory *>(this);
	}
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CTrigonometricClassFactory::AddRef()
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CTrigonometricClassFactory::Release()
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return 0;
	}
	return m_cRef;
}

HRESULT CTrigonometricClassFactory::CreateInstance(IUnknown * pUnkOuter, REFIID riid, void ** ppv)
{
	HRESULT hr;
	if (pUnkOuter != NULL)
	{
		return(CLASS_E_NOAGGREGATION);
	}
	CTrigonometric * pCTrigonometric = NULL;
	pCTrigonometric = new CTrigonometric;
	if (pCTrigonometric == NULL)
	{
		return(E_OUTOFMEMORY);
	}
	hr = pCTrigonometric->QueryInterface(riid, ppv);
	pCTrigonometric->Release();
	return(hr);
}

HRESULT CTrigonometricClassFactory::LockServer(BOOL Flock)
{
	if (Flock)
	{
		InterlockedIncrement(&glNumberOfServevrLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServevrLocks);
	}
	return(S_OK);
}

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	HRESULT hr;
	if (rclsid != CLSID_Trigonometric)
	{
		return (CLASS_E_CLASSNOTAVAILABLE);
	}

	CTrigonometricClassFactory * pCTrigonometricClassFactory=NULL;
	pCTrigonometricClassFactory = new CTrigonometricClassFactory;

	if (pCTrigonometricClassFactory == NULL)
	{
		return(E_OUTOFMEMORY);
	}
	hr = pCTrigonometricClassFactory->QueryInterface(riid, ppv);
	pCTrigonometricClassFactory->Release();
	return(hr);
}

HRESULT __stdcall DllCanUnloadNow()
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServevrLocks == 0))
	{
		return (S_OK);
	}
	else
	{
		return(FALSE);
	}
}
