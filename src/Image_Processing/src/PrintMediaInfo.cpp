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
  AVFormatContext *formatContext= NULL;

  AVCodec *pCodec = NULL;
  AVCodecParameters *pCodecParameters =  NULL;
  int video_stream_index = -1;

  public:
  Media(int argc, const char *argv[]){
    if (argc < 2) {
      cout << "usage: " << argv[0] << " input_file" << endl;
    }

    formatContext= avformat_alloc_context();
    if (!formatContext)
      cout << "formatContext ERROR" << endl;

    if (avformat_open_input(&formatContext, 
							argv[1], NULL, NULL) != 0)
	  cout << "Can't open file" << endl;

    printf("format: %s,\n duration: %lld us,\n bit_rate %lld\n", 
			formatContext->iformat->name, 
			formatContext->duration, 
			formatContext->bit_rate);

    if (avformat_find_stream_info(formatContext,  NULL) < 0) {
      cout << "ERROR could not get the stream info" << endl;
    }

    for (int i = 0; i < formatContext->nb_streams; i++){
	  AVCodecParameters *pLocalCodecParameters =  NULL;
      pLocalCodecParameters = formatContext->streams[i]->codecpar;
      printf("AVStream->time_base before open coded %d/%d \n", 
        formatContext->streams[i]->time_base.num, 
	    formatContext->streams[i]->time_base.den);

      printf("AVStream->r_frame_rate before open coded %d/%d\n", 	
	    formatContext->streams[i]->r_frame_rate.num, 
		formatContext->streams[i]->r_frame_rate.den);

	  printf("AVStream->start_time %d\n", formatContext->streams[i]->start_time);
      printf("AVStream->duration %d\n", formatContext->streams[i]->duration);

	  AVCodec *pLocalCodec = NULL;
      pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);

	  if (pLocalCodec==NULL) {
        printf("ERROR unsupported codec!");
        continue;
      }

	  if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
        if (video_stream_index == -1) {
          video_stream_index = i;
          pCodec = pLocalCodec;
          pCodecParameters = pLocalCodecParameters;
        }
		printf("Video Codec: resolution %d x %d", 
          pLocalCodecParameters->width, 
	      pLocalCodecParameters->height);
  	  }
	}  
  }
};

int main(int argc, const char *argv[]){
  Media m = Media(argc, argv);
  return 0;
}


  //  } else if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO) {
  //    logging("Audio Codec: %d channels, sample rate %d", pLocalCodecParameters->channels, pLocalCodecParameters->sample_rate);
  //  }

  //  logging("\tCodec %s ID %d bit_rate %lld", pLocalCodec->name, pLocalCodec->id, pLocalCodecParameters->bit_rate);
  //}

  //if (video_stream_index == -1) {
  //  logging("File %s does not contain a video stream!", argv[1]);
  //  return -1;
  //}

  //AVCodecContext *pCodecContext = avcodec_alloc_context3(pCodec);
  //if (!pCodecContext){
  //  logging("failed to allocated memory for AVCodecContext");
  //  return -1;
  //}

  //if (avcodec_parameters_to_context(pCodecContext, pCodecParameters) < 0){
  //  logging("failed to copy codec params to codec context");
  //  return -1;
  //}

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
