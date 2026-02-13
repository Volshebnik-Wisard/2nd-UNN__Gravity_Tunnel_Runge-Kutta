#include "stdafx.h"
#include "Mayatnik-2.h"
#include <cmath>
using namespace std;

Mayatnik2::Mayatnik2(double v0)
{
	pi = 4 * atan(1);
	R2 = 6371 * 1000;  // радиус Земли, м
	R1 = R2 / 2; // радиус ядра, м
	G = 6.67430 * pow(10, -11);
	Me = 5.9722 * pow(10, 24); // масса Земли, кг
	g0 = (G * Me) / (R2 * R2); // ускорение на поверхности
	p = 5515.3;  // средняя плотность Земли, кг/м³

	// плотности ядра и оболочки (из условия ρ_ядра = 2ρ_оболочки, масса неизменна)
	p1 = 16 * p / 9; // плотность ядра
	p2 = 8 * p / 9; // плотность оболочки

	// массы ядра и оболочки
	Me1 = 2 * Me / 9; // масса ядра
	Me2 = 7 * Me / 9; // масса оболочки

	x = R2; // начальное положение
	v1 = v0; // начальная скорость
	t = 0;
	dt = 0.005 * 2 * pi / sqrt(g0 / R2); // шаг по времени
	m = 0.000001;  // масса тела
}

// Ускорение (правая часть ДУ)
double Mayatnik2::func(double x)
{
	double r = abs(x);
	int sign = (x >= 0) ? 1 : -1;

	// Внутри ядра
	if (r <= R1)
	{
		return -(16.0 * g0 / (9.0 * R2)) * x;
	}
	// В оболочке
	else if (r <= R2)
	{
		double M_inside = Me1 + (4.0 / 3.0) * pi * p2 * (r * r * r - R1 * R1 * R1);
		return -(G * M_inside / (r * r)) * sign;
	}
	// Вне Земли
	else
	{
		return -(G * Me / (r * r)) * sign;
	}
}

// Потенциальная энергия (ИСПРАВЛЕННАЯ - через интеграл от ускорения)
double Mayatnik2::potential_energy(double x)
{
	double r = abs(x);

	// U = -m * ∫ a dr, где a = func(r) - ускорение (знак уже учтен в func)

	// Внутри ядра
	if (r <= R1)
	{
		// a = -(16g0/(9R2)) * r
		// ∫ a dr = -(16g0/(9R2)) * r²/2 = -(8g0/(9R2)) * r²
		// U = -m * ∫ a dr = -m * [-(8g0/(9R2)) * r²] = m * (8g0/(9R2)) * r²
		// Выбираем U(0) = 0
		return m * (8.0 * g0 / (9.0 * R2)) * r * r;
	}
	// В оболочке
	else if (r <= R2)
	{
		// U(R1) из формулы для ядра
		double U_R1 = m * (8.0 * g0 / (9.0 * R2)) * R1 * R1;

		// a = -G * M_inside / r²
		// M_inside = Me1 + (4/3)πρ₂(r³ - R1³)
		// ∫ a dr от R1 до r = ∫ -G*Me1/r² dr + ∫ -G*(4/3)πρ₂(r - R1³/r²) dr
		// = G*Me1/r + [ -G*(4/3)πρ₂*(r²/2 + R1³/r) ]
		// Проверяем знаки!

		double integral_a = G * Me1 * (1.0 / r - 1.0 / R1);
		integral_a += (4.0 / 3.0) * pi * p2 * G * (-(r * r - R1 * R1) / 2.0 - R1 * R1 * R1 * (1.0 / r - 1.0 / R1));

		// U = U(R1) - m * integral_a
		return U_R1 - m * integral_a;
	}
	// Вне Земли
	else
	{
		// Сначала вычисляем U(R2)
		double r2 = R2;
		double U_R1 = m * (8.0 * g0 / (9.0 * R2)) * R1 * R1;

		double integral_a_R2 = G * Me1 * (1.0 / r2 - 1.0 / R1);
		integral_a_R2 += (4.0 / 3.0) * pi * p2 * G * (-(r2 * r2 - R1 * R1) / 2.0 - R1 * R1 * R1 * (1.0 / r2 - 1.0 / R1));
		double U_R2 = U_R1 - m * integral_a_R2;

		// Вне Земли: a = -G*Me/r²
		// ∫ a dr от R2 до r = G*Me*(1/r - 1/R2)
		double integral_a = G * Me * (1.0 / r - 1.0 / r2);

		return U_R2 - m * integral_a;
	}
}

