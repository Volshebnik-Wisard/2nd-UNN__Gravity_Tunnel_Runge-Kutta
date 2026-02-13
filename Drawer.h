#pragma once

#include <afxwin.h>
#include <vector>
#include <fstream>
using namespace std;

class Drawer
{
	// Прямоугольник области рисования.
	CRect frame;
	// Указатель на объект окна, обалсти рисования.
	CWnd* wnd;
	// Контекст рисования, привязанный к области рисования.
	CDC* dc;
	// Контекст рисования, привязанный к памяти.
	CDC memDC;
	// Память для контекста рисования memDC.
	CBitmap bmp;
	// Флаг для отслеживания состояния инициализации класса.
	bool init;
public:
	// Проинициализировать объект класса на основе HWND.
	void Create(HWND hWnd)
	{
		// Получаем указатель на окно.
		wnd = CWnd::FromHandle(hWnd);
		// Получаем прямоугольник окна.
		wnd->GetClientRect(frame);
		// Получаем контекст для рисования в этом окне.
		dc = wnd->GetDC();

		// Создаем буфер-контекст.
		memDC.CreateCompatibleDC(dc);
		// Создаем растр для контекста рисования.
		bmp.CreateCompatibleBitmap(dc, frame.Width(), frame.Height());
		// Выбираем растр для использования буфер-контекстом.
		memDC.SelectObject(&bmp);
		init = true;
	}

	void Draw(double x0, bool task)//рисует картинку по переданным данным
	{
		double pi = 4 * atan(1);
		double R = 6371 * 1000;
		double x = R;


		if (!init) return;
		int padding = 0;
		int left_keys_padding = 0;
		int bottom_keys_padding = 0;

		int actual_width = frame.Width() - 2 * padding - left_keys_padding;
		int actual_height = frame.Height() - 2 * padding - bottom_keys_padding;

		int actual_top = padding;
		int actual_bottom = actual_top + actual_height;
		int actual_left = padding + left_keys_padding;
		int actual_right = actual_left + actual_width;

		//границы рисунка
		double data_y_max(1.1 * (2 * x)), data_y_min(-1.1 * (2 * x));
		double data_x_max(1.1 * (2 * x)), data_x_min(-1.1 * (2 * x));

		// Белый фон.
		memDC.FillSolidRect(frame, RGB(255, 255, 255));

		//рисуем точку крепления
		CPen APen(PS_SOLID, 3, RGB(0, 0, 0));
		memDC.SelectObject(APen);
		vector<double>A0x, A0y;
		A0x.push_back(0);
		A0y.push_back(0);
		A0x = convert_range(A0x, actual_right, actual_left, data_x_max, data_x_min);//сворачивает координаты в нашей системе отсчета в координаты окна рисования
		A0y = convert_range(A0y, actual_top, actual_bottom, data_y_max, data_y_min);
		memDC.MoveTo(A0x[0], A0y[0]);
		memDC.Ellipse(A0x[0] - 120, A0y[0] - 120, A0x[0] + 120, A0y[0] + 120);

		if (task == true)
		{
			CPen BPen(PS_SOLID, 3, RGB(0, 0, 0));
			memDC.SelectObject(APen);
			vector<double>B0x, B0y;
			B0x.push_back(0);
			B0y.push_back(0);
			B0x = convert_range(B0x, actual_right, actual_left, data_x_max, data_x_min);//сворачивает координаты в нашей системе отсчета в координаты окна рисования
			B0y = convert_range(B0y, actual_top, actual_bottom, data_y_max, data_y_min);
			memDC.MoveTo(B0x[0], B0y[0]);
			memDC.Ellipse(B0x[0] - 120 / 2, B0y[0] - 120 / 2, B0x[0] + 120 / 2, B0y[0] + 120 / 2);
		}

		CPen ConstructPen(PS_SOLID, 3, RGB(0, 0, 0));
		memDC.SelectObject(ConstructPen);


		//Рисуем шарик
		vector<double>Shx, Shy;
		Shx.push_back(0);
		Shy.push_back(x0);
		Shx[0];
		Shy[0];
		Shx = convert_range(Shx, actual_right, actual_left, data_x_max, data_x_min);
		Shy = convert_range(Shy, actual_top, actual_bottom, data_y_max, data_y_min);
		memDC.MoveTo(Shx[0], Shy[0]);
		CPen ShPen(PS_SOLID, 6, RGB(255, 0, 0));
		memDC.SelectObject(ShPen);
		memDC.Ellipse(Shx[0] - 1.5, Shy[0] - 1.5, Shx[0] + 1.5, Shy[0] + 1.5);

		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
	}


