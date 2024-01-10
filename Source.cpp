#include <iostream>
#include <cmath>

const double epsilon = 0.000001;

void calcEquationCoeff(double[], double[], double[]);
void printEquation(double[]);
void printParabola(double[]);
void printIntersectionPoints(double[], double[]);
void simplify(double[]);
bool pointLies(double[], double[]);
void parallelLine(double[], double[], double[]);
void perpendicularLine(double[], double[], double[]);
double getAbs(const double);
void intersectionPoint(double[], double[], double[]);
void getMidPoint(double[], double[], double[]);
void printAltitudes(double[][2], double[][3]);
void printMedians(double[][2], double[][2]);
void printSymetrals(double[][3], double[][2]);
double calculateArea(double[][2]);
double calculatePerimeter(double[][2]);
double calculateDistance(double[], double[]);
bool quadraticEquation(double[],double[]);
double valueOfLinFunc(double[], double);
double valueOfParabola(double[], double);
void calculateTangentCoeffs(double[], double, double, double[]);
void printTangents(double[], double[]);
void welcomeMessage();
void triangleMessage(char&);

void operationLineInput();
void operationPointLies();
void operationParallel();
void operationPerpendicular();
void operationIntersectLines();
void operationTriangle();
void operationIntersectParabolaLine();
void operationTangents();

void readLineCoeffs(double[]);
void readLineCoordinates(double[], const int);
void readParabolaCoeffs(double[]);
bool validateCoordinates(double[][2], int); // checks if all points have unique coordinates

// zakruglqvane
//sukrushtavane na koef
//imena na tochki i pravi!!!!!!!


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
		case '4': operationPerpendicular(); break;
		case '5': operationIntersectLines(); break;
		case '6': operationTriangle(); break;
		case '7':  operationTangents(); break;
		case '8': operationIntersectParabolaLine();  break;
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

bool quadraticEquation(double coeffs[], double roots[])
{

	double discriminamt = coeffs[1] * coeffs[1] - 4 * coeffs[0] * coeffs[2];

	if (discriminamt < 0)
	{

		return false;
	}
	else if(discriminamt>=0)
	{
		roots[0] = (-coeffs[1] + sqrt(discriminamt)) / (2 * coeffs[0]);
		roots[1] = (-coeffs[1] - sqrt(discriminamt)) / (2 * coeffs[0]);
	}
	return true;
}

double valueOfLinFunc(double lineCoeffs[], double var)
{
	double value = -(lineCoeffs[0] * var + lineCoeffs[2]) / lineCoeffs[1];

	return value;
}

double valueOfParabola(double parabolaCoeffs[], double var)
{
	double value = parabolaCoeffs[0] * var * var + parabolaCoeffs[1] * var + parabolaCoeffs[2];
	return value;
}

void calcEquationCoeff(double firstPoint[], double secondPoint[], double lineCoeff[])
{

	lineCoeff[0] = secondPoint[1] - firstPoint[1];
	lineCoeff[1] = firstPoint[0] - secondPoint[0];
	lineCoeff[2] = secondPoint[0] * firstPoint[1] - firstPoint[0] * secondPoint[1];

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
			std::cout << '-' << 'x';
		}
		else
		{
			std::cout << lineCoeff[0] << 'x';
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
					std::cout << '+' << lineCoeff[1] << 'y';
				}
				else
				{
					std::cout << lineCoeff[1] << 'y';
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
	std::cout << '=' << 0 << std::endl;
}

void printParabola(double parabolaCoeffs[])
{
	std::cout <<"y=";

	if (parabolaCoeffs[0] == 1)
	{
		std::cout << "x^2";
	}
	else if (parabolaCoeffs[0] == -1)
	{
		std::cout << "-x^2";
	}
	else
	{
		std::cout << parabolaCoeffs[0] << "x^2";
	}

	if (parabolaCoeffs[1] != 0)
	{
		if (parabolaCoeffs[1] == 1)
		{
			std::cout << "+x";
		}
		else if (parabolaCoeffs[1] == -1)
		{
			std::cout << "-x";
		}
		else
		{
			if (parabolaCoeffs[1] > 0)
			{
				std::cout << '+';
			}
			std::cout << parabolaCoeffs[1] << 'x';
		}
	}
	if (parabolaCoeffs[2] != 0)
	{
		if (parabolaCoeffs[2] > 0)
		{
			std::cout << '+' << parabolaCoeffs[2];
		}
		else
		{
			std::cout << parabolaCoeffs[2];
		}
	}
}

void simplify(double lineCoeff[])
{
	if (lineCoeff[0] < 0 || (lineCoeff[0] == 0 && lineCoeff[1] < 0))
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
	parallelCoeff[2] = -(parallelCoeff[0] * pointCoordinates[0] + parallelCoeff[1] * pointCoordinates[1]);
}

