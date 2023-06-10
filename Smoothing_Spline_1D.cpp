#include <functional>
#include "Smoothing_Spline_1D.h"
#include <iostream>
#include <fstream>

namespace Com_Methods
{
	std::vector<double> parse_points() {

		std::ifstream file;
		file.open("input_data.txt");

		std::vector<double> res{};
		double data;
		while (!file.eof()) {
			file >> data;
			res.push_back(data);
		}
		file.close();
		return res;
	}
	//êîíñòðóêòîð: SMOOTH - ïàðàìåòð ñãëàæèâàíèÿ
	Smoothing_Spline_1D::Smoothing_Spline_1D(const double &SMOOTH)
	{
		this->SMOOTH = SMOOTH;
	}

	//ïåðåõîä íà ìàñòåð ýëåìåíò [-1, 1]: 
	//Seg_Num - íîìåð ñåãìåíòà, Õ - àáñöèññà, Ksi - êîîðäèíàòà íà ìàñòåð-ýëåìåíòå
	void Smoothing_Spline_1D::Transition_To_Master_Element(int Seg_Num, const double &X, double &Ksi) const
	{
		Ksi = 2.0 * (X - Points[Seg_Num].x()) / (Points[Seg_Num + 1].x() - Points[Seg_Num].x()) - 1.0;
	}

	//áàçèñíûå ôóíêöèè íà [-1, 1]:
	//Number - íîìåð ôóíêöèè, Ksi - êîîðäèíàòà íà ìàñòåð-ýëåìåíòå
	double Smoothing_Spline_1D::Basis_Function(int Number, const double &Ksi) const
	{
		switch (Number)
		{
			case 1:  {return 0.5*(1 - Ksi); break; }
			case 2:  {return 0.5*(1 + Ksi); break; }
			default: {throw std::exception("Error in the basis function number..."); break; }
		}
	}

	//ïðîèçâîäíûå áàçèñíûõ ôóíêöèé íà [-1, 1]:
	//Number - íîìåð ôóíêöèè, Ksi - êîîðäèíàòà íà ìàñòåð-ýëåìåíòå
	double Smoothing_Spline_1D::Der_Basis_Function(int Number, const double &Ksi) const
	{
		switch (Number)
		{
			case 1:  {return -0.5; break; }
			case 2:  {return  0.5; break; }
			default: {throw std::exception("Error in the basis function derivative number..."); break; }
		}
	}

