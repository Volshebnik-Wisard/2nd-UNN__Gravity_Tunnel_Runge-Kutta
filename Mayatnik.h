#pragma once
#include<cmath>
#include<fstream>
#include<iomanip>
#include"Runge-KuttaDlg.h"
class Mayatnik
{
private:
	double pi;
	double R;
	double G;
	double p;
	double Me;
	double g0;
	double x;
	double v1;
	double t;
	double dt;
	double m;

protected:
	double func(double x);//правая часть ДУ
public:
	Mayatnik(double v0);//коструктор, первичная инициализация переменных
	void Start(CRungeKuttaDlg& dlg);
};