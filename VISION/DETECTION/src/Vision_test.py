import cv2
import numpy as np

def main():
    # Lire l'image
    image = cv2.imread("../Image/vision_test_small.jpg")

    # Appliquer un filtre gaussien pour lisser l'image
    # Le choix de la taille du noyau (par exemple, (5,5)) et de l'écart-type (sigmaX)
    # dépend de la quantité de flou que vous souhaitez.
    image_blurred = cv2.GaussianBlur(image, (9, 9), 3)

    # Convertir l'image en espace couleur HSV pour une meilleure séparation des couleurs
    hsv = cv2.cvtColor(image_blurred, cv2.COLOR_BGR2HSV)

    # Calculer l'histogramme de la teinte (H)
    hist_hue = cv2.calcHist([hsv], [0], None, [180], [0, 180])
    # Trouver la teinte la plus fréquente (couleur majoritaire)
    most_frequent_hue = np.argmax(hist_hue)

    # Déterminer les seuils pour isoler la couleur majoritaire
    # Ces seuils peuvent nécessiter des ajustements
    hue_range = 70  # à ajuster selon vos besoins
    lower_hue = np.array([most_frequent_hue - hue_range, 20, 20])
    upper_hue = np.array([most_frequent_hue + hue_range, 255, 255])
    print(f"[DEBUG] {lower_hue=}")
    print(f"[DEBUG] {upper_hue=}")
    # Créer un masque pour les couleurs qui ne sont pas dans la plage de la couleur majoritaire
    mask_majority_color = cv2.inRange(hsv, lower_hue, upper_hue)
    mask_others = cv2.bitwise_not(mask_majority_color)

    # Optionnel: appliquer des opérations morphologiques pour nettoyer le masque
    kernel = np.ones((5, 5), np.uint8)
    mask_others = cv2.morphologyEx(mask_others, cv2.MORPH_OPEN, kernel)
    mask_others = cv2.morphologyEx(mask_others, cv2.MORPH_CLOSE, kernel)

    # Trouver les contours dans le masque des autres couleurs
    contours, _ = cv2.findContours(mask_others, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    # Filtrer et dessiner les contours
    for contour in contours:
        area = cv2.contourArea(contour)
        if area > 100:  # Filtre basé sur la taille de l'objet
            x, y, w, h = cv2.boundingRect(contour)
            cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)

    # Afficher l'image originale avec les détections
    cv2.imshow('Detection de l\'element', image)

    # Afficher le masque des autres couleurs
    cv2.imshow('Masque des autres couleurs', mask_others)
    cv2.imshow('blurred img', image_blurred)
    # Attendre qu'une touche soit pressée avant de fermer les fenêtres d'image
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
