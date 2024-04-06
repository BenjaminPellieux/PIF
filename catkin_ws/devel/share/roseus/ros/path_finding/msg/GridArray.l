;; Auto-generated. Do not edit!


(when (boundp 'path_finding::GridArray)
  (if (not (find-package "PATH_FINDING"))
    (make-package "PATH_FINDING"))
  (shadow 'GridArray (find-package "PATH_FINDING")))
(unless (find-package "PATH_FINDING::GRIDARRAY")
  (make-package "PATH_FINDING::GRIDARRAY"))

(in-package "ROS")
;;//! \htmlinclude GridArray.msg.html


(defclass path_finding::GridArray
  :super ros::object
  :slots (_gridX ))

(defmethod path_finding::GridArray
  (:init
   (&key
    ((:gridX __gridX) ())
    )
   (send-super :init)
   (setq _gridX __gridX)
   self)
  (:gridX
   (&rest __gridX)
   (if (keywordp (car __gridX))
       (send* _gridX __gridX)
     (progn
       (if __gridX (setq _gridX (car __gridX)))
       _gridX)))
  (:serialization-length
   ()
   (+
    ;; path_finding/Grid[] _gridX
    (apply #'+ (send-all _gridX :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; path_finding/Grid[] _gridX
     (write-long (length _gridX) s)
     (dolist (elem _gridX)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; path_finding/Grid[] _gridX
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _gridX (let (r) (dotimes (i n) (push (instance path_finding::Grid :init) r)) r))
     (dolist (elem- _gridX)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get path_finding::GridArray :md5sum-) "c9bfbf14df9229b96f8d392a4058d7ed")
(setf (get path_finding::GridArray :datatype-) "path_finding/GridArray")
(setf (get path_finding::GridArray :definition-)
      "path_finding/Grid[] gridX
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



(provide :path_finding/GridArray "c9bfbf14df9229b96f8d392a4058d7ed")


