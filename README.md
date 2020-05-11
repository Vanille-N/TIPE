# TIPE

## Simulation de la circulation thermohaline

#### Note
As this is a school project, an english version is neither available nor scheduled anytime soon.

### Modélisation informatique interactive du modèle océanique à compartiments de Stommel.

Villani Neven, MP*3 au lycée Louis-le-Grand (Paris)

Ce projet aurait dû servir pour l'épreuve orale de TIPE (Océan) des concours de fin de CPGE (session 2019-2020), mais celle-ci a été annulée.

Des versions précompilées sont disponibles dans `dist/`, le code source intégral se trouve dans `src/`.

Informations de compilation :
- pour Windows :
    - VM 32 bits (hôte Ubuntu 18.04)
    - Qt 5.14.1
    - qmake 3.1
    - mingw 7.3
- pour Linux :
    - Ubuntu 18.04, 64 bits
    - Qt 5.9.5
    - qmake 3.1
    - gcc 9.3.0

Pour plus d'information sur l'utilisation de cette application, consulter `src/helpsetup.h`, qui contient entre autres un protocole expérimental destiné à mettre en évidence l'existence d'un phénomène d'hystérésis dans le modèle de Stommel. Ce même protocole est accessible lors de l'exécution via le bouton d'aide (bleu).
