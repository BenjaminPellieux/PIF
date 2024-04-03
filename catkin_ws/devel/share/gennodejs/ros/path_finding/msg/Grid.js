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
      this.sub_area = null;
      this.done = null;
      this.unreachable = null;
    }
    else {
      if (initObj.hasOwnProperty('sub_area')) {
        this.sub_area = initObj.sub_area
      }
      else {
        this.sub_area = new Array(4).fill(new geometry_msgs.msg.Point());
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
    // Check that the constant length array field [sub_area] has the right length
    if (obj.sub_area.length !== 4) {
      throw new Error('Unable to serialize array field sub_area - length must be 4')
    }
    // Serialize message field [sub_area]
    obj.sub_area.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
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
    // Deserialize message field [sub_area]
    len = 4;
    data.sub_area = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.sub_area[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [done]
    data.done = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [unreachable]
    data.unreachable = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 26;
  }

  static datatype() {
    // Returns string type for a message object
    return 'path_finding/Grid';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8477af00e98f03fd36c0b55bb90bc58b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Point[4] sub_area
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
    if (msg.sub_area !== undefined) {
      resolved.sub_area = new Array(4)
      for (let i = 0; i < resolved.sub_area.length; ++i) {
        if (msg.sub_area.length > i) {
          resolved.sub_area[i] = geometry_msgs.msg.Point.Resolve(msg.sub_area[i]);
        }
        else {
          resolved.sub_area[i] = new geometry_msgs.msg.Point();
        }
      }
    }
    else {
      resolved.sub_area = new Array(4).fill(new geometry_msgs.msg.Point())
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
