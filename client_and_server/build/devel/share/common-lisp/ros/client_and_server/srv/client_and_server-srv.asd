
(cl:in-package :asdf)

(defsystem "client_and_server-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :nav_msgs-msg
)
  :components ((:file "_package")
    (:file "capture_global_path" :depends-on ("_package_capture_global_path"))
    (:file "_package_capture_global_path" :depends-on ("_package"))
  ))