; Auto-generated. Do not edit!


(cl:in-package path_finding-msg)


;//! \htmlinclude Grid.msg.html

(cl:defclass <Grid> (roslisp-msg-protocol:ros-message)
  ((sub_area
    :reader sub_area
    :initarg :sub_area
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 4 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point)))
   (done
    :reader done
    :initarg :done
    :type cl:boolean
    :initform cl:nil)
   (unreachable
    :reader unreachable
    :initarg :unreachable
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Grid (<Grid>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Grid>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Grid)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name path_finding-msg:<Grid> is deprecated: use path_finding-msg:Grid instead.")))

(cl:ensure-generic-function 'sub_area-val :lambda-list '(m))
(cl:defmethod sub_area-val ((m <Grid>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_finding-msg:sub_area-val is deprecated.  Use path_finding-msg:sub_area instead.")
  (sub_area m))

(cl:ensure-generic-function 'done-val :lambda-list '(m))
(cl:defmethod done-val ((m <Grid>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_finding-msg:done-val is deprecated.  Use path_finding-msg:done instead.")
  (done m))

(cl:ensure-generic-function 'unreachable-val :lambda-list '(m))
(cl:defmethod unreachable-val ((m <Grid>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader path_finding-msg:unreachable-val is deprecated.  Use path_finding-msg:unreachable instead.")
  (unreachable m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Grid>) ostream)
  "Serializes a message object of type '<Grid>"
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'sub_area))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'done) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'unreachable) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Grid>) istream)
  "Deserializes a message object of type '<Grid>"
  (cl:setf (cl:slot-value msg 'sub_area) (cl:make-array 4))
  (cl:let ((vals (cl:slot-value msg 'sub_area)))
    (cl:dotimes (i 4)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
    (cl:setf (cl:slot-value msg 'done) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'unreachable) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Grid>)))
  "Returns string type for a message object of type '<Grid>"
  "path_finding/Grid")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Grid)))
  "Returns string type for a message object of type 'Grid"
  "path_finding/Grid")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Grid>)))
  "Returns md5sum for a message object of type '<Grid>"
  "8477af00e98f03fd36c0b55bb90bc58b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Grid)))
  "Returns md5sum for a message object of type 'Grid"
  "8477af00e98f03fd36c0b55bb90bc58b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Grid>)))
  "Returns full string definition for message of type '<Grid>"
  (cl:format cl:nil "geometry_msgs/Point[4] sub_area~%bool done~%bool unreachable~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Grid)))
  "Returns full string definition for message of type 'Grid"
  (cl:format cl:nil "geometry_msgs/Point[4] sub_area~%bool done~%bool unreachable~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Grid>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'sub_area) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Grid>))
  "Converts a ROS message object to a list"
  (cl:list 'Grid
    (cl:cons ':sub_area (sub_area msg))
    (cl:cons ':done (done msg))
    (cl:cons ':unreachable (unreachable msg))
))