void perpendicularLine(double pointCoordinates[], double lineCoeff[], double perpendicularCoeff[])
{
	perpendicularCoeff[0] = -lineCoeff[1];
	perpendicularCoeff[1] = lineCoeff[0];
	perpendicularCoeff[2] = -(perpendicularCoeff[0] * pointCoordinates[0] + perpendicularCoeff[1] * pointCoordinates[1]);
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
			std::cout << "Lines coincide" << '\n';
		}
		else
		{
			std::cout << "Lines are parallel. They don't intersect." << '\n';
		}
	}
	else
	{
		intersection[0] = detA / det;
		intersection[1] = detB / det;
		std::cout << intersection[0] << ' ' << intersection[1] << '\n';
	}
}

void getMidPoint(double firstPoint[], double secondPoint[], double midPoint[])
{
	midPoint[0] = firstPoint[0] / 2.00 + secondPoint[0] / 2.00;
	midPoint[1] = firstPoint[1] / 2.00 + secondPoint[1] / 2.00;
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
	std::cout << "6. Determine the equations of all altitudes, medians and symetrals of a triangle defined by the coordinates of its vertices\n";
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
		readLineCoordinates(lineCoeff, 2);
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
	std::cout << '(' << pointCoordinates[0] << ';' << pointCoordinates[1] << ')' << '\n';
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

	std::cout << "Your new paraellel line is: ";
	printEquation(parallelCoef);
}

void operationPerpendicular()
{
	double lineCoeff[3]{};
	double pointCoordinates[2]{};

	std::cout << "Enter point (x;y) coordinates: \n";
	std::cout << "x = ";
	std::cin >> pointCoordinates[0];
	std::cout << "y = ";
	std::cin >> pointCoordinates[1];
	std::cout << '(' << pointCoordinates[0] << ';' << pointCoordinates[1] << ')' << '\n';
	readLineCoeffs(lineCoeff);

	if (pointLies(pointCoordinates, lineCoeff))
	{
		double perpendicularCoef[3]{};
		perpendicularLine(pointCoordinates, lineCoeff, perpendicularCoef);
		std::cout << "Your new perpendicular line is: ";
		printEquation(perpendicularCoef);
	}

	else
	{
		std::cout << "The line doesn't pass through the point" << '\n';
	}

}

void operationIntersectLines()
{
	double firstLineCoeffs[3]{};
	double secondLineCoeffs[3]{};
	double intersect[2]{};
	readLineCoeffs(firstLineCoeffs);
	readLineCoeffs(secondLineCoeffs);
	printEquation(firstLineCoeffs);
	printEquation(secondLineCoeffs);
	intersectionPoint(firstLineCoeffs, secondLineCoeffs, intersect);
}

void operationTriangle()
{
	double vertices[3][2]{};
	double midPoints[3][2]{};
	double sideEquationCoeff[3][3]{};

	double area = 0.00;
	int counter = 0;
	char optionTriangle = 'a';
	
	while (true)
	{
		for (int i = 0; i < 3; i++)
		{
			std::cout << "Enter Point " << i + 1 << "= ";
			std::cin >> vertices[i][0] >> vertices[i][1];
		}

		area = calculateArea(vertices);

		if (area <= epsilon)
		{
			std::cout << "Triangle with such coordinates doesn't exist. Please, enter your coordinates again" << '\n';
		}
		else
		{
			break;
		}
	}
	std::cout << "Your triangle has equations : \n";
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{
			calcEquationCoeff(vertices[i], vertices[j], sideEquationCoeff[counter]);
			printEquation(sideEquationCoeff[counter]);
			getMidPoint(vertices[i], vertices[j], midPoints[counter]);
			counter++;
		}
	}

	triangleMessage(optionTriangle);

	switch (optionTriangle)
	{
	case 'a': printAltitudes(vertices, sideEquationCoeff); break;
	case 'b': printMedians(vertices, midPoints); break;
	case 'c': printSymetrals(sideEquationCoeff, midPoints); break;
	case 'd': std::cout << "Area = " << area<<'\n';
	case 'e': std::cout << "Perimeter = " << calculatePerimeter(vertices) << '\n'; break;
	}
}

void operationTangents()
{
	double parabolaCoeffs[3]{};
	double pointCoordinates[2]{};
	

	readParabolaCoeffs(parabolaCoeffs);
	std::cout << "Your parabola is: ";
	printParabola(parabolaCoeffs);
	std::cout << '\n';
	std::cout << "Enter a point (x;y) you want to find a tangent through >> ";
	std::cin >> pointCoordinates[0]>>pointCoordinates[1];
	std::cout << "Your point is (" << pointCoordinates[0] <<';'<<pointCoordinates[1]<<')'<<'\n';

	printTangents(parabolaCoeffs, pointCoordinates);
}

