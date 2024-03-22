// Fonction pour simuler l'état de l'aspirateur
function aspirateurAspire() {
    // Ici, capteur ou logiciel detection/ retour info aspiration
    return Math.random() < 0.5 ? 'ON' : 'OFF'; // Retourne aléatoirement 'ON' ou 'OFF'
}

// Fonction pour mettre à jour l'état de l'aspirateur dans la cellule du tableau HTML
function mettreAJourEtatAspirateur() {
    var etatCell = document.getElementById('etatAspirateur'); // Récupère l'élément de la cellule
    var etat = aspirateurAspire(); // Obtient l'état de l'aspirateur
    etatCell.textContent = etat; // Met à jour le contenu de la cellule avec l'état de l'aspirateur
}

// Appel de la fonction pour mettre à jour l'état de l'aspirateur dans la cellule du tableau
mettreAJourEtatAspirateur();
