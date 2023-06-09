// Generated by gencpp from file client_and_server/capture_global_pathRequest.msg
// DO NOT EDIT!


#ifndef CLIENT_AND_SERVER_MESSAGE_CAPTURE_GLOBAL_PATHREQUEST_H
#define CLIENT_AND_SERVER_MESSAGE_CAPTURE_GLOBAL_PATHREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace client_and_server
{
template <class ContainerAllocator>
struct capture_global_pathRequest_
{
  typedef capture_global_pathRequest_<ContainerAllocator> Type;

  capture_global_pathRequest_()
    {
    }
  capture_global_pathRequest_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> const> ConstPtr;

}; // struct capture_global_pathRequest_

typedef ::client_and_server::capture_global_pathRequest_<std::allocator<void> > capture_global_pathRequest;

typedef boost::shared_ptr< ::client_and_server::capture_global_pathRequest > capture_global_pathRequestPtr;
typedef boost::shared_ptr< ::client_and_server::capture_global_pathRequest const> capture_global_pathRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::client_and_server::capture_global_pathRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


} // namespace client_and_server

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::client_and_server::capture_global_pathRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "client_and_server/capture_global_pathRequest";
  }

  static const char* value(const ::client_and_server::capture_global_pathRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
;
  }

  static const char* value(const ::client_and_server::capture_global_pathRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct capture_global_pathRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::client_and_server::capture_global_pathRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::client_and_server::capture_global_pathRequest_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // CLIENT_AND_SERVER_MESSAGE_CAPTURE_GLOBAL_PATHREQUEST_H
