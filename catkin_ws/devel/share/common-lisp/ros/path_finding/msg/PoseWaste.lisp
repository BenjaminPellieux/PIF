; Auto-generated. Do not edit!


(cl:in-package path_finding-msg)


;//! \htmlinclude PoseWaste.msg.html

(cl:defclass <PoseWaste> (roslisp-msg-protocol:ros-message)
  ((waste
    :reader waste
    :initarg :waste
    :type cl:string
    :initform "")
   (center
    :reader center
    :initarg :center
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point)))
)

(cl:defclass PoseWaste (<PoseWaste>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PoseWaste>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PoseWaste)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name path_finding-msg:<PoseWaste> is deprecated: use path_finding-msg:PoseWaste instead.")))

(cl:ensure-generic-function 'waste-val :lambda-list '(m))
(cl:defmethod waste-val ((m <PoseWaste>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_finding-msg:waste-val is deprecated.  Use path_finding-msg:waste instead.")
  (waste m))

(cl:ensure-generic-function 'center-val :lambda-list '(m))
(cl:defmethod center-val ((m <PoseWaste>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_finding-msg:center-val is deprecated.  Use path_finding-msg:center instead.")
  (center m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PoseWaste>) ostream)
  "Serializes a message object of type '<PoseWaste>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'waste))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'waste))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'center) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PoseWaste>) istream)
  "Deserializes a message object of type '<PoseWaste>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'waste) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'waste) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'center) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PoseWaste>)))
  "Returns string type for a message object of type '<PoseWaste>"
  "path_finding/PoseWaste")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PoseWaste)))
  "Returns string type for a message object of type 'PoseWaste"
  "path_finding/PoseWaste")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PoseWaste>)))
  "Returns md5sum for a message object of type '<PoseWaste>"
  "5a4d766ff7efd04002a2333631f161f9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PoseWaste)))
  "Returns md5sum for a message object of type 'PoseWaste"
  "5a4d766ff7efd04002a2333631f161f9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PoseWaste>)))
  "Returns full string definition for message of type '<PoseWaste>"
  (cl:format cl:nil "string waste~%geometry_msgs/Point center~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PoseWaste)))
  "Returns full string definition for message of type 'PoseWaste"
  (cl:format cl:nil "string waste~%geometry_msgs/Point center~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PoseWaste>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'waste))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'center))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PoseWaste>))
  "Converts a ROS message object to a list"
  (cl:list 'PoseWaste
    (cl:cons ':waste (waste msg))
    (cl:cons ':center (center msg))
))
