// Initialisation de la carte
var map = L.map('map').setView([48.98479706310472, 1.7016915401253376], 18);
var api_status = false;
var bat_level = "NONE";
var dist_traveled = 0.0;

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
    handleOdom(requestTopicValue('/odometry/filtered'));
    handleAspi(requestTopicValue('/pif/hard/aspi'));
    setTimeout(500);
    updateTab()
    console.log("INFO SLEEPING");
      
    
}, 2000);


function handleAspi(data){
    if (data){
        api_status = data.data;
    }
    api_status = "NONE";
}


function handleOdom(data){
    if (data){
        dist_traveled =  Math.sqrt(Math.pow(data.pose.pose.position.x, 2) + Math.pow(data.pose.pose.position.z, 2)); 
        console.log("[DEBUG] ", dist_traveled)
    }
    dist_traveled = "NONE";
}

function requestTopicValue(topic) {
    fetch('/post_topic_value', {
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
        return false;
    }
    return data;

})
.catch(error => console.error('Erreur lors de la récupération des données:', error));
}


function updateTab() {
    var cell_bat = document.getElementById('battery-level');
    var cell_dist = document.getElementById('distance-traveled');
    var cell_api = document.getElementById('etatAspirateur');
    cell_bat.innerText = bat_level;
    cell_dist.innerText = dist_traveled;
    cell_api.innerHTML = api_status;
}
