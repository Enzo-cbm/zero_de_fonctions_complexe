import os

import numpy as np
import matplotlib.pyplot as plt


# Dossier contenant les fichiers .txt générés par le C++
DATA_DIR = "/home/cb/progra/c++/td/classes/complexe"


# ---------------------------
# LISTES SÉPARÉES PAR PAGE
# ---------------------------

# PAGE 1 : polynômes z^n - 1
fractales_page1 = [
    ("newton_z1_minus_1.txt",  r"$f(z) = z - 1$"),
    ("newton_z2_minus_1.txt",  r"$f(z) = z^2 - 1$"),
    ("newton_z3_minus_1.txt",  r"$f(z) = z^3 - 1$"),
    ("newton_z4_minus_1.txt",  r"$f(z) = z^4 - 1$"),
    ("newton_z5_minus_1.txt",  r"$f(z) = z^5 - 1$"),
    ("newton_z6_minus_1.txt",  r"$f(z) = z^6 - 1$"),
    ("newton_z7_minus_1.txt",  r"$f(z) = z^7 - 1$"),
    ("newton_z8_minus_1.txt",  r"$f(z) = z^8 - 1$"),
    ("newton_z9_minus_1.txt",  r"$f(z) = z^9 - 1$"),
    ("newton_z10_minus_1.txt", r"$f(z) = z^{10} - 1$"),
]

# PAGE 2 : autres fonctions
fractales_page2 = [
    ("newton_z2_plus_i.txt",          r"$f(z) = z^2 + i$"),
    ("newton_z3_minus_2z_plus_2.txt", r"$f(z) = z^3 - 2z + 2$"),
    ("newton_z4_plus_z2_plus_1.txt",  r"$f(z) = z^4 + z^2 + 1$"),
    ("newton_z5_minus_2z_plus_2.txt", r"$f(z) = z^5 - 2z + 2$"),
    ("newton_z_plus_invz.txt",        r"$f(z) = z + 1/z$"),
]

# PAGE 3 : anciens fichiers
fractales_page3 = [
    ("zero_de_fonction_holomorphe.txt",  "Ancien fichier 1"),
    ("zero_de_fonction_holomorphe1.txt", "Ancien fichier 2"),
]


# ---------------------------
# COULEURS DES BASSINS
# ---------------------------
palette = {
    -1: [0, 0, 0],  # non convergé
     0: [1, 0, 0],  # rouge
     1: [0, 1, 0],  # vert
     2: [0, 0, 1],  # bleu
     3: [1, 1, 0],  # jaune
     4: [1, 0, 1],  # magenta
     5: [0, 1, 1],  # cyan
}


def load_image(filename):
    """Charge une grille d'indices (txt) et la convertit en image RGB."""
    path = os.path.join(DATA_DIR, filename)
    try:
        grid = np.loadtxt(path, dtype=int)
    except Exception:
        print(f"Impossible de charger : {filename}")
        return None

    n = grid.shape[0]
    img = np.zeros((n, n, 3))

    for k, col in palette.items():
        img[grid == k] = col

    return img


def afficher_page(fractales, titre_page):
    nb = len(fractales)
    cols = 3
    rows = (nb + cols - 1) // cols

    plt.figure(figsize=(4 * cols, 4 * rows))
    plt.suptitle(titre_page, fontsize=16)

    for idx, (fname, title) in enumerate(fractales):
        img = load_image(fname)
        if img is None:
            continue

        plt.subplot(rows, cols, idx + 1)
        plt.imshow(img, extent=[-2, 2, -2, 2], origin="lower")
        plt.title(title, fontsize=10)
        plt.axis("off")

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    afficher_page(fractales_page1, "Fractales Newton — Polynômes zⁿ − 1")
    afficher_page(fractales_page2, "Fractales Newton — Fonctions avancées")
    afficher_page(fractales_page3, "Anciens résultats")