	vector<double> convert_range(vector <double>& data, double outmax, double outmin, double inmax, double inmin)
	{
		vector<double> output = data;
		double k = (outmax - outmin) / (inmax - inmin);
		for (auto& item : output)
		{
			item = (item - inmin) * k + outmin;
		}

		return output;
	}

	void DrawGraphScene(double data_x_min, double data_x_max, double data_y_min, double data_y_max)
	{
		if (!init) return;

		CPen subgrid_pen(PS_DOT, 1, RGB(200, 200, 200));
		CPen grid_pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen data_pen(PS_SOLID, 2, RGB(255, 0, 0));
		CPen data2_pen(PS_SOLID, 2, RGB(0, 255, 0));
		CFont font;
		font.CreateFontW(18, 0, 0, 0,
			FW_DONTCARE,
			FALSE,				// Курсив
			FALSE,				// Подчеркнутый
			FALSE,				// Перечеркнутый
			DEFAULT_CHARSET,	// Набор символов
			OUT_OUTLINE_PRECIS,	// Точность соответствия.	
			CLIP_DEFAULT_PRECIS,//  
			CLEARTYPE_QUALITY,	// Качество
			VARIABLE_PITCH,		//
			TEXT("Times New Roman")		//
		);

		int padding = 20;
		int left_keys_padding = 20;
		int bottom_keys_padding = 10;

		int actual_width = frame.Width() - 2 * padding - left_keys_padding;
		int actual_height = frame.Height() - 2 * padding - bottom_keys_padding;

		int actual_top = padding;
		int actual_bottom = actual_top + actual_height;
		int actual_left = padding + left_keys_padding;
		int actual_right = actual_left + actual_width;



		// Белый фон.
		memDC.FillSolidRect(frame, RGB(255, 255, 255));

		// Рисуем сетку и подсетку.
		unsigned int grid_size = 10;

		memDC.SelectObject(&subgrid_pen);

		for (double i = 0.5; i < grid_size; i += 1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}

		memDC.SelectObject(&grid_pen);

		for (double i = 0.0; i < grid_size + 1; i += 1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}




		memDC.SelectObject(&font);
		memDC.SetTextColor(RGB(0, 0, 0));
		for (int i = 0; i < grid_size / 2 + 1; i++)
		{
			CString str;
			str.Format(L"%.1f", data_x_min + i * (data_x_max - data_x_min) / (grid_size / 2));
			memDC.TextOutW(actual_left + (double)i * actual_width / (grid_size / 2) - bottom_keys_padding, actual_bottom + bottom_keys_padding / 2, str);

			str.Format(L"%.1f", data_y_min + i * (data_y_max - data_y_min) / (grid_size / 2));
			memDC.TextOutW(actual_left - 1.5 * left_keys_padding, actual_bottom - (double)i * actual_height / (grid_size / 2) - bottom_keys_padding, str);
		}

		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
	}
	void PrintGraphDot(double dt, double x, double y, double data_x_min, double data_x_max, double data_y_min, double data_y_max, vector<double>& xgraph, vector<double>& ygraph)
	{


		CPen data_pen(PS_SOLID, 2, RGB(0, 0, 255));

		int padding = 20;
		int left_keys_padding = 20;
		int bottom_keys_padding = 10;

		int actual_width = frame.Width() - 2 * padding - left_keys_padding;
		int actual_height = frame.Height() - 2 * padding - bottom_keys_padding;

		int actual_top = padding;
		int actual_bottom = actual_top + actual_height;
		int actual_left = padding + left_keys_padding;
		int actual_right = actual_left + actual_width;


		if (x <= 200 * dt)
		{
			vector<double> X, Y;
			Y.push_back(y);
			X.push_back(x);
			memDC.SelectObject(&data_pen);
			Y = convert_range_graph(Y, actual_top, actual_bottom, data_y_max, data_y_min);
			X = convert_range_graph(X, actual_right, actual_left, data_x_max, data_x_min);
			xgraph.push_back(x);
			ygraph.push_back(y);
			memDC.LineTo(X[0], Y[0]);
		}
		else
		{
			data_x_min = x - 200 * dt;
			data_x_max = x;
			DrawGraphScene(data_x_min, data_x_max, data_y_min, data_y_max);

			update_vector(xgraph);
			update_vector(ygraph);
			xgraph[xgraph.size() - 1] = x;
			ygraph[ygraph.size() - 1] = y;
			vector<double> X, Y;
			Y = convert_range_graph(create_vector_copy(ygraph), actual_top, actual_bottom, data_y_max, data_y_min);
			X = convert_range_graph(create_vector_copy(xgraph), actual_right, actual_left, data_x_max, data_x_min);
			memDC.SelectObject(&data_pen);
			memDC.MoveTo(X[0], Y[0]);
			for (int i = 0; i < X.size(); i++)
			{
				memDC.LineTo(X[i], Y[i]);
			}
		}
		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
	}
	vector<double> convert_range_graph(vector <double>& data, double outmax, double outmin, double inmax, double inmin)
	{
		vector<double> output = data;
		double k = (outmax - outmin) / (inmax - inmin);
		for (auto& item : output)
		{
			item = (item - inmin) * k + outmin;
		}

		return output;
	}
	void update_vector(vector<double>& vect)
	{
		for (int i = 0; i < vect.size() - 1; i++)
		{
			vect[i] = vect[i + 1];
		}
	}
	vector<double>create_vector_copy(vector<double> x)
	{
		vector <double> copy;
		for (int i = 0; i < x.size(); i++)
		{
			copy.push_back(x[i]);
		}
		return copy;
	}
	void SetGraphStart(double y, double data_x_min, double data_x_max, double data_y_min, double data_y_max)
	{

		int padding = 20;
		int left_keys_padding = 20;
		int bottom_keys_padding = 10;

		int actual_width = frame.Width() - 2 * padding - left_keys_padding;
		int actual_height = frame.Height() - 2 * padding - bottom_keys_padding;

		int actual_top = padding;
		int actual_bottom = actual_top + actual_height;
		int actual_left = padding + left_keys_padding;
		int actual_right = actual_left + actual_width;
		vector<double>Y;
		Y.push_back(y);
		Y = convert_range_graph(Y, actual_top, actual_bottom, data_y_max, data_y_min);
		memDC.MoveTo(actual_left, Y[0]);
	}