void printTangents(double parabolaCoeffs[], double pointCoordinates[])
{
	double tangentCoeffs[3]{};

	double valueofX = valueOfParabola(parabolaCoeffs, pointCoordinates[0]);

	if (getAbs(valueofX - pointCoordinates[1]) <= epsilon) // the point lies on the parabola so we have one tangent only
	{
		std::cout << "Only one tangent passes through your parabola: ";
		calculateTangentCoeffs(parabolaCoeffs, pointCoordinates[0], pointCoordinates[1], tangentCoeffs);
		printEquation(tangentCoeffs);
	}

	else // we may have 2 or 0 tangents here
	{
		double newCoeffs[3]{}, helpPoints[2]{}; // we try to find points on our parabola the tangents also pass through
		double valueY = 0;
		newCoeffs[0] = -parabolaCoeffs[0];
		newCoeffs[1] = 2 * parabolaCoeffs[0] * pointCoordinates[0];
		newCoeffs[2] = parabolaCoeffs[1] * pointCoordinates[0] + parabolaCoeffs[2] - pointCoordinates[1];
		
		if (quadraticEquation(newCoeffs, helpPoints))
		{
				std::cout << "Two tangents pass through your parabola: ";
				valueY = valueOfParabola(parabolaCoeffs, helpPoints[0]);
				calculateTangentCoeffs(parabolaCoeffs, helpPoints[0], valueY, tangentCoeffs);
				printEquation(tangentCoeffs);

				valueY = valueOfParabola(parabolaCoeffs, helpPoints[1]);
				calculateTangentCoeffs(parabolaCoeffs, helpPoints[1], valueY, tangentCoeffs);
				printEquation(tangentCoeffs);
		}
		else
		{
			std::cout << "No tangents passing through this point!\n";
		}
	}
}

void calculateTangentCoeffs(double parabolaCoeffs[], double pointX, double pointY, double tangentCoeffs[])
{
	// y=y'(x0)*(x-x0)+y0 where (x0;y0) lies on the parabola
	tangentCoeffs[0] = 2 * parabolaCoeffs[0] * pointX + parabolaCoeffs[1];
	tangentCoeffs[1] = -1;
	tangentCoeffs[2] = -2 * parabolaCoeffs[0] * pointX*pointX - parabolaCoeffs[1] * pointX + pointY;
}

void operationIntersectParabolaLine()
{
	double parabolaCoeffs[3];
	double lineCoeffs[3];
	
	readParabolaCoeffs(parabolaCoeffs);
	readLineCoeffs(lineCoeffs);

	std::cout << "Your parabola is: ";
	printParabola(parabolaCoeffs);
	std::cout << '\n';
	std::cout << "Your line is: ";
	printEquation(lineCoeffs);
	std::cout << '\n';

	printIntersectionPoints(parabolaCoeffs, lineCoeffs);
}

void printIntersectionPoints(double parabolaCoeffs[], double lineCoeffs[])
{
	if (lineCoeffs[1] == 0) // ax+c=0
	{
		std::cout << "Your parabola and line intersect in: ";
		double value = valueOfParabola(parabolaCoeffs, -lineCoeffs[2]/lineCoeffs[0]);
		std::cout << '(' << -lineCoeffs[2] / lineCoeffs[0] << " ; " << value << ')';
		std::cout << '\n';
		return;
	}

	double newCoeffs[3]{}; //| ax^2+bx+c=y
	double roots[2]{};	   //| mx+ny+p=0 we express y from the line and plug it into the parabola to calculte the x's both intersect in

	newCoeffs[0] = parabolaCoeffs[0] * lineCoeffs[1];
	newCoeffs[1] = parabolaCoeffs[1] * lineCoeffs[1] + lineCoeffs[0];
	newCoeffs[2] = parabolaCoeffs[2] * lineCoeffs[1] + lineCoeffs[2];

	if (quadraticEquation(newCoeffs, roots))
	{
		if (roots[0] == roots[1]) // when D=0 we have a double root
		{
			double value = valueOfLinFunc(lineCoeffs, roots[0]);
			std::cout << '(' << roots[0] << " ; " << value << ')';
			std::cout << '\n';
		}
		else
		{
			double value1 = valueOfLinFunc(lineCoeffs, roots[0]);
			double value2 = valueOfLinFunc(lineCoeffs, roots[1]);
			std::cout << "Two intersection points: ";
			std::cout << '(' << roots[0] << " ; " << value1 << ')';
			std::cout << " (" << roots[1] << " ; " << value2 << ')';
			std::cout << '\n';
		}
	}
	else
	{
		std::cout << "No real roots!\n";
	}
}

