#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class CPoint2D {
public:
	double x = 0, y = 0;
	CPoint2D() = default;
	CPoint2D(double x, double y) {
		this->x = x;
		this->y = y;
	}
};

class CVector2D {
public:
	double x = 0, y = 0;
	CVector2D() = default;
	CVector2D(double x, double y) {
		this->x = x;
		this->y = y;
	}
	double length() {
		return sqrt(this->x * this->x + this->y * this->y);
	}
};

class IGeoFig {
public:
	virtual double square() = 0;
	virtual double perimeter() = 0;
};

class IPhysObject {
public:
	virtual double mass() const = 0;
	virtual CPoint2D position() const = 0;
	//virtual bool operator==(const IPhysObject& ob) const = 0;
	//virtual bool operator<(const IPhysObject& ob) const = 0;
	bool operator==(const IPhysObject& ob) const {
		return mass() == ob.mass();
	}

	bool operator<(const IPhysObject& ob) const {
		return mass() < ob.mass();
	}
};

class IPrintable {
public:
	virtual void draw() = 0;
};

class IDialogInitiable {
public:
	virtual void initFromDialog() = 0;
};

class IBaseObject {
public:
	virtual const char* classname() = 0;
	virtual unsigned int size() = 0;
};

class CFigure : public IBaseObject, public IPhysObject, public IGeoFig, public IPrintable, public IDialogInitiable {};

class CEquilateralTriangle : public CFigure {
private:
	double _mass;
	CPoint2D _position;
	CVector2D _a;
public:
	CEquilateralTriangle() {
		this->_mass = 0;
		this->_position = CPoint2D(0, 0);
		this->_a = CVector2D(0, 0);
	}
	CEquilateralTriangle(double mass, CPoint2D position, CVector2D a) {
		this->_mass = mass;
		this->_position = position;
		this->_a = a;
	}
	void initFromDialog() {
		cout << "Input params of " << this->classname() << ": " << endl << "  Mass(kg): ";
		cin >> this->_mass;

		cout << "  Center of mass" << endl << "    X: ";
		cin >> this->_position.x;
		cout << "    Y: ";
		cin >> this->_position.y;

		cout << "  Vector of side" << endl << "    X: ";
		cin >> this->_a.x;
		cout << "    Y: ";
		cin >> this->_a.y;
	}

	double square() override {
		double len = this->_a.length();
		return len * len * sqrt(3) / 4;
	}

	double perimeter() override {
		return this->_a.length() * 3;
	}

	virtual const char* classname() {
		return "equilateral triangle";
	}

	unsigned int size() override {
		return sizeof(this->_mass) + sizeof(this->_position) + sizeof(this->_a);
	}

	double mass() const override {
		return this->_mass;
	}

	CPoint2D position() const override {
		return this->_position;
	}

	//bool operator==(const IPhysObject& ob) const override {
	//	return mass() == ob.mass();
	//}

	//bool operator<(const IPhysObject& ob) const override {
	//	cout << mass();
	//	return mass() < ob.mass();
	//}

	void draw() override {
		cout << "  mass = " << mass() << "kg" << endl;
		cout << "  center = (" << position().x << ", " << position().y << ")" << endl;
		cout << "  vector = (" << _a.x << ", " << _a.y << ")" << endl;
		cout << "  square = " << square() << endl;
		cout << "  perimeter = " << perimeter() << endl;
		cout << "  size = " << size() << endl;
	}
};

class CParallelogram : public CFigure {
private:
	double _mass = 0;
	CPoint2D _position;
	CVector2D _a;
	CVector2D _b;
public:
	CParallelogram() {
		this->_mass = 0;
		this->_position = CPoint2D(0, 0);
		this->_a = CVector2D(0, 0);
		this->_b = CVector2D(0, 0);
	};
	CParallelogram(double mass, CPoint2D position, CVector2D a, CVector2D b) {
		this->_mass = mass;
		this->_position = position;
		this->_a = a;
		this->_b = b;
	}
	void initFromDialog() {
		cout << "Input params of " << this->classname() << ": " << endl << "  Mass(kg): ";
		cin >> this->_mass;

		cout << "  Center of mass" << endl << "    X: ";
		cin >> this->_position.x;
		cout << "    Y: ";
		cin >> this->_position.y;

		cout << "  Vector of first side" << endl << "    X: ";
		cin >> this->_a.x;
		cout << "    Y: ";
		cin >> this->_a.y;

		cout << "  Vector of second side" << endl << "    X: ";
		cin >> this->_b.x;
		cout << "    Y: ";
		cin >> this->_b.y;
	}

