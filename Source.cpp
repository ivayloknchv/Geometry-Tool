#include <iostream>

const double epsilon = 0.000001;

void calcEquationCoeff(double [][2], double[]);
void printEquation(double[]);
void simplify(double[]);
bool pointLies(double[], double[]);
void parallelLine(double[], double[],double[]);
void perpendicularLine(double[], double[], double[]);
double getAbs(const double);
void intersectionPoint(double[], double[], double[]);
void welcomeMessage();

void operationLineInput();
void operationPointLies();
void operationParallel();

void readLineCoeffs(double[]);
void readLineCoordinates(double[], const int);
bool validateCoordinates(double[][2], int); // checks if all points have unique coordinates


//proverka dali koordinatite sa razlichni
//sukrushtavane na koef
//imena na tochki i pravi!!!!!!!
//void ili pointer masiv???
//a=0 i b=0 ednovremenno
// funkciqta za perpendikulqra i petata
//razl naredeni dvoyki

int main()
{
	welcomeMessage();

	char operation = '0';
	std::cout << "Enter the number of operation you want to execute >> ";
	std::cin >> operation;
	while (operation != '0')
	{
		while (true)
		{
			if (operation >= '1' && operation <= '9')
			{
				break;
			}
			else
			{
				std::cout << "Invalid number! Please, try again >> ";
				std::cin >> operation;
			}
		}

		switch (operation)
		{
		case '1': operationLineInput(); break;
		case '2': operationPointLies();  break;
		case '3': operationParallel(); break;
		}
		std::cout << "----------------------------\n";
		std::cout << "Enter the number of operation you want to execute >> ";
		std::cin >> operation;
	}

	return 0;
}

double getAbs(double num)
{
	return (num >= 0) ? num : -num;
}

void calcEquationCoeff(double pointCoordinates[][2], double lineCoeff[])
{

	lineCoeff[0] = pointCoordinates[1][1] - pointCoordinates[0][1];
	lineCoeff[1] = pointCoordinates[0][0] - pointCoordinates[1][0];
	lineCoeff[2] = pointCoordinates[1][0] * pointCoordinates[0][1] - pointCoordinates[0][0] * pointCoordinates[1][1];
	
}

void printEquation(double lineCoeff[])
{


	simplify(lineCoeff);
	if (lineCoeff[0] != 0) 
	{
		if (lineCoeff[0] == 1)
		{
			std::cout << 'x';
		}
		else if (lineCoeff[0] == -1)
		{
			std::cout << '-'<<'x';
		}
		else
		{
			std::cout << lineCoeff[0]<<'x';
		}
	}

	if (lineCoeff[1] != 0)
	{

		if (lineCoeff[1] == 1)
		{
			if (lineCoeff[0] == 0)
			{
				std::cout << 'y';
			}
			else
			{
				std::cout << '+' << 'y';
			}
		}
		else if (lineCoeff[1] == -1)
		{	
			std::cout << '-' << 'y';
		}
		else
		{
			if (lineCoeff[0] == 0)
			{
				std::cout << lineCoeff[1] << 'y';
			}
			else
			{
				if (lineCoeff[1] > 0)
				{
					std::cout <<'+'<<lineCoeff[1] << 'y';
				}
				else
				{
					std::cout << lineCoeff[1]<<'y';
				}
			}
		}
	}

	if (lineCoeff[2] != 0)
	{
		if (lineCoeff[2] < 0)
		{
			std::cout << lineCoeff[2];
		}
		else
		{
			std::cout << '+' << lineCoeff[2];
		}
	}
	std::cout << '='<<0<<std::endl;
}

void simplify(double lineCoeff[])
{
	if (lineCoeff[0] < 0 || (lineCoeff[0]==0 && lineCoeff[1]<0))
	{
		for (int i = 0; i < 3; i++)
		{
			lineCoeff[i] *= -1;
		}
	}
} 

bool pointLies(double coordinates[], double lineCoeff[])
{
	double result = coordinates[0] * lineCoeff[0] + coordinates[1] * lineCoeff[1] + lineCoeff[2];

	if (getAbs((result)) <= epsilon)
	{
		return true;
	}

	return false;
}

void parallelLine(double pointCoordinates[], double lineCoeff[], double parallelCoeff[])
{
	parallelCoeff[0] = lineCoeff[0];
	parallelCoeff[1] = lineCoeff[1];
	parallelCoeff[2] = -(parallelCoeff[0]*pointCoordinates[0]+parallelCoeff[1]*pointCoordinates[1]);
	printEquation(parallelCoeff);
}

void perpendicularLine(double pointCoordinates[], double lineCoeff[], double perpendicularCoeff[])
{
	if (pointLies(pointCoordinates, lineCoeff))
	{
		perpendicularCoeff[0] = -lineCoeff[1];
		perpendicularCoeff[1] = lineCoeff[0];
		perpendicularCoeff[2] = -(perpendicularCoeff[0] * pointCoordinates[0] + perpendicularCoeff[1] * pointCoordinates[1]);
		printEquation(perpendicularCoeff);
	}
	else
	{
		std::cout << "The point doesn't lie on the line";
	}
}

