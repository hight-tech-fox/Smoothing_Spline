#include "grid_generator.h"
#include "Smoothing_Spline_1D.h"
#include <iostream>

int main() {
	try {
		//���������� �����
		auto Mesh = Com_Methods::Grid(1, 16, 15);

		//�������� ��������� ������� f(x)
		auto Func = Com_Methods::parse_points();

		//������������ �������
		Com_Methods::Smoothing_Spline_1D Sp(0.1);

		//���������� �������
		Sp.Update_Spline(Mesh, Func);

		//�������� ������� � ������
		double Res[3];
		for (int i = 0; i < 15; i++) {
			Sp.Get_Value(Com_Methods::Point(Mesh[i].x(), 0.0, 0.0), Res);
			std::cout << "(" << Mesh[i].x() << ", " << Res[0] << "),";
		}
	}
	catch (std::exception& Ex)
	{
		std::cout << "Error: " << Ex.what() << std::endl;
	}

}