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
  :slots (_grid ))

(defmethod path_finding::GridArray
  (:init
   (&key
    ((:grid __grid) ())
    )
   (send-super :init)
   (setq _grid __grid)
   self)
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
    ;; path_finding/Grid[] _grid
    (apply #'+ (send-all _grid :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; path_finding/Grid[] _grid
     (write-long (length _grid) s)
     (dolist (elem _grid)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; path_finding/Grid[] _grid
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _grid (let (r) (dotimes (i n) (push (instance path_finding::Grid :init) r)) r))
     (dolist (elem- _grid)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get path_finding::GridArray :md5sum-) "3dc66829f5cad491c9d9128ab16fff09")
(setf (get path_finding::GridArray :datatype-) "path_finding/GridArray")
(setf (get path_finding::GridArray :definition-)
      "path_finding/Grid[] grid
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



(provide :path_finding/GridArray "3dc66829f5cad491c9d9128ab16fff09")


