#import "Physics.tlb" no_namespace, raw_interfaces_only
#include "Debug/physics.tlh"


#define PI 3.14159265
#include<Windows.h>
#include<stdio.h>
#include <tchar.h>
#include "TrigonometricClassFactoryServer.h"

ISin * pISin = NULL;
ICos * pICos = NULL;
ITan * pITan = NULL;
ICot * pICot = NULL;
ISec * pISec = NULL;
ICosec * pICosec = NULL;
TCHAR temp1;
int i = 0;

TCHAR V_Distance[256];
TCHAR V_Time[256];

double dVelocity = 0.0;
double dAcceleration = 0.0;
double dInitialVelocity = 0.0;
double dFinalVelocity = 0.0;
double dTimeDelta = 0.0;



double dDistance = 00.00;
double dTime = 00.00;

TCHAR A_InitialVelocity[256];
TCHAR A_FinalVelocity [256];
TCHAR A_TimeDelta [256];

const char * trigo;
TCHAR Animal_Name[2560];
double radian;
double result;
TCHAR str[256];
TCHAR str1[256];
TCHAR Store_Velo[256];
TCHAR Store_Acce[256];
int iSelect = 0;
TCHAR animal[6][256] = { TEXT("COW"),TEXT("Grizzly Bear"),TEXT("Clown Fish"), TEXT("Chilean flamingo") ,TEXT("Blue whale") ,TEXT("Horse") };
TCHAR list_trigonometric[6][256] = { TEXT("sin"),TEXT("cos"),TEXT("tan"),TEXT("cot"), TEXT("sec") ,TEXT("cosec")};
const TCHAR *  degree_list[5] = { TEXT("0"), TEXT("30"), TEXT("45"),TEXT("60"),TEXT("90") };

