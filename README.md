# TIPE

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Simulation de la circulation thermohaline

```diff
! NOTE
As this is a school project, an english version is neither available nor scheduled anytime soon. The code however is commented in english.
```

```diff
- WARNING
A few memory leaks have recently been discovered and patched.
Both precompiled versions are up to date with the patched source
code, but be aware that some other leaks may still be present.
```

```diff
! NOTE
According to this answer:
@@ Stack Overflow - How to make Qt GUI apps in C++ without memory leaks @@
@@ https://stackoverflow.com/a/14073965/10027774                        @@
The remaining leaks detected by Valgrind are mild at worst, intentional at best.
```

```diff
! NOTE
Some visual differences can arise depending on the OS and Qt version.
All images available throughout this document were obtained running
Qt 5.9.5+ on Ubuntu 18.04 or 20.04
```

### Modélisation informatique interactive du modèle océanique à compartiments de Stommel.

#### Villani Neven, MP*3 au lycée Louis-le-Grand (Paris)

Ce projet aurait dû servir pour l'épreuve orale de TIPE (Océan) des concours de fin de CPGE (session 2019-2020), mais celle-ci a été annulée.

Des versions précompilées sont disponibles dans `dist/`, le code source intégral se trouve dans `src/`.

Informations de compilation :
- pour Windows :
    - VM Windows 10, 32bits (VirtualBox, hôte Ubuntu 20.04)
    - Qt 5.15.0
    - qmake 3.1
    - mingw 7.3


- pour Linux :
    - Ubuntu 20.04, 64bits
    - Qt 5.15.0
    - qmake 3.1
    - gcc 9.3.0

Pour plus d'information sur l'utilisation de cette application, consulter `src/helpsetup.h`, qui contient entre autres un protocole expérimental destiné à mettre en évidence l'existence d'un phénomène d'hystérésis dans le modèle de Stommel. Ce même protocole est accessible lors de l'exécution via le bouton d'aide (point d'interrogation bleu).

Une présentation de l'interface graphique est disponible dans `LAYOUT.pdf`

Pour des informations non sur cette application mais sur le modèle de Stommel lui-même, il est possible de consulter `PRESENTATION.pdf`, qui est la version annotée du diaporama `BEAMER.pdf`.
