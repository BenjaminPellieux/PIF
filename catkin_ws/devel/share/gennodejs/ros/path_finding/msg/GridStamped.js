// Auto-generated. Do not edit!

// (in-package path_finding.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let GridArray = require('./GridArray.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class GridStamped {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.gridY = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('gridY')) {
        this.gridY = initObj.gridY
      }
      else {
        this.gridY = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GridStamped
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [gridY]
    // Serialize the length for message field [gridY]
    bufferOffset = _serializer.uint32(obj.gridY.length, buffer, bufferOffset);
    obj.gridY.forEach((val) => {
      bufferOffset = GridArray.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GridStamped
    let len;
    let data = new GridStamped(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [gridY]
    // Deserialize array length for message field [gridY]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.gridY = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.gridY[i] = GridArray.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.gridY.forEach((val) => {
      length += GridArray.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'path_finding/GridStamped';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b2cce48243258197a47cce7c1b23af50';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    path_finding/GridArray[] gridY
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: path_finding/GridArray
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
    const resolved = new GridStamped(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.gridY !== undefined) {
      resolved.gridY = new Array(msg.gridY.length);
      for (let i = 0; i < resolved.gridY.length; ++i) {
        resolved.gridY[i] = GridArray.Resolve(msg.gridY[i]);
      }
    }
    else {
      resolved.gridY = []
    }

    return resolved;
    }
};

module.exports = GridStamped;
