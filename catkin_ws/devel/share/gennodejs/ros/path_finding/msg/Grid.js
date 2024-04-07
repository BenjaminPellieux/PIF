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

class Grid {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.top_left = null;
      this.bottom_right = null;
      this.done = null;
      this.unreachable = null;
    }
    else {
      if (initObj.hasOwnProperty('top_left')) {
        this.top_left = initObj.top_left
      }
      else {
        this.top_left = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('bottom_right')) {
        this.bottom_right = initObj.bottom_right
      }
      else {
        this.bottom_right = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('done')) {
        this.done = initObj.done
      }
      else {
        this.done = false;
      }
      if (initObj.hasOwnProperty('unreachable')) {
        this.unreachable = initObj.unreachable
      }
      else {
        this.unreachable = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Grid
    // Serialize message field [top_left]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.top_left, buffer, bufferOffset);
    // Serialize message field [bottom_right]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.bottom_right, buffer, bufferOffset);
    // Serialize message field [done]
    bufferOffset = _serializer.bool(obj.done, buffer, bufferOffset);
    // Serialize message field [unreachable]
    bufferOffset = _serializer.bool(obj.unreachable, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Grid
    let len;
    let data = new Grid(null);
    // Deserialize message field [top_left]
    data.top_left = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [bottom_right]
    data.bottom_right = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [done]
    data.done = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [unreachable]
    data.unreachable = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 50;
  }

  static datatype() {
    // Returns string type for a message object
    return 'path_finding/Grid';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '326792e8c45913b0ed6b6b020c9acb4b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new Grid(null);
    if (msg.top_left !== undefined) {
      resolved.top_left = geometry_msgs.msg.Point.Resolve(msg.top_left)
    }
    else {
      resolved.top_left = new geometry_msgs.msg.Point()
    }

    if (msg.bottom_right !== undefined) {
      resolved.bottom_right = geometry_msgs.msg.Point.Resolve(msg.bottom_right)
    }
    else {
      resolved.bottom_right = new geometry_msgs.msg.Point()
    }

    if (msg.done !== undefined) {
      resolved.done = msg.done;
    }
    else {
      resolved.done = false
    }

    if (msg.unreachable !== undefined) {
      resolved.unreachable = msg.unreachable;
    }
    else {
      resolved.unreachable = false
    }

    return resolved;
    }
};

module.exports = Grid;