	//îáíîâèòü ñïëàéí
	void Smoothing_Spline_1D::Update_Spline(const std::vector<Point>  & Points,
											const std::vector<double> & F_Value)
	{
		//îáíîâëåíèå ñïèñêà òî÷åê ñïëàéíà
		this->Points.clear();
		for (auto & elem : Points) this->Points.push_back(elem);

		//÷èñëî îòðåçêîâ ðàçáèåíèÿ
		int Num_Segments = Points.size() - 1;

		//êîýôôèöèåíòû ðàçëîæåíèÿ ïî áàçèñó
		alpha.resize(Num_Segments + 1);

		//äèàãîíàëè ìàòðèöû
		std::vector <double> a, b, c;
		a.resize(Num_Segments + 1); b.resize(Num_Segments + 1); c.resize(Num_Segments + 1);
		
		//ïðîöåäóðà äëÿ àññåìáëèðîâàíèÿ ÑËÀÓ: 
		//Num_Segment - íîìåð îòðåçêà, P - òî÷êà, F_Val - çíà÷åíèå òàáëè÷íîé ôóíêöèè â òî÷êå, w - âåñ  
		std::function<void(int Num_Segment, const Point &P, const double &F_Val, const double &w)> 
		Assembling = [&](int i, const Point &P, const double &F_Val, const double &w)
		{
			double X = P.x(), Ksi;
			//ïåðåõîä íà ìàñòåð-ýëåìåíò
		    Transition_To_Master_Element(i, X, Ksi);
			//âû÷èñëåíèå çíà÷åíèé áàçèñíûõ ôóíêöèé íà ìàñòåð-ýëåìåíòå
			double f1 = Basis_Function(1, Ksi);
			double f2 = Basis_Function(2, Ksi);

			//âíåñåíèå âêëàäîâ â ìàòðèöó ÑËÀÓ
			b[i]     += (1.0 - SMOOTH) * w * f1 * f1;
			b[i + 1] += (1.0 - SMOOTH) * w * f2 * f2;
			a[i + 1] += (1.0 - SMOOTH) * w * f1 * f2;
			c[i]	 += (1.0 - SMOOTH) * w * f2 * f1;
			//âíåñåíèå âêëàäîâ â âåêòîð ïðàâîé ÷àñòè ÑËÀÓ
			alpha[i]     += (1.0 - SMOOTH) * w * f1 * F_Val;
			alpha[i + 1] += (1.0 - SMOOTH) * w * f2 * F_Val;
		};

		//ñáîðêà ÑËÀÓ ïî ñåòêå: ñóììà âêëàäîâ îò êàæäîãî ñåãìåíòà ðàçáèåíèÿ
		for (int i = 0; i < Num_Segments; i++)
		{
			//äîáàâëåíèå óçëà ñåòêè â ÑËÀÓ
			double W = 4.0; //âåñ-1
			Assembling(i, this->Points[i], F_Value[i], W);
			Assembling(i, this->Points[i + 1], F_Value[i + 1], W);

			//âêëàä îò ñãëàæèâàíèÿ ïî ïåðâîé ïðîèçâîäíîé
			double h = Points[i + 1].x() - Points[i].x();
			b[i]	 += 1.0 / h * SMOOTH;
			b[i + 1] += 1.0 / h * SMOOTH;
			a[i + 1] -= 1.0 / h * SMOOTH;
			c[i]	 -= 1.0 / h * SMOOTH;
		}

		//ìåòîä ïðîãîíêè: ïðÿìîé õîä
		for (int j = 1; j < Num_Segments + 1; j++)
		{
			//äèàãîíàëü
			b[j] -= a[j] / b[j - 1] * c[j - 1];
			//ïðàâàÿ ÷àñòü         
			alpha[j] -= a[j] / b[j - 1] * alpha[j - 1]; 
		}

		//ìåòîä ïðîãîíêè: îáðàòíûé õîä
		alpha[Num_Segments] /= b[Num_Segments];
		for (int j = Num_Segments - 1; j >= 0; j--)
			alpha[j] = (alpha[j] - alpha[j + 1] * c[j]) / b[j];
	}

	//âû÷èñëèòü çíà÷åíèå ñïëàéíà â òî÷êå P
	void Smoothing_Spline_1D::Get_Value(const Point &P, double * Res)const
	{
		//ìàøèííûé íîëü
		double eps = 1e-7;
		//÷èñëî îòðåçêîâ
		int Num_Segments = Points.size() - 1;
		//êîîðäèíàòà òî÷êè
		double X = P.x();

		//ïîèñê îòðåçêà, êîòîðîìó ïðèíàäëåæèò òî÷êà
		for (int i = 0; i < Num_Segments; i++)
		{
			if (X > Points[i].x() && X < Points[i + 1].x() ||
				fabs(X - Points[i].x()) < eps ||
				fabs(X - Points[i + 1].x()) < eps)
			{
				//äëèíà îòðåçêà
				double h = Points[i + 1].x() - Points[i].x();
				//ïåðåõîä íà ìåñòåð-ýëåìåíò, Ksi - êîîðäèíàòà íà ìàñòåð-ýëåìåíòå
				double Ksi;
				Transition_To_Master_Element(i, X, Ksi);
				//âû÷èñëÿåì çíà÷åíèå ñïëàéíà è ïðîèçâîäíîé ïî áàçèñíûì ôóíêöèÿì
				Res[0] = alpha[i]      * Basis_Function(1, Ksi) +
						 alpha[i + 1]  * Basis_Function(2, Ksi);
				Res[1] = (alpha[i]     * Der_Basis_Function(1, Ksi) +
						  alpha[i + 1] * Der_Basis_Function(2, Ksi)) * 2.0 / h;
				Res[2] = 0.0;
				return;
			}
		}
		throw std::exception("The point is not found in the segments...");
	}
}
