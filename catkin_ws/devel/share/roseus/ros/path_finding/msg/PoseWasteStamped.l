;; Auto-generated. Do not edit!


(when (boundp 'path_finding::PoseWasteStamped)
  (if (not (find-package "PATH_FINDING"))
    (make-package "PATH_FINDING"))
  (shadow 'PoseWasteStamped (find-package "PATH_FINDING")))
(unless (find-package "PATH_FINDING::POSEWASTESTAMPED")
  (make-package "PATH_FINDING::POSEWASTESTAMPED"))

(in-package "ROS")
;;//! \htmlinclude PoseWasteStamped.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass path_finding::PoseWasteStamped
  :super ros::object
  :slots (_header _data ))

(defmethod path_finding::PoseWasteStamped
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:data __data) (instance path_finding::PoseWaste :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _data __data)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:data
   (&rest __data)
   (if (keywordp (car __data))
       (send* _data __data)
     (progn
       (if __data (setq _data (car __data)))
       _data)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; path_finding/PoseWaste _data
    (send _data :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; path_finding/PoseWaste _data
       (send _data :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; path_finding/PoseWaste _data
     (send _data :deserialize buf ptr-) (incf ptr- (send _data :serialization-length))
   ;;
   self)
  )

(setf (get path_finding::PoseWasteStamped :md5sum-) "fec343c0b056b50bf89033eb229e869c")
(setf (get path_finding::PoseWasteStamped :datatype-) "path_finding/PoseWasteStamped")
(setf (get path_finding::PoseWasteStamped :definition-)
      "Header header
path_finding/PoseWaste data
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
MSG: path_finding/PoseWaste
string waste
geometry_msgs/Point center
================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :path_finding/PoseWasteStamped "fec343c0b056b50bf89033eb229e869c")


