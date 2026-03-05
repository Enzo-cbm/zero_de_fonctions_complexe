#ifndef COMPLEXE_HPP
#define COMPLEXE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

class Complexe
{
public:

    double re;
    double im;

    Complexe();
    Complexe(double a, double b);

    double norme() const;
    double argument() const;

    Complexe operator+(const Complexe& z) const;
    Complexe operator-(const Complexe& z) const;
    Complexe operator*(const Complexe& z) const;
    Complexe operator/(const Complexe& z) const;

    Complexe operator+=(Complexe& z);
    Complexe operator*=(Complexe& z);
};

Complexe exponentielle(Complexe z);

Complexe derive(Complexe (*f)(Complexe), Complexe z);

Complexe methode_newton(Complexe (*f)(Complexe), Complexe z0);

std::vector<std::vector<int>> grillez3(
    Complexe (*f)(Complexe),
    double xmin,
    double xmax,
    double ymin,
    double ymax,
    int n
);

std::vector<std::vector<int>> grillez4(
    Complexe (*f)(Complexe),
    double xmin,
    double xmax,
    double ymin,
    double ymax,
    int n
);

void fractale_newton(
    Complexe (*f)(Complexe),
    double xmin,
    double xmax,
    double ymin,
    double ymax,
    int n,
    std::string nom_fichier
);

std::vector<Complexe> racines_zn_moins_un(int n);

#endif
