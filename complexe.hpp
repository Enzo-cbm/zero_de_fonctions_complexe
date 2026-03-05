#ifndef COMPLEXE_HPP
#define COMPLEXE_HPP

#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

class Complexe
{
private:
    float _re;
    float _im;

public:
    Complexe(float a, float b);
    ~Complexe();

    double get_re() const;
    double get_im() const;

    double norme() const;
    double argument() const;
    void affiche_complexe() const;

    // Non-member overloads (friends)
    friend Complexe operator+(const Complexe &a, const Complexe &b);
    friend Complexe operator*(const Complexe &a, const Complexe &b);

    // Member overloads
    Complexe operator+=(Complexe &z);
    Complexe operator*=(Complexe &z);

    Complexe operator-(double a) const;
    Complexe operator+(double a) const;
    Complexe operator*(double a) const;

    Complexe operator/(const Complexe &z) const;
    Complexe operator-(const Complexe &z) const;

    // Stream output
    friend std::ostream &operator<<(std::ostream &os, const Complexe &z);
};

// Fonctions non membres
Complexe exponentielle(const Complexe &z);
void verif_expo();

// Méthode de Newton-Raphson : retourne (zéro estimé, nombre d'itérations)
std::tuple<Complexe, int> methode_newton(
    int max_it,
    Complexe z_init,
    std::function<Complexe(Complexe)> &f,
    double epsilon = 1e-12
);

Complexe derive(
    std::function<Complexe(Complexe)> &f,
    Complexe z,
    double h = 1e-6
);


void fractale_newton(
    std::function<Complexe(Complexe)> &f,
    const std::vector<Complexe> &racines,
    const std::string &filename,
    double a,
    int taille
);

std::vector<Complexe> racines_zn_moins_un(int n);

#endif
