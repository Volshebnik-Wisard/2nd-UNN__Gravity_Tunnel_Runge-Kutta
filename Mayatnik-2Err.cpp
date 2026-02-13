#include"stdafx.h"
#include"Mayatnik-2Err.h"
#include<cmath>
using namespace std;

Mayatnik2Err::Mayatnik2Err(double v0)
{
	pi = 4 * atan(1);
	R2 = 6371 * 1000;
	R1 = R2 / 2;
	G = 6.67430 * pow(10, -11);
	Me = 5.9722 * pow(10, 24);
	g0 = (G * Me) / (R2 * R2);
	p = 5515.3;
	p1 = 16 * p / 9;
	p2 = 8 * p / 9;
	Me1 = 2 * Me / 9;
	Me2 = 7 * Me / 9;
	x = R2;
	v1 = v0;
	t = 0;
	dt = 0.005 * 2 * pi / sqrt(g0 / R2);
	m = 0.000001;
}



double Mayatnik2Err::func(double x)
//{
//	if ((-R2 <= x) && (x <= R2))
//	{
//		return -(g0 / R2) * x;
//	}
//	else
//	{
//		if (x >= 0)
//		{
//			return -(G * Me) / (x * x);
//		}
//		else
//		{
//			return (G * Me) / (x * x);
//		}
//	}
//}
{
	if ((-R1 <= x) && (x <= R1))

	{
		return -16 * x * g0 / (9 * R2);
	}
	else
	{
		if (((-R2 <= x) && (x <= -R1)) || ((R1 <= x) && (x <= R2)))
		{

			if (x >= 0)
			{
				//return -((G*Me1 / (x*x)) + 4 * G*pi*p2*x*x*x / (3 * x*x) - (4 * G*pi*p2*R1*R1*R1 / (3 * x*x)));
				return -(G * Me1 / (x * x)) - abs((4 / 3) * G * pi * p2 * x * x * x / (x * x)) + (4 / 3) * G * pi * p2 * R1 * R1 * R1 / (x * x);
				//return  -(G / (x * x)) * (Me1 + (4 / 3) * pi * p2 * (x * x * x - R1 * R1 * R1));
			}
			else
			{
				//return (G*Me1 / (x*x)) - 4 * G*pi*p2*x*x*x / (3 * x*x) - (4 * G*pi*p2*R1*R1*R1 / (3 * x*x));
				return (G * Me1 / (x * x)) - abs((4 / 3) * G * pi * p2 * x * x * x / (x * x)) + (4 / 3) * G * pi * p2 * R1 * R1 * R1 / (x * x);
				//return  (G / (x * x)) * (Me1 + (4 / 3) * pi * p2 * (x * x * x - R1 * R1 * R1));
			}
			//return -(G*Me1 / (x*x)) - abs((4 / 3)*G*pi*p2*x*x*x / (x*x)) + (4 / 3)*G*pi*p2*R1*R1*R1 / (x*x);
			//return  -(G / (x*x))*(Me1 + (4 / 3)*pi*p2*(x*x*x - R1*R1*R1));
		}
		else
		{
			if ((x <= -R2) || (R2 <= x))
			{
				if (x >= 0)
				{
					return -(G * Me) / (x * x);
				}
				else
				{
					return (G * Me) / (x * x);
				}
			}
		}

	}

}


