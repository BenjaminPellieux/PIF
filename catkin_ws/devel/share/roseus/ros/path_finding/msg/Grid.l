;; Auto-generated. Do not edit!


(when (boundp 'path_finding::Grid)
  (if (not (find-package "PATH_FINDING"))
    (make-package "PATH_FINDING"))
  (shadow 'Grid (find-package "PATH_FINDING")))
(unless (find-package "PATH_FINDING::GRID")
  (make-package "PATH_FINDING::GRID"))

(in-package "ROS")
;;//! \htmlinclude Grid.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass path_finding::Grid
  :super ros::object
  :slots (_top_left _bottom_right _done _unreachable ))

(defmethod path_finding::Grid
  (:init
   (&key
    ((:top_left __top_left) (instance geometry_msgs::Point :init))
    ((:bottom_right __bottom_right) (instance geometry_msgs::Point :init))
    ((:done __done) nil)
    ((:unreachable __unreachable) nil)
    )
   (send-super :init)
   (setq _top_left __top_left)
   (setq _bottom_right __bottom_right)
   (setq _done __done)
   (setq _unreachable __unreachable)
   self)
  (:top_left
   (&rest __top_left)
   (if (keywordp (car __top_left))
       (send* _top_left __top_left)
     (progn
       (if __top_left (setq _top_left (car __top_left)))
       _top_left)))
  (:bottom_right
   (&rest __bottom_right)
   (if (keywordp (car __bottom_right))
       (send* _bottom_right __bottom_right)
     (progn
       (if __bottom_right (setq _bottom_right (car __bottom_right)))
       _bottom_right)))
  (:done
   (&optional (__done :null))
   (if (not (eq __done :null)) (setq _done __done)) _done)
  (:unreachable
   (&optional (__unreachable :null))
   (if (not (eq __unreachable :null)) (setq _unreachable __unreachable)) _unreachable)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point _top_left
    (send _top_left :serialization-length)
    ;; geometry_msgs/Point _bottom_right
    (send _bottom_right :serialization-length)
    ;; bool _done
    1
    ;; bool _unreachable
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point _top_left
       (send _top_left :serialize s)
     ;; geometry_msgs/Point _bottom_right
       (send _bottom_right :serialize s)
     ;; bool _done
       (if _done (write-byte -1 s) (write-byte 0 s))
     ;; bool _unreachable
       (if _unreachable (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point _top_left
     (send _top_left :deserialize buf ptr-) (incf ptr- (send _top_left :serialization-length))
   ;; geometry_msgs/Point _bottom_right
     (send _bottom_right :deserialize buf ptr-) (incf ptr- (send _bottom_right :serialization-length))
   ;; bool _done
     (setq _done (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _unreachable
     (setq _unreachable (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get path_finding::Grid :md5sum-) "326792e8c45913b0ed6b6b020c9acb4b")
(setf (get path_finding::Grid :datatype-) "path_finding/Grid")
(setf (get path_finding::Grid :definition-)
      "geometry_msgs/Point top_left
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



(provide :path_finding/Grid "326792e8c45913b0ed6b6b020c9acb4b")


