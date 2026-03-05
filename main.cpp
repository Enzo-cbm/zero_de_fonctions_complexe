#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <string>

#include "Complexe.hpp"

int main()
{
    /*
    double re, im;
    std::cout << "enter real and imaginary part : " << std::endl;
    std::cin >> re >> im;
    Complexe z(re, im);
    std::function<Complexe(Complexe)> f = [] (Complexe z) { return z - 1.0; };
    // type                        fonction     argument     corps de la foction

    std::tuple<Complexe, int> res = methode_newton(100, z, f);
    std::cout << "for the fonction f(z) = z-1 the root is : " << std::get<0>(res) << " for : " << std::endl;
    std::cout << "for " << std::get<1>(res) << " iteration" << std::endl;
    */

    /*
    std::function<Complexe(Complexe)> fz = [] (Complexe z) { return z * z * z - 1.0; };
    grillez3(fz, 2, 1000);

    std::function<Complexe(Complexe)> fz1 = [] (Complexe z) {
        Complexe z2 = z * z;
        Complexe z4 = z2 * z2;
        return z4 - z2 * 2.0 - 1.0;
    };
    grillez4(fz1, 2, 1000);
    */

    double a = 2.0;  // domaine [-a,a]×[-a,a]
    int N = 800;     // grille N×N

    // =========================
    // 1) z^5 - 2z + 2
    // =========================
    std::function<Complexe(Complexe)> f1 = [] (Complexe z) {
        Complexe z2 = z * z;
        Complexe z4 = z2 * z2;
        return z4 * z - z * 2.0 + 2.0;  // z^5 - 2z + 2
    };

    std::vector<Complexe> roots1 = {
        Complexe(-1.36443011217253,  0.0),
        Complexe(-0.192960604861626, -1.26891757358474),
        Complexe(-0.192960604861626,  1.26891757358474),
        Complexe( 0.875175660947889, -0.351922135554889),
        Complexe( 0.875175660947889,  0.351922135554889)
    };

    fractale_newton(f1, roots1, "newton_z5_minus_2z_plus_2.txt", a, N);

    // =========================
    // 2) z^4 + z^2 + 1
    // =========================
    std::function<Complexe(Complexe)> f2 = [] (Complexe z) {
        Complexe z2 = z * z;
        Complexe z4 = z2 * z2;
        return z4 + z2 + 1.0;
    };

    std::vector<Complexe> roots2 = {
        Complexe(-0.5, -0.866025403784439),
        Complexe(-0.5,  0.866025403784439),
        Complexe( 0.5, -0.866025403784439),
        Complexe( 0.5,  0.866025403784439)
    };

    fractale_newton(f2, roots2, "newton_z4_plus_z2_plus_1.txt", a, N);

    // =========================
    // 3) z^2 + i
    // =========================
    std::function<Complexe(Complexe)> f3 = [] (Complexe z) {
        Complexe z2 = z * z;
        return z2 + Complexe(0.0, 1.0);
    };

    std::vector<Complexe> roots3 = {
        Complexe(-0.707106781186548,  0.707106781186548),
        Complexe( 0.707106781186548, -0.707106781186548)
    };

    fractale_newton(f3, roots3, "newton_z2_plus_i.txt", a, N);

    // =========================
    // 4) z + 1/z
    // =========================
    std::function<Complexe(Complexe)> f4 = [] (Complexe z) {
        Complexe un(1.0, 0.0);
        // Attention : si z est très proche de 0, ça peut exploser → Newton renverra souvent "n'importe quoi",
        // ce sera classé en -1.
        Complexe un_sur_z = un / z;
        return z + un_sur_z;
    };

    std::vector<Complexe> roots4 = {
        Complexe(0.0,  1.0),
        Complexe(0.0, -1.0)
    };

    fractale_newton(f4, roots4, "newton_z_plus_invz.txt", a, N);

    // =========================
    // 5) z^3 - 2z + 2
    // =========================
    std::function<Complexe(Complexe)> f5 = [] (Complexe z) {
        Complexe z2 = z * z;
        Complexe z3 = z2 * z;
        return z3 - z * 2.0 + 2.0;
    };

    std::vector<Complexe> roots5 = {
        Complexe(-1.76929235423863, 0.0),
        Complexe( 0.884646177119316, -0.589742805022206),
        Complexe( 0.884646177119316,  0.589742805022206)
    };

    fractale_newton(f5, roots5, "newton_z3_minus_2z_plus_2.txt", a, N);

    // =========================
    // 6) Famille z^n - 1, n = 1..10
    // =========================
    for (int n = 1; n <= 10; ++n)
    {
        std::function<Complexe(Complexe)> fn = [n] (Complexe z) {
            Complexe res(1.0, 0.0);
            for (int k = 0; k < n; ++k)
                res = res * z;  // res = z^n
            return res - 1.0;
        };

        std::vector<Complexe> roots_n = racines_zn_moins_un(n);

        std::string filename = "newton_z" + std::to_string(n) + "_minus_1.txt";
        fractale_newton(fn, roots_n, filename, a, N);
    }

    std::cout << "Fractales générées.\n";
    return 0;
}
