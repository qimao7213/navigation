; Auto-generated. Do not edit!


(cl:in-package client_and_server-srv)


;//! \htmlinclude capture_global_path-request.msg.html

(cl:defclass <capture_global_path-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass capture_global_path-request (<capture_global_path-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <capture_global_path-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'capture_global_path-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name client_and_server-srv:<capture_global_path-request> is deprecated: use client_and_server-srv:capture_global_path-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <capture_global_path-request>) ostream)
  "Serializes a message object of type '<capture_global_path-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <capture_global_path-request>) istream)
  "Deserializes a message object of type '<capture_global_path-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<capture_global_path-request>)))
  "Returns string type for a service object of type '<capture_global_path-request>"
  "client_and_server/capture_global_pathRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'capture_global_path-request)))
  "Returns string type for a service object of type 'capture_global_path-request"
  "client_and_server/capture_global_pathRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<capture_global_path-request>)))
  "Returns md5sum for a message object of type '<capture_global_path-request>"
  "b6cc1eec0e09cd42154f0c63641fcdc8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'capture_global_path-request)))
  "Returns md5sum for a message object of type 'capture_global_path-request"
  "b6cc1eec0e09cd42154f0c63641fcdc8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<capture_global_path-request>)))
  "Returns full string definition for message of type '<capture_global_path-request>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'capture_global_path-request)))
  "Returns full string definition for message of type 'capture_global_path-request"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <capture_global_path-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <capture_global_path-request>))
  "Converts a ROS message object to a list"
  (cl:list 'capture_global_path-request
))
;//! \htmlinclude capture_global_path-response.msg.html

(cl:defclass <capture_global_path-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:string
    :initform "")
   (GlobalPath
    :reader GlobalPath
    :initarg :GlobalPath
    :type nav_msgs-msg:Path
    :initform (cl:make-instance 'nav_msgs-msg:Path)))
)

(cl:defclass capture_global_path-response (<capture_global_path-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <capture_global_path-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'capture_global_path-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name client_and_server-srv:<capture_global_path-response> is deprecated: use client_and_server-srv:capture_global_path-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <capture_global_path-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader client_and_server-srv:result-val is deprecated.  Use client_and_server-srv:result instead.")
  (result m))

(cl:ensure-generic-function 'GlobalPath-val :lambda-list '(m))
(cl:defmethod GlobalPath-val ((m <capture_global_path-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader client_and_server-srv:GlobalPath-val is deprecated.  Use client_and_server-srv:GlobalPath instead.")
  (GlobalPath m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <capture_global_path-response>) ostream)
  "Serializes a message object of type '<capture_global_path-response>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'result))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'result))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'GlobalPath) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <capture_global_path-response>) istream)
  "Deserializes a message object of type '<capture_global_path-response>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'result) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'result) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'GlobalPath) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<capture_global_path-response>)))
  "Returns string type for a service object of type '<capture_global_path-response>"
  "client_and_server/capture_global_pathResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'capture_global_path-response)))
  "Returns string type for a service object of type 'capture_global_path-response"
  "client_and_server/capture_global_pathResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<capture_global_path-response>)))
  "Returns md5sum for a message object of type '<capture_global_path-response>"
  "b6cc1eec0e09cd42154f0c63641fcdc8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'capture_global_path-response)))
  "Returns md5sum for a message object of type 'capture_global_path-response"
  "b6cc1eec0e09cd42154f0c63641fcdc8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<capture_global_path-response>)))
  "Returns full string definition for message of type '<capture_global_path-response>"
  (cl:format cl:nil "string result~%nav_msgs/Path GlobalPath~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'capture_global_path-response)))
  "Returns full string definition for message of type 'capture_global_path-response"
  (cl:format cl:nil "string result~%nav_msgs/Path GlobalPath~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <capture_global_path-response>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'result))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'GlobalPath))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <capture_global_path-response>))
  "Converts a ROS message object to a list"
  (cl:list 'capture_global_path-response
    (cl:cons ':result (result msg))
    (cl:cons ':GlobalPath (GlobalPath msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'capture_global_path)))
  'capture_global_path-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'capture_global_path)))
  'capture_global_path-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'capture_global_path)))
  "Returns string type for a service object of type '<capture_global_path>"
  "client_and_server/capture_global_path")