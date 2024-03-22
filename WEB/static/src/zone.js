// ZONE !!!
var error = false;
var pose = {
    P1: { x: 0.0, y: 0.0 },
    P2: { x: 0.0, y: 0.0 },
    P3: { x: 0.0, y: 0.0 },
    P4: { x: 0.0, y: 0.0 }
};

var odom = pose;

var clock = {
    nsecs: 0,
    secs: 0
};
var OrignLat = 48.98479706310472; 
var OrigLng = 1.7016915401253376;

var NewLat = 49.900000000642166;
var NewLng = 8.90000009517094;

var DiffLat = 0.915202938;
var DiffLng = 7.198308555;

var map = L.map('map').setView([OrignLat, OrigLng], 18); // Réglage initial de la carte 

// Ajoutez une couche OpenStreetMap : Utilisez la couche TileLayer de Leaflet pour afficher la carte OpenStreetMap.
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
}).addTo(map);

var marker = L.marker([OrignLat, OrigLng]).addTo(map);

function updateMarker(lat, lng) {
    marker.setLatLng([lat, lng]).update();
    map.setView([lat, lng], map.getZoom());
}			

// Simulez la réception de nouvelles données GPS toutes les 2 secondes
setInterval(function() {
    // Récupération des données du topic
    requestTopicValue('/odometry/filtered');
    setTimeout(function(){ 
        console.log("INFO SLEEPING");
    }, 2000);  

    requestTopicValue('/navsat/fix');
    requestTopicValue('/Area/Point');
    
    // Remplacez les valeurs par vos données odom en temps réel 
    updateData(pose, clock);
    // Remplacez les valeurs par vos données GPS en temps réel sur la MAP
    updateMarker(NewLat - DiffLat, NewLng - DiffLng);
    
}, 1000);

function command(e) {
    console.log("[DEBUG] Name command: "  +e.name);
    $.post( "/command", {
        comd: e.name 
    });
}

document.addEventListener("DOMContentLoaded", function() {
    var speedRange = document.getElementById("speedRange");
    var speedValue = document.getElementById("speedValue");
    
    speedRange.oninput = function() {
        var speed = this.value;
        speedValue.innerHTML = "Vitesse: " + speed;
        
        // Envoi de la valeur au serveur
        $.ajax({
            url: '/newspeed',  // Remplacez par l'URL appropriée
            type: 'POST',
            data: { 'speed': speed },
            success: function(response) {
                console.log('Vitesse mise à jour avec succès');
            },
            error: function(error) {
                console.error('Erreur lors de la mise à jour de la vitesse', error);
            }
        });
    }
});

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
        //alert("Une erreur est survenue\n WALL-E semble déconnecté !!!")
        error =  true;
    } else if (topic == "/odometry/filtered") {
        pose = data.pose.pose;
        clock = data.header.stamp;
        error = false;
    } else if (topic == "/Area/Point") {
        pose.P1 = { x: data.P1.x, y: data.P1.y };
        pose.P2 = { x: data.P2.x, y: data.P2.y };
        pose.P3 = { x: data.P3.x, y: data.P3.y };
        pose.P4 = { x: data.P4.x, y: data.P4.y };
    } else {
        NewLat = data.latitude;
        NewLng = data.longitude;
    }
})
.catch(error => console.error('Erreur lors de la récupération des données:', error));
}

function updateData() {
    var dataTable = document.getElementById('dataTable');
    if (error){
        var error = document.createElement('h2');
        error.innerHTML = "Une erreur est survenue lors de la récupération des données";
        dataTable.insertBefore(error, dataTable.children[0]);
    } else {
        dataTable.innerHTML = ''; // Effacer le contenu actuel
        dataTable.appendChild(createTableFromData(pose, clock));
    }
}

function createTableFromData(pose, clock) {
    var table = document.createElement('table');
    var thead = document.createElement('thead');
    var tbody = document.createElement('tbody');
    table.appendChild(thead);
    table.appendChild(tbody);
    
    // Création de l'en-tête du tableau
    var row = document.createElement('tr');
    var th1 = document.createElement('th');
    th1.textContent = 'Coordonnées';
    var th2 = document.createElement('th');
    th2.textContent = 'Valeurs';
    row.appendChild(th1);
    row.appendChild(th2);
    thead.appendChild(row);
    
    // Ajout des lignes pour les points P1, P2, P3 et P4 uniquement
    addRows(tbody, 'P1', pose.P1);
    addRows(tbody, 'P2', pose.P2);
    addRows(tbody, 'P3', pose.P3);
    addRows(tbody, 'P4', pose.P4);
    
    return table;
}

function addRows(tbody, parentKey, dataObject) {
    for (var key in dataObject) {
        var tr = document.createElement('tr');
        var tdKey = document.createElement('td');
        tdKey.textContent = parentKey + '.' + key;
        var tdValue = document.createElement('td');
        tdValue.textContent = dataObject[key];
        tr.appendChild(tdKey);
        tr.appendChild(tdValue);
        tbody.appendChild(tr);
    }
}
// Ajoutez le tableau à la div avec l'ID 'poseTable'
var poseTableDiv = document.getElementById('poseTable');
poseTableDiv.appendChild(createTableFromData(pose, clock));
