# Configuration Initiale

    git config --global user.name "VotreNom" : Définir le nom que vous voulez associer à vos commit.
    git config --global user.email "votre.email@example.com" : Définir l'email que vous voulez associer à vos commit.

# Démarrage avec Git

    git init : Initialiser un nouveau dépôt Git local.
    git clone <url> : Cloner un dépôt distant pour travailler localement.

# Gestion des Fichiers et des Commits

    git status : Vérifier l'état actuel de la branche (fichiers modifiés, ajoutés, etc.).
    git add <fichier> : Ajouter un fichier spécifique à la zone de staging.
    git add . : Ajouter tous les fichiers modifiés à la zone de staging.
    git commit -m "Message de commit" : Commit vos changements avec un message descriptif.
    git push origin <nom_de_branche> : Pousser vos commits sur la branche distante.

# Branches

    git branch : Lister toutes les branches locales.
    git branch <nom_de_branche> : Créer une nouvelle branche.
    git checkout <nom_de_branche> : Changer de branche.
    git checkout -b <nom_de_branche> : Créer une nouvelle branche et s'y positionner.
    git merge <nom_de_branche> : Fusionner une branche dans votre branche active.

# Mise à jour et Synchronisation

    git pull : Récupérer les derniers changements du dépôt distant et les appliquer à votre branche locale.
    git fetch : Récupérer les changements du dépôt distant sans les appliquer automatiquement.

# Annulation de Modifications

    git checkout -- <fichier> : Annuler les modifications d'un fichier (avant staging).
    git reset HEAD <fichier> : Retirer un fichier de la zone de staging (avant commit).
    git reset --hard : Annuler tous les changements locaux (attention, cette commande est irréversible !).

# Historique et Logs

    git log : Afficher l'historique des commits.
    git log --oneline : Afficher l'historique des commits de manière condensée.

# Collaboration et Pull Requests

    git fetch origin : Récupérer l'état actuel du dépôt distant sans fusionner.
    git pull origin <nom_de_branche> : Récupérer les changements d'une branche distante et les fusionner.
    git push origin <nom_de_branche> : Pousser les changements de votre branche locale vers une branche distante.

# Résolution de Conflits

    En cas de conflits après un git merge ou git pull, Git vous avertira et vous devrez manuellement résoudre les conflits dans les fichiers concernés.
    Après avoir résolu les conflits, marquez-les comme résolus avec git add <fichier_résolu>.
    Puis finalisez la fusion avec git commit.

Ces commandes constituent les bases de l'utilisation de Git pour le contrôle de version et la collaboration. Il est recommandé de pratiquer ces commandes dans le cadre de votre formation pour se familiariser avec leur fonctionnement.