void Mayatnik2Err::Start(CRungeKuttaDlg& dlg)
{
	ofstream
		/*outx("123/1 - X.txt"), outv("123/2 - V.txt"), outg("123/3 - g.txt"),
		outT("123/4 - T.txt"), outU("123/5 - U.txt"), outE("123/6 - E.txt"),*/
		outall("Task 2.txt");

	dlg.STOP = false;

	//график х от т
	dlg.graphX.DrawGraphScene(0, 200 * dt, -R2 - abs(v1 * v1 / 4), R2 + abs(v1 * v1 / 4));
	dlg.graphX.SetGraphStart(x, 0, 200 * dt, -R2 - abs(v1 * v1 / 4), R2 + abs(v1 * v1 / 4));


	dlg.graphX2.DrawGraphScene(0, 200 * dt, -8100 - abs(v1), 8100 + abs(v1));
	dlg.graphX2.SetGraphStart(v1, 0, 200 * dt, -8100 - abs(v1), 8100 + abs(v1));

	dlg.graphX3.DrawGraphScene(0, 200 * dt, -18, 18);
	dlg.graphX3.SetGraphStart(func(x), 0, 200 * dt, -18, 18);

	dlg.graphX4.DrawGraphScene(0, 200 * dt, 0, m * 6000 * 18000);
	dlg.graphX4.SetGraphStart(m * v1 * v1 / 2, 0, 200 * dt, 0, m * 6000 * 18000);



	if ((-R1 <= x) && (x <= R1))

	{
		dlg.graphX5.DrawGraphScene(0, 200 * dt, 0, m * 6000 * 18000);
		dlg.graphX5.SetGraphStart(-(-16 * g0 * (R1 * R1 - x * x) / (9 * R2 * 2) + m * G * ((-Me1 / R2 + Me1 / R1) + 4 * pi * p2 * ((R2 * R2 - R1 * R1) / 2 - (R1 * R1 * R1) * (-1 / R2 + 1 / R1)) / 3) + m * g0 * R2), 0, 200 * dt, 0, m * 6000 * 18000);

		dlg.graphX6.DrawGraphScene(0, 200 * dt, 0, m * 6000 * 18000);
		dlg.graphX6.SetGraphStart(-(-16 * g0 * (R1 * R1 - x * x) / (9 * R2 * 2) + m * G * ((-Me1 / R2 + Me1 / R1) + 4 * pi * p2 * ((R2 * R2 - R1 * R1) / 2 - (R1 * R1 * R1) * (-1 / R2 + 1 / R1)) / 3) + m * g0 * R2 + m * v1 * v1 / 2), 0, 200 * dt, 0, m * 6000 * 18000);
	}
	else
	{
		if (((-R2 <= x) && (x <= -R1)) || ((R1 <= x) && (x <= R2)))
		{


			dlg.graphX5.DrawGraphScene(0, 200 * dt, 0, m * 6000 * 18000);
			dlg.graphX5.SetGraphStart(-(-m * G * ((-Me1 / R2 + Me1 / x) + 4 * pi * p2 * ((R2 * R2 - x * x) / 2 - (R1 * R1 * R1) * (-1 / R2 + 1 / x)) / 3) + m * g0 * R2), 0, 200 * dt, 0, m * 6000 * 18000);

			dlg.graphX6.DrawGraphScene(0, 200 * dt, 0, m * 6000 * 18000);
			dlg.graphX6.SetGraphStart(-(-m * G * ((-Me1 / R2 + Me1 / x) + 4 * pi * p2 * ((R2 * R2 - x * x) / 2 - (R1 * R1 * R1) * (-1 / R2 + 1 / x)) / 3) + m * g0 * R2 + m * v1 * v1 / 2), 0, 200 * dt, 0, m * 6000 * 18000);

			//return -(G*Me1 / (x*x)) - abs((4 / 3)*G*pi*p2*x*x*x / (x*x)) + (4 / 3)*G*pi*p2*R1*R1*R1 / (x*x);
			//return  -(G / (x*x))*(Me1 + (4 / 3)*pi*p2*(x*x*x - R1*R1*R1));
		}
		else
		{
			if ((x <= -R2) || (R2 <= x))
			{
				dlg.graphX5.DrawGraphScene(0, 200 * dt, 0, m * 6000 * 18000);
				dlg.graphX5.SetGraphStart(-(-m * g0 * R2 * R2 / x), 0, 200 * dt, 0, m * 6000 * 18000);

				dlg.graphX6.DrawGraphScene(0, 200 * dt, 0, m * 6000 * 18000);
				dlg.graphX6.SetGraphStart(-(-m * g0 * R2 * R2 / x + m * v1 * v1 / 2), 0, 200 * dt, 0, m * 6000 * 18000);

			}
		}
	}








	vector<double> xgraphX, ygraphX, xgraphX2, ygraphX2, xgraphX3, ygraphX3,
		xgraphX4, ygraphX4, xgraphX5, ygraphX5, xgraphX6, ygraphX6;

	double k[4];
	double X, V;
	double v2 = v1;
	double x1 = x;
	int i = 0;
	t = 0;
	do
	{
		X = x1;
		V = v2;
		t = i * dt;
		k[0] = func(X) * dt;
		k[1] = func(X + V * dt / 2.) * dt;
		k[2] = func(X + V * dt / 2. + k[0] * dt / 4.) * dt;
		k[3] = func(X + V * dt + k[1] * dt / 2.) * dt;

		x1 = X + V * dt + (k[0] + k[1] + k[2]) * dt / 6.;
		v2 = V + (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6.;
		i++;


		dlg.drv.Draw(x1, true);
		dlg.graphX.PrintGraphDot(dt, t, x1, 0, 200 * dt, -R2 - abs(v1 * v1 / 4), R2 + abs(v1 * v1 / 4), xgraphX, ygraphX);
		dlg.graphX2.PrintGraphDot(dt, t, v2, 0, 200 * dt, -8100 - abs(v1), 8100 + abs(v1), xgraphX2, ygraphX2);
		dlg.graphX3.PrintGraphDot(dt, t, func(x1), 0, 200 * dt, -18, 18, xgraphX3, ygraphX3);
		dlg.graphX4.PrintGraphDot(dt, t, m * v2 * v2 / 2, 0, 200 * dt, 0, m * 6000 * 18000, xgraphX4, ygraphX4);

		if ((-R1 <= x) && (x <= R1))

		{
			dlg.graphX5.PrintGraphDot(dt, t, (-16 * g0 * (R1 * R1 - x1 * x1) / (9 * R2 * 2) + m * G * ((-Me1 / R2 + Me1 / R1) + 4 * pi * p2 * ((R2 * R2 - R1 * R1) / 2 - (R1 * R1 * R1) * (-1 / R2 + 1 / R1)) / 3) + m * g0 * R2), 0, 200 * dt, 0, m * 6000 * 18000, xgraphX5, ygraphX5);
			dlg.graphX6.PrintGraphDot(dt, t, (-16 * g0 * (R1 * R1 - x1 * x1) / (9 * R2 * 2) + m * G * ((-Me1 / R2 + Me1 / R1) + 4 * pi * p2 * ((R2 * R2 - R1 * R1) / 2 - (R1 * R1 * R1) * (-1 / R2 + 1 / R1)) / 3) + m * g0 * R2 + m * v2 * v2 / 2), 0, 200 * dt, 0, m * 6000 * 18000, xgraphX6, ygraphX6);

		}
		else
		{
			if (((-R2 <= x) && (x <= -R1)) || ((R1 <= x) && (x <= R2)))
			{
				if (x1 >= 0)
				{
					dlg.graphX5.PrintGraphDot(dt, t, (-m * G * ((-Me1 / R2 + Me1 / x1) + 4 * pi * p2 * ((R2 * R2 - x1 * x1) / 2 - (R1 * R1 * R1) * (-1 / R2 + 1 / x1)) / 3) + m * g0 * R2), 0, 200 * dt, 0, m * 6000 * 18000, xgraphX5, ygraphX5);
					dlg.graphX6.PrintGraphDot(dt, t, (-m * G * ((-Me1 / R2 + Me1 / x1) + 4 * pi * p2 * ((R2 * R2 - x1 * x1) / 2 - (R1 * R1 * R1) * (-1 / R2 + 1 / x1)) / 3) + m * g0 * R2 + m * v1 * v1 / 2), 0, 200 * dt, 0, m * 6000 * 18000, xgraphX6, ygraphX6);
				}
				else
				{
					dlg.graphX5.PrintGraphDot(dt, t, (-m * G * ((-Me1 / R2 + Me1 / x1) + 4 * pi * p2 * ((R2 * R2 - x1 * x1) / 2 - (R1 * R1 * R1) * (-1 / R2 + 1 / x1)) / 3) + m * g0 * R2), 0, 200 * dt, 0, m * 6000 * 18000, xgraphX5, ygraphX5);
					dlg.graphX6.PrintGraphDot(dt, t, (-m * G * ((-Me1 / R2 + Me1 / x1) + 4 * pi * p2 * ((R2 * R2 - x1 * x1) / 2 - (R1 * R1 * R1) * (-1 / R2 + 1 / x1)) / 3) + m * g0 * R2 + m * v1 * v1 / 2), 0, 200 * dt, 0, m * 6000 * 18000, xgraphX6, ygraphX6);
				}
				//return -(G*Me1 / (x*x)) - abs((4 / 3)*G*pi*p2*x*x*x / (x*x)) + (4 / 3)*G*pi*p2*R1*R1*R1 / (x*x);
				//return  -(G / (x*x))*(Me1 + (4 / 3)*pi*p2*(x*x*x - R1*R1*R1));
			}
			else
			{
				if ((x <= -R2) || (R2 <= x))
				{
					if (x1 >= 0)
					{
						dlg.graphX5.PrintGraphDot(dt, t, (-m * g0 * R2 * R2 / x1), 0, 200 * dt, 0, m * 6000 * 18000, xgraphX5, ygraphX5);
						dlg.graphX6.PrintGraphDot(dt, t, (-m * g0 * R2 * R2 / x1 + m * v2 * v2 / 2), 0, 200 * dt, 0, m * 6000 * 18000, xgraphX6, ygraphX6);
					}
					else
					{
						dlg.graphX5.PrintGraphDot(dt, t, (m * g0 * R2 * R2 / x1), 0, 200 * dt, 0, m * 6000 * 18000, xgraphX5, ygraphX5);
						dlg.graphX6.PrintGraphDot(dt, t, (m * g0 * R2 * R2 / x1 + m * v2 * v2 / 2), 0, 200 * dt, 0, m * 6000 * 18000, xgraphX6, ygraphX6);
					}
				}
			}
		}


		//}



		/*
		outx << setprecision(5) << "t = " << t << "    x = " << x1 << endl;
		outv << setprecision(5) << "t = " << t << "    v = " << v2 << endl;
		outg << setprecision(5) << "t = " << t << "    g = " << func(x1) << endl;
		outT << setprecision(5) << "t = " << t << "    T = " << m*v2*v2 / 2 << endl;

		if ((-R <= x1) && (x1 <= R))
		{
		outU << setprecision(4) << "t = " << t << "    U = " << -m*func(x1)*x1/2 << endl;
		outE << setprecision(4) << "t = " << t << "    E = " << -m*func(x1)*x1/2 + m*v2*v2 / 2 << endl;
		}
		else
		{

		outU << setprecision(5) << "t = " << t << "    U = " << -m*func(x1)*x1 << endl;
		outE << setprecision(5) << "t = " << t << "    E = " << -(m*func(x1)*x1 + m*v2*v2 / 2) << endl;
		}
		*/
		outall << setw(5) << i << setw(4) << "| " << setprecision(5) << "t = " << setw(6) << t << setw(4) << "| " <<
			"x = " << setw(12) << x1 << setw(2) << "| " << "v= " << setw(12) << v2 << setw(2) << "|" << " g= " << setw(12) << func(x1) << setw(2) << "|" << setw(5) <<
			"T = " << setw(12) << m * v2 * v2 / 2 << setw(2) << "| " << "U = " << setw(12) << -m * func(x1) * x1 << setw(2) << "|" << " E = " << setw(12) << -(m * func(x1) * x1 + m * v2 * v2 / 2) << setw(2) << "|" << endl;



		Sleep(5);


		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


	} while (dlg.STOP == false);
	/*
	outx.close();
	outv.close();
	outg.close();
	outT.close();
	outU.close();
	outE.close();
	*/

	outall.close();

}