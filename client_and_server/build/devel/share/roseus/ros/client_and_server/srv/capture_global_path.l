;; Auto-generated. Do not edit!


(when (boundp 'client_and_server::capture_global_path)
  (if (not (find-package "CLIENT_AND_SERVER"))
    (make-package "CLIENT_AND_SERVER"))
  (shadow 'capture_global_path (find-package "CLIENT_AND_SERVER")))
(unless (find-package "CLIENT_AND_SERVER::CAPTURE_GLOBAL_PATH")
  (make-package "CLIENT_AND_SERVER::CAPTURE_GLOBAL_PATH"))
(unless (find-package "CLIENT_AND_SERVER::CAPTURE_GLOBAL_PATHREQUEST")
  (make-package "CLIENT_AND_SERVER::CAPTURE_GLOBAL_PATHREQUEST"))
(unless (find-package "CLIENT_AND_SERVER::CAPTURE_GLOBAL_PATHRESPONSE")
  (make-package "CLIENT_AND_SERVER::CAPTURE_GLOBAL_PATHRESPONSE"))

(in-package "ROS")



(if (not (find-package "NAV_MSGS"))
  (ros::roseus-add-msgs "nav_msgs"))


(defclass client_and_server::capture_global_pathRequest
  :super ros::object
  :slots ())

(defmethod client_and_server::capture_global_pathRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass client_and_server::capture_global_pathResponse
  :super ros::object
  :slots (_result _GlobalPath ))

(defmethod client_and_server::capture_global_pathResponse
  (:init
   (&key
    ((:result __result) "")
    ((:GlobalPath __GlobalPath) (instance nav_msgs::Path :init))
    )
   (send-super :init)
   (setq _result (string __result))
   (setq _GlobalPath __GlobalPath)
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:GlobalPath
   (&rest __GlobalPath)
   (if (keywordp (car __GlobalPath))
       (send* _GlobalPath __GlobalPath)
     (progn
       (if __GlobalPath (setq _GlobalPath (car __GlobalPath)))
       _GlobalPath)))
  (:serialization-length
   ()
   (+
    ;; string _result
    4 (length _result)
    ;; nav_msgs/Path _GlobalPath
    (send _GlobalPath :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _result
       (write-long (length _result) s) (princ _result s)
     ;; nav_msgs/Path _GlobalPath
       (send _GlobalPath :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _result
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _result (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; nav_msgs/Path _GlobalPath
     (send _GlobalPath :deserialize buf ptr-) (incf ptr- (send _GlobalPath :serialization-length))
   ;;
   self)
  )

(defclass client_and_server::capture_global_path
  :super ros::object
  :slots ())

(setf (get client_and_server::capture_global_path :md5sum-) "b6cc1eec0e09cd42154f0c63641fcdc8")
(setf (get client_and_server::capture_global_path :datatype-) "client_and_server/capture_global_path")
(setf (get client_and_server::capture_global_path :request) client_and_server::capture_global_pathRequest)
(setf (get client_and_server::capture_global_path :response) client_and_server::capture_global_pathResponse)

(defmethod client_and_server::capture_global_pathRequest
  (:response () (instance client_and_server::capture_global_pathResponse :init)))

(setf (get client_and_server::capture_global_pathRequest :md5sum-) "b6cc1eec0e09cd42154f0c63641fcdc8")
(setf (get client_and_server::capture_global_pathRequest :datatype-) "client_and_server/capture_global_pathRequest")
(setf (get client_and_server::capture_global_pathRequest :definition-)
      "
---
string result
nav_msgs/Path GlobalPath

================================================================================
MSG: nav_msgs/Path
#An array of poses that represents a Path for a robot to follow
Header header
geometry_msgs/PoseStamped[] poses

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
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
")

(setf (get client_and_server::capture_global_pathResponse :md5sum-) "b6cc1eec0e09cd42154f0c63641fcdc8")
(setf (get client_and_server::capture_global_pathResponse :datatype-) "client_and_server/capture_global_pathResponse")
(setf (get client_and_server::capture_global_pathResponse :definition-)
      "
---
string result
nav_msgs/Path GlobalPath

================================================================================
MSG: nav_msgs/Path
#An array of poses that represents a Path for a robot to follow
Header header
geometry_msgs/PoseStamped[] poses

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
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
")



(provide :client_and_server/capture_global_path "b6cc1eec0e09cd42154f0c63641fcdc8")