// Кинетическая энергия
double Mayatnik2::kinetic_energy(double v)
{
	return m * v * v / 2.0;
}

void Mayatnik2::Start(CRungeKuttaDlg& dlg)
{
	ofstream outall("Task 2.txt");

	dlg.STOP = false;

	// Настройка графиков
	double x_min = -R2 - abs(v1 * v1 / 4);
	double x_max = R2 + abs(v1 * v1 / 4);
	double v_max = 8100 + abs(v1);
	double E_max = m * 6000 * 18000;

	dlg.graphX.DrawGraphScene(0, 200 * dt, x_min, x_max);
	dlg.graphX.SetGraphStart(x, 0, 200 * dt, x_min, x_max);

	dlg.graphX2.DrawGraphScene(0, 200 * dt, -v_max, v_max);
	dlg.graphX2.SetGraphStart(v1, 0, 200 * dt, -v_max, v_max);

	dlg.graphX3.DrawGraphScene(0, 200 * dt, -18, 18);
	dlg.graphX3.SetGraphStart(func(x), 0, 200 * dt, -18, 18);

	dlg.graphX4.DrawGraphScene(0, 200 * dt, 0, E_max);
	dlg.graphX4.SetGraphStart(kinetic_energy(v1), 0, 200 * dt, 0, E_max);

	dlg.graphX5.DrawGraphScene(0, 200 * dt, 0, E_max);
	dlg.graphX5.SetGraphStart(potential_energy(x), 0, 200 * dt, 0, E_max);

	dlg.graphX6.DrawGraphScene(0, 200 * dt, 0, E_max);
	dlg.graphX6.SetGraphStart(potential_energy(x) + kinetic_energy(v1), 0, 200 * dt, 0, E_max);

	vector<double> xgraphX, ygraphX, xgraphX2, ygraphX2, xgraphX3, ygraphX3,
		xgraphX4, ygraphX4, xgraphX5, ygraphX5, xgraphX6, ygraphX6;

	double k[4];
	double X, V;
	double v2 = v1;
	double x1 = x;
	int i = 0;
	t = 0;

	double E0 = potential_energy(x) + kinetic_energy(v1);

	do
	{
		X = x1;
		V = v2;
		t = i * dt;

		// Метод Рунге-Кутты 4-го порядка
		k[0] = func(X) * dt;
		k[1] = func(X + V * dt / 2.0) * dt;
		k[2] = func(X + V * dt / 2.0 + k[0] * dt / 4.0) * dt;
		k[3] = func(X + V * dt + k[1] * dt / 2.0) * dt;

		x1 = X + V * dt + (k[0] + k[1] + k[2]) * dt / 6.0;
		v2 = V + (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6.0;
		i++;

		// Отрисовка
		dlg.drv.Draw(x1, true);

		double T_kin = kinetic_energy(v2);
		double U_pot = potential_energy(x1);
		double E_total = U_pot + T_kin;

		dlg.graphX.PrintGraphDot(dt, t, x1, 0, 200 * dt, x_min, x_max, xgraphX, ygraphX);
		dlg.graphX2.PrintGraphDot(dt, t, v2, 0, 200 * dt, -v_max, v_max, xgraphX2, ygraphX2);
		dlg.graphX3.PrintGraphDot(dt, t, func(x1), 0, 200 * dt, -18, 18, xgraphX3, ygraphX3);
		dlg.graphX4.PrintGraphDot(dt, t, T_kin, 0, 200 * dt, 0, E_max, xgraphX4, ygraphX4);
		dlg.graphX5.PrintGraphDot(dt, t, U_pot, 0, 200 * dt, 0, E_max, xgraphX5, ygraphX5);
		dlg.graphX6.PrintGraphDot(dt, t, E_total, 0, 200 * dt, 0, E_max, xgraphX6, ygraphX6);

		// Запись в файл
		double dE = abs((E_total - E0) / E0);

		outall << setw(5) << i << setw(4) << "| "
			<< setprecision(5) << "t = " << setw(6) << t << setw(4) << "| "
			<< "x = " << setw(12) << x1 << setw(2) << "| "
			<< "v = " << setw(12) << v2 << setw(2) << "| "
			<< "g = " << setw(12) << func(x1) << setw(2) << "| "
			<< "T = " << setw(12) << T_kin << setw(2) << "| "
			<< "U = " << setw(12) << U_pot << setw(2) << "| "
			<< "E = " << setw(12) << E_total << setw(2) << "| "
			<< "dE/E0 = " << setw(12) << dE << setw(2) << "|" << endl;

		Sleep(5);

		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	} while (dlg.STOP == false);

	outall.close();
}