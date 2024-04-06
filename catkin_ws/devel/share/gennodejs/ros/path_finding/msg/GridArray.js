// Auto-generated. Do not edit!

// (in-package path_finding.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Grid = require('./Grid.js');

//-----------------------------------------------------------

class GridArray {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.gridX = null;
    }
    else {
      if (initObj.hasOwnProperty('gridX')) {
        this.gridX = initObj.gridX
      }
      else {
        this.gridX = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GridArray
    // Serialize message field [gridX]
    // Serialize the length for message field [gridX]
    bufferOffset = _serializer.uint32(obj.gridX.length, buffer, bufferOffset);
    obj.gridX.forEach((val) => {
      bufferOffset = Grid.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GridArray
    let len;
    let data = new GridArray(null);
    // Deserialize message field [gridX]
    // Deserialize array length for message field [gridX]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.gridX = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.gridX[i] = Grid.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 50 * object.gridX.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'path_finding/GridArray';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c9bfbf14df9229b96f8d392a4058d7ed';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    path_finding/Grid[] gridX
    ================================================================================
    MSG: path_finding/Grid
    geometry_msgs/Point top_left
    geometry_msgs/Point bottom_right
    bool done
    bool unreachable
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
    const resolved = new GridArray(null);
    if (msg.gridX !== undefined) {
      resolved.gridX = new Array(msg.gridX.length);
      for (let i = 0; i < resolved.gridX.length; ++i) {
        resolved.gridX[i] = Grid.Resolve(msg.gridX[i]);
      }
    }
    else {
      resolved.gridX = []
    }

    return resolved;
    }
};

module.exports = GridArray;