void intersectionPoint(double firstLine[], double secondLine[], double intersection[])
{
	//Using Cramer's rule to solve system of linear equations
	// x = detA/det, y = detB/det

	double det = (firstLine[0] * secondLine[1] - secondLine[0] * firstLine[1]);
	double detA = (-firstLine[2] * secondLine[1] + firstLine[1] * secondLine[2]);
	double detB = (-firstLine[0] * secondLine[2] + secondLine[0] * firstLine[2]);

	if (getAbs(det) <= epsilon)
	{
		if (getAbs(detA) <= epsilon && getAbs(detB) <= epsilon)
		{
			std::cout << "Lines coincide";
		}
		else
		{
			std::cout << "Lines are parallel. They don't intersect.";
		}
	}
	else
	{
		intersection[0] = detA / det;
		intersection[1] = detB / det;
		std::cout << intersection[0] << ' ' << intersection[1];
	}
}

void welcomeMessage()
{
	std::cout << "Welcome to Geometry Tool!\n\n";
	std::cout << "This mini project can help you solve the following Analytic geometry problems and operations: \n\n";

	std::cout << "1. Determine the equation of a line using its coefficents or two points and their coordinates\n";
	std::cout << "2. Check if a point lies on a certain line\n";
	std::cout << "3. Determine the equation of the line that passes through a point and is parallel to another line\n";
	std::cout << "4. Determine the equation of the line that is perpendicular to another line and passes through a point that lies on the given line \n";
	std::cout << "5. Find the intersection point of two lines, if it exists\n";
	std::cout << "6. Determine the equations of all altitudes, medians and symetrals of a triangle defined by the coordinates of its edges\n";
	std::cout << "7. Find the tangent of a parabolyc equation through a point\n";
	std::cout << "8. Determine the intersection point of a line and a parabola\n";
	std::cout << "9. Determime if four lines form a quadrilateral and its type. If they don't, show an appropriate message\n\n";
	std::cout << "Press 0 if you want to quit.\n\n";

}

void operationLineInput()
{
	char option = 'a';
	double lineCoeff[3]{};
	std::cout << "\nHow would you like to input your line?\n";
	std::cout << "\t a. With coordinates\n \t b. With coefficents\n";
	std::cout << "Choose a OR b >> ";
	std::cin >> option;

	while (true)
		{
			if (option == 'a' || option == 'b')
			{
				break;
			}
			else
			{
				std::cout << "Invalid input! Please, enter a OR b >> \n";
				std::cin >> option;
			}	
	}
	if (option == 'a')
	{
		readLineCoordinates(lineCoeff,2);
	}
	else
	{
		readLineCoeffs(lineCoeff);
	}

	printEquation(lineCoeff);
}

void operationPointLies()
{
	double lineCoeff[3]{};
	double pointCoordinates[2]{};

	std::cout << "Enter point (x;y) coordinates: \n";
	std::cout << "x = ";
	std::cin >> pointCoordinates[0];
	std::cout << "y = ";
	std::cin >> pointCoordinates[1];
	std::cout << '(' << pointCoordinates[0] << ';' << pointCoordinates[1] << ')'<<'\n';
	readLineCoeffs(lineCoeff);
	printEquation(lineCoeff);
	if (pointLies(pointCoordinates, lineCoeff))
	{
		std::cout << "The point lies on the given line\n";
	}
	else
	{
		std::cout << "The point doesn't on the given line\n";
	}
}

void operationParallel()
{
	double lineCoeff[3]{};
	double pointCoordinates[2]{};
	double parallelCoef[3]{};
	std::cout << "Enter point (x;y) coordinates: \n";
	std::cout << "x = ";
	std::cin >> pointCoordinates[0];
	std::cout << "y = ";
	std::cin >> pointCoordinates[1];
	std::cout << '(' << pointCoordinates[0] << ';' << pointCoordinates[1] << ')' << '\n';
	readLineCoeffs(lineCoeff);

	parallelLine(pointCoordinates, lineCoeff, parallelCoef);

	std::cout << "Your paraellel line is: ";
	printEquation(parallelCoef);
}

void readLineCoeffs(double lineCoeff[])
{
	std::cout << "Your line has equation ax+by+c=0. Please enter the coefficents a, b, c respectfully>> ";
	while (true)
	{
		std::cin >> lineCoeff[0] >> lineCoeff[1] >> lineCoeff[2];
		if (getAbs(lineCoeff[0]) <= epsilon && getAbs(lineCoeff[1]) <= epsilon)
		{
			std::cout<<"Coefficents a and be CAN'T be both 0 zeros simultaneously. Try again>> ";
		}
		else
		{
			break;
		}
	}
}

void readLineCoordinates(double lineCoeff[], const int count)
{
	double coordinates[3][2]{};
	while (true)
	{
		for (int i = 0; i < count; i++)
		{
			std::cout << "Point " << (i + 1) << "= ";

			for (int j = 0; j < 2; j++)
			{
				std::cin >> coordinates[i][j];
			}
		}
		if (validateCoordinates(coordinates, 2))
		{
			break;
		}
		else
		{
			std::cout << "You have entered the same coordinates. Try again\n";
		}
	}
	calcEquationCoeff(coordinates, lineCoeff);
}

bool validateCoordinates(double coordinates[][2], const int count)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			if (coordinates[i][0] == coordinates[j][0] && coordinates[i][1] == coordinates[j][1])
			{
				return false;
			}
		}
	}
	return true;
}