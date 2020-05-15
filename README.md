# TIPE

## Simulation de la circulation thermohaline

#### Note
As this is a school project, an english version is neither available nor scheduled anytime soon.

```diff
- WARNING
A few memory leaks have recently been discovered and patched.
Both precompiled versions are up to date with the patched source
code, but be aware that some other leaks may still be present.
```

```diff
! NOTE
Some characters are not properly displayed in the Windows version.
Qt for Windows seems not to support UTF-8 symbols in the same way
that Qt for Linux does.
```

### Modélisation informatique interactive du modèle océanique à compartiments de Stommel.

#### Villani Neven, MP*3 au lycée Louis-le-Grand (Paris)

Ce projet aurait dû servir pour l'épreuve orale de TIPE (Océan) des concours de fin de CPGE (session 2019-2020), mais celle-ci a été annulée.

Des versions précompilées sont disponibles dans `dist/`, le code source intégral se trouve dans `src/`.

Informations de compilation :
- pour Windows :
    - VM Windows 10, 32bits (hôte Ubuntu 20.04)
    - Qt 5.14.1
    - qmake 3.1
    - mingw 7.3


- pour Linux :
    - Ubuntu 20.04, 64bits
    - Qt 5.9.5
    - qmake 3.1
    - gcc 9.3.0

Pour plus d'information sur l'utilisation de cette application, consulter `src/helpsetup.h`, qui contient entre autres un protocole expérimental destiné à mettre en évidence l'existence d'un phénomène d'hystérésis dans le modèle de Stommel. Ce même protocole est accessible lors de l'exécution via le bouton d'aide (point d'interrogation bleu).

Une présentation de l'interface graphique est disponible dans `LAYOUT.pdf`

Pour des informations non sur cette application mais sur le modèle de Stommel lui-même, il est possible de consulter `PRESENTATION.pdf`, qui est un diaporama annoté.
