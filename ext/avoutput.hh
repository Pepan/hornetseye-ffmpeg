/* HornetsEye - Computer Vision with Ruby
   Copyright (C) 2006, 2007, 2008, 2009, 2010   Jan Wedekind

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */
#ifndef AVOUTPUT_HH
#define AVOUTPUT_HH

#include <boost/shared_ptr.hpp>
extern "C" {
  #include <libswscale/swscale.h>
  #include <libavformat/avformat.h>
}
#undef RSHIFT
#include <ruby.h>
#include "error.hh"
#include "frame.hh"

class AVOutput
{
public:
  AVOutput( const std::string &mrl, int bitrate, 
            int width, int height, int timeBaseNum, int timeBaseDen ) throw (Error);
  virtual ~AVOutput(void);
  void close(void);
  void write( FramePtr frame ) throw (Error);
  static VALUE cRubyClass;
  static VALUE registerRubyClass( VALUE rbModule );
  static void deleteRubyObject( void *ptr );
  static VALUE wrapNew( VALUE rbClass, VALUE rbMRL, VALUE rbBitRate, VALUE rbWidth,
                        VALUE rbHeight, VALUE rbTimeBaseNum, VALUE rbTimeBaseDen );
  static VALUE wrapClose( VALUE rbSelf );
  static VALUE wrapWrite( VALUE rbSelf, VALUE rbFrame );
protected:
  std::string m_mrl;
  AVFormatContext *m_oc;
  AVStream *m_video_st;
  bool m_video_codec_open;
  char *m_video_buf;
  bool m_file_open;
  bool m_header_written;
  struct SwsContext *m_swsContext;
  AVFrame *m_frame;
};

typedef boost::shared_ptr< AVOutput > AVOutputPtr;

#endif
