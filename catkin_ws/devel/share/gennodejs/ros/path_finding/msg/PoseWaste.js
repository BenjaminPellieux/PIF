// Auto-generated. Do not edit!

// (in-package path_finding.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class PoseWaste {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.waste = null;
      this.center = null;
    }
    else {
      if (initObj.hasOwnProperty('waste')) {
        this.waste = initObj.waste
      }
      else {
        this.waste = '';
      }
      if (initObj.hasOwnProperty('center')) {
        this.center = initObj.center
      }
      else {
        this.center = new geometry_msgs.msg.Point();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PoseWaste
    // Serialize message field [waste]
    bufferOffset = _serializer.string(obj.waste, buffer, bufferOffset);
    // Serialize message field [center]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.center, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PoseWaste
    let len;
    let data = new PoseWaste(null);
    // Deserialize message field [waste]
    data.waste = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [center]
    data.center = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.waste);
    return length + 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'path_finding/PoseWaste';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5a4d766ff7efd04002a2333631f161f9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string waste
    geometry_msgs/Point center
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PoseWaste(null);
    if (msg.waste !== undefined) {
      resolved.waste = msg.waste;
    }
    else {
      resolved.waste = ''
    }

    if (msg.center !== undefined) {
      resolved.center = geometry_msgs.msg.Point.Resolve(msg.center)
    }
    else {
      resolved.center = new geometry_msgs.msg.Point()
    }

    return resolved;
    }
};

module.exports = PoseWaste;