void triangleMessage(char& optionTriangle)
{
	std::cout << "Choose an operation you want to execute with your triangle:\n\n";
	std::cout << "	a. find equations of the altitudes\n";
	std::cout << "	b. find equations of the medians\n";
	std::cout << "	c. find equations of the symetrals\n";
	std::cout << "	d. calculate area\n";
	std::cout << "	e. calculate perimeter\n\n";
	std::cout << "Enter your choice here>> ";
	std::cin >> optionTriangle;

	while (true)
	{
		if (optionTriangle >= 'a' && optionTriangle <= 'f')
		{
			break;
		}
		else if ((optionTriangle >= 'A' && optionTriangle <= 'F'))
		{
			optionTriangle = 'a' + (optionTriangle - 'A');
			break;
		}

		std::cout << "You have entered an invalid input. Please, try again >> ";
		std::cin >> optionTriangle;
	}
	std::cout << '\n';
}

void printAltitudes(double vertices[][2], double sideEquationCoeff[][3])
{
	int counter = 2;
	double altitudeEquationCoeffs[3][3]{};
	std::cout << "Altitudes: \n";

	for (int i = 0; i < 3; i++)
	{
		perpendicularLine(vertices[counter], sideEquationCoeff[i], altitudeEquationCoeffs[i]);
		printEquation(altitudeEquationCoeffs[i]);
		counter--;
	}
}

void printMedians(double vertices[][2], double midPoints[][2])
{
	int counter = 2;
	double medianEquationCoeffs[3][3]{};
	std::cout << "Medians: \n";
	for (int i = 0; i < 3; i++)
	{
		calcEquationCoeff(vertices[i], midPoints[counter], medianEquationCoeffs[i]);
		printEquation(medianEquationCoeffs[i]);
		counter--;
	}
}

void printSymetrals(double sideEquationCoeff[][3], double midPoints[][2])
{
	
	double symetralEquationCoeffs[3][3]{};
	std::cout << "Symetrals: \n";
	for (int i = 0; i < 3; i++)
	{
		perpendicularLine(midPoints[i], sideEquationCoeff[i], symetralEquationCoeffs[i]);
		printEquation(symetralEquationCoeffs[i]);
	}
}

double calculatePerimeter(double vertices[][2])
{
	double perimeter = 0.00;

	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{
			perimeter += calculateDistance(vertices[i], vertices[j]);
		}
	}
	return perimeter;
}

double calculateDistance(double point1[], double point2[])
{
	double distance = (point2[0]-point1[0]) * (point2[0] - point1[0]) + (point2[1] - point1[1]) * (point2[1] - point1[1]);
	distance = sqrt(distance);

	return distance;
	
}

void readLineCoeffs(double lineCoeff[])
{
	std::cout << "Your line has equation ax+by+c=0. Please enter the coefficents a, b, c respectfully>> ";
	while (true) //validation
	{
		std::cin >> lineCoeff[0] >> lineCoeff[1] >> lineCoeff[2];
		if (getAbs(lineCoeff[0]) <= epsilon && getAbs(lineCoeff[1]) <= epsilon)
		{
			std::cout << "Coefficents a and be CAN'T be both  zeros simultaneously. Try again>> ";
		}
		else
		{
			break;
		}
	}
}

void readParabolaCoeffs(double parabolaCoeffs[])
{
	std::cout << "Your parabola has equation y=ax^2+bx+c, where a=/=0. Please enter the coefficents a, b, c respectfully>> ";

	while (true) //validation
	{
		std::cin >> parabolaCoeffs[0] >> parabolaCoeffs[1] >> parabolaCoeffs[2];
		if (getAbs(parabolaCoeffs[0]) <= epsilon)
		{
			std::cout << "Coefficent a can't be zero. Try again>> ";
		}
		else
		{
			break;
		}
	}
}

void readLineCoordinates(double lineCoeff[], const int count)
{
	double coordinates[2][2]{};
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
		if (validateCoordinates(coordinates, count))
		{
			break;
		}
		else
		{
			std::cout << "You have entered the same coordinates. Try again\n";
		}
	}
	calcEquationCoeff(coordinates[0], coordinates[1], lineCoeff);
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

double calculateArea(double coord[][2])
{
	double result = 0.5 * (coord[0][0] * (coord[1][1] - coord[2][1]) + coord[1][0] * (coord[2][1] - coord[0][1]) + coord[2][0] * (coord[0][1] - coord[1][1]));
	result = getAbs(result);
	return result;
}