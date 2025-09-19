

# 🚗 KiO – Mini voiture avec détection de mur

KiO est un projet de mini voiture équipée d’un capteur à ultrasons.  
Elle est capable de mesurer la distance face à un obstacle et de s’arrêter automatiquement.  
Un écran affiche en temps réel la distance mesurée, et une LED change de couleur en fonction de la proximité.

---

## ✨ Fonctionnalités
- Détection des obstacles  
- Arrêt automatique à 10 cm du mur  
- Affichage de la distance en temps réel sur écran  
- Indicateur lumineux avec LED RGB :  
  - 🔵 Bleu : > 30 cm (avance)  
  - 🟢 Vert : 15–30 cm (avance)  
  - 🟡 Jaune : 10–15 cm (arrêt)  
  - 🔴 Rouge : < 10 cm (recule)  

---

## 📂 Structure du projet
```
KiO/
├── code/
     ├── KiO/       # Code Arduino pour la gestion du capteur, LED, écran et logique d'arrêt
├── footprints/     # Empreintes utilisées dans KiCad pour le PCB
├── symbols/        # Symboles électroniques pour KiCad
└── README.md       # Documentation du projet
```

---

## 🛠️ Électronique utilisé
- Microcontrôleur : **Seeed XIAO ESP32S3**  
- Capteur ultrason : **HC-SR04**  
- Écran : **SSD 1306**  
- LED RGB 4 broches  
- Moteur DC double axe 1:48

---

## 📸 Modélisation
Les schémas électroniques et la modélisation du PCB ont été réalisés avec **KiCad**.  
- Les symboles personnalisés sont dans le dossier `symbols`.  
- Les empreintes personnalisées sont dans le dossier `footprints`.

---

## 🚀 Mise en route
1. Cloner le projet :  
   ```bash
   git clone https://github.com/julien7518/KiO.git
   ```
2. Ouvrir le dossier `code/` dans l’IDE Arduino.  
3. Sélectionner la carte Arduino correspondante.  
4. Compiler et téléverser le code.  
5. Connecter la voiture et tester la détection de mur.  

---

## 📜 Licence
Ce projet est distribué sous licence MIT – voir le fichier [LICENSE](LICENSE) pour plus de détails.
  