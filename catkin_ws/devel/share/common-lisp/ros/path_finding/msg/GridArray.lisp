; Auto-generated. Do not edit!


(cl:in-package path_finding-msg)


;//! \htmlinclude GridArray.msg.html

(cl:defclass <GridArray> (roslisp-msg-protocol:ros-message)
  ((grid
    :reader grid
    :initarg :grid
    :type (cl:vector path_finding-msg:Grid)
   :initform (cl:make-array 0 :element-type 'path_finding-msg:Grid :initial-element (cl:make-instance 'path_finding-msg:Grid))))
)

(cl:defclass GridArray (<GridArray>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GridArray>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GridArray)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name path_finding-msg:<GridArray> is deprecated: use path_finding-msg:GridArray instead.")))

(cl:ensure-generic-function 'grid-val :lambda-list '(m))
(cl:defmethod grid-val ((m <GridArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_finding-msg:grid-val is deprecated.  Use path_finding-msg:grid instead.")
  (grid m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GridArray>) ostream)
  "Serializes a message object of type '<GridArray>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'grid))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'grid))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GridArray>) istream)
  "Deserializes a message object of type '<GridArray>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'grid) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'grid)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'path_finding-msg:Grid))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GridArray>)))
  "Returns string type for a message object of type '<GridArray>"
  "path_finding/GridArray")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GridArray)))
  "Returns string type for a message object of type 'GridArray"
  "path_finding/GridArray")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GridArray>)))
  "Returns md5sum for a message object of type '<GridArray>"
  "3dc66829f5cad491c9d9128ab16fff09")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GridArray)))
  "Returns md5sum for a message object of type 'GridArray"
  "3dc66829f5cad491c9d9128ab16fff09")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GridArray>)))
  "Returns full string definition for message of type '<GridArray>"
  (cl:format cl:nil "path_finding/Grid[] grid~%================================================================================~%MSG: path_finding/Grid~%geometry_msgs/Point[4] sub_area~%bool done~%bool unreachable~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GridArray)))
  "Returns full string definition for message of type 'GridArray"
  (cl:format cl:nil "path_finding/Grid[] grid~%================================================================================~%MSG: path_finding/Grid~%geometry_msgs/Point[4] sub_area~%bool done~%bool unreachable~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GridArray>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'grid) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GridArray>))
  "Converts a ROS message object to a list"
  (cl:list 'GridArray
    (cl:cons ':grid (grid msg))
))
