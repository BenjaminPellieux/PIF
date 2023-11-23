// Connecting to ROS
// -----------------

var ros = new ROSLIB.Ros({
url : 'ws://10.8.0.2:9090'
});

ros.on('connection', function() {
console.log('Connected to websocket server.');
});

ros.on('error', function(error) {
console.log('Error connecting to websocket server: ', error);
});

ros.on('close', function() {
console.log('Connection to websocket server closed.');
});

// Publishing a Topic
// ------------------

// var cmdVel = new ROSLIB.Topic({
// ros : ros,
// name : '/cmd_vel',
// messageType : 'geometry_msgs/Twist'
// });

// var twist = new ROSLIB.Message({
// linear : {
// x : 0.1,
// y : 0.2,
// z : 0.3
// },
// angular : {
// x : -0.1,
// y : -0.2,
// z : -0.3
// }
// });
// cmdVel.publish(twist);

// Subscribing to a Topic
// ----------------------

var listener_odo = new ROSLIB.Topic({
    ros : ros,
    name : '/jackal_velocity_controller/odom',
    messageType : 'geometry_msgs/Twist'
});
var listener_clock = new ROSLIB.Topic({
    ros : ros,
    name : '/clock',
    messageType : 'rosgraph_msgs/Clock'
})

setInterval(function() {
    listener_odo.subscribe(function(message_odo) {
        console.log('Received message on ' + listener_odo.name + ': ' + message_odo.data);
        listener_odo.unsubscribe();
    });


    listener_clock.subscribe(function(message_clock) {
        console.log('Received message on ' + listener_clock.name + ': ' + message_clock.data);
        listener_clock.unsubscribe();
    });
},500)

    // Calling a service
// -----------------

// var addTwoIntsClient = new ROSLIB.Service({
// ros : ros,
// name : '/add_two_ints',
// serviceType : 'rospy_tutorials/AddTwoInts'
// });

// var request = new ROSLIB.ServiceRequest({
// a : 1,
// b : 2
// });

// addTwoIntsClient.callService(request, function(result) {
// console.log('Result for service call on '
// + addTwoIntsClient.name
// + ': '
// + result.sum);
// });

// Getting and setting a param value
// ---------------------------------

// ros.getParams(function(params) {
// console.log(params);
// });

// var maxVelX = new ROSLIB.Param({
// ros : ros,
// name : 'max_vel_y'
// });

// maxVelX.set(0.8);
// maxVelX.get(function(value) {
// console.log('MAX VAL: ' + value);
// });

