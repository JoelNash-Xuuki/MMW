/*Main components
 *
 * Format (Container) - a wrapper, providing sync, metadata and muxing for the streams.
 * Stream - a continuous stream (audio or video) of data over time.
 * Codec - defines how data are enCOded (from Frame to Packet)
 *        and DECoded (from Packet to Frame).
 * Packet - are the data (kind of slices of the stream data) to be decoded as raw frames.
 * Frame - a decoded raw frame (to be encoded or filtered).
 */

//#include <libavcodec/avcodec.h>
extern "C"{
  #include <libavformat/avformat.h>
  #include <stdio.h>
}

#include <iostream>
using namespace std;

class Media{
  private: 
  AVFormatContext *container= NULL;

  AVCodec *codec = NULL;
  AVCodecParameters *codecParameters =  NULL;
  AVCodec *localCodec = NULL;

  AVCodecContext *codecContext; 

  int video_stream_index = -1;
  const char *filename;

  public:
  Media(int argc, const char *argv[]){
    if (argc < 2) {
      cout << "usage: " << argv[0] << " input_file" << endl;
    }
	else
	  filename= argv[1];

    this->containerFormatData();
	this->accessStreamCodec();

    codecContext= avcodec_alloc_context3(codec);
	avcodec_parameters_to_context(codecContext, codecParameters);
	avcodec_open2(codecContext, codec, NULL);

  }

  void containerFormatData(){
    container= avformat_alloc_context();
	avformat_open_input(&container, filename, NULL, NULL);
    printf("format: %s,\n duration: %lld us,\n bit_rate %lld\n", 
			container->iformat->name, 
			container->duration, 
			container->bit_rate);
  }

  void accessStreamCodec(){
    avformat_find_stream_info(container,  NULL);
    for (int i = 0; i < container->nb_streams; i++){

      codecParameters = container->streams[i]->codecpar;
      localCodec= avcodec_find_decoder(codecParameters->codec_id);

      if(codecParameters->codec_type == AVMEDIA_TYPE_VIDEO){
        printf("Video Codec: resolution %d x %d\n", 
        codecParameters->width, 
	    codecParameters->height);
		int video_stream_index= i;
        codec= localCodec;
	  } else if (codecParameters->codec_type== 
        AVMEDIA_TYPE_AUDIO){
	    printf("Audio Codec: %d channels, sample rate %d\n", 
	 	  codecParameters->channels, 
		  codecParameters->sample_rate);
	  }
    }
  }
};

int main(int argc, const char *argv[]){
  Media m = Media(argc, argv);
  return 0;
}


 
  //if (avcodec_open2(pCodecContext, pCodec, NULL) < 0){
  //  logging("failed to open codec through avcodec_open2");
  //  return -1;
  //}

  //AVFrame *pFrame = av_frame_alloc();
  //if (!pFrame){
  //  logging("failed to allocated memory for AVFrame");
  //  return -1;
  //}

  //AVPacket *pPacket = av_packet_alloc();
  //if (!pPacket){
  //  logging("failed to allocated memory for AVPacket");
  //  return -1;
  //}

  //int response = 0;
  //int how_many_packets_to_process = 8;

  //while (av_read_frame(pFormatContext, pPacket) >= 0){
  //  if (pPacket->stream_index == video_stream_index) {
  //  logging("AVPacket->pts %" PRId64, pPacket->pts);
  //    response = decode_packet(pPacket, pCodecContext, pFrame);
  //    if (response < 0)
  //      break;
  //    if (--how_many_packets_to_process <= 0) break;
  //  }
  //  av_packet_unref(pPacket);
  //}

  //logging("releasing all the resources");

  //avformat_close_input(&pFormatContext);
  //av_packet_free(&pPacket);
  //av_frame_free(&pFrame);
  //avcodec_free_context(&pCodecContext);



//
//static int decode_packet(AVPacket *pPacket, AVCodecContext *pCodecContext, AVFrame *pFrame){
//  int response = avcodec_send_packet(pCodecContext, pPacket);
//
//  if (response < 0) {
//    logging("Error while sending a packet to the decoder: %s", av_err2str(response));
//    return response;
//  }
//
//  while (response >= 0){
//    response = avcodec_receive_frame(pCodecContext, pFrame);
//    if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) {
//      break;
//    } else if (response < 0) {
//      logging("Error while receiving a frame from the decoder: %s", av_err2str(response));
//      return response;
//    }
//
//    if (response >= 0) {
//      logging(
//          "Frame %d (type=%c, size=%d bytes, format=%d) pts %d key_frame %d [DTS %d]",
//          pCodecContext->frame_number,
//          av_get_picture_type_char(pFrame->pict_type),
//          pFrame->pkt_size,
//          pFrame->format,
//          pFrame->pts,
//          pFrame->key_frame,
//          pFrame->coded_picture_number
//      );
//
//      char frame_filename[1024];
//      snprintf(frame_filename, sizeof(frame_filename), "%s-%d.pgm", "frame", pCodecContext->frame_number);
//      if (pFrame->format != AV_PIX_FMT_YUV420P){
//        logging("Warning: the generated file may not be a grayscale image, but could e.g. be just the R component if the video format is RGB");
//      }
//      save_gray_frame(pFrame->data[0], pFrame->linesize[0], pFrame->width, pFrame->height, frame_filename);
//    }
//  }
//  return 0;
//}
//
//static void save_gray_frame(unsigned char *buf, int wrap, int xsize, int ysize, char *filename){
//    FILE *f;
//    int i;
//    f = fopen(filename,"w");
//    fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);
//
//    for (i = 0; i < ysize; i++)
//        fwrite(buf + i * wrap, 1, xsize, f);
//    fclose(f);
//}
