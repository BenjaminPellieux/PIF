var bool = false;

function requestTopicValue(topic) {
    fetch('/get_topic_value', {
    method: 'POST',
    headers: {
        'Content-Type': 'application/json'
    },
    body: JSON.stringify({ topic: topic})
})
.then(response => response.json())
.then(data => {
    console.log(`[INFO] Update Valeur pour ${topic}: `, data);
    if ("ERROR" === data){
        //alert("Une erreur est survenue\n WALL-E semble déconécter !!!")
        error =  true;
    }else if(topic == "/odometry/filtered"){
        pose = data.pose.pose;
        clock = data.header.stamp;
        error = false;
    }else if(topic == "Aspi/Status"){
        bool = data.data;	
    }
})
.catch(error => console.error('Erreur lors de la récupération des données:', error));
}




// Fonction pour simuler l'état de l'aspirateur
function aspirateurAspire() {
    // Ici, capteur ou logiciel detection/ retour info aspiration
    setInterval(function() {
    // Recuperation des donnée du topic
    requestTopicValue('Aspi/Status');
    setTimeout(function(){ 
        console.log("INFO SLEEPING");
    }, 2000);  
    
    
}, 1000);

    if (bool){
    	return 'ON';
    } else{
    	return 'OFF';
    }

}

// Fonction pour mettre à jour l'état de l'aspirateur dans la cellule du tableau HTML
function mettreAJourEtatAspirateur() {
    var etatCell = document.getElementById('etatAspirateur'); // Récupère l'élément de la cellule
    var etat = aspirateurAspire(); // Obtient l'état de l'aspirateur
    etatCell.textContent = etat; // Met à jour le contenu de la cellule avec l'état de l'aspirateur
}

// Appel de la fonction pour mettre à jour l'état de l'aspirateur dans la cellule du tableau
mettreAJourEtatAspirateur();
