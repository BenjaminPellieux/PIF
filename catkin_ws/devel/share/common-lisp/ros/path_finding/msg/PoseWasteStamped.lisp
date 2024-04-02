; Auto-generated. Do not edit!


(cl:in-package path_finding-msg)


;//! \htmlinclude PoseWasteStamped.msg.html

(cl:defclass <PoseWasteStamped> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (data
    :reader data
    :initarg :data
    :type path_finding-msg:PoseWaste
    :initform (cl:make-instance 'path_finding-msg:PoseWaste)))
)

(cl:defclass PoseWasteStamped (<PoseWasteStamped>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PoseWasteStamped>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PoseWasteStamped)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name path_finding-msg:<PoseWasteStamped> is deprecated: use path_finding-msg:PoseWasteStamped instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <PoseWasteStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_finding-msg:header-val is deprecated.  Use path_finding-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <PoseWasteStamped>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_finding-msg:data-val is deprecated.  Use path_finding-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PoseWasteStamped>) ostream)
  "Serializes a message object of type '<PoseWasteStamped>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'data) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PoseWasteStamped>) istream)
  "Deserializes a message object of type '<PoseWasteStamped>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'data) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PoseWasteStamped>)))
  "Returns string type for a message object of type '<PoseWasteStamped>"
  "path_finding/PoseWasteStamped")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PoseWasteStamped)))
  "Returns string type for a message object of type 'PoseWasteStamped"
  "path_finding/PoseWasteStamped")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PoseWasteStamped>)))
  "Returns md5sum for a message object of type '<PoseWasteStamped>"
  "fec343c0b056b50bf89033eb229e869c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PoseWasteStamped)))
  "Returns md5sum for a message object of type 'PoseWasteStamped"
  "fec343c0b056b50bf89033eb229e869c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PoseWasteStamped>)))
  "Returns full string definition for message of type '<PoseWasteStamped>"
  (cl:format cl:nil "Header header~%path_finding/PoseWaste data~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: path_finding/PoseWaste~%string waste~%geometry_msgs/Point center~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PoseWasteStamped)))
  "Returns full string definition for message of type 'PoseWasteStamped"
  (cl:format cl:nil "Header header~%path_finding/PoseWaste data~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: path_finding/PoseWaste~%string waste~%geometry_msgs/Point center~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PoseWasteStamped>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'data))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PoseWasteStamped>))
  "Converts a ROS message object to a list"
  (cl:list 'PoseWasteStamped
    (cl:cons ':header (header msg))
    (cl:cons ':data (data msg))
))