	double square() override {
		double lenA = this->_a.length();
		double lenB = this->_b.length();
		double scalar = this->_a.x * this->_b.x + this->_a.y * this->_b.y;
		double cosAngle = scalar / lenA / lenB;
		double sinAngle = sqrt(1 - cosAngle * cosAngle);
		return lenA * lenB * sinAngle;
	}

	double perimeter() override {
		return (this->_a.length() + this->_b.length()) * 2;
	}

	virtual const char* classname() {
		return "parallelogram";
	}

	unsigned int size() override {
		return sizeof(this->_mass) + sizeof(this->_position) + sizeof(this->_a) + sizeof(this->_b);
	}

	double mass() const override {
		return this->_mass;
	}

	CPoint2D position() const override {
		return this->_position;
	}

	//bool operator==(const IPhysObject& ob) const override {
	//	return mass() == ob.mass();
	//}
	//
	//bool operator<(const IPhysObject& ob) const override {
	//	return mass() < ob.mass();
	//}

	void draw() override {
		cout << "  mass = " << mass() << "kg" << endl;
		cout << "  center = (" << position().x << ", " << position().y << ")" << endl;
		cout << "  vectors = (" << _a.x << ", " << _a.y << "), (" << _b.x << ", " << _b.y << ")" << endl;
		cout << "  square = " << square() << endl;
		cout << "  perimeter = " << perimeter() << endl;
		cout << "  size = " << size() << endl;
	}
};

unsigned int totalSize(vector <CFigure*>& figures) {
	unsigned int total = 0;
	for (auto f : figures)
		total += f->size();
	return total;
}

double totalMass(vector <CFigure*>& figures) {
	double total = 0;
	for (auto f : figures)
		total += f->mass();
	return total;
}

CPoint2D totalMassCenter(vector <CFigure*> &figures) {
	double M = totalMass(figures);
	CPoint2D center;
	for (auto f : figures) {
		center.x += f->mass() * f->position().x;
		center.y += f->mass() * f->position().y;
	}
	center.x /= M;
	center.y /= M;
	return center;
}

double totalSquare(vector <CFigure*>& figures) {
	double total = 0;
	for (auto f : figures)
		total += f->square();
	return total;
}

double totalPerimeter(vector <CFigure*>& figures) {
	double total = 0;
	for (auto f : figures)
		total += f->perimeter();
	return total;
}

void totalDraw(vector <CFigure*>& figures) {
	int i = 0;
	for (auto f : figures) {
		i++;
		cout << "Figure " << i << ": " << f->classname() << endl;
		f->draw();
	}
}

void totalInit(vector <CFigure*>& figures) {
	bool ok = true;

	while (ok) {
		int type;

		cout << "Input number of figure type: " << endl;
		cout << "  parallelogram = 1" << endl;
		cout << "  equilateral triangle = 2" << endl;
		cout << "  stop = 0" << endl;
		cin >> type;

		switch (type) {
		case 0: {
			ok = false;
			break;
		}
		case 1: {
			CFigure* f = new CParallelogram();
			f->initFromDialog();
			figures.push_back(f);
			break;
		}
		case 2: {
			CFigure* f = new CEquilateralTriangle();
			f->initFromDialog();
			figures.push_back(f);
			break;
		}
		}
	}
}

int main() {
	vector <CFigure*> figures;
	figures.push_back(new CParallelogram(8, CPoint2D(0, 0), CVector2D(0, 6), CVector2D(3, 3)));
	figures.push_back(new CEquilateralTriangle(2, CPoint2D(10, 10), CVector2D(2, 7)));
	totalInit(figures);
	sort(figures.begin(), figures.end(), [](const CFigure* a, const CFigure* b) { return *a < *b; });
	totalDraw(figures);
	cout << "Total square: " << totalSquare(figures) << endl;
	cout << "Total perimeter: " << totalPerimeter(figures) << endl;

	CPoint2D center = totalMassCenter(figures);
	cout << "Total center of mass: (" << center.x << ", " << center.y << ")" << endl;
	cout << "Total size: " << totalSize(figures) << endl;
	return 0;
}
