#pragma once
#include<cmath>
#include<fstream>
#include<iomanip>
#include"Runge-KuttaDlg.h"
class Mayatnik2Err
{
private:
	double pi;
	double R1;
	double R2;
	double G;
	double p;
	double p1;
	double p2;
	double Me;
	double Me1;
	double Me2;
	double g0;
	double x;
	double v1;
	double t;
	double dt;
	double m;

protected:
	double func(double x);//правая часть ДУ
public:
	Mayatnik2Err(double v0);//коструктор, первичная инициализация переменных
	void Start(CRungeKuttaDlg& dlg);
};