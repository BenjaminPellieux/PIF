;; Auto-generated. Do not edit!


(when (boundp 'path_finding::GridStamped)
  (if (not (find-package "PATH_FINDING"))
    (make-package "PATH_FINDING"))
  (shadow 'GridStamped (find-package "PATH_FINDING")))
(unless (find-package "PATH_FINDING::GRIDSTAMPED")
  (make-package "PATH_FINDING::GRIDSTAMPED"))

(in-package "ROS")
;;//! \htmlinclude GridStamped.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass path_finding::GridStamped
  :super ros::object
  :slots (_header _gridY ))

(defmethod path_finding::GridStamped
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:gridY __gridY) ())
    )
   (send-super :init)
   (setq _header __header)
   (setq _gridY __gridY)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:gridY
   (&rest __gridY)
   (if (keywordp (car __gridY))
       (send* _gridY __gridY)
     (progn
       (if __gridY (setq _gridY (car __gridY)))
       _gridY)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; path_finding/GridArray[] _gridY
    (apply #'+ (send-all _gridY :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; path_finding/GridArray[] _gridY
     (write-long (length _gridY) s)
     (dolist (elem _gridY)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; path_finding/GridArray[] _gridY
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _gridY (let (r) (dotimes (i n) (push (instance path_finding::GridArray :init) r)) r))
     (dolist (elem- _gridY)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get path_finding::GridStamped :md5sum-) "b2cce48243258197a47cce7c1b23af50")
(setf (get path_finding::GridStamped :datatype-) "path_finding/GridStamped")
(setf (get path_finding::GridStamped :definition-)
      "Header header
<<<<<<< HEAD
path_finding/GridArray[] grid
=======
path_finding/GridArray[] gridY
>>>>>>> 0b949d28773dff8622021b58d2a2983cc2a15580
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

")



(provide :path_finding/GridStamped "b2cce48243258197a47cce7c1b23af50")


