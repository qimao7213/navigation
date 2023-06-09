// Generated by gencpp from file client_and_server/capture_global_pathResponse.msg
// DO NOT EDIT!


#ifndef CLIENT_AND_SERVER_MESSAGE_CAPTURE_GLOBAL_PATHRESPONSE_H
#define CLIENT_AND_SERVER_MESSAGE_CAPTURE_GLOBAL_PATHRESPONSE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <nav_msgs/Path.h>

namespace client_and_server
{
template <class ContainerAllocator>
struct capture_global_pathResponse_
{
  typedef capture_global_pathResponse_<ContainerAllocator> Type;

  capture_global_pathResponse_()
    : result()
    , GlobalPath()  {
    }
  capture_global_pathResponse_(const ContainerAllocator& _alloc)
    : result(_alloc)
    , GlobalPath(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _result_type;
  _result_type result;

   typedef  ::nav_msgs::Path_<ContainerAllocator>  _GlobalPath_type;
  _GlobalPath_type GlobalPath;





  typedef boost::shared_ptr< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> const> ConstPtr;

}; // struct capture_global_pathResponse_

typedef ::client_and_server::capture_global_pathResponse_<std::allocator<void> > capture_global_pathResponse;

typedef boost::shared_ptr< ::client_and_server::capture_global_pathResponse > capture_global_pathResponsePtr;
typedef boost::shared_ptr< ::client_and_server::capture_global_pathResponse const> capture_global_pathResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::client_and_server::capture_global_pathResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::client_and_server::capture_global_pathResponse_<ContainerAllocator1> & lhs, const ::client_and_server::capture_global_pathResponse_<ContainerAllocator2> & rhs)
{
  return lhs.result == rhs.result &&
    lhs.GlobalPath == rhs.GlobalPath;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::client_and_server::capture_global_pathResponse_<ContainerAllocator1> & lhs, const ::client_and_server::capture_global_pathResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace client_and_server

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b6cc1eec0e09cd42154f0c63641fcdc8";
  }

  static const char* value(const ::client_and_server::capture_global_pathResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb6cc1eec0e09cd42ULL;
  static const uint64_t static_value2 = 0x154f0c63641fcdc8ULL;
};

template<class ContainerAllocator>
struct DataType< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "client_and_server/capture_global_pathResponse";
  }

  static const char* value(const ::client_and_server::capture_global_pathResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string result\n"
"nav_msgs/Path GlobalPath\n"
"\n"
"================================================================================\n"
"MSG: nav_msgs/Path\n"
"#An array of poses that represents a Path for a robot to follow\n"
"Header header\n"
"geometry_msgs/PoseStamped[] poses\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/PoseStamped\n"
"# A Pose with reference coordinate frame and timestamp\n"
"Header header\n"
"Pose pose\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
;
  }

  static const char* value(const ::client_and_server::capture_global_pathResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.result);
      stream.next(m.GlobalPath);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct capture_global_pathResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::client_and_server::capture_global_pathResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::client_and_server::capture_global_pathResponse_<ContainerAllocator>& v)
  {
    s << indent << "result: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.result);
    s << indent << "GlobalPath: ";
    s << std::endl;
    Printer< ::nav_msgs::Path_<ContainerAllocator> >::stream(s, indent + "  ", v.GlobalPath);
  }
};

} // namespace message_operations
} // namespace ros

#endif // CLIENT_AND_SERVER_MESSAGE_CAPTURE_GLOBAL_PATHRESPONSE_H
