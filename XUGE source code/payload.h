DWORD WINAPI GDIShader1(LPVOID lpParam){
	HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	
	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	
	for( ; ; ) { 	
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, 13369376);
    	for(int y = 0; y < h; y++) {
            for(int x = 0; x < w; x++){
                int rgb = (prgbScreen[x + w * y].r + prgbScreen[x + w * y].g + prgbScreen[x + w * y].b) / 3;
                prgbScreen[x + w * y].r = rgb;
                prgbScreen[x + w * y].g = rgb;
                prgbScreen[x + w * y].b = rgb;
            }
    	}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, 13369376);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(100);
	}
	
	ReleaseDC(NULL, hcdc);
	DeleteObject(hcdc);
	DeleteObject(hBitmap);
	return 0;
}
DWORD WINAPI Payload1a_Big(LPVOID lpParam){
	HDC hdc = GetDC(0);
  	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	for(;;){
		StretchBlt(hdc,-10,-10,w+20,h+20,hdc,0,0,w,h,SRCCOPY);
		Sleep(100);
	}
}
DWORD WINAPI GDIShader2(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void **)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (int i = 0; i < w * h; i++) {
			rgbScreen[i].rgb = (rgbScreen[i].rgb * 2) % (RGB(255, 255, 255));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteDC(hdcScreen);
		Sleep(50);
	}
}
DWORD WINAPI Payload2a_Move(LPVOID lpParam){
	for (int t = 0;; t++) {
		HDC hdc = GetDC(NULL);
    	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
    	BitBlt(hcdc, 0, 0, w / 20, h, hdc, w / 20 * 19, 0, SRCCOPY);
    	BitBlt(hcdc, w / 20, 0, w / 20 * 19, h, hdc, 0, 0, SRCCOPY);
    	BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(10);
	}
}
int RotateDC(HDC hdc, int Angle, POINT ptCenter) {
	int nGraphicsMode = SetGraphicsMode(hdc, GM_ADVANCED);
	XFORM xform;
	if (Angle != 0)
	{
		double fangle = (double)Angle / 180. * 3.1415926;
		xform.eM11 = (float)cos(fangle);
		xform.eM12 = (float)sin(fangle);
		xform.eM21 = (float)-sin(fangle);
		xform.eM22 = (float)cos(fangle);
		xform.eDx = (float)(ptCenter.x - cos(fangle) * ptCenter.x + sin(fangle) * ptCenter.y);
		xform.eDy = (float)(ptCenter.y - cos(fangle) * ptCenter.y - sin(fangle) * ptCenter.x);
		SetWorldTransform(hdc, &xform);
	}
	return nGraphicsMode;
}
DWORD WINAPI Payload3a_CircleMelt(LPVOID lpParam){
	for (int t = 0;; t++) {
		HDC hdcScreen = GetDC(NULL);
	  	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);

		HDC hcdc = CreateCompatibleDC(hdcScreen);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);

		POINT p = { 0 };
		p.x = (w / 2);
		p.y = (h / 2);

		BLENDFUNCTION blf = { 0 };
		blf.BlendOp = AC_SRC_OVER;
		blf.BlendFlags = 0;
		blf.SourceConstantAlpha = 128;
		blf.AlphaFormat = 0;

		RotateDC(hdcScreen, 10, p);
		AlphaBlend(hdcScreen, 0, t, w, h, hcdc, 0, 0, w, h, blf);

		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		ReleaseDC(NULL, hdcScreen);
		DeleteObject(hdcScreen);
		Sleep(60);
	}
}
DWORD WINAPI Payload4a_Wind(LPVOID lparam){
	for (int t = 0;; t++) {
		HDC hdc = GetDC(NULL);
    	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
    	BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    	BLENDFUNCTION blf = { 0 };
    	blf.BlendOp = AC_SRC_OVER;
    	blf.BlendFlags = 0;
    	blf.SourceConstantAlpha = 128;
    	blf.AlphaFormat = 0;
    	AlphaBlend(hdc, 0 + t % 200 + 10, 0 - t % 25, w, h, hcdc, 0, 0, w, h, blf);
		SelectObject(hdc,CreateSolidBrush(RGB(rand()%256,rand()%256,rand()%256)));
		PatBlt(hdc,0,0,w,h,PATINVERT);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(20);
	}
	return 0;
}
DWORD WINAPI GDIShader3(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	for(;;){
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
		RGBQUAD rgbquadCopy;
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;
				int fx = (int)((i ^ 4) + (i * 4) * pow(x ^ y,(1.0/3.0)));
				rgbquadCopy = rgbquad[index];
				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 300.f + y / h * .1f + i / 1000.f, 1.f);
				hslcolor.s = 0.7f;
				hslcolor.l = 0.5f;
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
	return 0;
}
DWORD WINAPI GDIShader4(LPVOID lpParam)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
		RGBQUAD rgbquadCopy;
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;
				int fx = (x + i*4) + (y + i*4);
				rgbquadCopy = rgbquad[index];
				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 300.f + y / h * .1f + i / 1000.f, 1.f);
				hslcolor.s = 0.7f;
				hslcolor.l = 0.5f;
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
	return 0;
}
DWORD WINAPI GDIShader5(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			rgbScreen[i].rgb -= 666;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		Sleep(100);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI GDIShader6(LPVOID lpParam){
	HDC hdcScreen = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

	BITMAPINFO bmi = { 0 };
	PRGBQUAD prgbScreen={0};
	HDC hdcTempScreen;
	HBITMAP hbmScreen;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

//	prgbScreen = {0};

	hdcTempScreen = CreateCompatibleDC(hdcScreen);
	hbmScreen = CreateDIBSection(hdcScreen, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);

	for (int i = 0;; i++) {
		hdcScreen = GetDC(NULL);
		BitBlt(hdcTempScreen, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		PRGBQUAD prgbTemp = { 0 };
		prgbTemp = prgbScreen;
		int i;
		for (i = 0; i < h / 2; i++) {
			for (int j = 0; j < w; j++) {
				prgbScreen[i * w + j].rgb = prgbTemp[(int)((float)(i * w + j) + (float)sqrt((2 * (h / 2) * i - i * i))) % (w * h)].rgb;
			}
		}
		for (i = h / 2; i < h; i++) {
			for (int j = 0; j < w; j++) {
				prgbScreen[i * w + j].rgb = prgbTemp[(int)((float)(i * w + j) + (float)sqrt((2 * (h / 2) * i - i * i))) % (w * h)].rgb;
			}
		}
		Sleep(50);
		BitBlt(hdcScreen, 0, 0, w, h, hdcTempScreen, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteObject(hdcScreen);
		Sleep(10);
	}
}
DWORD WINAPI GDIShader7(LPVOID lpParam){
	HDC hdcScreen = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

	BITMAPINFO bmi = { 0 };
	PRGBQUAD prgbScreen={0};
	HDC hdcTempScreen;
	HBITMAP hbmScreen;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

//	prgbScreen = {0};

	hdcTempScreen = CreateCompatibleDC(hdcScreen);
	hbmScreen = CreateDIBSection(hdcScreen, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);

	for (int i = 0;; i++) {
		hdcScreen = GetDC(NULL);
		BitBlt(hdcTempScreen, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		PRGBQUAD prgbTemp = { 0 };
		prgbTemp = prgbScreen;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				prgbScreen[i * w + j].rgb = prgbTemp[(unsigned int)((float)(j * w + i) + (float)sqrt((unsigned int)(2 * h * j - j * j))) % (w * h)].rgb;
			}
		}
		Sleep(100);
		BitBlt(hdcScreen, 0, 0, w, h, hdcTempScreen, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteObject(hdcScreen);
		Sleep(10);
	}
}
DWORD WINAPI GDIShader8(LPVOID lpParam){
	HDC hdcScreen = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

	BITMAPINFO bmi = { 0 };
	PRGBQUAD prgbScreen={0};
	HDC hdcTempScreen;
	HBITMAP hbmScreen;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

//	prgbScreen = {0};

	hdcTempScreen = CreateCompatibleDC(hdcScreen);
	hbmScreen = CreateDIBSection(hdcScreen, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);

	for (int t = 0;; t++) {
		hdcScreen = GetDC(NULL);
		BitBlt(hdcTempScreen, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (int i = 0; i < w * h; i++) {
			prgbScreen[i].rgb = (t * i) % (RGB(255, 255, 255));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcTempScreen, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteObject(hdcScreen);
		Sleep(10);
	}
}
DWORD WINAPI GDIShader9(LPVOID lpParam){
	HDC hdcScreen = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

	BITMAPINFO bmi = { 0 };
	PRGBQUAD prgbScreen={0};
	HDC hdcTempScreen;
	HBITMAP hbmScreen;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

//	prgbScreen = {0};

	hdcTempScreen = CreateCompatibleDC(hdcScreen);
	hbmScreen = CreateDIBSection(hdcScreen, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);

	for (int t = 0;; t++) {
		hdcScreen = GetDC(NULL);
		BitBlt(hdcTempScreen, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		t *= 50;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				prgbScreen[i * w + j].rgb = RGB((prgbScreen[i * w + j].r + i / 10) % 256, (prgbScreen[i * w + j].g + j / 10) % 256, (prgbScreen[i * w + j].b + t) % 256);
			}
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcTempScreen, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteObject(hdcScreen);
		Sleep(10);
	}
}
DWORD WINAPI GDIShader10(LPVOID lpParam){
	HDC hdcScreen = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

	BITMAPINFO bmi = { 0 };
	PRGBQUAD prgbScreen={0};
	HDC hdcTempScreen;
	HBITMAP hbmScreen;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

//	prgbScreen = {0};

	hdcTempScreen = CreateCompatibleDC(hdcScreen);
	hbmScreen = CreateDIBSection(hdcScreen, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);

	for (int t = 0;; t++) {
		hdcScreen = GetDC(NULL);
		BitBlt(hdcTempScreen, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (int i = 0; i < w * h; i++) {
			int r = GetRValue(prgbScreen[i].rgb);
			int g = GetGValue(prgbScreen[i].rgb);
			int b = GetBValue(prgbScreen[i].rgb);
			prgbScreen[i].rgb = RGB((r + 100) % 256, ((r + g + b) / 4 + t) % 256, ((r + g + b) / 4 + i) % 256) % (RGB(255, 255, 255)) + t * 10;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcTempScreen, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteObject(hdcScreen);
		Sleep(10);
	}
}
/*Draw Cube Area-Start*/
float scrWidth = (float)GetSystemMetrics(0), scrHeight = (float)GetSystemMetrics(1);
float scrPosX = 0.0f, scrPosY = 0.0f;
float turnX = 1.0f, turnY = 1.0f;
float cubeScale = 100.0f, cube_OutIn_Scale = 0.5f;
float rotateAngle = PI / 36.f;
float lineHue = 0.f;

typedef struct {
    float x;
    float y;
    float z;

    void def_coordinate() {
        this->x = 0.0f, this->y = 0.0f, this->z = 0.0f;
    }
    void def_coordinate(float x, float y, float z) {
        this->x = x, this->y = y, this->z = z;
    }
} def_coordinate;

float rotateSineAngle = sin(rotateAngle);
float rotateCosineAngle = sin(rotateAngle + PI / 2.0f);

#define ROTATE_X 0
#define ROTATE_Y 1
#define ROTATE_Z 2

#define ROTATE_FUNC1(v1, v2, rad) (v1 * rotateCosineAngle - v2 * rotateSineAngle)
#define ROTATE_FUNC2(v1, v2, rad) (v2 * rotateCosineAngle + v1 * rotateSineAngle)



void RotateCoordinate(def_coordinate(*coord)[8], int status, float radSet) {
    int rotateNum = 0;
    float x_tmp, y_tmp, z_tmp = 0.f;
    switch (status) {
    case ROTATE_X:
        for (; rotateNum < 8; rotateNum++) {
            y_tmp = (*coord)[rotateNum].y, z_tmp = (*coord)[rotateNum].z;
            (*coord)[rotateNum].y = ROTATE_FUNC1(y_tmp, z_tmp, radSet);
            (*coord)[rotateNum].z = ROTATE_FUNC2(y_tmp, z_tmp, radSet);
        }
        break;

    case ROTATE_Y:
        for (; rotateNum < 8; rotateNum++) {
            x_tmp = (*coord)[rotateNum].x, z_tmp = (*coord)[rotateNum].z;
            (*coord)[rotateNum].x = ROTATE_FUNC1(x_tmp, z_tmp, radSet);
            (*coord)[rotateNum].z = ROTATE_FUNC2(x_tmp, z_tmp, radSet);
        }
        break;

    case ROTATE_Z:
        for (; rotateNum < 8; rotateNum++) {
            x_tmp = (*coord)[rotateNum].x, y_tmp = (*coord)[rotateNum].y;
            (*coord)[rotateNum].x = ROTATE_FUNC1(x_tmp, y_tmp, radSet);
            (*coord)[rotateNum].y = ROTATE_FUNC2(x_tmp, y_tmp, radSet);
        }
        break;

    default:;
    }
}

#undef ROTATE_FUNC2
#undef ROTATE_FUNC1

void CubePositionCalculate(POINT(*pos_Out)[8], POINT(*pos_In)[8], def_coordinate(*coord)[8]) {
    for (int fillNum = 0; fillNum < 8; fillNum++) {
        (*pos_Out)[fillNum].x = (*coord)[fillNum].x * cubeScale + scrPosX;
        (*pos_Out)[fillNum].y = (*coord)[fillNum].y * cubeScale + scrPosY;
        (*pos_In)[fillNum].x = (*coord)[fillNum].x * cubeScale * cube_OutIn_Scale + scrPosX;
        (*pos_In)[fillNum].y = (*coord)[fillNum].y * cubeScale * cube_OutIn_Scale + scrPosY;
    }
}
COLORREF Hue2RGB(float hue){
	COLORREF rgb;
	float r = 0, g = 0, b = 0;
	float h = hue * 6.f;
	float f = h - (int)h;
		switch((int)h){
			case 0:
				r = 1.f, g = f, b = 0.f;
				break;
			case 1:
				r = 1.f - f, g = 1.f, b = 0.f;
				break;
			case 2:
				r = 0.f, g = 1.f, b = f;
				break;
			case 3:
				r = 0.f, g = 1.f - f, b = 1.f;
				break;
			case 4:
				r = f, g = 0.f; b = 1.f;
				break;
			case 5:
				r = 1.f, g = 0.f, b = 1.f - f;
				break;
		}

	rgb = RGB((unsigned char)(r * 255.f + 0.5f), (unsigned char)(g * 255.f + 0.5f), (unsigned char)(b * 255.f + 0.5f));
	return rgb;
}
DWORD WINAPI Payload5a_Cube(LPVOID lpParam) {
 	def_coordinate coord[8];
	int initNum = 0;
	for(float initX = -1.0f; initX <= 1.0f; initX += 2.0f){
		for(float initY = -1.0f; initY <= 1.0f; initY += 2.0f){
			for(float initZ = -1.0f; initZ <= 1.0f; initZ += 2.0f){
				coord[initNum].x = initX;
				coord[initNum].y = initY;
				coord[initNum].z = initZ;
				initNum++;
	}}}
	int linePointIndex[12][2] = {
		{0, 2}, {0, 4}, {0, 1},
		{6, 2}, {6, 4}, {6, 7},
		{3, 1}, {3, 7}, {3, 2},
		{5, 1}, {5, 7}, {5, 4}
	};
/*
	coord[8] data:
	(-1,-1,-1)	(-1,-1,1)
	(-1,1,-1)	(-1,1,1)
	(1,-1,-1)	(1,-1,1)
	(1,1,-1)	(1,1,1)
*/

	RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
	Sleep(1000);

	HDC hdcDst, hdcSrc;
	HBITMAP hbmpSrc;
	
	hdcDst = GetDC(0);
	hdcSrc = CreateCompatibleDC(hdcDst);
	hbmpSrc = CreateCompatibleBitmap(hdcDst, scrWidth, scrHeight);
	SelectObject(hdcSrc, hbmpSrc);

	BitBlt(hdcSrc, 0, 0, scrWidth, scrHeight, hdcDst, 0, 0, 0x00000042);

	POINT linePoint_In[8];
	POINT linePoint_Out[8];
	for(;;){
		hdcDst = GetDC(0);
		BitBlt(hdcSrc, 0, 0, scrWidth, scrHeight, hdcSrc, 0, 0, 0x00000042);

		RotateCoordinate(&coord, ROTATE_X, (-1) * rotateAngle);
		RotateCoordinate(&coord, ROTATE_Y, (-1) * turnY * rotateAngle);
		RotateCoordinate(&coord, ROTATE_Z, turnX * rotateAngle);
		CubePositionCalculate(&linePoint_Out, &linePoint_In, &coord);

		int drawNum = 0;
		SelectObject(hdcSrc, CreatePen(0, 10, Hue2RGB(lineHue)));
		for(drawNum = 0; drawNum < 12; drawNum++){
			MoveToEx(hdcSrc, linePoint_Out[linePointIndex[drawNum][0]].x, linePoint_Out[linePointIndex[drawNum][0]].y, NULL);
			LineTo(hdcSrc, linePoint_Out[linePointIndex[drawNum][1]].x, linePoint_Out[linePointIndex[drawNum][1]].y);
			MoveToEx(hdcSrc, linePoint_In[linePointIndex[drawNum][0]].x, linePoint_In[linePointIndex[drawNum][0]].y, NULL);
			LineTo(hdcSrc, linePoint_In[linePointIndex[drawNum][1]].x, linePoint_In[linePointIndex[drawNum][1]].y);
		}
		for(drawNum = 0; drawNum < 8; drawNum++){
			MoveToEx(hdcSrc, linePoint_Out[drawNum].x, linePoint_Out[drawNum].y, NULL);
			LineTo(hdcSrc, linePoint_In[drawNum].x, linePoint_In[drawNum].y);
		}
		
		BitBlt(hdcDst, 0, 0, scrWidth, scrHeight, hdcSrc, 0, 0, 0x00CC0020);
		
		int changeTurnNum = 0;
		int saveTurnX = turnX, saveTurnY = turnY;
		for( ;changeTurnNum < 12; changeTurnNum++){
			if(linePoint_Out[linePointIndex[changeTurnNum][0]].x >= scrWidth - 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].x >= scrWidth - 10){turnX = -1.0f;}
			if(linePoint_Out[linePointIndex[changeTurnNum][0]].x <= 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].x <= 10){turnX = 1.0f;}
			if(linePoint_Out[linePointIndex[changeTurnNum][0]].y >= scrHeight - 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].y >= scrHeight - 10){turnY = -1.0f;}
			if(linePoint_Out[linePointIndex[changeTurnNum][0]].y <= 10 || linePoint_Out[linePointIndex[changeTurnNum][1]].y <= 10){turnY = 1.0f;}
		}
		if(saveTurnX != turnX || saveTurnY != turnY){lineHue = fmod(lineHue * 360.f + 30.f, 360.f) / 360.f;}
		scrPosX += (turnX * 10.f), scrPosY += (turnY * 10.f);
		Sleep(50);
	}

	ReleaseDC(0, hdcDst);
	ReleaseDC(0, hdcSrc);
	DeleteObject(hdcDst);
	DeleteObject(hdcSrc);
	DeleteObject(hbmpSrc);
}
/*Draw Cube Area-End*/
DWORD WINAPI Payload6a_Icon(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    for (;;) {
        for (int x = 0; x <= w; x += 64 * wdpi / 96) {
            for (int y = 0; y <= h; y += 64 * hdpi / 96) {
                DrawIconEx(hdc, x, y, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)), 64 * wdpi / 96, 64 * hdpi / 96, 0, 0, DI_NORMAL);
            }
        }
    }
}
DWORD WINAPI GDIShader11(LPVOID lpParam) {
    HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
    int wdpi = GetDeviceCaps(hdcScreen, LOGPIXELSX);
    int hdpi = GetDeviceCaps(hdcScreen, LOGPIXELSY);
    INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    BITMAPINFO bmi = { 0 };
    PRGBQUAD rgbScreen = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = h;
    HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
    SelectObject(hdcMem, hbmTemp);
    for (;;) {
        hdcScreen = GetDC(0);
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
        for (INT i = 0; i < w * h; i++) {
            INT x = i + w, y = i - w;
            rgbScreen[i].rgb += x | y;
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
    }
}
DWORD WINAPI Payload7a_Swirl(LPVOID lpParam) {//by pankoza(Neurozine safety.cpp)
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 10, ySize = 9;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		int i;
		for (i = 0; i < sh * 2; i++) {
			int wave = sin(i / ((float)xSize) * PI) * (ySize);
			BitBlt(hdcMem, i, 0, 1, sh, hdcMem, i, wave, SRCCOPY);
		}
		for (i = 0; i < sw * 2; i++) {
			int wave = sin(i / ((float)xSize) * PI) * (ySize);
			BitBlt(hdcMem, 0, i, sw, 1, hdcMem, wave, i, SRCCOPY);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
		Sleep(1);
	}
}
DWORD WINAPI GDIShader12(LPVOID lpParam){
	HDC hdc = GetDC(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	for (int t = 0;; t++) {
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int i = 0; i < h; i++) {
            int rgbTemp = rand() % 255;
            for(int l = 0; l < w; l++){
                prgbScreen[i * w + l].rgb = RGB(rgbTemp, rgbTemp, rgbTemp);
            }
        }
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(10);
	}
	DeleteObject(hBitmap);
	DeleteDC(hcdc);
    return 0;
}
DWORD WINAPI GDIShader13(LPVOID lpvd) //by fr4ctalz
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;
				int fx = (int)((i ^ 4) + (i * 4) * pow(30,1.0/3));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
		Sleep(5);
	}

	return 0;
}
DWORD WINAPI GDIShader14(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			rgbScreen[i].rgb = rand();
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI GDIShader15(LPVOID lpParam){
	HDC hdc = GetDC(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	for (int t = 0;; t++) {
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for (int i = 0; i < w * h; i++) {
            prgbScreen[i].r = rand() % 255;
            prgbScreen[i].g = rand() % 255;
            prgbScreen[i].b = rand() % 255;
        }
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(10);
	}
	DeleteObject(hBitmap);
	DeleteDC(hcdc);
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
    return 0;
}
DWORD WINAPI GDIShader16(LPVOID lpParam){
	HDC hdcScreen = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

	BITMAPINFO bmi = { 0 };
	PRGBQUAD prgbScreen={0};
	HDC hdcTempScreen;
	HBITMAP hbmScreen;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

//	prgbScreen = {0};

	hdcTempScreen = CreateCompatibleDC(hdcScreen);
	hbmScreen = CreateDIBSection(hdcScreen, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);

	for (int t = 0;; t++) {
		hdcScreen = GetDC(NULL);
		BitBlt(hdcTempScreen, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (int i = 0; i < w * h; i++) {
			prgbScreen[i].rgb = (Xorshift32() % 0x100) * 0x010101;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcTempScreen, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteObject(hdcScreen);
		Sleep(10);
	}
}