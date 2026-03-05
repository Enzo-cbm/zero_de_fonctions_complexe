#include "Complexe.hpp"

#include <cmath>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <vector>


Complexe::Complexe(float a, float b) : _re(a), _im(b) {}

Complexe::~Complexe() {}


double Complexe::get_re() const { return _re; }

double Complexe::get_im() const { return _im; }


// Non-member overloads
Complexe operator+(const Complexe &a, const Complexe &b)
{
    return Complexe(a._re + b._re, a._im + b._im);
}

Complexe operator*(const Complexe &a, const Complexe &b)
{
    return Complexe(
        a._re * b._re - a._im * b._im,
        a._re * b._im + a._im * b._re
    );
}


// Member overloads
Complexe Complexe::operator+=(Complexe &z)
{
    _re += z._re;
    _im += z._im;
    return *this;
}

Complexe Complexe::operator*=(Complexe &z)
{
    double re = _re * z._re - _im * z._im;
    double im = _re * z._im + _im * z._re;

    _re = re;
    _im = im;

    return *this;
}

Complexe Complexe::operator-(double a) const
{
    return Complexe(_re - a, _im);
}

Complexe Complexe::operator+(double a) const
{
    return Complexe(_re + a, _im);
}

Complexe Complexe::operator*(double a) const
{
    return Complexe(_re * a, _im * a);
}

Complexe Complexe::operator-(const Complexe &z) const
{
    return Complexe(_re - z._re, _im - z._im);
}

Complexe Complexe::operator/(const Complexe &z) const
{
    double d = z._re * z._re + z._im * z._im;
    return Complexe(
        (_re * z._re + _im * z._im) / d,
        (_im * z._re - _re * z._im) / d
    );
}


std::ostream &operator<<(std::ostream &os, const Complexe &z)
{
    os << '(' << z._re << " + i" << z._im << ')';
    return os;
}


double Complexe::norme() const
{
    return std::sqrt(_re * _re + _im * _im);
}

double Complexe::argument() const
{
    return std::atan2(_im, _re);
}

void Complexe::affiche_complexe() const
{
    std::cout << "Z = " << _re << " + i" << _im << '\n' << std::endl;
}


// Fonctions non membres
Complexe exponentielle(const Complexe &z)
{
    float real = std::exp(z.get_re()) * std::cos(z.get_im());
    float imag = std::exp(z.get_re()) * std::sin(z.get_im());
    return Complexe(real, imag);
}


void verif_expo()
{
    int N;
    std::cout << "Please enter an integer to set the lenght of the vector : \n" << std::endl;
    std::cin >> N;

    std::vector<Complexe> v;

    for (int i = 0; i < N; i++)
    {
        Complexe z(0, 2 * M_PI * i / N);
        std::cout << " Soit le nombre complexe z : " << std::endl;
        z.affiche_complexe();
        Complexe expz = exponentielle(z);
        std::cout << " Soit l exponetielle de nombre complexe z  exp(z): " << std::endl;
        expz.affiche_complexe();
        v.push_back(expz);
    }

    double verif_re = 0.0;
    double verif_im = 0.0;
    for (int i = 0; i < N; i++)
    {
        verif_re += v[i].get_re();
        verif_im += v[i].get_im();
    }

    Complexe verif(verif_re, verif_im);
    std::cout << "result of Σexp(2.pi.n/N) de n=0 a N-1 sould be nul\n" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    verif.affiche_complexe();
}


std::tuple<Complexe, int> methode_newton(
    int max_it,
    Complexe z_init,
    std::function<Complexe(Complexe)> &f,
    double epsilon
)
{
    Complexe z = z_init;

    for (int i = 0; i < max_it; ++i)
    {
        Complexe fz = f(z);
        Complexe dfz = derive(f, z);

        if (dfz.norme() < 1e-12)
        {
            // On considère que la méthode ne peut pas continuer
            return std::make_tuple(z, i);
        }

        Complexe z_new = z - fz / dfz;

        if ((z_new - z).norme() < epsilon)
        {
            return std::make_tuple(z_new, i);
        }

        z = z_new;
    }

    return std::make_tuple(z, max_it);
}


Complexe derive(std::function<Complexe(Complexe)> &f, Complexe z, double h)
{
    Complexe z_plus(z.get_re() + h, z.get_im());
    Complexe z_minus(z.get_re() - h, z.get_im());

    Complexe f_plus = f(z_plus);
    Complexe f_minus = f(z_minus);

    // (f(z+h) - f(z-h)) / (2h)
    return Complexe(
        (f_plus.get_re() - f_minus.get_re()) / (2 * h),
        (f_plus.get_im() - f_minus.get_im()) / (2 * h)
    );
}



void fractale_newton(
    std::function<Complexe(Complexe)> &f,
    const std::vector<Complexe> &racines,
    const std::string &filename,
    double a,
    int taille
)
{
    Complexe z_zero(-a, -a);
    int max_it = 100;
    double tol_root = 1e-3;

    std::ofstream fichier(filename);
    if (!fichier)
    {
        std::cerr << "Erreur ouverture du fichier : " << filename << "\n";
        return;
    }

    for (int i = 0; i < taille; ++i)
    {
        for (int j = 0; j < taille; ++j)
        {
            Complexe z_pas(2 * a * i / (taille - 1), 2 * a * j / (taille - 1));
            Complexe z = z_zero + z_pas;

            std::tuple<Complexe, int> res = methode_newton(max_it, z, f);
            Complexe zero = std::get<0>(res);

            int couleur = -1;
            double best = std::numeric_limits<double>::max();

            for (std::size_t k = 0; k < racines.size(); ++k)
            {
                Complexe diff = zero - racines[k];
                double d = diff.norme();
                if (d < tol_root && d < best)
                {
                    best = d;
                    couleur = static_cast<int>(k);
                }
            }

            fichier << couleur;
            if (j < taille - 1)
                fichier << ' ';
        }
        fichier << '\n';
    }
}


std::vector<Complexe> racines_zn_moins_un(int n)
{
    std::vector<Complexe> r;
    double deuxpi_sur_n = 2.0 * M_PI / n;

    for (int k = 0; k < n; ++k)
    {
        double theta = deuxpi_sur_n * k;
        r.emplace_back(std::cos(theta), std::sin(theta));
    }

    return r;
}
