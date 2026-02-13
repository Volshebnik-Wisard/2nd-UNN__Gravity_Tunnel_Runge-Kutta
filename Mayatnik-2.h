// Mayatnik2.h
#pragma once
#include <cmath>
#include <fstream>
#include <iomanip>
#include "Runge-KuttaDlg.h"

class Mayatnik2
{
private:
	double pi;
	double R1;      // радиус ядра
	double R2;      // радиус Земли
	double G;       // гравитационная постоянная
	double p;       // средняя плотность Земли
	double p1;      // плотность ядра
	double p2;      // плотность оболочки
	double Me;      // масса Земли
	double Me1;     // масса ядра
	double Me2;     // масса оболочки
	double g0;      // ускорение на поверхности
	double x;       // начальная координата
	double v1;      // начальная скорость
	double t;       // время
	double dt;      // шаг по времени
	double m;       // масса тела

protected:
	double func(double x);              // ускорение
	double potential_energy(double x);  // потенциальная энергия
	double kinetic_energy(double v);    // кинетическая энергия

public:
	Mayatnik2(double v0);               // конструктор
	void Start(CRungeKuttaDlg& dlg);
};