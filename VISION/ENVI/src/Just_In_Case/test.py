import cv2
import numpy as np

# Initialiser la capture vidéo depuis la webcam
cap = cv2.VideoCapture(0)

# Vérifier si la capture vidéo est ouverte
if not cap.isOpened():
    print("Erreur lors de l'ouverture de la webcam.")
    exit()

# Définir la valeur de seuil
seuil = 127  # Remplacez 127 par la valeur de seuil souhaitée

# Définir la valeur de seuil_obstacle
seuil_obstacle = 10.0  # Ajustez selon vos besoins

while True:
    # Capturer une image depuis la webcam
    ret, src = cap.read()

    # Vérifier si l'image est correctement capturée
    if not ret:
        print("Erreur lors de la capture de l'image depuis la webcam.")
        break

    # Convertir l'image en niveaux de gris
    gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)

    # Seuillage
    _, binary_image = cv2.threshold(gray, seuil, 255, cv2.THRESH_BINARY)

    # Analyse de l'image seuillée
    half_height = binary_image.shape[0] // 2
    bottom_half = binary_image[half_height:, :]

    # Calculer le pourcentage de pixels noirs dans la moitié inférieure de l'image
    black_percentage = (np.count_nonzero(bottom_half == 0) * 100.0) / bottom_half.size

    # Prendre une décision
    if black_percentage > seuil_obstacle:
        print("Obstacle détecté, ne pas avancer.")
        # Ajoutez ici le code pour arrêter le véhicule
    else:
        print("Aucun obstacle détecté dans la moitié inférieure, vous pouvez avancer.")
        # Ajoutez ici le code pour commander l'avancement du véhicule

    # Afficher l'image seuillée
    cv2.imshow("Resultat", binary_image)

    # Attendre une petite période et vérifier si une touche est pressée
    if cv2.waitKey(30) >= 0:
        break

# Fermer la fenêtre et libérer la capture vidéo
cap.release()
cv2.destroyAllWindows()
