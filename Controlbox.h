#ifndef _ROS_pesan_pkg_Controlbox_h
#define _ROS_pesan_pkg_Controlbox_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace pesan_pkg
{

  class Controlbox : public ros::Msg
  {
    public:
      typedef uint8_t _key_type;
      _key_type key;
      typedef bool _state_type;
      _state_type state;

    Controlbox():
      key(0),
      state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->key >> (8 * 0)) & 0xFF;
      offset += sizeof(this->key);
      union {
        bool real;
        uint8_t base;
      } u_state;
      u_state.real = this->state;
      *(outbuffer + offset + 0) = (u_state.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      this->key =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->key);
      union {
        bool real;
        uint8_t base;
      } u_state;
      u_state.base = 0;
      u_state.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->state = u_state.real;
      offset += sizeof(this->state);
     return offset;
    }

    virtual const char * getType() override { return "pesan_pkg/Controlbox"; };
    virtual const char * getMD5() override { return "65d31dde61d04b75b47dd567bf1d5917"; };

  };

}
#endif
