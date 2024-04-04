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
  :slots (_header _grid ))

(defmethod path_finding::GridStamped
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:grid __grid) ())
    )
   (send-super :init)
   (setq _header __header)
   (setq _grid __grid)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:grid
   (&rest __grid)
   (if (keywordp (car __grid))
       (send* _grid __grid)
     (progn
       (if __grid (setq _grid (car __grid)))
       _grid)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; path_finding/GridArray[] _grid
    (apply #'+ (send-all _grid :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; path_finding/GridArray[] _grid
     (write-long (length _grid) s)
     (dolist (elem _grid)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; path_finding/GridArray[] _grid
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _grid (let (r) (dotimes (i n) (push (instance path_finding::GridArray :init) r)) r))
     (dolist (elem- _grid)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get path_finding::GridStamped :md5sum-) "bb89431ea13652c1ae0d876e69593b78")
(setf (get path_finding::GridStamped :datatype-) "path_finding/GridStamped")
(setf (get path_finding::GridStamped :definition-)
      "Header header
path_finding/GridArray[] grid
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
path_finding/Grid[] grid
================================================================================
MSG: path_finding/Grid
geometry_msgs/Point[4] sub_area
bool done
bool unreachable
================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :path_finding/GridStamped "bb89431ea13652c1ae0d876e69593b78")