	void PrintGraphDot(double x, double y, double data_x_min, double data_x_max, double data_y_min, double data_y_max)
	{


		CPen data_pen(PS_SOLID, 2, RGB(0, 0, 255));

		int padding = 20;
		int left_keys_padding = 20;
		int bottom_keys_padding = 10;

		int actual_width = frame.Width() - 2 * padding - left_keys_padding;
		int actual_height = frame.Height() - 2 * padding - bottom_keys_padding;

		int actual_top = padding;
		int actual_bottom = actual_top + actual_height;
		int actual_left = padding + left_keys_padding;
		int actual_right = actual_left + actual_width;



		vector<double> X, Y;
		Y.push_back(y);
		X.push_back(x);
		memDC.SelectObject(&data_pen);
		Y = convert_range_graph(Y, actual_top, actual_bottom, data_y_max, data_y_min);
		X = convert_range_graph(X, actual_right, actual_left, data_x_max, data_x_min);
		memDC.LineTo(X[0], Y[0]);

		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
	}
	void SetGraphStart(double x, double y, double data_x_min, double data_x_max, double data_y_min, double data_y_max)
	{

		int padding = 20;
		int left_keys_padding = 20;
		int bottom_keys_padding = 10;

		int actual_width = frame.Width() - 2 * padding - left_keys_padding;
		int actual_height = frame.Height() - 2 * padding - bottom_keys_padding;

		int actual_top = padding;
		int actual_bottom = actual_top + actual_height;
		int actual_left = padding + left_keys_padding;
		int actual_right = actual_left + actual_width;
		vector<double> X, Y;
		X.push_back(x);
		Y.push_back(y);
		X = convert_range_graph(X, actual_right, actual_left, data_x_max, data_x_min);
		Y = convert_range_graph(Y, actual_top, actual_bottom, data_y_max, data_y_min);
		memDC.MoveTo(X[0], Y[0]);
	}
};