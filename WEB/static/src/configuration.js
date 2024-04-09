// Initialisation de la carte
var map = L.map('map').setView([48.98479706310472, 1.7016915401253376], 18);
var api_status = false;
var bat_level = "NONE";
var dist_traveled = 0.0;
var pose = {
    orientation: {
        w: 0.0,
        x: 0.0,
        y: 0.0,
        z: 0.0
    },
    position: {
        x: 0.0,
        y: 0.0,
        z: 0.0
    }
};
var odom = pose;

L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
    attribution: '© OpenStreetMap contributors'
}).addTo(map);


var drawnItems = new L.FeatureGroup();
map.addLayer(drawnItems);

var drawControl = new L.Control.Draw({
    edit: {
        featureGroup: drawnItems
    }
});
map.addControl(drawControl);

var lastLayer;

map.on(L.Draw.Event.CREATED, function (event) {
    var layer = event.layer;
    drawnItems.addLayer(layer);
    lastLayer = layer; // Store the reference to the layer
});

document.getElementById('sendData').onclick = function() {
    if (lastLayer) {
        var coordinates = lastLayer.getLatLngs();
        if (coordinates[0].length != 4){
            alert("Saisie incorrecte selectionnez une zone CARRE !")
        }
        else {
            var readableCoordinates = coordinates.map(function(latlng) {
            return { lat: latlng.lat, lng: latlng.lng };
            });
            
            submit_area(JSON.stringify(coordinates))
        }
    }
    else {
        alert("No shape drawn on the map.");
    }
};


function submit_area(coordinates) {
    console.log("[DEBUG] new area : " + coordinates + typeof(coordinates[0]) );
    $.post( "/area", {
    points: coordinates
});
}

//Simulez la réception de nouvelles données GPS toutes les 2 secondes
setInterval(function() {
    handleOdom('/odometry/filtered');
    handleAspi('/pif/hard/aspi');
    setTimeout(500);
    updateTab()
    console.log("INFO SLEEPING");
      
    
}, 2000);


async function handleAspi(topic){
    const data = await requestTopicValue(topic);
    if ("ERROR" === data){
        api_status = "NONE";
    }else{
        api_status = data.data;
    }
}


async function handleOdom(topic){
    const data = await requestTopicValue(topic);
    if ("ERROR" === data){
        dist_traveled = "NONE";
    }else{
        dist_traveled =  Math.sqrt(Math.pow(data.pose.pose.position.x, 2) + Math.pow(data.pose.pose.position.z, 2)); 
    }
}

async function requestTopicValue(topic) {
    try {
        const response = await fetch('/post_topic_value', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ topic: topic })
        });
        const data = await response.json();
        console.log(`[INFO] Update Valeur pour ${topic}: `, data);
        return data; // Retourne data qui peut être utilisé avec await
    } catch (error) {
        console.error('Erreur lors de la récupération des données:', error);
    }
}


function updateTab() {
    var cell_bat = document.getElementById('battery-level');
    var cell_dist = document.getElementById('distance-traveled');
    var cell_api = document.getElementById('etatAspirateur');
    cell_bat.innerText = bat_level;
    cell_dist.innerText = dist_traveled;
    cell_api.innerHTML = api_status;
}