BOOL CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Trignometric");
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("Com Library cannot be initilized \n Program will exit "), TEXT("Program Error"), MB_OK);
		exit(0);
	}
	//Initialization Of WNDCLASSEX
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("Clent of COM Dll server "),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CoUninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//void SafeInterfaceRelease();

	HINSTANCE hInstance;
	switch (iMsg)	
	{
	case WM_CREATE:

		hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
		DialogBox(hInstance, TEXT("DATAENTRY"), hwnd, MyDlgProc);
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void ClearAllFields(HWND hwnd)
{

	SetDlgItemText(hwnd, ID_ETPHYLUM, "");
	SetDlgItemText(hwnd, ID_ETCLASS, "");
	SetDlgItemText(hwnd, ID_ETORDER, "");
	SetDlgItemText(hwnd, ID_ETFAMILY, "");
	SetDlgItemText(hwnd, ID_ETGENUS, "");
	SetDlgItemText(hwnd, ID_ETSPECIES, "");

	SetDlgItemText(hwnd, ID_CB, "");
	SetDlgItemText(hwnd, ID_CBDEGREE, "");
	SetDlgItemText(hwnd, ID_CBTRIGONOMETRIC, "");
	SetDlgItemText(hwnd, ID_ETRESULT, "");
	SetDlgItemText(hwnd, ID_ETVELOCITY, "");
	SetDlgItemText(hwnd, ID_ETDISTANCE, "");
	SetDlgItemText(hwnd, ID_ETTIME, "");

	SetDlgItemText(hwnd, ID_ETACCELERATION, "");
	SetDlgItemText(hwnd, ID_ETINITIALVELOCITY, "");
	SetDlgItemText(hwnd, ID_ETFINALVELOCITY, "");
	SetDlgItemText(hwnd, ID_ETDELTATIME, "");
	
}


void SafeInterfaceRelease()
{
	if (pISin)
	{
		pISin->Release();
		pISin = NULL;
	}
}
BOOL CALLBACK MyDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	double degree = 0.0;
	Animal obj;
	HRESULT hr1;
	HINSTANCE hInstance;
	static HMODULE hLib = NULL;
	typedef Animal(*intPointer)(const char *);
	intPointer pfn1 = NULL;
	FILE * ptr=NULL;
	errno_t file_error;
	int answer = 0;


	HRESULT hr = E_FAIL;
	


	hLib = LoadLibrary(TEXT("Animal_Server.dll"));
	if (hLib == NULL)
	{
		MessageBox(hwnd, TEXT("Canot load the library"), TEXT("Erroor"), MB_OK);
		DestroyWindow(hwnd);
		return -1;
	}

	pfn1 = (intPointer)GetProcAddress(hLib, "ShowDetails");
	if (pfn1 == NULL)
	{
		MessageBox(hwnd, TEXT("Canot get the address of the function"), TEXT("Erroor"), MB_OK);
		DestroyWindow(hwnd);
		return -1;
	}


	hr1 = CoCreateInstance(CLSID_Trigonometric, NULL, CLSCTX_INPROC_SERVER, IID_ISin, (void **)&pISin);
	if (FAILED(hr1))
	{
		MessageBox(hwnd, TEXT("ISin Interface canot be obtained "), TEXT("Error"), MB_OK);
		DestroyWindow(hwnd);
	}
////////////////////////////////////

	CLSID clsidPhysics;
	
	IPhysics *app;
	hr1 = CLSIDFromProgID(L"ManagedServerForInterop.Physics", &clsidPhysics);
	if (FAILED(hr1))
	{
		//ComError Function.
		MessageBox(NULL, TEXT("CLSIDFromProgID Failed. \n 1 "), TEXT("Program Error"), MB_OK);
		DestroyWindow(hwnd);
		//return odAcceleration;
	}
	hr1 = CoCreateInstance(clsidPhysics, NULL, CLSCTX_INPROC_SERVER, __uuidof(IPhysics), (void **)&app);

	if (FAILED(hr1))
	{
		//ComError Function.
		MessageBox(NULL, TEXT("CoCreateInstance Failed. \n 2"), TEXT("Program Error"), MB_OK);
		DestroyWindow(hwnd);
		//return odAcceleration;
	}

	//////////////////////////////////////////////

	switch (iMsg)
	{

	case WM_INITDIALOG:
		//SetFocus(GetDlgItem(hwnd, ID_CB));
		for (i = 0; i <= 5; i++)
		{
			SendDlgItemMessage(hwnd, ID_CB, CB_ADDSTRING, (WPARAM)0, (LPARAM)animal[i]);
		}

		for (i = 0; i <= 5; i++)
		{
			SendDlgItemMessage(hwnd, ID_CBTRIGONOMETRIC, CB_ADDSTRING, (WPARAM)0, (LPARAM)list_trigonometric[i]);
		}
		for (i = 0; i <= 4; i++)
		{
			SendDlgItemMessage(hwnd, ID_CBDEGREE, CB_ADDSTRING, (WPARAM)0, (LPARAM)degree_list[i]);
		}
		return(TRUE);
		//break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_ALLCLEAR:
			ClearAllFields(hwnd);
			break;
		case ID_CB:

			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				iSelect = SendDlgItemMessage(hwnd, ID_CB, CB_GETCURSEL, 0, 0);
				//Animal_Name =animal[iSelect];
				obj = (Animal)pfn1((TCHAR *)animal[iSelect]);
				
				SetDlgItemText(hwnd, ID_ETPHYLUM, obj.Phylum);
				SetDlgItemText(hwnd, ID_ETCLASS, obj.Class);
				SetDlgItemText(hwnd, ID_ETORDER, obj.Order);
				SetDlgItemText(hwnd, ID_ETFAMILY, obj.Family);
				SetDlgItemText(hwnd, ID_ETGENUS, obj.Genus);
				SetDlgItemText(hwnd, ID_ETSPECIES, obj.Species);
				sprintf_s(Animal_Name, " Animal Name:  %s \n\n \t Phylum : %s \t Class: %s \t Order: %s \t Family: %s \t Genus: %s \t Species: %s \n",
					animal[iSelect], obj.Phylum, obj.Class, obj.Order, obj.Family, obj.Genus, obj.Species);
			}
			break;
		case IDCONTINUE:
			iSelect = SendDlgItemMessage(hwnd, ID_CB | ID_CBTRIGONOMETRIC, CB_GETCURSEL, 0, 0);
			break;
		case ID_OK:
			iSelect = SendDlgItemMessage(hwnd, ID_CB | ID_CBTRIGONOMETRIC, CB_GETCURSEL, 0, 0);
			EndDialog(hwnd, 0);
			break;
		case ID_CANCEL:
			EndDialog(hwnd, 0);
			break;
		case ID_CBTRIGONOMETRIC:

			//take a global boolean variable trigonometric cha combo box selct zala ki to true karaycha 
			//ajun ek variable trigo function konta select kelay te check karaych 
			//
			
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				iSelect = SendDlgItemMessage(hwnd, ID_CBTRIGONOMETRIC, CB_GETCURSEL, 0, 0);

				if (iSelect == 0)
				{
					trigo = "sin";
				}
				else if (iSelect == 1)
				{
					trigo = "cos";
				}
				else if (iSelect == 2)
				{
					trigo = "tan";
				}
				else if (iSelect == 3)
				{
					trigo = "cot";
				}
				else if (iSelect == 4)
				{
					trigo = "sec";
				}
				else if (iSelect == 5)
				{
					trigo = "cosec";
				}
			}
			break;
		case ID_CBDEGREE:
		//check kar global boolean variable trigo ch te jar false asel tr messagebox error cha 
		// true asel tr degree madhla combo selecte
		//
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				char strText[255];
				iSelect = SendDlgItemMessage(hwnd, ID_CBDEGREE, CB_GETCURSEL, 0, 0);
								
				degree = _ttoi (degree_list[iSelect]);
				radian = (degree * PI / 180);
				/*sprintf_s(str, "index %d  %lf  trigo %s ", iSelect, degree,trigo);
				MessageBox(hwnd, str, TEXT("DEGREE"), MB_OK);*/

				if (trigo == "sin")
					{
						
						pISin->MySin(degree, &result);
						sprintf_s(str1, "sin %lf is %lf  ", degree, result);
						//MessageBox(hwnd, str1, TEXT("Sin "), MB_OK);
						//swprintf(str1, sizeof(str1), L"sin %lf is %lf", degree, result);
						SetDlgItemText(hwnd, ID_ETRESULT, str1);
					}
					hr = pISin->QueryInterface(IID_ICos, (void**)&pICos);
					if (FAILED(hr))
					{
						MessageBox(hwnd, TEXT("ICos Interface canot be found "), TEXT("Error"), MB_OK);
						DestroyWindow(hwnd);
					}


					if (trigo=="cos")
					{
						pICos->MyCos(degree, &result);
						sprintf_s(str1,"cos %lf is %lf", degree, result);
						SetDlgItemText(hwnd, ID_ETRESULT, str1);
					}
					pISin->Release();
					pISin = NULL;
					hr = pICos->QueryInterface(IID_ITan, (void**)&pITan);
					if (FAILED(hr))
					{
						MessageBox(hwnd, TEXT("ITan interface cannot be found "), TEXT("Error"), MB_OK);
						DestroyWindow(hwnd);
					}


					if (trigo == "tan")
					{

						pITan->MyTan(degree, &result);
						sprintf_s(str1, "tan %lf is %lf", degree, result);
						SetDlgItemText(hwnd, ID_ETRESULT, str1);

					}
					pICos->Release();
					pICos = NULL;
					hr = pITan->QueryInterface(IID_ICot, (void **)&pICot);
					if (FAILED(hr))
					{
						MessageBox(hwnd, TEXT("ICot interface cannot be found "), TEXT("Error"), MB_OK);
						DestroyWindow(hwnd);
					}


					if (trigo == "cot")
					{
						pICot->MyCot(degree, &result);
						sprintf_s(str1, "cot %lf is %lf", degree, result);
						SetDlgItemText(hwnd, ID_ETRESULT, str1);
					}
					pITan->Release();
					pITan = NULL;
					hr = pICot->QueryInterface(IID_ISec, (void**)&pISec);
					if (FAILED(hr))
					{
						MessageBox(hwnd, TEXT("ISec interface cannot be found "), TEXT("Error"), MB_OK);
						DestroyWindow(hwnd);
					}


					if (trigo == "sec")
					{
						pISec->MySec(degree, &result);
						sprintf_s(str1,"sec %lf is %lf", degree, result);
						SetDlgItemText(hwnd, ID_ETRESULT, str1);
					}
					pICot->Release();
					pICot = NULL;
					hr = pISec->QueryInterface(IID_ICosec, (void**)&pICosec);
					if (FAILED(hr))
					{
						MessageBox(hwnd, TEXT("ICosec interface cannot be found "), TEXT("Error"), MB_OK);
						DestroyWindow(hwnd);
					}

					if (trigo == "cosec")
					{
						pICosec->MyCosec(degree, &result);
						sprintf_s(str1,"Cosec %lf is %lf", degree, result);
						SetDlgItemText(hwnd, ID_ETRESULT, str1);
					}
					pISec->Release();
					pISec = NULL;
			}
		break;
		case ID_PBVCAL:

			GetDlgItemText(hwnd, ID_ETDISTANCE, V_Distance, 15);
			dDistance = atof(V_Distance);
			
			GetDlgItemText(hwnd, ID_ETTIME, V_Time, 15);
			dTime = atof(V_Time);
			if (dDistance == NULL)
			{
				MessageBox(hwnd, TEXT("Please Enter the Distance "), TEXT("Error"), MB_OK);
			}
			else if (dTime == NULL)
			{
				MessageBox(hwnd, TEXT("Please Enter the Time"), TEXT("Error"), MB_OK);

			}
			else
			{
				hr = app->ComputeVelocity(dDistance, dTime, &dVelocity);
				if (FAILED(hr))
				{
					//ComError Function.
					MessageBox(hwnd, TEXT("ComputeVelocity Failed. \n 3"), TEXT("Program Error"), MB_OK);
					DestroyWindow(hwnd);
					//return odVelocity;
				}

				//swprintf(str, sizeof(str), L" New Velocity of %lf And %lf Is %lf", idDistance, idTime, odVelocity);
				sprintf_s(Store_Velo, "Velocity Is %lf", dVelocity);
				//wsprintf(str, TEXT("Velocity of %lf And %lf Is %lf"), idDistance, idTime, odVelocity);
				SetDlgItemText(hwnd, ID_ETVELOCITY, Store_Velo);

			}

			
			//MessageBox(NULL, str, TEXT("Velocity"), MB_OK);
			break;

		case ID_PBACAL:

			GetDlgItemText(hwnd, ID_ETINITIALVELOCITY, A_InitialVelocity, 15);
			dInitialVelocity = atof(A_InitialVelocity);
			
			GetDlgItemText(hwnd, ID_ETFINALVELOCITY, A_FinalVelocity, 15);
			dFinalVelocity = atof(A_FinalVelocity);

			GetDlgItemText(hwnd, ID_ETDELTATIME, A_TimeDelta, 15);
			dTimeDelta = atof(A_TimeDelta);
			
			if (dInitialVelocity == NULL)
			{
				MessageBox(hwnd, TEXT("Please Enter the InitialVelocity "), TEXT("Error"), MB_OK);
			}
			else if (dFinalVelocity == NULL)
			{
				MessageBox(hwnd, TEXT("Please Enter the FinalVelocity "), TEXT("Error"), MB_OK);
			}
			else if (dTimeDelta == NULL)
			{
				MessageBox(hwnd, TEXT("Please Enter the TimeDelta "), TEXT("Error"), MB_OK);
			}
			else
			{
				hr = app->ComputeAcceleration(dInitialVelocity, dFinalVelocity, dTimeDelta, &dAcceleration);
				if (FAILED(hr))
				{
					//ComError Function.
					MessageBox(NULL, TEXT("ComputeAcceleration Failed. \nProgram Will Now Exit. MiddleWare 165"), TEXT("Program Error"), MB_OK);
					//return odAcceleration;
					DestroyWindow(hwnd);
				}
				//swprintf(str, sizeof(str), L"Acceleration of %f to %f in %f is %f", idInitialVelocity, idFinalVelocity, idTimeDelta, odAcceleration);
				sprintf_s(Store_Acce, "Acceleration is %lf", dAcceleration);
				//wsprintf(str, TEXT("Acceleration of %lf to %lf in %lf is %lf"), idInitialVelocity, idFinalVelocity, idTimeDelta, odAcceleration);
				SetDlgItemText(hwnd, ID_ETACCELERATION, Store_Acce);
				//MessageBox(NULL, str, TEXT("Acceleration"), MB_OK);
			}
			
			break;


		case ID_PBDATASTORE:
			file_error = fopen_s(&ptr, "project_data.txt","a+");
			if (file_error != 0)
			{
				MessageBox(NULL, TEXT("File not found "), TEXT("Error"),MB_OK);
				break;
			}
			fprintf_s(ptr, "\n ");
			fprintf_s(ptr, "\n ********************************************************************************************************************************************* \n");
			fprintf_s(ptr, "\n  \t Animal Kingdom :-  \t\t\t");
			fprintf_s(ptr, "\n  \t Animal  : %s \t\t\t\n", Animal_Name);
			fprintf_s(ptr, " ------------------------------------------------------------------------------------------------------------------------------------------------ \n");
			fprintf_s(ptr, "\n  \t Trigonometric:-  \t\t\t");
			fprintf_s(ptr, "\n  \t %s   \t\t\t\n",str1);
			fprintf_s(ptr, " ------------------------------------------------------------------------------------------------------------------------------------------------\n");
			fprintf_s(ptr, "\n  \t Physics:-  \t\t\t");
			fprintf_s(ptr, "\n  \tDistance: %lf  Time: %lf = Velocity  %s   \t\t\t\n",dDistance,dTime,Store_Velo);
			fprintf_s(ptr, "\n  \tInitial Velocity: %lf Final Velocity: %lf Time Delta: %lf = Acceleration %s   \t\t", dInitialVelocity, dFinalVelocity, dTimeDelta,Store_Acce);
			fclose(ptr);
			break;


		}
		return(TRUE);
	}
	return(FALSE);
}
