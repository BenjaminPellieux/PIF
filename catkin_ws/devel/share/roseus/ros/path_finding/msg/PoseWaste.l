;; Auto-generated. Do not edit!


(when (boundp 'path_finding::PoseWaste)
  (if (not (find-package "PATH_FINDING"))
    (make-package "PATH_FINDING"))
  (shadow 'PoseWaste (find-package "PATH_FINDING")))
(unless (find-package "PATH_FINDING::POSEWASTE")
  (make-package "PATH_FINDING::POSEWASTE"))

(in-package "ROS")
;;//! \htmlinclude PoseWaste.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass path_finding::PoseWaste
  :super ros::object
  :slots (_waste _center ))

(defmethod path_finding::PoseWaste
  (:init
   (&key
    ((:waste __waste) "")
    ((:center __center) (instance geometry_msgs::Point :init))
    )
   (send-super :init)
   (setq _waste (string __waste))
   (setq _center __center)
   self)
  (:waste
   (&optional __waste)
   (if __waste (setq _waste __waste)) _waste)
  (:center
   (&rest __center)
   (if (keywordp (car __center))
       (send* _center __center)
     (progn
       (if __center (setq _center (car __center)))
       _center)))
  (:serialization-length
   ()
   (+
    ;; string _waste
    4 (length _waste)
    ;; geometry_msgs/Point _center
    (send _center :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _waste
       (write-long (length _waste) s) (princ _waste s)
     ;; geometry_msgs/Point _center
       (send _center :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _waste
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _waste (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; geometry_msgs/Point _center
     (send _center :deserialize buf ptr-) (incf ptr- (send _center :serialization-length))
   ;;
   self)
  )

(setf (get path_finding::PoseWaste :md5sum-) "5a4d766ff7efd04002a2333631f161f9")
(setf (get path_finding::PoseWaste :datatype-) "path_finding/PoseWaste")
(setf (get path_finding::PoseWaste :definition-)
      "string waste
geometry_msgs/Point center
================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :path_finding/PoseWaste "5a4d766ff7efd04002a2333631f161f9")


