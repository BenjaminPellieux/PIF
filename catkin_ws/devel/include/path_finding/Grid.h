// Generated by gencpp from file path_finding/Grid.msg
// DO NOT EDIT!


#ifndef PATH_FINDING_MESSAGE_GRID_H
#define PATH_FINDING_MESSAGE_GRID_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point.h>

namespace path_finding
{
template <class ContainerAllocator>
struct Grid_
{
  typedef Grid_<ContainerAllocator> Type;

  Grid_()
    : top_left()
    , bottom_right()
    , done(false)
    , unreachable(false)  {
    }
  Grid_(const ContainerAllocator& _alloc)
    : top_left(_alloc)
    , bottom_right(_alloc)
    , done(false)
    , unreachable(false)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _top_left_type;
  _top_left_type top_left;

   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _bottom_right_type;
  _bottom_right_type bottom_right;

   typedef uint8_t _done_type;
  _done_type done;

   typedef uint8_t _unreachable_type;
  _unreachable_type unreachable;





  typedef boost::shared_ptr< ::path_finding::Grid_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::path_finding::Grid_<ContainerAllocator> const> ConstPtr;

}; // struct Grid_

typedef ::path_finding::Grid_<std::allocator<void> > Grid;

typedef boost::shared_ptr< ::path_finding::Grid > GridPtr;
typedef boost::shared_ptr< ::path_finding::Grid const> GridConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::path_finding::Grid_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::path_finding::Grid_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::path_finding::Grid_<ContainerAllocator1> & lhs, const ::path_finding::Grid_<ContainerAllocator2> & rhs)
{
  return lhs.top_left == rhs.top_left &&
    lhs.bottom_right == rhs.bottom_right &&
    lhs.done == rhs.done &&
    lhs.unreachable == rhs.unreachable;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::path_finding::Grid_<ContainerAllocator1> & lhs, const ::path_finding::Grid_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace path_finding

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::path_finding::Grid_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::path_finding::Grid_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::path_finding::Grid_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::path_finding::Grid_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::path_finding::Grid_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::path_finding::Grid_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::path_finding::Grid_<ContainerAllocator> >
{
  static const char* value()
  {
    return "326792e8c45913b0ed6b6b020c9acb4b";
  }

  static const char* value(const ::path_finding::Grid_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x326792e8c45913b0ULL;
  static const uint64_t static_value2 = 0xed6b6b020c9acb4bULL;
};

template<class ContainerAllocator>
struct DataType< ::path_finding::Grid_<ContainerAllocator> >
{
  static const char* value()
  {
    return "path_finding/Grid";
  }

  static const char* value(const ::path_finding::Grid_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::path_finding::Grid_<ContainerAllocator> >
{
  static const char* value()
  {
    return "geometry_msgs/Point top_left\n"
"geometry_msgs/Point bottom_right\n"
"bool done\n"
"bool unreachable\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
;
  }

  static const char* value(const ::path_finding::Grid_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::path_finding::Grid_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.top_left);
      stream.next(m.bottom_right);
      stream.next(m.done);
      stream.next(m.unreachable);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Grid_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::path_finding::Grid_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::path_finding::Grid_<ContainerAllocator>& v)
  {
    s << indent << "top_left: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.top_left);
    s << indent << "bottom_right: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.bottom_right);
    s << indent << "done: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.done);
    s << indent << "unreachable: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.unreachable);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PATH_FINDING_MESSAGE_GRID_H
