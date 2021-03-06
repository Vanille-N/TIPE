#pragma once

#include <iostream>
#include <QString>
#include <QDataStream>
#include <QTextStream>
#include <QFile>
#include "metavars.h"

void buildHelp () ;

static QString helpMessage (
"Écrit et testé intégralement par Neven VILLANI\n"
"MP*3 (Lycée LLG à Paris) -- TIPE 2019-2020\n"
"OCÉANS\n"
"\n"
"Ce programme est une simulation d'un modèle simplifié de la circulation thermohaline dans l'océan.\n"
"Il suppose deux compartiments de même masse et homogènes en température et en salinité, et entre lesquels s'établit un flux qui tend à rééquilibrer les caractéristiques de chaque compartiment. En parallèle, ces masses d'eau sont soumises à des forçages thermique et halin.\n"
"On observe l'établissement progressif au cours du temps d'une situation stable où le flux équilibre parfaitement les effets des forçages, et on est amené à étudier le sens de ce flux en fonction des paramètres.\n"
"Pour commencer une nouvelle simulation, initialiser les valeurs des constantes soit manuellement soit en ouvrant des fichiers .cst et .stt à l'aide des icônes de droite de la barre supérieure, sélectionner les options de lecture dans le coin inférieur droit, puis lancer Skip ou Play (arrêter avec Pause).\n"
"Si vous ne savez pas quels valeurs fournir, il est recommandé d'accéder à default.cst pour les constantes et default.stt pour les états. Ces fichiers ont été initialisés avec des valeurs des constantes aussi proches de la réalité que possible et qui ont été testées.\n"
"Les paramètres de la simulation (état et constantes) peuvent être édités via les boutons centraux et latéraux respectivement, y compris en pendant que les calculs sont en cours. Il n'est pas recommandé de modifier brutalement les valeurs, donc il peut être judicieux de changer progressivement les constantes tout en maintenant la simulation active. En ce qui concerne les états, il est au contraire recommandé de mettre les calculs en pause.\n"
"Si les valeurs deviennent NaN (indiqué sur les LCD par 'A'), mettre en pause et éditer les états.\n"
"\n"
"Fenêtre principale :\n"
"Les constantes peuvent êtres éditées en cliquant sur les boutons latéraux, ce qui ouvre un éditeur associé.\n"
"Les trois colonnes de flèches (une vers le bas, une vers le haut à chaque fois) modifient la valeur cible des constantes de respectivement 1, 1/10 et 1/100 de l'ordre de grandeur de la valeur actuelle, la valeur réelle tend exponentiellement vers la valeur cible pour amortir les changements abrupts de valeurs, il a été observé que cela réduisait les risques d'aboutir à des valeurs NaN.\n"
"La zone supérieure sert à lancer/interrompre la simulation, charger et enregistrer des fichiers de constantes et d'états.\n"
"La zone centrale permet de visualiser l'état de la simulation, avec en particulier les paramètres de forçage définis lors de l'étude analytique.\n"
"\n"
"Diagramme Flux-forçage :\n"
"On représente la courbe (en bleu) définie lors de l'étude analytique, il s'agit de justifier par la simulation qu'elle constitue bien la courbe d'équilibre.\n"
"La situation actuelle est représentée par le point rouge.\n"
"\n"
"Diagramme Salinité-Température :\n"
"On représente divers points liés à l'état actuel de la simulation.\n"
"En bleu : situation d'équilibre au pôle.\n"
"En vert : situation réelle au pôle.\n"
"En rouge : situation d'équilibre à l'équateur.\n"
"En jaune : situation réelle à l'équateur.\n"
"Le dégradé blanc-bleu est un indicateur de la densité.\n"
"\n"
"Protocole destiné à mettre en évidence un phénomène d'hysteresis :\n"
"   - Charger les fichiers default.cst et default.stt\n"
"   - Les valeurs attendues sont :\n"
"    α = 2.1\n"
"γ = 2.0\n"
"δ = 0.17\n"
"ϕ' = 0.8\n"
"En particulier, ϕ' est positif, le flux de surface se fait de l'équateur vers le pôle.\n"
"   - Modifier Tₚ* progressivement (augmenter) jusqu'à-ce que ϕ' soit approximativement 0.4 et noter les valeurs des paramètres α, γ, δ, ϕ', Tₚ*.\n"
"   - Modifier à nouveau Tₚ*, en laissant l'équilibre se faire à chaque étape (faire de petites modifications), jusq'à-ce-que ϕ' change de signe.\n"
"   - Baisser à nouveau la valeur de Tₚ* pour que α, γ, δ reprennent les mêmes valeurs que précédemment. On constate alors que ϕ' a gardé son signe négatif.\n"
"Il s'agit ici d'un phénomène d'hysteresis : selon l'équilibre déjà établi, les mêmes valeurs des paramètres de forçage ne fournissent pas le même nouvel équilibre.\n"
"\n"
"Merci en particulier à\n"
"   - M. Deremble (idée du sujet et premières références)\n"
"   - M. Kious (encadrant)\n"
"   - Stack Overflow (questions techniques sur Qt)\n"
"   - Les créateurs de Qt\n"
"   - Les créateurs de QCustomPlot\n"
"\n"
"Première version fonctionnelle Sam. 21 Sept. 2019\n"
"Vérifications et premières expériences le Lun. 28 Oct. 2019"
) ;
