// Initialisation de la carte
var map = L.map('map').setView([48.98479706310472, 1.7016915401253376], 18);


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
            alert("Saisie incorrecte selectionnez une zone RECTANGLE !")
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