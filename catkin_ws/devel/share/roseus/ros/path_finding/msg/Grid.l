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
  :slots (_sub_area _done _unreachable ))

(defmethod path_finding::Grid
  (:init
   (&key
    ((:sub_area __sub_area) (let (r) (dotimes (i 4) (push (instance geometry_msgs::Point :init) r)) r))
    ((:done __done) nil)
    ((:unreachable __unreachable) nil)
    )
   (send-super :init)
   (setq _sub_area __sub_area)
   (setq _done __done)
   (setq _unreachable __unreachable)
   self)
  (:sub_area
   (&rest __sub_area)
   (if (keywordp (car __sub_area))
       (send* _sub_area __sub_area)
     (progn
       (if __sub_area (setq _sub_area (car __sub_area)))
       _sub_area)))
  (:done
   (&optional (__done :null))
   (if (not (eq __done :null)) (setq _done __done)) _done)
  (:unreachable
   (&optional (__unreachable :null))
   (if (not (eq __unreachable :null)) (setq _unreachable __unreachable)) _unreachable)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point[4] _sub_area
    (apply #'+ (send-all _sub_area :serialization-length))
    ;; bool _done
    1
    ;; bool _unreachable
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point[4] _sub_area
     (dolist (elem _sub_area)
       (send elem :serialize s)
       )
     ;; bool _done
       (if _done (write-byte -1 s) (write-byte 0 s))
     ;; bool _unreachable
       (if _unreachable (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point[4] _sub_area
   (dotimes (i 4)
     (send (elt _sub_area i) :deserialize buf ptr-) (incf ptr- (send (elt _sub_area i) :serialization-length))
     )
   ;; bool _done
     (setq _done (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _unreachable
     (setq _unreachable (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get path_finding::Grid :md5sum-) "8477af00e98f03fd36c0b55bb90bc58b")
(setf (get path_finding::Grid :datatype-) "path_finding/Grid")
(setf (get path_finding::Grid :definition-)
      "geometry_msgs/Point[4] sub_area
bool done
bool unreachable
================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :path_finding/Grid "8477af00e98f03fd36c0b55bb90bc58b")


